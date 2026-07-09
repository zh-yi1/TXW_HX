/**********************************************************************************
 *
 * @file    prod_test_simple.c
 * @brief   产测模块简化版 — PROD_TEST_SIMPLE_EN 管理, 暂不启用
 *
 *          帧协议: AA 55 | Len | Cmd | Params[N] | Checksum
 *          上行:   文本行, \r\n 结尾
 *
 *          命令:
 *            CMD 0x01 (上报): Params[0] = 功能码
 *              0x01 → SN, BAT_SN, 校准温度
 *              0x02 → TEST=OK
 *            CMD 0x02 (写密匙): 固定 0x5A, 直接应答
 *            CMD 0x21 (写整机SN) → Flash
 *            CMD 0x22 (写电池SN) → Flash
 *            CMD 0x23 (同步时间) → Flash
 *
 **********************************************************************************
 */

#include "global_define.h"

#ifndef DEBUG_EN

#ifdef PROD_TEST_SIMPLE_EN

/* ---- 帧常量 ---- */
#define PT_FH1          0xAAU
#define PT_FH2          0x55U
#define PT_PARAM_MAX    72U     /* 电池SN最长72字节 (4节×18) */
#define PT_SN_LEN       32U
#define PT_BAT_SN_LEN   72U     /* 4节×18字符 */

/* ---- 帧解析状态 ---- */
enum {
    FS_AA = 0,
    FS_55,
    FS_LEN,
    FS_CMD,
    FS_PARAMS,
    FS_CKSUM,
};

/* ---- 数据 ---- */
static char pt_sn[PT_SN_LEN + 1];
static char pt_bat_sn[PT_BAT_SN_LEN + 1];

/* ---- 帧解析器 ---- */
static uint8_t fs;
static uint8_t fb[PT_PARAM_MAX + 4];
static uint8_t fi;
static uint8_t fl;
static uint8_t fc;
static uint8_t fpc;

/* ---- 场测低功耗屏蔽 ---- */
static uint32_t s_pt_enter_tick = 0; /* 首次收到指令的时刻 */

#define PT_PUTC(c)  usart_send_byte((uint8_t)(c))
#define PT_PUTS(s)  usart_send_string(s)

/* ========================================================================== */
/*  发送辅助                                                                   */
/* ========================================================================== */
static void pt_line(const char *s)
{
    PT_PUTS(s);
    PT_PUTS("\r\n");
}

static void pt_kv_str(const char *k, const char *v)
{
    PT_PUTS(k);
    PT_PUTC('=');
    PT_PUTS(v);
    PT_PUTS("\r\n");
}

static void pt_kv_s16(const char *k, int16_t v)
{
    char buf[8];
    uint8_t p = 0, i;
    uint16_t u;

    PT_PUTS(k);
    PT_PUTC('=');
    if (v < 0) { PT_PUTC('-'); u = (uint16_t)(-v); }
    else       { u = (uint16_t)v; }

    if (u == 0) {
        PT_PUTC('0');
    } else {
        while (u && p < 7) { buf[p++] = '0' + (u % 10); u /= 10; }
        for (i = 0; i < p / 2; i++) {
            char t = buf[i];
            buf[i] = buf[p - 1 - i];
            buf[p - 1 - i] = t;
        }
        for (i = 0; i < p; i++) PT_PUTC(buf[i]);
    }
    PT_PUTS("\r\n");
}

/* ========================================================================== */
/*  Flash 保存                                                                 */
/* ========================================================================== */
static void pt_save_cfg(const factory_cfg_t *cfg)
{
    factory_cfg_write(cfg);
    pt_line("FLASH_SAVE=OK");
}


/* ========================================================================== */
/*  数据初始化 — Flash 回读 SN/BAT_SN, 否则用默认值                             */
/* ========================================================================== */
static void pt_init_data(void)
{
    factory_cfg_t cfg;

    pt_sn[0]     = '\0';
    pt_bat_sn[0] = '\0';

    factory_cfg_read(&cfg);
    if (cfg.magic != 0x55) return;

    /* SN */
    memcpy(pt_sn, cfg.device_sn, PT_SN_LEN);
    pt_sn[PT_SN_LEN] = '\0';

    /* BAT_SN: 4 节 × 18 字节拼接 + 同步 ui_data */
    memcpy(&pt_bat_sn[0],  cfg.bat_model[0], 18);
    memcpy(&pt_bat_sn[18], cfg.bat_model[1], 18);
    memcpy(&pt_bat_sn[36], cfg.bat_model[2], 18);
    memcpy(&pt_bat_sn[54], cfg.bat_model[3], 18);
    pt_bat_sn[72] = '\0';
}

/* ========================================================================== */
/*  命令处理                                                                   */
/* ========================================================================== */

/* CMD 0x01 — 数据上报 */
static void pt_cmd_report(uint8_t func)
{
    switch (func) {
    case 0x01:
        pt_kv_str("SN", pt_sn);
        pt_kv_str("BAT_SN", pt_bat_sn);
        pt_kv_s16("TEMP", ui_data.bat_temperature);
        pt_line("ACK=OK");
        break;
    case 0x02:
        pt_line("TEST=OK");
        break;
    default:
        pt_line("ERR=INVALID_FUNC");
        break;
    }
}

/* CMD 0x02 — 写密匙 (固定 0x5A) */
static void pt_cmd_write_key(void)
{
    pt_line("ACK=OK");
}

/* CMD 0x21 — 写整机 SN → Flash */
static void pt_cmd_write_sn(const uint8_t *params, uint8_t len)
{
    factory_cfg_t cfg;

    if (len > PT_SN_LEN) len = PT_SN_LEN;
    memset(pt_sn, 0, sizeof(pt_sn));
    memcpy(pt_sn, params, len);
    pt_sn[len] = '\0';

    factory_cfg_read(&cfg);
    memset(cfg.device_sn, 0, sizeof(cfg.device_sn));
    memcpy(cfg.device_sn, pt_sn, len);
    pt_save_cfg(&cfg);
}

