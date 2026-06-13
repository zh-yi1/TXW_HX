/**********************************************************************************
 *
 * @file    prod_test.h
 * @brief   产测模块 — 基于 USART1 的产测协议栈
 *
 * @note    协议依据: 《蓝禾移动电源智能管理产测软件方案》
 *           通信接口: USART1 (PB0=RX, PB1=TX), 115200-8-N-1
 *           下行: AA 55 | Len | CmdID | Params[N] | Checksum
 *           上行: 文本行, 以 \r\n 结尾
 *
 *           名词解释全部字段 (PDF §2):
 *           -------------------------------------------------------------
 *           SN, BAT_SN, UID, VBAT, SOC, TEMP, BAT_R, BAT_R0,
 *           CYCLE_U, CYCLE_A, VER, MODEL, MFG, MFG_DATE,
 *           OVP, OVP_MAX, OTP, OTP_MAX, ERR_TIME, ERR_CNT,
 *           R_ERR, UID_ERR, LIQ_CN, ACK
 *           -------------------------------------------------------------
 *
 **********************************************************************************
 */

#ifndef __PROD_TEST_H
#define __PROD_TEST_H

#include "global_define.h"

/* ---- 产测状态 ---- */
typedef enum {
    PT_IDLE      = 0,  /* 正常模式 (非产测) */
    PT_TEST_MODE = 1,  /* 已进入测试模式, 未解锁 */
    PT_UNLOCKED  = 2,  /* 已解锁, 可写入 SN/时间 */
    PT_NG_LOCK   = 3,  /* 测试 NG 锁定, 需充电退出 */
} prod_test_state_t;

/* ---- 帧解析状态 ---- */
typedef enum {
    FRAME_WAIT_AA = 0,
    FRAME_WAIT_55,
    FRAME_WAIT_LEN,
    FRAME_WAIT_CMD,
    FRAME_WAIT_PARAMS,
    FRAME_WAIT_CKSUM,
} frame_parse_state_t;

/* ---- 命令 ID (来自 PDF §4) ---- */
#define PT_CMD_MODE_CTRL    0x01U  /* 模式控制 */
#define PT_CMD_UNLOCK       0x20U  /* 解锁写入 */
#define PT_CMD_WRITE_SN     0x21U  /* 写入整机 SN */
#define PT_CMD_WRITE_BAT_SN 0x22U  /* 写入电池 SN */
#define PT_CMD_SYNC_TIME    0x23U  /* 同步时间 */

/* ---- 模式控制参数 ---- */
#define PT_MODE_ENTER_TEST  0x01U  /* 进入测试模式 */
#define PT_MODE_OK_EXIT     0x02U  /* 测试 OK, 退出 */
#define PT_MODE_NG_LOCK     0x03U  /* 测试 NG, 锁定 */

/* ---- 协议常量 (对齐 PDF 名词解释) ---- */
#define PT_FRAME_HEADER1    0xAAU
#define PT_FRAME_HEADER2    0x55U
#define PT_FRAME_MAX_PARAMS 64U    /* 电池SN最长64字节 */
#define PT_UID_LEN          8U
#define PT_UNLOCK_KEY_LEN   8U
#define PT_SN_LEN           12U     /* 整机 SN 长度 (不含 null) */
#define PT_BAT_SN_LEN       64U     /* 电池 SN 长度 (不含 null, 多组;分隔) */
#define PT_MODEL_LEN        8U      /* 产品型号编码长度 (不含 null) */
#define PT_MFG_LEN          4U      /* 生产工厂代码长度 (不含 null) */

/* ---- 解锁密钥 (PDF §7.1, 不可修改) ---- */
#define UNLOCK_KEY          0x12345678U

/* ---- Flash 存储地址 ---- */
#define PROD_DATA_FLASH_ADDR    0x7800U
#define PROD_DATA_FLASH_SIZE    512U

/* ========================================================================== */
/*  产测数据体 — 字段顺序 = 名词解释上报顺序                                   */
/* ========================================================================== */
#pragma pack(1)
typedef struct {
    uint8_t  unlock_sign[PT_UNLOCK_KEY_LEN];          // 加密签名 64位哈希 (MCU_UID+密钥)
    char     sn[PT_SN_LEN + 1];                      // SN      整机序列号
    char     bat_sn[PT_BAT_SN_LEN + 1];              // BAT_SN  电池序列号
    uint8_t  uid[PT_UID_LEN];                        // UID     MCU硬件ID (8字节)
    uint16_t vbat_mv;                                // VBAT    电池组总电压 (mV)
    uint8_t  soc;                                    // SOC     剩余电量 (%)
    int16_t  temp;                                   // TEMP    电池温度 (°C)
    uint16_t bat_r;                                  // BAT_R   当前内阻 (mΩ)
    uint16_t bat_r0;                                 // BAT_R0  初始内阻 (mΩ)
    uint16_t cycle_u;                                // CYCLE_U 用户循环次数
    uint16_t cycle_a;                                // CYCLE_A 真实循环次数
    uint8_t  ver_major, ver_minor, ver_patch;         // VER     固件版本 VX.X.X
    char     model[PT_MODEL_LEN + 1];                // MODEL   产品型号编码
    char     mfg[PT_MFG_LEN + 1];                    // MFG     生产工厂代码
    uint8_t  mfg_date[6];                            // MFG_DATE 生产日期 (BCD)
    uint16_t ovp;                                    // OVP     末次过压值 (mV)
    uint16_t ovp_max;                                // OVP_MAX 1小时过压峰值 (mV)
    int16_t  otp;                                    // OTP     末次过温值 (0.1°C)
    int16_t  otp_max;                                // OTP_MAX 1小时过温峰值 (0.1°C)
    uint8_t  err_time[6];                            // ERR_TIME 异常时间 (BCD)
    uint16_t err_cnt;                                // ERR_CNT 累计异常次数
    uint8_t  r_err;                                  // R_ERR   内阻异常 (0/1)
    uint8_t  uid_err;                                // UID_ERR UID异常 (0/1)
    uint16_t liq_cnt;                                // LIQ_CN  进液次数
} prod_test_data_t;
#pragma pack()

/* ---- 产测运行时数据 (仅 SRAM) ---- */
typedef struct {
    prod_test_state_t state;
    uint8_t           unlocked;
    uint32_t          unlock_deadline;
    uint32_t          ng_lock_tick;
    uint8_t           ng_led_toggle;
    uint32_t          last_report_tick;
} prod_test_rt_t;

/* ---- 公开 API ---- */
void prod_test_init(void);
void prod_test_proc(void);
uint32_t Secure_Sign(const uint8_t *uid, uint32_t key);
uint8_t  CheckUnlock(const uint8_t *uid, uint16_t uid_len, uint32_t unlock_code);

/* ---- 辅助: 字节转十六进制字符 ---- */
static __inline uint8_t pt_nibble_to_hex(uint8_t nibble)
{
    return (nibble < 10) ? (nibble + '0') : (nibble - 10 + 'A');
}

#endif /* __PROD_TEST_H */
