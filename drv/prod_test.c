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

#ifndef DEBUG_EN

/* ========================================================================== */
/*  模块级全局变量                                                           */
/* ========================================================================== */

static prod_test_rt_t   pt_rt;      /* 运行时状态 */
static prod_test_data_t pt_data;    /* 名词解释全部数据 (先填测试值, 后续接真实数据) */

/* ---- 帧解析器 ---- */
static frame_parse_state_t frame_state = FRAME_WAIT_AA;
static uint8_t  frame_buf[PT_FRAME_MAX_PARAMS + 4];
static uint8_t  frame_idx;
static uint8_t  frame_len;
static uint8_t  frame_cmd;
static uint8_t  frame_param_cnt;

/* ---- 前向声明 ---- */
static void pt_report_all(void);

/* ========================================================================== */
/*  测试数据填充 (后续替换为真实采集)                                         */
/* ========================================================================== */
static void pt_fill_test_values(void)
{
    /* 加密签名 */
    memset(pt_data.unlock_sign, 0, PT_UNLOCK_KEY_LEN);

    /* SN + BAT_SN (初始值, 不等同于写入值) */
    memcpy(pt_data.sn,     "000000000000", sizeof("000000000000"));
    memcpy(pt_data.bat_sn, "BAT00000000",   sizeof("BAT00000000"));

    /* UID (模拟测试值: 123456789ABCDEF0) */
    { uint8_t tmp[8] = {0x12,0x34,0x56,0x78,0x9A,0xBC,0xDE,0xF0};
      memcpy(pt_data.uid, tmp, PT_UID_LEN); }

    /* 实时数据 */
    pt_data.vbat_mv = 15000;
    pt_data.soc      = 85;
    pt_data.temp     = 28;
    pt_data.bat_r    = 35;
    pt_data.bat_r0   = 30;
    pt_data.cycle_u  = 105;
    pt_data.cycle_a  = 125;

    /* VER + MODEL + MFG */
    pt_data.ver_major = 1;
    pt_data.ver_minor = 0;
    pt_data.ver_patch = 0;
    memcpy(pt_data.model,  "PW", sizeof("PW"));
    memcpy(pt_data.mfg,    "SZ", sizeof("SZ"));
    memset(pt_data.mfg_date, 0, 6);

    /* ---- 异常记录 ---- */
    pt_data.ovp      = 0;
    pt_data.ovp_max  = 0;
    pt_data.otp      = 0;
    pt_data.otp_max  = 0;
    memset(pt_data.err_time, 0, 6);
    pt_data.err_cnt  = 0;
    pt_data.r_err    = 0;
    pt_data.uid_err  = 0;
    pt_data.liq_cnt  = 0;
}

/* ========================================================================== */
/*  Secure_Sign — 生成 32 位签名 (PDF §7.2, 算法不可修改)                     */
/* ========================================================================== */
uint32_t Secure_Sign(const uint8_t *uid, uint32_t key)
{
    const uint32_t mul1 = 0x45D9F3AB;
    const uint32_t mul2 = 0x9E3779B9;
    uint32_t hash = key;
    int i;

    for (i = 0; i < 8; i++)
    {
        hash ^= uid[i];
        hash *= mul1;
        hash ^= hash >> 17;
        hash += mul2;
    }

    hash ^= hash << 19;
    hash *= mul2;
    hash ^= hash >> 23;
    hash *= mul1;

    return hash;
}

/* ========================================================================== */
/*  CheckUnlock — 校验解锁码, 仅比对前 4 字节               */
/* ========================================================================== */
uint8_t CheckUnlock(const uint8_t *uid, uint16_t uid_len, uint32_t unlock_code)
{
    uint8_t uid8[8] = {0};
    uint32_t local;

    if (uid_len >= 8)
        memcpy(uid8, uid, 8);
    else
        memcpy(uid8, uid, uid_len);

    local = Secure_Sign(uid8, UNLOCK_KEY);

    return (((local & 0xFFFF0000) >> 16) == ((unlock_code & 0xFFFF0000) >> 16)) ? 1 : 0;
}