/* CMD 0x22 — 写电池 SN → Flash (72 字节 = 4 节 × 18) */
static void pt_cmd_write_bat_sn(const uint8_t *params, uint8_t len)
{
    factory_cfg_t cfg;
    uint8_t cell, copy;

    if (len > 72) len = 72;

    factory_cfg_read(&cfg);
    memset(cfg.bat_model, 0, sizeof(cfg.bat_model));

    for (cell = 0; cell < 4 && cell * 18 < len; cell++) {
        copy = (len - cell * 18 > 18) ? 18 : (len - cell * 18);
        memcpy(cfg.bat_model[cell], &params[cell * 18], copy);
    }
    cfg.cell_count = cell;
    pt_save_cfg(&cfg);

    /* 同步 ui_data */
    memcpy(ui_data.bat_model_1, cfg.bat_model[0], 18);
    ui_data.bat_model_1[18] = '\0';
    memcpy(ui_data.bat_model_2, cfg.bat_model[1], 18);
    ui_data.bat_model_2[18] = '\0';
    memcpy(ui_data.bat_model_3, cfg.bat_model[2], 18);
    ui_data.bat_model_3[18] = '\0';
    memcpy(ui_data.bat_model_4, cfg.bat_model[3], 18);
    ui_data.bat_model_4[18] = '\0';

    /* 同步 pt_bat_sn 供上报 */
    memcpy(pt_bat_sn, params, len);
    pt_bat_sn[len] = '\0';
}

/* CMD 0x23 — 同步时间 → Flash */
static void pt_cmd_sync_time(const uint8_t *params, uint8_t len)
{
    factory_cfg_t cfg;
    uint32_t unix_ts;

    if (len < 6) { pt_line("ERR=DATE_FAIL"); return; }

    unix_ts = rtc_bcd6_to_unix(params);

    factory_cfg_read(&cfg);
    cfg.start_timestamp = unix_ts;
    pt_save_cfg(&cfg);
    rtc_timer_reinit();
}

/* ========================================================================== */
/*  帧分发                                                                     */
/* ========================================================================== */
static void pt_dispatch(uint8_t cmd, const uint8_t *params, uint8_t len)
{
    /* 首次收到指令 → 记录进入场测时刻, 3min 内不进低功耗 */
    if (s_pt_enter_tick == 0)
        s_pt_enter_tick = md_get_tick();

    switch (cmd) {
    case 0x01:  /* 上报 */
        if (len >= 1) pt_cmd_report(params[0]);
        else          pt_line("ERR=NO_FUNC");
        break;
    case 0x02:  /* 写密匙 */
        pt_cmd_write_key();
        break;
    case 0x21:  /* 写整机 SN */
        pt_cmd_write_sn(params, len);
        break;
    case 0x22:  /* 写电池 SN */
        pt_cmd_write_bat_sn(params, len);
        break;
    case 0x23:  /* 同步时间 */
        pt_cmd_sync_time(params, len);
        break;
    default:
        pt_line("ERR=UNKNOWN_CMD");
        break;
    }
}

/* ========================================================================== */
/*  校验和                                                                     */
/* ========================================================================== */
static uint8_t pt_cksum(const uint8_t *d, uint8_t n)
{
    uint8_t s = 0, i;
    for (i = 0; i < n; i++) s += d[i];
    return s;
}

/* ========================================================================== */
/*  帧解析                                                                     */
/* ========================================================================== */
static void pt_parse(uint8_t b)
{
    switch (fs) {
    case FS_AA:
        if (b == PT_FH1) { fb[0] = b; fi = 1; fs = FS_55; }
        break;
    case FS_55:
        if (b == PT_FH2) { fb[1] = b; fi = 2; fs = FS_LEN; }
        else             { fs = FS_AA; }
        break;
    case FS_LEN:
        if (b < 3 || b > (PT_PARAM_MAX + 4)) { fs = FS_AA; break; }
        fl = b; fb[2] = b; fi = 3; fs = FS_CMD;
        break;
    case FS_CMD:
        fc = b; fb[3] = b; fi = 4;
        fpc = fl - 4;
        fs = (fpc > 0) ? FS_PARAMS : FS_CKSUM;
        break;
    case FS_PARAMS:
        fb[fi++] = b;
        if (fi >= (uint8_t)(4 + fpc)) fs = FS_CKSUM;
        break;
    case FS_CKSUM:
        if (b == pt_cksum(fb, fl))
            pt_dispatch(fc, (fpc > 0) ? &fb[4] : NULL, fpc);
        fs = FS_AA;
        break;
    default:
        fs = FS_AA;
        break;
    }
}

/* ========================================================================== */
/*  公开 API                                                                   */
/* ========================================================================== */
void prod_test_init(void)
{
    fs = FS_AA;
    fi = 0;
    pt_init_data();
    usart_send_string("PROD_READY\r\n");
}

void prod_test_proc(void)
{
    while (usart_recv_available())
        pt_parse(usart_recv_byte());
}

/* ========================================================================== */
/*  场测低功耗屏蔽: 收到开始指令后 3min 内阻止进低功耗                           */
/* ========================================================================== */
uint8_t prod_test_is_sleep_blocked(void)
{
    if (s_pt_enter_tick == 0)
        return 0;
    if ((md_get_tick() - s_pt_enter_tick) < PROD_TEST_SLEEP_BLOCK_MS)
        return 1;
    return 0;
}

#endif

#endif /* PROD_TEST_SIMPLE_EN */
