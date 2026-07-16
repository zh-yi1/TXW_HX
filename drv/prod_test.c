/**********************************************************************************
 *
 * @file    prod_test.c
 * @brief   产测模块 — USART1 帧协议 + 数据上报 (按名词解释顺序)
 *
 *          pt_data 结构体 1:1 对应名词解释全部字段。
 *          当前用测试数据填充, 后续接入真实传感器/I2C/Flash 数据。
 *
 **********************************************************************************
 */

#include "prod_test.h"

#if !defined(PROD_TEST_SIMPLE_EN) && !defined(DEBUG_EN)

/* ========================================================================== */
/*  模块级全局变量                                                           */
/* ========================================================================== */

static prod_test_rt_t pt_rt;         /* 运行时状态 */
static prod_test_data_t pt_data;     /* 名词解释全部数据*/
static uint32_t s_pt_enter_tick = 0; /* 进入场测时刻 (tick), 用于 3min 低功耗屏蔽 */
static volatile uint8_t s_pt_unlock_flag = 0; /* 解锁标志: i2c_slave_proc 消费后清除 */

#define PT_PUTC(c) usart_send_byte((uint8_t)(c))
#define PT_PUTS(s) usart_send_string(s)

/* ---- 帧解析器 ---- */
static frame_parse_state_t frame_state = FRAME_WAIT_AA; /* 解析状态机当前状态 */
static uint8_t frame_buf[PT_FRAME_MAX_PARAMS + 4];      /* 帧缓冲区: 包头(2)+长度(1)+CMD(1)+参数(N) */
static uint8_t frame_idx;                               /* 帧缓冲区写入位置 */
static uint8_t frame_len;                               /* 帧总长度 (不含校验和), 由 LEN 字段决定 */
static uint8_t frame_cmd;                               /* 命令 ID, 由 CMD 字段决定 */
static uint8_t frame_param_cnt;                         /* 参数个数 = frame_len - 4 */

/* ---- 前向声明 ---- */
static void pt_report_all(void);

/* ========================================================================== */
/*  数据初始化 — Flash 静态值 + 硬件实时值                                      */
/* ========================================================================== */
static void pt_fill_test_values(void)
{
    /* 加密签名 (解锁时由上位机下发填充) */
    memset(pt_data.unlock_sign, 0, PT_UNLOCK_KEY_LEN);

    /* SN / BAT_SN — 默认空值, pt_load_factory_cfg() 会从 Flash 覆盖 */
    memset(pt_data.sn, '0', PT_SN_LEN);
    pt_data.sn[PT_SN_LEN] = '\0';
    memset(pt_data.bat_sn, 0, PT_BAT_SN_LEN + 1);

    /* 实时数据 — 从 ui_data 采集 */
    pt_data.vbat_mv = (uint16_t)ui_data.bat_voltage * 100; /* 0.1V → mV */
    pt_data.soc = ui_data.bat_power;                       /* % */
    pt_data.temp = ui_data.bat_temperature / 10;           /* 0.1°C → °C */

    /* VER — 编译期常量, 由 main.h VERSION_MAJOR / VERSION_MINOR 决定 */
    pt_data.ver_major = VERSION_MAJOR;
    pt_data.ver_minor = VERSION_MINOR;

    /* 异常日志总条数 */
    pt_data.err_cnt = ui_data.abnormal_volt_count + ui_data.abnormal_temp_count;

    /* 当前时间 (Unix 时间戳) */
    pt_data.time_now = rtc_get_timestamp();
}

/*
 * pt_load_factory_cfg — 从 Flash 回读 factory_cfg, 覆盖 pt_data 中对应字段
 *
 * 在 pt_fill_test_values 之后调用, 若 Flash 中已有有效配置则用保存值替换默认值.
 * 这样重启后进入厂测模式, pt_report_all() 报的就是上次写入的值.
 */
