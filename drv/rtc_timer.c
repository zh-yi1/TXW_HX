#include "rtc_timer.h"

/* ---- LSI 时基漂移校准 ----
 * IWDT 用 ES32F0100 的内部低速 RC (LSI, 标称 ±5%) 作为时钟源,
 * 真实 IWDG 周期可能比标称偏快或偏慢. 由于本设备无外部时基,
 * 无法在线测量, 此处提供两个可调静态补偿:
 *
 *   RTC_LSI_BOOST_MS  — LSI 偏慢时用, 每周期额外累加 N 毫秒 (正值)
 *   RTC_LSI_TRIM_SEC  — LSI 偏快时用, 每周期从补偿秒数中扣除 N 秒
 *
 * 调参方法: 观察长时间 STOP 循环后设备时间相对真实时间的累积漂移.
 *   偏慢 X 秒 / N 周期 -> 设置 RTC_LSI_BOOST_MS ≈ (X * 1000) / N
 *   偏快 X 秒 / N 周期 -> 设置 RTC_LSI_TRIM_SEC ≈ X / N
 *
 * 实测样机: 120s 周期, 每小时快 ~120s (30 周期),
 *   RTC_LSI_TRIM_SEC = 4 (每周期扣 4s, 30×4=120s 校正).
 */
#ifndef RTC_LSI_BOOST_MS
#define RTC_LSI_BOOST_MS   0U
#endif

#ifndef RTC_LSI_TRIM_SEC
#define RTC_LSI_TRIM_SEC   4U    /* 每周期扣除秒数, 补偿 LSI 偏快: 1h快120s / 30周期 = 4s/周期 */
#endif

/* ---- 内部状态 ---- */
static uint32_t g_start_timestamp;     /* 起始 Unix 时间戳 */
static uint32_t g_running_seconds;     /* 累计运行秒数 */
static uint32_t g_saved_addr;          /* 当前写入地址 (绝对) */
static uint32_t g_dis_start_ts;        /* 显示的运行时间起始点 (Flash dis_start_ts 的 RAM 镜像) */

static uint8_t  g_time_synced;         /* 是否已时间同步 */
static uint32_t g_last_second_tick;    /* 上次秒数更新时刻 */

/* 当前使用的时间戳块索引 (0/1/2) */
static uint8_t  g_ts_block_idx;

/* 时间戳区各块绝对地址 */
static const uint32_t ts_block_addrs[] = {
    FLASH_DATA_BASE + FLASH_OFFS_TIMESTAMP_BLOCK0,
    FLASH_DATA_BASE + FLASH_OFFS_TIMESTAMP_BLOCK1,
    FLASH_DATA_BASE + FLASH_OFFS_TIMESTAMP_BLOCK2,
};
#define TS_BLOCK_SIZE       256U
#define TS_ENTRY_SIZE       sizeof(timestamp_entry_t)  /* 7B */
#define TS_ENTRIES_PER_BLOCK (TS_BLOCK_SIZE / TS_ENTRY_SIZE)  /* 36 */

/* CRC-8: X^8 + X^2 + X + 1 */
#define RTC_CRC8_POLY  0x07U

/* ---- 内部函数 ---- */
static uint8_t crc8_update(uint8_t crc, uint8_t data)
{
    crc ^= data;
    for (uint8_t i = 0; i < 8; i++) {
        if (crc & 0x80)
            crc = (uint8_t)((crc << 1) ^ RTC_CRC8_POLY);
        else
            crc <<= 1;
    }
    return crc;
}

static uint8_t entry_crc8(const timestamp_entry_t *e)
{
    const uint8_t *p = (const uint8_t *)e;
    uint8_t crc = 0;
    for (uint8_t i = 0; i < TS_ENTRY_SIZE - 1; i++) {
        crc = crc8_update(crc, p[i]);
    }
    return crc;
}


