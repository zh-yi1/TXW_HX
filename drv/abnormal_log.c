#include "abnormal_log.h"

/* ---- 固定区参数 ---- */
#define BLOCK_SIZE          256U
#define RECORD_SIZE         sizeof(abnormal_record_t)     /* 16B */
#define RECORDS_PER_BLOCK   (BLOCK_SIZE / RECORD_SIZE)    /* 16 */
#define MAX_RECORDS         100U

/* 每类使用 7 个块 (112 条容量, 限 100 条) */
#define AREA_BLOCKS         7U
#define AREA_SIZE           (AREA_BLOCKS * BLOCK_SIZE)    /* 1792B */

/* ---- 基地址 ---- */
#define VOLT_BASE  (FLASH_DATA_BASE + FLASH_OFFS_ABNORMAL_VOLTAGE)
#define TEMP_BASE  (FLASH_DATA_BASE + FLASH_OFFS_ABNORMAL_TEMPERATURE)

/* ---- 异常状态上下文 ---- */
typedef struct {
    /* 当前小时追踪 (RAM) */
    uint32_t hour_start;      /* 当前小时起始 Unix 时间戳 */
    uint16_t worst_value;     /* 当前小时最差值 (mV 或 0.1℃) */
    uint8_t  extra;           /* 电压=cell(0~3), 温度=event_type */
    uint8_t  chg_state;       /* 异常发生时的充放电状态 */
    uint8_t  dirty;           /* 1=本小时有异常, 0=无 */
    /* Flash 写指针 */
    uint32_t write_addr;      /* 下一条记录写入地址 */
    uint8_t  count;           /* 已存总条数 */
} abnormal_ctx_t;

static abnormal_ctx_t g_volt_ctx;   /* 电压异常 */
static abnormal_ctx_t g_temp_ctx;   /* 温度异常 */

/* ---- 内部: 扫描固定区, 恢复写指针和计数 ---- */
static void scan_area(uint32_t base, uint32_t *write_addr, uint8_t *count)
{
    uint32_t newest_addr = base;
    uint32_t newest_ts   = 0;
    uint8_t  n           = 0;
    uint8_t  buf[RECORD_SIZE];

    for (uint16_t offs = 0; offs < AREA_SIZE; offs += RECORD_SIZE) {
        uint32_t addr = base + offs;

        if (flash_read(addr, buf, RECORD_SIZE) != MD_OK)
            break;

        if (buf[0] == 0xFF) {
            uint32_t blk_end = (addr & ~(BLOCK_SIZE - 1)) + BLOCK_SIZE;
            uint32_t area_end = base + AREA_SIZE;
            if (blk_end > area_end) blk_end = area_end;
            if (blk_end <= addr) break;
            offs = blk_end - base - RECORD_SIZE;
            continue;
        }

        if (buf[0] != 0x5A)
            continue;

        n++;

        abnormal_record_t *rec = (abnormal_record_t *)buf;
        if (rec->timestamp >= newest_ts) {
            newest_ts   = rec->timestamp;
            newest_addr = addr;
        }
    }

    /* 防御: 避免重启后 count 超过软件上限导致写永久阻塞 */
    if (n > MAX_RECORDS)
        n = MAX_RECORDS;

    *count = n;

    if (n == 0) {
        *write_addr = base;
    } else {
        uint32_t next = newest_addr + RECORD_SIZE;

        uint32_t block_end = (newest_addr & ~(BLOCK_SIZE - 1)) + BLOCK_SIZE;
        if (next + RECORD_SIZE > block_end)
            next = block_end;

        if (next >= base + AREA_SIZE)
            next = base;

        *write_addr = next;
    }
}

/* ---- 内部: 前进写指针 ---- */
static void advance_write_ptr(uint32_t base, uint32_t *write_addr)
{
    uint32_t next = *write_addr + RECORD_SIZE;

    if ((next & ~(BLOCK_SIZE - 1)) != (*write_addr & ~(BLOCK_SIZE - 1)))
        next = (next & ~(BLOCK_SIZE - 1));

    if (next >= base + AREA_SIZE)
        next = base;

    *write_addr = next;
}

