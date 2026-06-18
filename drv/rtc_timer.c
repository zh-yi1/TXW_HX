#include "rtc_timer.h"

/* ---- 内部状态 ---- */
static uint32_t g_start_timestamp;     /* 起始 Unix 时间戳 */
static uint32_t g_running_seconds;     /* 累计运行秒数 */
static uint32_t g_saved_addr;          /* 当前写入地址 (绝对) */

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

/* CRC-8: X^8 + X^2 + X + 1 (同 CW1573) */
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
    flash_sector_erase(ts_block_addrs[next]);
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

    /* magic != 0x55 → 上位机尚未写入配置 */
    if (cfg.magic != 0x55) {
        g_running_seconds = 0;
        g_ts_block_idx    = 0;
        g_saved_addr      = ts_block_addrs[0];
        return;
    }

    g_start_timestamp = cfg.start_timestamp;
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

    if (cfg.magic != 0x55)
        return;

    /* start_timestamp 没变且已同步 → 无需重复初始化 */
    if (g_time_synced && cfg.start_timestamp == g_start_timestamp)
        return;

    /* start_timestamp 变了 → 擦除旧时间戳块，避免重启后恢复出混合时间 */
    if (g_time_synced) {
        flash_sector_erase(ts_block_addrs[0]);
        flash_wait_unbusy();
        flash_sector_erase(ts_block_addrs[1]);
        flash_wait_unbusy();
        flash_sector_erase(ts_block_addrs[2]);
        flash_wait_unbusy();
    }

    g_start_timestamp    = cfg.start_timestamp;
    g_running_seconds    = 0;
    g_last_second_tick   = md_get_tick();
    g_ts_block_idx       = 0;
    g_saved_addr         = ts_block_addrs[0];
    g_time_synced        = 1;
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

        usart_send_string(time_str);
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

#if FACTORY_RESET_EN
/*
 * rtc_reset_running_time — 恢复出厂设置: 清零运行时间并擦除 Flash 存盘点
 *
 * V1.3 新增: 场测串口下发恢复出厂设置时调用,
 * 清零 RAM 中的累计运行秒数并擦除全部时间戳块,
 * 确保掉电重启后不会从 Flash 恢复出旧值.
 */
void rtc_reset_running_time(void)
{
    /* 清零 RAM 运行时间 */
    g_running_seconds  = 0;
    g_last_second_tick = md_get_tick();

    /* 擦除全部时间戳块, 防止重启后 scan 恢复 */
    flash_sector_erase(ts_block_addrs[0]);
    flash_wait_unbusy();
    flash_sector_erase(ts_block_addrs[1]);
    flash_wait_unbusy();
    flash_sector_erase(ts_block_addrs[2]);
    flash_wait_unbusy();

    /* 复位写指针到块 0 起始 */
    g_ts_block_idx = 0;
    g_saved_addr   = ts_block_addrs[0];
}
#endif /* FACTORY_RESET_EN */

uint8_t rtc_is_synced(void)
{
    return g_time_synced;
}

/* ---- 生产配置读写 ---- */

void factory_cfg_read(factory_cfg_t *cfg)
{
    uint32_t addr = FLASH_DATA_BASE + FLASH_OFFS_FACTORY_CFG;

    if (cfg == NULL) return;

    flash_read(addr, (uint8_t *)cfg, sizeof(factory_cfg_t));
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

    flash_sector_erase(addr);
    flash_wait_unbusy();
    flash_write(addr, (uint8_t *)&local, sizeof(factory_cfg_t));
    flash_wait_unbusy();
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