//TODO :可优化，先读三区第一个时间戳确定是那个区的
/* 找时间戳区最后一条有效记录 */
static uint32_t scan_all_ts_blocks(void)
{
    uint32_t best_seconds = 0;
    uint32_t best_addr    = 0;
    uint8_t  best_block   = 0;

    for (uint8_t i = 0; i < sizeof(ts_block_addrs) / sizeof(ts_block_addrs[0]); i++) {
        timestamp_entry_t entry;
        uint32_t last_addr = 0;
        uint32_t s = 0;

        for (uint16_t offs = 0; offs < TS_BLOCK_SIZE; offs += TS_ENTRY_SIZE) {
            uint8_t head[2];
            if (flash_read(ts_block_addrs[i] + offs, head, 2) != MD_OK)
                break;
            if (head[0] == 0xFF && head[1] == 0xFF)
                break;
            if (head[0] != 0xAA || head[1] != 0x55)
                continue;

            if (flash_read(ts_block_addrs[i] + offs, (uint8_t *)&entry, TS_ENTRY_SIZE) != MD_OK)
                break;

            if (entry.crc8 != entry_crc8(&entry))
                continue;

            s = entry.running_seconds;
            last_addr = ts_block_addrs[i] + offs;
        }

        if (s > best_seconds) {
            best_seconds = s;
            best_addr    = last_addr;
            best_block   = i;
        }
    }

    g_ts_block_idx = best_block;
    g_saved_addr   = best_addr;
    return best_seconds;
}

/* 写一条时间戳记录到指定地址 */
static uint8_t write_ts_entry(uint32_t addr, const timestamp_entry_t *entry)
{
    return (flash_write(addr, (uint8_t *)entry, TS_ENTRY_SIZE) == MD_OK) ? 0 : 1;
}

/* 擦除下一块并切换到新块 */
static void move_to_next_block(void)
{
    uint8_t next = (g_ts_block_idx + 1) %
                   (sizeof(ts_block_addrs) / sizeof(ts_block_addrs[0]));

    /* 先擦除下一块 */
    flash_page_erase(ts_block_addrs[next]);
    flash_wait_unbusy();

    g_ts_block_idx = next;
    g_saved_addr   = ts_block_addrs[next];
}

/* ---- 对外函数 ---- */

void rtc_timer_init(void)
{
    g_time_synced = 0;

    /* 读生产配置，获取起始时间戳 */
    factory_cfg_t cfg = {0};
    factory_cfg_read(&cfg);

    /* magic != 0x55 → 首次开机, 给默认初始时间 2026-07-11 12:00:00 */
    if (!factory_cfg_is_valid(&cfg)) {
        g_running_seconds   = 0;
        g_ts_block_idx      = 0;
        g_saved_addr        = ts_block_addrs[0];
        g_start_timestamp   = 1783771200UL;  /* 2026-07-11 12:00:00 */
        g_dis_start_ts = g_start_timestamp;
        g_last_second_tick  = md_get_tick();
        g_time_synced       = 1;
        /* 首次开机: 将默认时间和运行起始时间写入 Flash, 防止重启后重置 */
        cfg.start_timestamp      = g_start_timestamp;
        cfg.dis_start_ts  = g_dis_start_ts;
        cfg.cell_count = 4;
        cfg.disable_reason = 0;
        factory_cfg_write(&cfg);
        return;
    }

    g_start_timestamp = cfg.start_timestamp;
    g_dis_start_ts = cfg.dis_start_ts;
    g_time_synced = 1;

    /* 扫描 Flash 恢复运行秒数 */
    g_running_seconds = scan_all_ts_blocks();

    /* 没有保存过，从 0 开始 */
    if (g_running_seconds == 0 && g_saved_addr == 0) {
        g_ts_block_idx = 0;
        g_saved_addr   = ts_block_addrs[0];
    }
    /* 计算下一个写入位置 (当前最后位置 + 条目大小) */
    else if (g_saved_addr > 0) {
        uint32_t block_start = ts_block_addrs[g_ts_block_idx];
        uint32_t offs = g_saved_addr - block_start + TS_ENTRY_SIZE;

        /* 如果当前块写满了，移到下一块 */
        if (offs + TS_ENTRY_SIZE > TS_BLOCK_SIZE) {
            move_to_next_block();
        } else {
            g_saved_addr += TS_ENTRY_SIZE;
        }
    }

}