/* ---- 内部: 写一条记录到 Flash ---- */
static uint8_t write_one_record(uint32_t base, uint32_t *write_addr, uint8_t *count,
                                 uint32_t timestamp, uint16_t value,
                                 uint8_t type, uint8_t cell, uint8_t chg_state)
{
    if (*count >= MAX_RECORDS)
        return 0;

    abnormal_record_t rec;
    memset(&rec, 0, sizeof(rec));
    rec.magic     = 0x5A;
    rec.timestamp = timestamp;
    rec.value     = value;
    rec.type      = type;
    rec.cell      = cell;
    rec.chg_state = chg_state;

    /* 目标位置非空则擦除所在块 */
    {
        uint8_t test;
        if (flash_read(*write_addr, &test, 1) == MD_OK && test != 0xFF) {
            flash_page_erase(*write_addr & ~(BLOCK_SIZE - 1));
        }
    }

    if (flash_write(*write_addr, (uint8_t *)&rec, RECORD_SIZE) != MD_OK)
        return 0;

    (*count)++;
    advance_write_ptr(base, write_addr);
    return 1;
}

/* ---- 内部: 读一条 Flash 记录 ---- */
static uint8_t read_record_at(uint32_t base, uint32_t addr, abnormal_record_t *out)
{
    uint8_t buf[RECORD_SIZE];

    if (addr < base || addr >= base + AREA_SIZE)
        return 1;

    if (flash_read(addr, buf, RECORD_SIZE) != MD_OK)
        return 1;

    if (buf[0] != 0x5A)
        return 1;

    memcpy(out, buf, RECORD_SIZE);
    return 0;
}

/* ---- 内部: 按索引读记录 ---- */
static uint8_t read_by_index(uint32_t base, uint32_t write_addr, uint8_t count,
                              uint8_t index, abnormal_record_t *out)
{
    if (index >= count)
        return 1;

    uint8_t found = 0;
    int32_t start_offs = (int32_t)(write_addr - base) - RECORD_SIZE;

    int16_t i;
    for (i = start_offs; i >= 0 && found <= index; i -= RECORD_SIZE) {
        if (read_record_at(base, base + i, out) == 0) {
            if (found == index)
                return 0;
            found++;
        }
    }

    if (found <= index) {
        for (i = AREA_SIZE - RECORD_SIZE; i > start_offs && found <= index; i -= RECORD_SIZE) {
            if (read_record_at(base, base + i, out) == 0) {
                if (found == index)
                    return 0;
                found++;
            }
        }
    }

    return 1;
}

/* ========================================================================
 *  对外接口
 * ======================================================================== */

void abnormal_log_init(void)
{
    scan_area(VOLT_BASE, &g_volt_ctx.write_addr, &g_volt_ctx.count);
    scan_area(TEMP_BASE, &g_temp_ctx.write_addr, &g_temp_ctx.count);

    g_volt_ctx.hour_start  = 0;
    g_volt_ctx.worst_value = 0;
    g_volt_ctx.extra  = 0;
    g_volt_ctx.dirty       = 0;

    g_temp_ctx.hour_start  = 0;
    g_temp_ctx.worst_value = 0;
    g_temp_ctx.extra  = ABNORMAL_EVT_NONE;
    g_temp_ctx.dirty       = 0;
}

#if FACTORY_RESET_EN
/*
 * abnormal_log_reset — 恢复出厂设置: 擦除全部异常记录 Flash 区并复位 RAM 状态
 *
 * V1.3 新增: 场测串口下发恢复出厂设置时调用,
 * 擦除电压异常区 (7 块) 和温度异常区 (7 块) 的全部数据,
 * 同时复位 RAM 中的小时追踪和写指针.
 */
void abnormal_log_reset(void)
{
    uint8_t i;

    /* 擦除电压异常区 (7 × 256B) */
    for (i = 0; i < AREA_BLOCKS; i++) {
        flash_page_erase(VOLT_BASE + (uint32_t)i * BLOCK_SIZE);
    }

    /* 擦除温度异常区 (7 × 256B) */
    for (i = 0; i < AREA_BLOCKS; i++) {
        flash_page_erase(TEMP_BASE + (uint32_t)i * BLOCK_SIZE);
    }

    /* 复位电压异常 RAM 上下文 */
    g_volt_ctx.hour_start  = 0;
    g_volt_ctx.worst_value = 0;
    g_volt_ctx.extra       = 0;
    g_volt_ctx.dirty       = 0;
    g_volt_ctx.write_addr  = VOLT_BASE;
    g_volt_ctx.count       = 0;

    /* 复位温度异常 RAM 上下文 */
    g_temp_ctx.hour_start  = 0;
    g_temp_ctx.worst_value = 0;
    g_temp_ctx.extra       = ABNORMAL_EVT_NONE;
    g_temp_ctx.dirty       = 0;
    g_temp_ctx.write_addr  = TEMP_BASE;
    g_temp_ctx.count       = 0;
}
#endif /* FACTORY_RESET_EN */