/* ========================================================================== */
/*  USART 发送辅助                                                           */
/* ========================================================================== */

static void pt_send_kv_u32(const char *key, uint32_t val)
{
    char buf[12];
    uint8_t pos = 0, i;

    if (val == 0) {
        buf[pos++] = '0';
    } else {
        while (val > 0 && pos < 11) {
            buf[pos++] = '0' + (val % 10);
            val /= 10;
        }
        for (i = 0; i < pos / 2; i++) {
            char tmp = buf[i];
            buf[i] = buf[pos - 1 - i];
            buf[pos - 1 - i] = tmp;
        }
    }
    buf[pos] = '\0';

    if (key && key[0] != '\0') {
        usart_send_string(key);
        usart_send_byte('=');
    }
    usart_send_string(buf);
    usart_send_string("\r\n");
}

static void pt_send_kv_str(const char *key, const char *val)
{
    usart_send_string(key);
    usart_send_byte('=');
    usart_send_string(val);
    usart_send_string("\r\n");
}

static void pt_send_line(const char *str)
{
    usart_send_string(str);
    usart_send_string("\r\n");
}

/**
 * @brief  输出定点小数 "XXX.XX" (无前缀, 无换行)
 */
static void pt_send_val_fixed2(int32_t val_hundredths)
{
    uint32_t v = (val_hundredths < 0) ? (uint32_t)(-val_hundredths) : (uint32_t)val_hundredths;
    uint32_t int_part = v / 100;
    uint8_t  frac     = (uint8_t)(v % 100);
    char buf[12];
    uint8_t pos = 0, i;

    if (val_hundredths < 0) usart_send_byte('-');

    if (int_part == 0) {
        buf[pos++] = '0';
    } else {
        uint32_t n = int_part;
        while (n > 0 && pos < 11) { buf[pos++] = '0' + (n % 10); n /= 10; }
        for (i = 0; i < pos / 2; i++) {
            char tmp = buf[i]; buf[i] = buf[pos - 1 - i]; buf[pos - 1 - i] = tmp;
        }
    }
    for (i = 0; i < pos; i++) usart_send_byte(buf[i]);

    usart_send_byte('.');
    usart_send_byte('0' + (frac / 10));
    usart_send_byte('0' + (frac % 10));
}

static void pt_send_kv_fixed2(const char *key, int32_t val_hundredths)
{
    usart_send_string(key);
    usart_send_byte('=');
    pt_send_val_fixed2(val_hundredths);
    usart_send_string("\r\n");
}

static void pt_send_uid_hex(const uint8_t *uid, uint8_t len)
{
    uint8_t i;
    usart_send_string("UID=");
    for (i = 0; i < len; i++) {
        usart_send_byte(pt_nibble_to_hex(uid[i] >> 4));
        usart_send_byte(pt_nibble_to_hex(uid[i] & 0x0F));
    }
    usart_send_string("\r\n");
}

static void pt_send_kv_bcd_time(const char *key, const uint8_t *bcd, uint8_t bcd_len)
{
    uint8_t i;
    usart_send_string(key);
    usart_send_byte('=');
    for (i = 0; i < bcd_len; i++) {
        usart_send_byte(pt_nibble_to_hex(bcd[i] >> 4));
        usart_send_byte(pt_nibble_to_hex(bcd[i] & 0x0F));
    }
    usart_send_string("\r\n");
}