/*
 * rtc_timer_reinit — 生产工具串口写入配置后调用，重新读取并同步时间
 *
 * 场景: boot 时 magic != 0x55, 主循环持续运行但未同步；
 *       生产工具通过串口写入 factory_cfg 后调用此函数激活计时。
 */
void rtc_timer_reinit(void)
{
    factory_cfg_t cfg = {0};

    factory_cfg_read(&cfg);

    if (!factory_cfg_is_valid(&cfg))
        return;

    /* 擦除旧时间戳块，避免重启后恢复出混合时间 */
    if (g_time_synced) {
        flash_page_erase(ts_block_addrs[0]);
        flash_wait_unbusy();
        flash_page_erase(ts_block_addrs[1]);
        flash_wait_unbusy();
        flash_page_erase(ts_block_addrs[2]);
        flash_wait_unbusy();
    }

    g_start_timestamp    = cfg.start_timestamp;
    g_running_seconds    = 0;
    g_last_second_tick   = md_get_tick();
    g_ts_block_idx       = 0;
    g_saved_addr         = ts_block_addrs[0];
    g_time_synced        = 1;
    g_dis_start_ts = cfg.dis_start_ts;
}

void rtc_timer_proc(void)
{
    static uint32_t last_save_seconds = 0;
#ifdef RTC_TIME_PRINT_EN
    static uint32_t last_print_seconds = 0;
#endif
    uint32_t now = md_get_tick();

    if (!g_time_synced)
        return;

    /* 按实际经过的整秒数累加，保留余数避免累积误差 */
    if (now - g_last_second_tick >= 1000) {
        uint32_t elapsed = now - g_last_second_tick;
        uint32_t seconds = elapsed / 1000;
        g_running_seconds += seconds;
        g_last_second_tick += seconds * 1000;
    }

#ifdef RTC_TIME_PRINT_EN
    /* 每 5 秒通过串口发送一次当前时间, 格式: 2026-06-18-14-03-10 */
    if (g_running_seconds - last_print_seconds >= 5) {
        uint32_t ts = g_start_timestamp + g_running_seconds;
        uint16_t y;
        uint8_t mo, d, h, mi, s;
        char time_str[20];  /* "YYYY-MM-DD-HH-MM-SS\0" = 19+1 */

        rtc_unix_to_datetime(ts, &y, &mo, &d, &h, &mi, &s);

        /* 手动格式化, 避免引入 sprintf (节省 SRAM) */
        time_str[0]  = (char)('0' + y / 1000);
        time_str[1]  = (char)('0' + (y / 100) % 10);
        time_str[2]  = (char)('0' + (y / 10) % 10);
        time_str[3]  = (char)('0' + y % 10);
        time_str[4]  = '-';
        time_str[5]  = (char)('0' + mo / 10);
        time_str[6]  = (char)('0' + mo % 10);
        time_str[7]  = '-';
        time_str[8]  = (char)('0' + d / 10);
        time_str[9]  = (char)('0' + d % 10);
        time_str[10] = ' ';
        time_str[11] = (char)('0' + h / 10);
        time_str[12] = (char)('0' + h % 10);
        time_str[13] = ':';
        time_str[14] = (char)('0' + mi / 10);
        time_str[15] = (char)('0' + mi % 10);
        time_str[16] = ':';
        time_str[17] = (char)('0' + s / 10);
        time_str[18] = (char)('0' + s % 10);
        time_str[19] = '\0';

        LOGI("%s\r\n", time_str);
        last_print_seconds = g_running_seconds;
    }
#endif /* RTC_TIME_PRINT_EN */

    /* 每 120 秒写一次 Flash 同步时间 (约 2 分钟) */

    if (g_running_seconds - last_save_seconds >= 120) {
        rtc_save_checkpoint();
        last_save_seconds = g_running_seconds;
    }
}