/* ---- 电压异常 ---- */

void abnormal_log_voltage_update(uint32_t hour_start, uint16_t value_mv,
                                  uint8_t cell, uint8_t chg_state)
{
    if (hour_start != g_volt_ctx.hour_start) {
        g_volt_ctx.hour_start  = hour_start;
        g_volt_ctx.worst_value = value_mv;
        g_volt_ctx.extra  = cell;
        g_volt_ctx.chg_state   = chg_state;
        g_volt_ctx.dirty       = 1;
    } else if (value_mv > g_volt_ctx.worst_value) {
        g_volt_ctx.worst_value = value_mv;
        g_volt_ctx.extra  = cell;
        g_volt_ctx.chg_state   = chg_state;
        g_volt_ctx.dirty       = 1;
    }
}

void abnormal_log_voltage_update_force(uint32_t hour_start, uint16_t value_mv,
                                       uint8_t cell, uint8_t chg_state)
{
    g_volt_ctx.hour_start  = hour_start;
    g_volt_ctx.worst_value = value_mv;
    g_volt_ctx.extra       = cell;
    g_volt_ctx.chg_state   = chg_state;
    g_volt_ctx.dirty       = 1;
}

uint8_t abnormal_log_voltage_commit(uint32_t timestamp)
{
    if (!g_volt_ctx.dirty)
        return 0;

    if (!write_one_record(VOLT_BASE, &g_volt_ctx.write_addr, &g_volt_ctx.count,
                           timestamp, g_volt_ctx.worst_value,
                           ABNORMAL_EVT_OV_PROT, g_volt_ctx.extra,
                           g_volt_ctx.chg_state))
        return 0;

    g_volt_ctx.dirty       = 0;
    g_volt_ctx.worst_value = 0;
    g_volt_ctx.hour_start  = 0;
    return 1;
}

uint8_t abnormal_log_voltage_read(uint8_t index, abnormal_record_t *out)
{
    if (out == NULL)
        return 1;
    return read_by_index(VOLT_BASE, g_volt_ctx.write_addr, g_volt_ctx.count, index, out);
}

uint8_t abnormal_log_voltage_count(void)
{
    return g_volt_ctx.count;
}

/* ---- 温度异常 ---- */

void abnormal_log_temperature_update(uint32_t hour_start, uint16_t value_01c,
                                      uint8_t type, uint8_t chg_state)
{
    if (hour_start != g_temp_ctx.hour_start) {
        g_temp_ctx.hour_start  = hour_start;
        g_temp_ctx.worst_value = value_01c;
        g_temp_ctx.extra  = type;
        g_temp_ctx.chg_state   = chg_state;
        g_temp_ctx.dirty       = 1;
    } else if (value_01c > g_temp_ctx.worst_value) {
        g_temp_ctx.worst_value = value_01c;
        g_temp_ctx.extra  = type;
        g_temp_ctx.chg_state   = chg_state;
        g_temp_ctx.dirty       = 1;
    }
}

void abnormal_log_temperature_update_force(uint32_t hour_start, uint16_t value_01c,
                                      uint8_t type, uint8_t chg_state)
{
    g_temp_ctx.hour_start  = hour_start;
    g_temp_ctx.worst_value = value_01c;
    g_temp_ctx.extra  = type;
    g_temp_ctx.chg_state   = chg_state;
    g_temp_ctx.dirty       = 1;
}

uint8_t abnormal_log_temperature_commit(uint32_t timestamp)
{
    if (!g_temp_ctx.dirty)
        return 0;

    if (!write_one_record(TEMP_BASE, &g_temp_ctx.write_addr, &g_temp_ctx.count,
                           timestamp, g_temp_ctx.worst_value,
                           g_temp_ctx.extra, 0xFF, g_temp_ctx.chg_state))
        return 0;

    g_temp_ctx.dirty       = 0;
    g_temp_ctx.worst_value = 0;
    g_temp_ctx.hour_start  = 0;
    return 1;
}

uint8_t abnormal_log_temperature_read(uint8_t index, abnormal_record_t *out)
{
    if (out == NULL)
        return 1;
    return read_by_index(TEMP_BASE, g_temp_ctx.write_addr, g_temp_ctx.count, index, out);
}

uint8_t abnormal_log_temperature_count(void)
{
    return g_temp_ctx.count;
}