static void pt_load_factory_cfg(void)
{
    factory_cfg_t cfg;
    uint8_t i, pos;

    factory_cfg_read(&cfg);
    if (!factory_cfg_is_valid(&cfg))
        return; /* 未写过, 保留测试默认值 */

    /* SN: ASCII 字符串直接回读 */
    {
        uint8_t k;
        for (k = 0; k < PT_SN_LEN && cfg.device_sn[k] != '\0'; k++)
            pt_data.sn[k] = cfg.device_sn[k];
        pt_data.sn[k] = '\0';
    }

    /* BAT_SN: bat_model[0..3] 用分号拼接 */
    {
        pos = 0;
        for (i = 0; i < PT_CELL_COUNT && pos < PT_BAT_SN_LEN; i++)
        {
            uint8_t j;
            for (j = 0; j < PT_CELL_SN_LEN && cfg.bat_model[i][j] != '\0' && pos < PT_BAT_SN_LEN; j++)
            {
                pt_data.bat_sn[pos++] = cfg.bat_model[i][j];
            }
            if (i < (PT_CELL_COUNT - 1) && cfg.bat_model[i + 1][0] != '\0' && pos < PT_BAT_SN_LEN)
            {
                pt_data.bat_sn[pos++] = ';';
            }
        }
        pt_data.bat_sn[pos] = '\0';
    }

    /* 循环次数 (掉电保存) */
    pt_data.cycle_u = cfg.cycle_count;
}

/* ========================================================================== */
/*  CheckUnlock — 8 字节固定密钥 0x5A 比对                                     */
/* ========================================================================== */
static uint8_t CheckUnlock(const uint8_t *key, uint8_t len)
{
    uint8_t i;
    if (len < 8)
        return 0;
    for (i = 0; i < 8; i++)
    {
        if (key[i] != 0x5A)
            return 0;
    }
    return 1;
}

/* ========================================================================== */
/*  USART 发送辅助                                                           */
/* ========================================================================== */

static void pt_send_kv_u32(const char *key, uint32_t val)
{
    char buf[12];
    uint8_t pos = 0, i;

    if (val == 0)
    {
        buf[pos++] = '0';
    }
    else
    {
        while (val > 0 && pos < 11)
        {
            buf[pos++] = '0' + (val % 10);
            val /= 10;
        }
        for (i = 0; i < pos / 2; i++)
        {
            char tmp = buf[i];
            buf[i] = buf[pos - 1 - i];
            buf[pos - 1 - i] = tmp;
        }
    }
    buf[pos] = '\0';

    if (key && key[0] != '\0')
    {
        PT_PUTS(key);
        PT_PUTC('=');
    }
    PT_PUTS(buf);
    PT_PUTS("\r\n");
}

static void pt_send_kv_str(const char *key, const char *val)
{
    PT_PUTS(key);
    PT_PUTC('=');
    PT_PUTS(val);
    PT_PUTS("\r\n");
}

static void pt_send_line(const char *str)
{
    PT_PUTS(str);
    PT_PUTS("\r\n");
}

/* ---- 无符号整数直接输出 (无换行) ---- */
static void pt_send_val_u16(uint16_t v)
{
    char buf[6];
    uint8_t p = 0, i;
    if (v == 0) { PT_PUTC('0'); return; }
    while (v > 0 && p < 5) { buf[p++] = '0' + (v % 10); v /= 10; }
    for (i = 0; i < p / 2; i++) { char t = buf[i]; buf[i] = buf[p-1-i]; buf[p-1-i] = t; }
    for (i = 0; i < p; i++) PT_PUTC(buf[i]);
}
static void pt_send_val_u8(uint8_t v)
{
    if (v >= 100) PT_PUTC('0' + v / 100);
    if (v >= 10)  PT_PUTC('0' + (v / 10) % 10);
    PT_PUTC('0' + v % 10);
}
static void pt_send_val_u8_2digit(uint8_t v)
{
    PT_PUTC('0' + (v / 10) % 10);
    PT_PUTC('0' + v % 10);
}

#if 0  /* 暂未使用, 待对应字段恢复后启用 */
/**
 * @brief  输出定点小数 "XXX.XX" (无前缀, 无换行)
 */