uint32_t rtc_get_timestamp(void)
{
    if (!g_time_synced || g_start_timestamp == 0)
        return 0;
    return g_start_timestamp + g_running_seconds;
}

void rtc_save_checkpoint(void)
{
    timestamp_entry_t entry;

    if (!g_time_synced)
        return;

    /* 检查当前块是否还有空间 */
    uint32_t block_start = ts_block_addrs[g_ts_block_idx];
    uint32_t offs = g_saved_addr - block_start;

    if (offs + TS_ENTRY_SIZE > TS_BLOCK_SIZE) {
        move_to_next_block();
    }

    /* 构造条目 */
    entry.magic_h = 0xAA;
    entry.magic_l = 0x55;
    entry.running_seconds = g_running_seconds;
    entry.crc8 = entry_crc8(&entry);

    /* 写入 */
    if (write_ts_entry(g_saved_addr, &entry) == 0) {
        flash_wait_unbusy();
        g_saved_addr += TS_ENTRY_SIZE;
    }
}


uint8_t rtc_is_synced(void)
{
    return g_time_synced;
}

/*
 * rtc_get_dis_seconds — 获取运行时间 (秒)
 */
uint32_t rtc_get_dis_seconds(void)
{
    uint32_t now_ts;

    now_ts = g_start_timestamp + g_running_seconds;
    if (now_ts >= g_dis_start_ts)
        return now_ts - g_dis_start_ts;
    return 0;
}

/*
 * rtc_reset_running_time_on_event — 充电完成/场测同步时复位运行时间起始点
 *
 * 将当前绝对时间写入 Flash dis_start_ts, 运行时间自然归零.
 * 外部调用场景:
 *   - i2c_slave.c: 检测到 is_charge 1→0 (充电完成)
 */
void rtc_reset_running_time_on_event(void)
{
    uint32_t now_ts;
    factory_cfg_t cfg;

    now_ts = g_start_timestamp + g_running_seconds;

    /* 读-改-写 factory_cfg: 仅更新 dis_start_ts */
    factory_cfg_read(&cfg);
    if (!factory_cfg_is_valid(&cfg))
        return;

    cfg.dis_start_ts = now_ts;
    factory_cfg_write(&cfg);

    g_dis_start_ts = now_ts;
}

/* ---- 生产配置读写 ---- */

void factory_cfg_read(factory_cfg_t *cfg)
{
    uint32_t addr = FLASH_DATA_BASE + FLASH_OFFS_FACTORY_CFG;

    if (cfg == NULL) return;

    flash_read(addr, (uint8_t *)cfg, sizeof(factory_cfg_t));
}

/*
 * factory_cfg_is_valid — 校验 magic + CRC8
 *
 * 仅 magic==0x55 不足以保证数据完整:
 * Flash 写入被中断 (掉电/复位) 时 magic 可能已写入但其余字段是垃圾值,
 * 此时 disable_reason 等字段不可信, 必须通过 CRC 二次确认.
 */
uint8_t factory_cfg_is_valid(const factory_cfg_t *cfg)
{
    const uint8_t *p;
    uint8_t crc;
    uint8_t i;

    if (cfg == NULL)
        return 0;

    if (cfg->magic != 0x55)
        return 0;

    /* CRC8 覆盖 crc8 字段之前的所有字节 */
    p   = (const uint8_t *)cfg;
    crc = 0;
    for (i = 0; i < sizeof(factory_cfg_t) - 1; i++) {
        crc = crc8_update(crc, p[i]);
    }

    return (crc == cfg->crc8) ? 1 : 0;
}