/* ========================================================================== */
/*  数据上报（基本信息上报）                   */
/* ========================================================================== */
static void pt_report_all(void)
{
    char date_str[9];
    uint8_t i;

    /* 0. 加密签名: 64位哈希 (MCU_UID+密钥, 8字节十六进制) */
    usart_send_string("UNLOCK_SIGN=");
    for (i = 0; i < PT_UNLOCK_KEY_LEN; i++) {
        usart_send_byte(pt_nibble_to_hex(pt_data.unlock_sign[i] >> 4));
        usart_send_byte(pt_nibble_to_hex(pt_data.unlock_sign[i] & 0x0F));
    }
    usart_send_string("\r\n");

    /* 1.  SN: 整机序列号 */
    pt_send_kv_str("SN", pt_data.sn);

    /* 2.  BAT_SN: 电池序列号 */
    pt_send_kv_str("BAT_SN", pt_data.bat_sn);

    /* 3.  UID: MCU硬件唯一ID (8字节十六进制) */
    pt_send_uid_hex(pt_data.uid, PT_UID_LEN);

    /* 4.  VBAT: 电池组总电压 (mV) */
    pt_send_kv_u32("VBAT", pt_data.vbat_mv);

    /* 5.  SOC: 剩余电量 (%) */
    pt_send_kv_u32("SOC", pt_data.soc);

    /* 6.  TEMP: 电池温度 (°C) */
    pt_send_kv_u32("TEMP", (uint32_t)(int32_t)pt_data.temp);

    /* 7.  BAT_R: 当前内阻 (mΩ) */
    pt_send_kv_u32("BAT_R", pt_data.bat_r);

    /* 8.  BAT_R0: 初始内阻 (mΩ) */
    pt_send_kv_u32("BAT_R0", pt_data.bat_r0);

    /* 9.  CYCLE_U: 用户显示循环次数 */
    pt_send_kv_u32("CYCLE_U", pt_data.cycle_u);

    /* 10. CYCLE_A: 真实老化循环次数 */
    pt_send_kv_u32("CYCLE_A", pt_data.cycle_a);

    /* 11. VER: 固件版本 VX.X.X */
    usart_send_string("VER=V");
    usart_send_byte('0' + pt_data.ver_major);
    usart_send_byte('.');
    usart_send_byte('0' + pt_data.ver_minor);
    usart_send_byte('.');
    usart_send_byte('0' + pt_data.ver_patch);
    usart_send_string("\r\n");

    /* 12. MODEL: 产品型号编码 */
    pt_send_kv_str("MODEL", pt_data.model);

    /* 13. MFG: 生产工厂代码 */
    pt_send_kv_str("MFG", pt_data.mfg);

    /* 14. MFG_DATE: 生产日期 (6位 BCD: 年月日) */
    date_str[0] = pt_nibble_to_hex(pt_data.mfg_date[0] >> 4);
    date_str[1] = pt_nibble_to_hex(pt_data.mfg_date[0] & 0x0F);
    date_str[2] = pt_nibble_to_hex(pt_data.mfg_date[1] >> 4);
    date_str[3] = pt_nibble_to_hex(pt_data.mfg_date[1] & 0x0F);
    date_str[4] = pt_nibble_to_hex(pt_data.mfg_date[2] >> 4);
    date_str[5] = pt_nibble_to_hex(pt_data.mfg_date[2] & 0x0F);
    date_str[6] = '\0';
    pt_send_kv_str("MFG_DATE", date_str);

    /* 15. OVP: 末次过压值 (mV) */
    pt_send_kv_u32("OVP", pt_data.ovp);

    /* 16. OVP_MAX: 1小时过压峰值 (X.XX V) */
    pt_send_kv_fixed2("OVP_MAX", (int32_t)pt_data.ovp_max / 10);

    /* 17. OTP: 末次过温值 (XX.X °C) */
    pt_send_kv_fixed2("OTP", (int32_t)pt_data.otp * 10);

    /* 18. OTP_MAX: 1小时过温峰值 (XX.X °C) */
    pt_send_kv_fixed2("OTP_MAX", (int32_t)pt_data.otp_max * 10);

    /* 19. ERR_TIME: 最近一次异常时间 (20YYMMDDHHMM) */
    pt_send_kv_bcd_time("ERR_TIME", pt_data.err_time, 5);

    /* 20. ERR_CNT: 累计异常次数 */
    pt_send_kv_u32("ERR_CNT", pt_data.err_cnt);

    /* 21. R_ERR: 内阻异常标志 (1=异常) */
    pt_send_kv_u32("R_ERR", pt_data.r_err);

    /* 22. UID_ERR: UID读取异常标志 (1=异常) */
    pt_send_kv_u32("UID_ERR", pt_data.uid_err);

    /* 23. LIQ_CN: 进液累计次数 */
    pt_send_kv_u32("LIQ_CN", pt_data.liq_cnt);

    /* 24. ACK: 通信应答 */
    pt_send_line("ACK=OK");
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

    case PT_MODE_NG_LOCK:
        pt_rt.state = PT_NG_LOCK;
        pt_rt.unlocked = 0;
        pt_rt.ng_lock_tick = md_get_tick();
        pt_rt.ng_led_toggle = 0;
        pt_send_line("ACK=NG");
        break;

    default:
        pt_send_line("ERR=INVALID_PARAM");
        break;
    }
}