static void pt_send_val_fixed2(int32_t val_hundredths)
{
    uint32_t v = (val_hundredths < 0) ? (uint32_t)(-val_hundredths) : (uint32_t)val_hundredths;
    uint32_t int_part = v / 100;
    uint8_t frac = (uint8_t)(v % 100);
    char buf[12];
    uint8_t pos = 0, i;

    if (val_hundredths < 0)
        PT_PUTC('-');

    if (int_part == 0)
    {
        buf[pos++] = '0';
    }
    else
    {
        uint32_t n = int_part;
        while (n > 0 && pos < 11)
        {
            buf[pos++] = '0' + (n % 10);
            n /= 10;
        }
        for (i = 0; i < pos / 2; i++)
        {
            char tmp = buf[i];
            buf[i] = buf[pos - 1 - i];
            buf[pos - 1 - i] = tmp;
        }
    }
    for (i = 0; i < pos; i++)
        PT_PUTC(buf[i]);

    PT_PUTC('.');
    PT_PUTC('0' + (frac / 10));
    PT_PUTC('0' + (frac % 10));
}

static void pt_send_kv_fixed2(const char *key, int32_t val_hundredths)
{
    PT_PUTS(key);
    PT_PUTC('=');
    pt_send_val_fixed2(val_hundredths);
    PT_PUTS("\r\n");
}

static void pt_send_kv_bcd_time(const char *key, const uint8_t *bcd, uint8_t bcd_len)
{
    uint8_t i;
    PT_PUTS(key);
    PT_PUTC('=');
    for (i = 0; i < bcd_len; i++)
    {
        PT_PUTC(pt_nibble_to_hex(bcd[i] >> 4));
        PT_PUTC(pt_nibble_to_hex(bcd[i] & 0x0F));
    }
    PT_PUTS("\r\n");
}
#endif /* 暂未使用 */

/* ---- UID 上报 (从硬件寄存器直接读, 8 字节 → 16 位十六进制) ---- */
static void pt_send_uid_hex(void)
{
    uint8_t i;
    uint32_t uid0 = *(volatile uint32_t *)MD_MCU_UID0_ADDR;
    uint32_t uid1 = *(volatile uint32_t *)MD_MCU_UID1_ADDR;
    uint8_t uid[8];

    uid[0] = (uint8_t)(uid0);
    uid[1] = (uint8_t)(uid0 >> 8);
    uid[2] = (uint8_t)(uid0 >> 16);
    uid[3] = (uint8_t)(uid0 >> 24);
    uid[4] = (uint8_t)(uid1);
    uid[5] = (uint8_t)(uid1 >> 8);
    uid[6] = (uint8_t)(uid1 >> 16);
    uid[7] = (uint8_t)(uid1 >> 24);

    PT_PUTS("UID=");
    for (i = 0; i < 8; i++)
    {
        PT_PUTC(pt_nibble_to_hex(uid[i] >> 4));
        PT_PUTC(pt_nibble_to_hex(uid[i] & 0x0F));
    }
    PT_PUTS("\r\n");
}

/* ========================================================================== */
/*  数据上报（基本信息上报）                   */
/* ========================================================================== */
static void pt_report_all(void)
{
    /* 每次上报前刷新全部数据: 实时值 + Flash 回读, 保证与屏幕一致 */
    pt_fill_test_values();
    pt_load_factory_cfg();

    /* 0.  UID: MCU硬件唯一ID (8字节十六进制) — 上位机解锁必须先拿到 UID */
    pt_send_uid_hex();

    /* 1.  SN: 整机序列号 */
    pt_send_kv_str("SN", pt_data.sn);

    /* 2.  BAT_SN: 电池序列号 */
    pt_send_kv_str("BAT_SN", pt_data.bat_sn);

    /* 3.  VBAT: 电池组总电压 (mV) */
    pt_send_kv_u32("VBAT", pt_data.vbat_mv);

    /* 4.  SOC: 剩余电量 (%) */
    pt_send_kv_u32("SOC", pt_data.soc);

    /* 5.  TEMP: 电池温度 (°C) */
    pt_send_kv_u32("TEMP", (uint32_t)(int32_t)pt_data.temp);

    /* 6.  CYCLE_U: 用户显示循环次数 */
    pt_send_kv_u32("CYCLE_U", pt_data.cycle_u);

    /* 7.  VER: 固件版本 VX.X */
    PT_PUTS("VER=V");
    PT_PUTC('0' + pt_data.ver_major);
    PT_PUTC('.');
    PT_PUTC('0' + pt_data.ver_minor);
    PT_PUTS("\r\n");

    /* 8.  ERR_CNT: 异常日志总条数 */
    pt_send_kv_u32("ERR_CNT", pt_data.err_cnt);

    /* 9.  TIME_NOW: 当前时间 YYYY-M-D HH:MM:SS */
    {
        uint16_t y;
        uint8_t mo, d, h, mi, s;
        rtc_unix_to_datetime(pt_data.time_now, &y, &mo, &d, &h, &mi, &s);
        PT_PUTS("TIME_NOW=");
        pt_send_val_u16(y);       PT_PUTC('-');
        pt_send_val_u8(mo);       PT_PUTC('-');
        pt_send_val_u8(d);        PT_PUTC(' ');
        pt_send_val_u8_2digit(h); PT_PUTC(':');
        pt_send_val_u8_2digit(mi);PT_PUTC(':');
        pt_send_val_u8_2digit(s);
        PT_PUTS("\r\n");
    }

    /* 10. ACK: 通信应答 */
    pt_send_line("ACK=OK");
}