void factory_cfg_write(const factory_cfg_t *cfg)
{
    uint32_t addr = FLASH_DATA_BASE + FLASH_OFFS_FACTORY_CFG;
    factory_cfg_t local;

    if (cfg == NULL) return;

    /* 强制写入 magic 标记，避免调用者遗漏 */
    local = *cfg;
    local.magic = 0x55;

    /* 计算 CRC8：覆盖 crc8 字段之前的所有字节 */
    {
        const uint8_t *p = (const uint8_t *)&local;
        uint8_t crc = 0;
        for (uint8_t i = 0; i < sizeof(factory_cfg_t) - 1; i++) {
            crc = crc8_update(crc, p[i]);
        }
        local.crc8 = crc;
    }

    flash_page_erase(addr);
    flash_wait_unbusy();
    flash_write(addr, (uint8_t *)&local, sizeof(factory_cfg_t));
    flash_wait_unbusy();
}

/*
 * factory_cfg_write_soh — 读-改-写 SOH (电池健康度)
 */
void factory_cfg_write_soh(uint8_t soh)
{
    factory_cfg_t cfg;

    factory_cfg_read(&cfg);
    if (!factory_cfg_is_valid(&cfg))
        return; /* 未写入过配置, 不单独写 SOH */

    cfg.soh = soh;
    factory_cfg_write(&cfg);
}

/*
 * factory_cfg_write_cycle — 读-改-写 循环次数
 */
void factory_cfg_write_cycle(uint16_t cycle_count)
{
    factory_cfg_t cfg;

    factory_cfg_read(&cfg);
    if (!factory_cfg_is_valid(&cfg))
        return; /* 未写入过配置, 不单独写循环次数 */

    cfg.cycle_count = cycle_count;
    factory_cfg_write(&cfg);
}

/* ========================================================================== */
/*  时间转换                                                                   */
/* ========================================================================== */

static uint8_t rtc_bcd_to_byte(uint8_t bcd)
{
    return ((bcd >> 4) & 0x0F) * 10 + (bcd & 0x0F);
}

static uint8_t rtc_is_leap(uint16_t y)
{
    return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) ? 1 : 0;
}