static void pt_handle_unlock(const uint8_t *params, uint8_t len)
{
    uint32_t unlock_code;

    if (pt_rt.state != PT_TEST_MODE) { pt_send_line("ERR=NOT_IN_TEST"); return; }
    if (len < 8)                     { pt_send_line("ERR=UNLOCK_FAIL"); return; }

    /* 大端序解析: 上位机发送 MSB first */
    unlock_code = ((uint32_t)params[0] << 24)
                | ((uint32_t)params[1] << 16)
                | ((uint32_t)params[2] << 8)
                | ((uint32_t)params[3]);

    if (CheckUnlock(pt_data.uid, PT_UID_LEN, unlock_code))
    {
        pt_rt.unlocked = 1;
        pt_rt.state = PT_UNLOCKED;
        /* 解锁持续有效, 直至掉电或OK退出 */
        /* 存储解锁签名 */
        memcpy(pt_data.unlock_sign, params, PT_UNLOCK_KEY_LEN);
        pt_send_line("ACK=OK");
    }
    else
    {
        pt_send_line("ERR=UNLOCK_FAIL");
    }
}

static void pt_handle_write_sn(const uint8_t *params, uint8_t len)
{
    if (!pt_rt.unlocked) { pt_send_line("ERR=NOT_UNLOCKED"); return; }

    if (len > PT_SN_LEN) len = PT_SN_LEN;
    memset(pt_data.sn, 0, sizeof(pt_data.sn));
    memcpy(pt_data.sn, params, len);
    pt_data.sn[len] = '\0';

    /* TODO: 写 Flash */
    pt_send_kv_str("SN", pt_data.sn);
}

static void pt_handle_write_bat_sn(const uint8_t *params, uint8_t len)
{
    if (!pt_rt.unlocked) { pt_send_line("ERR=NOT_UNLOCKED"); return; }

    if (len > PT_BAT_SN_LEN) len = PT_BAT_SN_LEN;
    memset(pt_data.bat_sn, 0, sizeof(pt_data.bat_sn));
    memcpy(pt_data.bat_sn, params, len);
    pt_data.bat_sn[len] = '\0';

    /* TODO: 写 Flash */
    pt_send_kv_str("BAT_SN", pt_data.bat_sn);
}

static void pt_handle_sync_time(const uint8_t *params, uint8_t len)
{
    if (!pt_rt.unlocked) { pt_send_line("ERR=NOT_UNLOCKED"); return; }
    if (len < 6)         { pt_send_line("ERR=DATE_FAIL");    return; }

    memcpy(pt_data.mfg_date, params, 6);

    /* TODO: 写 Flash */

    /* 上行: DATE=20YYMMDDHHMMSS */
    usart_send_string("DATE=20");
    usart_send_byte(pt_nibble_to_hex(params[0] >> 4));
    usart_send_byte(pt_nibble_to_hex(params[0] & 0x0F));
    usart_send_byte(pt_nibble_to_hex(params[1] >> 4));
    usart_send_byte(pt_nibble_to_hex(params[1] & 0x0F));
    usart_send_byte(pt_nibble_to_hex(params[2] >> 4));
    usart_send_byte(pt_nibble_to_hex(params[2] & 0x0F));
    usart_send_byte(pt_nibble_to_hex(params[3] >> 4));
    usart_send_byte(pt_nibble_to_hex(params[3] & 0x0F));
    usart_send_byte(pt_nibble_to_hex(params[4] >> 4));
    usart_send_byte(pt_nibble_to_hex(params[4] & 0x0F));
    usart_send_byte(pt_nibble_to_hex(params[5] >> 4));
    usart_send_byte(pt_nibble_to_hex(params[5] & 0x0F));
    usart_send_string("\r\n");
}