/* ========================================================================== */
/*  命令处理                                                                 */
/* ========================================================================== */

/* ========================================================================== */
/*  Flash 保存辅助                                                            */
/* ========================================================================== */

/*
 * prod_save_factory_cfg — 写入 factory_cfg 并应答
 */
static void prod_save_factory_cfg(const factory_cfg_t *cfg)
{
    factory_cfg_write(cfg);
    pt_send_line("FLASH_SAVE=OK");
}

/* ========================================================================== */
/*  命令处理                                                                 */
/* ========================================================================== */

static void pt_handle_mode_ctrl(uint8_t param)
{
    switch (param)
    {
    case PT_MODE_ENTER_TEST:
        pt_rt.state = PT_TEST_MODE;
        pt_rt.unlocked = 0;
        s_pt_enter_tick = md_get_tick();            /* 记录进入时刻, 3min 内不进低功耗 */
        pt_rt.last_activity_tick = s_pt_enter_tick; /* 复位不活动计时 */
        pt_report_all();
        break;

    case PT_MODE_OK_EXIT:
        if (pt_rt.state == PT_TEST_MODE || pt_rt.state == PT_UNLOCKED)
        {
            if (pt_rt.unlocked)
            {
                /* TODO: 保存 BAT_R0 / 清空 CYCLE_U / 写 Flash */
            }
            pt_rt.state = PT_IDLE;
            pt_rt.unlocked = 0;
            pt_send_line("ACK=OK");
        }
        break;

#if PT_NG_LOCK_EN
    case PT_MODE_NG_LOCK:
        pt_rt.state = PT_NG_LOCK;
        pt_rt.unlocked = 0;
        if (s_pt_enter_tick == 0)
            s_pt_enter_tick = md_get_tick();
        pt_rt.last_activity_tick = md_get_tick();
        pt_send_line("ACK=NG");
        break;
#else
    case PT_MODE_NG_LOCK:
        pt_send_line("ERR=NG_DISABLED");
        break;
#endif

    default:
        pt_send_line("ERR=INVALID_PARAM");
        break;
    }
}

static void pt_handle_unlock(const uint8_t *params, uint8_t len)
{
    if (pt_rt.state != PT_TEST_MODE)
    {
        pt_send_line("ERR=NOT_IN_TEST");
        return;
    }

    if (CheckUnlock(params, len))
    {
        pt_rt.unlocked = 1;
        pt_rt.state = PT_UNLOCKED;
        /* 存储解锁签名 */
        memcpy(pt_data.unlock_sign, params, PT_UNLOCK_KEY_LEN);

        /* 解锁后恢复出厂状态: 清异常 / 清禁用 / 循环置0 / SOH置100 */
        abnormal_log_reset();
        ui_data.abnormal_volt_count = 0;
        ui_data.abnormal_temp_count = 0;
        ui_data.abnormal_idx = 0;
        ui_data.disable_flag = 0;
        battery_mgr_clear_disable();
        pt_data.err_cnt = 0;

        /* Flash 一次写入: cycle=0, soh=100, disable_reason=0 */
        {
            factory_cfg_t cfg;
            factory_cfg_read(&cfg);
            cfg.disable_reason = 0; // 清除禁用
            cfg.cycle_count = 0;    // 循环置0
            cfg.soh = 100;          // SOH置100
            factory_cfg_write(&cfg);
        }
        pt_data.cycle_u = 0;

        /* 置解锁标志, i2c_slave_proc 消费后通知主机恢复出厂设置 */
        s_pt_unlock_flag = 1;

        pt_send_line("ACK=OK");
    }
    else
    {
        pt_send_line("ERR=UNLOCK_FAIL");
    }
}