static const uint8_t rtc_dim[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/*
 * rtc_bcd6_to_unix — 6B BCD (YY MM DD HH MM SS, 年偏移 2000) → Unix 时间戳
 */
uint32_t rtc_bcd6_to_unix(const uint8_t bcd[6])
{
    uint16_t year  = 2000 + rtc_bcd_to_byte(bcd[0]);
    uint8_t  month = rtc_bcd_to_byte(bcd[1]);
    uint8_t  day   = rtc_bcd_to_byte(bcd[2]);
    uint8_t  hour  = rtc_bcd_to_byte(bcd[3]);
    uint8_t  min   = rtc_bcd_to_byte(bcd[4]);
    uint8_t  sec   = rtc_bcd_to_byte(bcd[5]);
    uint32_t days  = 0;
    uint16_t y;
    uint8_t  m;

    for (y = 1970; y < year; y++)
        days += rtc_is_leap(y) ? 366 : 365;

    for (m = 1; m < month; m++) {
        days += rtc_dim[m - 1];
        if (m == 2 && rtc_is_leap(year)) days++;
    }
    days += (uint32_t)(day - 1);

    return days * 86400UL + (uint32_t)hour * 3600UL
           + (uint32_t)min * 60UL + sec;
}

/*
 * rtc_unix_to_datetime — Unix 时间戳 → 年/月/日/时/分/秒
 */
void rtc_unix_to_datetime(uint32_t ts, uint16_t *year, uint8_t *month,
                          uint8_t *day, uint8_t *hour, uint8_t *min, uint8_t *sec)
{
    uint32_t s = ts;
    uint16_t y;
    uint8_t  m;

    for (y = 1970; ; y++) {
        uint16_t diy = rtc_is_leap(y) ? 366 : 365;
        if (s < diy * 86400UL) break;
        s -= diy * 86400UL;
    }
    *year = y;

    for (m = 1; m <= 12; m++) {
        uint8_t dim = rtc_dim[m - 1];
        if (m == 2 && rtc_is_leap(y)) dim = 29;
        if (s < (uint32_t)dim * 86400UL) break;
        s -= (uint32_t)dim * 86400UL;
    }
    *month = m;
    *day   = (uint8_t)(s / 86400UL) + 1;
    s     %= 86400UL;
    *hour  = (uint8_t)(s / 3600UL);
    s     %= 3600UL;
    *min   = (uint8_t)(s / 60UL);
    *sec   = (uint8_t)(s % 60UL);
}

/* STOP 唤醒后补偿丢失的时间.
   每个 STOP 周期实际耗时 = IWDG睡眠N秒 + ~600ms awake工作 (NTC读取/存盘等).
   原实现只补 N 秒, 并把 awake 期间 SysTick 走过的进度丢弃, 导致每周期慢
   ~0.6s. 这里把上次补偿以来的 tick 增量 (即上一周期的 awake 毫秒数) 一并
   累计: 整秒加进 g_running_seconds, 余数部分用 g_last_second_tick 回拨
   的方式携带, 既不丢精度也不会被 rtc_timer_proc 二次累加.

   另外: IWDG 用 LSI 作时钟源 (ES32F0100 内部低速 RC, 标称 ±5%), 真实 IWDG
   周期可能比标称偏慢 0.1%~0.5%. 这部分时基漂移在芯片内部无法在线测量, 故
   用静态 RTC_LSI_BOOST_MS 每周期累加 compensate, 等效提高 extra_sec 平均
   频率. 调参见文件顶部 RTC_LSI_BOOST_MS 注释. */
void rtc_timer_compensate_stop(uint32_t seconds)
{
    if (!g_time_synced || seconds == 0)
        return;

    uint32_t now       = md_get_tick();
    uint32_t awake_ms  = now - g_last_second_tick;   /* 上一周期 awake 期间 tick 走过的毫秒 */

    /* 把静态 LSI 漂移补偿加进累计:
       RTC_LSI_BOOST_MS  — LSI 偏慢时加毫秒 (ms 级微调)
       RTC_LSI_TRIM_SEC  — LSI 偏快时扣秒数 (秒级粗调, 作用于 seconds).
       两者配合: Boost 在 total_ms 层补偿 sub-second 偏差,
       Trim  在 seconds 层补偿整秒偏差 (IWDG 实际周期 < 配置值).
       均加 saturate 防下溢. */
    uint32_t total_ms = awake_ms + RTC_LSI_BOOST_MS;

    uint32_t extra_sec = total_ms / 1000U;
    uint32_t remainder = total_ms % 1000U;

    /* IWDG 偏快 → 实际睡眠 < seconds, 用 trim 扣减校正 */
    uint32_t sum_sec = seconds + extra_sec;
    if (sum_sec > RTC_LSI_TRIM_SEC)
        sum_sec -= RTC_LSI_TRIM_SEC;
    else
        sum_sec = 0;

    g_running_seconds += sum_sec;

    /* 回拨到 now - remainder, 让余数 ms 平滑累计到下一周期;
       仍保证 g_last_second_tick <= now, 不会触发 rtc_timer_proc 下溢.
       注意: 若 RTC_LSI_BOOST_MS > (now - 0), remainder 可能 > now,
       会触发 uint32 下溢. 限制 Boost 远小于典型 now (开机后秒级 tick),
       这里加 saturate 保护避免极端边界. */
    if (remainder > now)
        g_last_second_tick = 0;
    else
        g_last_second_tick = now - remainder;
}