/* ========================================================================== */
/*  帧处理                                                                   */
/* ========================================================================== */

static void pt_dispatch_frame(uint8_t cmd, const uint8_t *params, uint8_t param_len)
{
    switch (cmd)
    {
    case PT_CMD_MODE_CTRL:     if (param_len >= 1) pt_handle_mode_ctrl(params[0]); break;
    case PT_CMD_UNLOCK:        pt_handle_unlock(params, param_len);               break;
    case PT_CMD_WRITE_SN:      pt_handle_write_sn(params, param_len);             break;
    case PT_CMD_WRITE_BAT_SN:  pt_handle_write_bat_sn(params, param_len);          break;
    case PT_CMD_SYNC_TIME:     pt_handle_sync_time(params, param_len);            break;
    default:                   pt_send_line("ERR=UNKNOWN_CMD");                   break;
    }
}

/* ========================================================================== */
/*  校验和                                                                   */
/* ========================================================================== */

static uint8_t pt_calc_checksum(const uint8_t *data, uint8_t len)
{
    uint8_t sum = 0, i;
    for (i = 0; i < len; i++) sum += data[i];
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
        if (byte == PT_FRAME_HEADER1) { frame_buf[0] = byte; frame_idx = 1; frame_state = FRAME_WAIT_55; }
        break;
    case FRAME_WAIT_55:
        if (byte == PT_FRAME_HEADER2) { frame_buf[1] = byte; frame_idx = 2; frame_state = FRAME_WAIT_LEN; }
        else                         { frame_state = FRAME_WAIT_AA; }
        break;
    case FRAME_WAIT_LEN:
        frame_len = byte;
        if (frame_len < 3 || frame_len > (PT_FRAME_MAX_PARAMS + 4)) { frame_state = FRAME_WAIT_AA; break; }
        frame_buf[2] = byte; frame_idx = 3; frame_state = FRAME_WAIT_CMD;
        break;
    case FRAME_WAIT_CMD:
        frame_cmd = byte; frame_buf[3] = byte; frame_idx = 4;
        frame_param_cnt = frame_len - 4;
        frame_state = (frame_param_cnt > 0) ? FRAME_WAIT_PARAMS : FRAME_WAIT_CKSUM;
        break;
    case FRAME_WAIT_PARAMS:
        frame_buf[frame_idx++] = byte;
        if (frame_idx >= (uint8_t)(4 + frame_param_cnt)) frame_state = FRAME_WAIT_CKSUM;
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

/* ========================================================================== */
/*  NG 锁定 / 解锁超时                                                       */
/* ========================================================================== */

static void pt_proc_ng_lock(void)
{
    uint32_t now = md_get_tick();

    if ((now - pt_rt.ng_lock_tick) >= 500) {
        pt_rt.ng_lock_tick = now;
        pt_rt.ng_led_toggle = !pt_rt.ng_led_toggle;
        /* TODO: 控制 LED GPIO */
    }

    if (ui_data.is_charge) {
        pt_rt.state = PT_IDLE;
        pt_rt.unlocked = 0;
        pt_rt.ng_led_toggle = 0;
    }
}

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

    /* 调试: 初始化完成 */
    /* prod_test init done */
}

void prod_test_proc(void)
{
    uint8_t byte;

    while (usart_recv_available()) {
        byte = usart_recv_byte();
        pt_parse_byte(byte);
    }

    if (pt_rt.state == PT_NG_LOCK)    pt_proc_ng_lock();
}

#endif /* !DEBUG_EN */