static void pt_handle_write_sn(const uint8_t *params, uint8_t len)
{
    factory_cfg_t cfg;

    if (!pt_rt.unlocked)
    {
        pt_send_line("ERR=NOT_UNLOCKED");
        return;
    }

    if (len > PT_SN_LEN)
        len = PT_SN_LEN;
    memset(pt_data.sn, 0, sizeof(pt_data.sn));
    memcpy(pt_data.sn, params, len);
    pt_data.sn[len] = '\0';

    /* ASCII 字符串直接写入 Flash */
    factory_cfg_read(&cfg);
    memset(cfg.device_sn, 0, sizeof(cfg.device_sn));
    memcpy(cfg.device_sn, pt_data.sn, len);
    prod_save_factory_cfg(&cfg);
    pt_send_kv_str("SN", pt_data.sn);
}

static void pt_handle_write_bat_sn(const uint8_t *params, uint8_t len)
{
    factory_cfg_t cfg;
    uint8_t cell_idx = 0;
    uint8_t start = 0;
    uint8_t i;

    if (!pt_rt.unlocked)
    {
        pt_send_line("ERR=NOT_UNLOCKED");
        return;
    }

    if (len > PT_BAT_SN_LEN)
        len = PT_BAT_SN_LEN;
    memset(pt_data.bat_sn, 0, sizeof(pt_data.bat_sn));
    memcpy(pt_data.bat_sn, params, len);
    pt_data.bat_sn[len] = '\0';

    /*
     * 写入 Flash: 按分号分隔, 逐个存入 bat_model[0..3] (每个最长 18B)
     *
     * 上位机格式: "CELL0_SN;CELL1_SN;CELL2_SN;CELL3_SN"
     * 例: "LG18650;SAMSUNG-21700;;"  → 2 节电芯, 后 2 槽为空
     */
    factory_cfg_read(&cfg);
    memset(cfg.bat_model, 0, sizeof(cfg.bat_model));

    for (i = 0; i < len && cell_idx < PT_CELL_COUNT; i++)
    {
        if (pt_data.bat_sn[i] == ';' || i == len - 1)
        {
            uint8_t end = (pt_data.bat_sn[i] == ';') ? i : i + 1;
            uint8_t chunk = (uint8_t)(end - start);
            if (chunk > PT_CELL_SN_LEN)
                chunk = PT_CELL_SN_LEN;
            if (chunk > 0)
            {
                memcpy(cfg.bat_model[cell_idx], &pt_data.bat_sn[start], chunk);
            }
            cell_idx++;
            start = i + 1;
        }
    }

    cfg.cell_count = cell_idx; /* 实际写入的电芯数量 */
    prod_save_factory_cfg(&cfg);
    /* 同步 ui_data, 屏幕立即显示新电池编码 */
    memcpy(ui_data.bat_model_1, cfg.bat_model[0], sizeof(ui_data.bat_model_1));
    memcpy(ui_data.bat_model_2, cfg.bat_model[1], sizeof(ui_data.bat_model_2));
    memcpy(ui_data.bat_model_3, cfg.bat_model[2], sizeof(ui_data.bat_model_3));
    memcpy(ui_data.bat_model_4, cfg.bat_model[3], sizeof(ui_data.bat_model_4));

    pt_send_kv_str("BAT_SN", pt_data.bat_sn);
}

static void pt_handle_sync_time(const uint8_t *params, uint8_t len)
{
    factory_cfg_t cfg;
    uint32_t unix_ts;

    if (!pt_rt.unlocked)
    {
        pt_send_line("ERR=NOT_UNLOCKED");
        return;
    }
    if (len < 6)
    {
        pt_send_line("ERR=DATE_FAIL");
        return;
    }

    /* BCD → Unix 时间戳, 写入 Flash */
    unix_ts = rtc_bcd6_to_unix(params);

    factory_cfg_read(&cfg);
    cfg.start_timestamp = unix_ts;
    cfg.dis_start_ts = unix_ts;

    prod_save_factory_cfg(&cfg);
	rtc_timer_reinit();

    /* 上行: DATE=20YYMMDDHHMMSS */
    PT_PUTS("DATE=20");
    PT_PUTC(pt_nibble_to_hex(params[0] >> 4));
    PT_PUTC(pt_nibble_to_hex(params[0] & 0x0F));
    PT_PUTC(pt_nibble_to_hex(params[1] >> 4));
    PT_PUTC(pt_nibble_to_hex(params[1] & 0x0F));
    PT_PUTC(pt_nibble_to_hex(params[2] >> 4));
    PT_PUTC(pt_nibble_to_hex(params[2] & 0x0F));
    PT_PUTC(pt_nibble_to_hex(params[3] >> 4));
    PT_PUTC(pt_nibble_to_hex(params[3] & 0x0F));
    PT_PUTC(pt_nibble_to_hex(params[4] >> 4));
    PT_PUTC(pt_nibble_to_hex(params[4] & 0x0F));
    PT_PUTC(pt_nibble_to_hex(params[5] >> 4));
    PT_PUTC(pt_nibble_to_hex(params[5] & 0x0F));
    PT_PUTS("\r\n");
}

/* ========================================================================== */
/*  帧处理                                                                   */
/* ========================================================================== */

static void pt_dispatch_frame(uint8_t cmd, const uint8_t *params, uint8_t param_len)
{
    /* 收到有效帧即刷新不活动计时 (NG_LOCK 除外, 仅充电可退出) */
    if (pt_rt.state != PT_NG_LOCK)
        pt_rt.last_activity_tick = md_get_tick();

    switch (cmd)
    {
    case PT_CMD_MODE_CTRL:
        if (param_len >= 1)
            pt_handle_mode_ctrl(params[0]);
        break;
    case PT_CMD_UNLOCK:
        pt_handle_unlock(params, param_len);
        break;
    case PT_CMD_WRITE_SN:
        pt_handle_write_sn(params, param_len);
        break;
    case PT_CMD_WRITE_BAT_SN:
        pt_handle_write_bat_sn(params, param_len);
        break;
    case PT_CMD_SYNC_TIME:
        pt_handle_sync_time(params, param_len);
        break;
    default:
        pt_send_line("ERR=UNKNOWN_CMD");
        break;
    }
}

/* ========================================================================== */
/*  校验和                                                                   */
/* ========================================================================== */

static uint8_t pt_calc_checksum(const uint8_t *data, uint8_t len)
{
    uint8_t sum = 0, i;
    for (i = 0; i < len; i++)
        sum += data[i];
    return sum & 0xFF;
}

/* ========================================================================== */
/*  帧解析状态机                                                             */
/* ========================================================================== */

static void pt_parse_byte(uint8_t byte)
{
    switch (frame_state)
    {
    case FRAME_WAIT_AA:
        if (byte == PT_FRAME_HEADER1)
        {
            frame_buf[0] = byte;
            frame_idx = 1;
            frame_state = FRAME_WAIT_55;
        }
        break;
    case FRAME_WAIT_55:
        if (byte == PT_FRAME_HEADER2)
        {
            frame_buf[1] = byte;
            frame_idx = 2;
            frame_state = FRAME_WAIT_LEN;
        }
        else
        {
            frame_state = FRAME_WAIT_AA;
        }
        break;
    case FRAME_WAIT_LEN:
        frame_len = byte;
        if (frame_len < 3 || frame_len > (PT_FRAME_MAX_PARAMS + 4))
        {
            frame_state = FRAME_WAIT_AA;
            break;
        }
        frame_buf[2] = byte;
        frame_idx = 3;
        frame_state = FRAME_WAIT_CMD;
        break;
    case FRAME_WAIT_CMD:
        frame_cmd = byte;
        frame_buf[3] = byte;
        frame_idx = 4;
        frame_param_cnt = frame_len - 4;
        frame_state = (frame_param_cnt > 0) ? FRAME_WAIT_PARAMS : FRAME_WAIT_CKSUM;
        break;
    case FRAME_WAIT_PARAMS:
        frame_buf[frame_idx++] = byte;
        if (frame_idx >= (uint8_t)(4 + frame_param_cnt))
            frame_state = FRAME_WAIT_CKSUM;
        break;
    case FRAME_WAIT_CKSUM:
        if (byte == pt_calc_checksum(frame_buf, frame_len))
            pt_dispatch_frame(frame_cmd, (frame_param_cnt > 0) ? &frame_buf[4] : NULL, frame_param_cnt);
        frame_state = FRAME_WAIT_AA;
        break;
    default:
        frame_state = FRAME_WAIT_AA;
        break;
    }
}

#if PT_NG_LOCK_EN
/* ========================================================================== */
/*  NG 锁定 / 超时管理                                                        */
/* ========================================================================== */

static void pt_proc_ng_lock(void)
{
    /* NG 锁定仅可通过插入充电器解除 */
    if (ui_data.is_charge)
    {
        pt_rt.state = PT_IDLE;
        pt_rt.unlocked = 0;
    }
}
#endif /* PT_NG_LOCK_EN */

/* ========================================================================== */
/*  公开 API                                                                 */
/* ========================================================================== */

void prod_test_init(void)
{
    memset(&pt_rt, 0, sizeof(prod_test_rt_t));
    pt_rt.state = PT_IDLE;
    pt_rt.unlocked = 0;

    frame_state = FRAME_WAIT_AA;
    frame_idx = 0;
    frame_len = 0;

    /* 填测试数据 (后续替换为真实采集 + Flash 加载) */
    pt_fill_test_values();

    /* 从 Flash 回读已保存的 factory_cfg, 覆盖 SN/BAT_SN/MFG_DATE */
    pt_load_factory_cfg();
}

void prod_test_proc(void)
{
    uint8_t byte;
    uint32_t now;

    while (usart_recv_available())
    {
        byte = usart_recv_byte();
        pt_parse_byte(byte);
    }

    now = md_get_tick();

    /* ---- 不活动超时: 3min 无有效帧 → 直接锁定退出场测 ---- */
    if (pt_rt.state == PT_TEST_MODE || pt_rt.state == PT_UNLOCKED)
    {
        if ((now - pt_rt.last_activity_tick) >= PT_INACTIVITY_TIMEOUT_MS)
        {
            pt_rt.state = PT_IDLE;
            pt_rt.unlocked = 0;
        }
    }

#if PT_NG_LOCK_EN
    /* ---- NG 锁定处理 ---- */
    if (pt_rt.state == PT_NG_LOCK)
        pt_proc_ng_lock();
#endif
}

/* ========================================================================== */
/*  场测低功耗屏蔽: 进入场测后 3min 内阻止进低功耗                              */
/* ========================================================================== */
uint8_t prod_test_is_sleep_blocked(void)
{
    if (pt_rt.state == PT_IDLE)
        return 0;
    if ((md_get_tick() - s_pt_enter_tick) < PROD_TEST_SLEEP_BLOCK_MS)
        return 1;
    return 0;
}

/* ---- 场测模式判断 ---- */
uint8_t prod_test_is_active(void)
{
    return (pt_rt.state != PT_IDLE) ? 1 : 0;
}

/* ---- 解锁标志接口 (i2c_slave_proc 调用) ---- */
uint8_t prod_test_get_unlock_flag(void)
{
    return s_pt_unlock_flag;
}
void prod_test_clear_unlock_flag(void)
{
    s_pt_unlock_flag = 0;
}

#endif /* !PROD_TEST_SIMPLE_EN && !DEBUG_EN */
