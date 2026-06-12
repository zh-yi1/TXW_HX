#ifndef __I2C_SLAVE_H
#define __I2C_SLAVE_H

#include "global_define.h"

/* ---- I2C 从机地址 (7-bit) ---- */
#define I2C_SLAVE_ADDR          0x2D

/* ---- 寄存器地址定义 (协议 V1.1) ---- */

/* 主机信息 §4.1 (0x00~0x0F) — 主机 → 从机 */
#define REG_HOST_FW_VER_L       0x00
#define REG_HOST_FW_VER_H       0x01
#define REG_ONLINE_CRC          0x02

/* 电池数据 §4.2 (0x10~0x1F) — 主机 → 从机 */
#define REG_SOC                 0x10
#define REG_SOH                 0x11
#define REG_CYCLE_L             0x12
#define REG_CYCLE_H             0x13
#define REG_CHARGE_REMAIN_0     0x14
#define REG_CHARGE_REMAIN_1     0x15
#define REG_CHARGE_REMAIN_2     0x16
#define REG_CHARGE_REMAIN_3     0x17
#define REG_DISCHARGE_REMAIN_0  0x18
#define REG_DISCHARGE_REMAIN_1  0x19
#define REG_DISCHARGE_REMAIN_2  0x1A
#define REG_DISCHARGE_REMAIN_3  0x1B
#define REG_RES_VBAT_L          0x1C
#define REG_RES_VBAT_H          0x1D

/* NTC 数据 §4.3 (0x20~0x3F) — 主机 → 从机 */
#define REG_NTC_STATUS          0x20
#define REG_BAT_NTC1_0          0x21
#define REG_BAT_NTC1_1          0x22
#define REG_BAT_NTC1_2          0x23
#define REG_BAT_NTC1_3          0x24
#define REG_BAT_NTC2_0          0x25
#define REG_BAT_NTC2_1          0x26
#define REG_BAT_NTC2_2          0x27
#define REG_BAT_NTC2_3          0x28
#define REG_PCB_NTC1_0          0x29
#define REG_PCB_NTC1_1          0x2A
#define REG_PCB_NTC1_2          0x2B
#define REG_PCB_NTC1_3          0x2C
#define REG_PCB_NTC2_0          0x2D
#define REG_PCB_NTC2_1          0x2E
#define REG_PCB_NTC2_2          0x2F
#define REG_PCB_NTC2_3          0x30

/* 端口数据 §4.4 (0x40~0x4F) — 主机 → 从机 */
#define REG_C1_STATUS           0x40
#define REG_C1_VOLTAGE_L        0x41
#define REG_C1_VOLTAGE_H        0x42
#define REG_C1_CURRENT_L        0x43
#define REG_C1_CURRENT_H        0x44
#define REG_C2_STATUS           0x45
#define REG_C2_VOLTAGE_L        0x46
#define REG_C2_VOLTAGE_H        0x47
#define REG_C2_CURRENT_L        0x48
#define REG_C2_CURRENT_H        0x49
#define REG_USBA_STATUS         0x4A
#define REG_USBA_VOLTAGE_L      0x4B
#define REG_USBA_VOLTAGE_H      0x4C
#define REG_USBA_CURRENT_L      0x4D
#define REG_USBA_CURRENT_H      0x4E
#define REG_SMALL_CURRENT_MODE  0x4F

/* 电芯/AFE 数据 §4.5 (0x50~0x6F) — 主机 ← 从机 (R) */
#define REG_V1_L                0x50
#define REG_V1_H                0x51
#define REG_V2_L                0x52
#define REG_V2_H                0x53
#define REG_V3_L                0x54
#define REG_V3_H                0x55
#define REG_V4_L                0x56
#define REG_V4_H                0x57
#define REG_VPACK_L             0x58
#define REG_VPACK_H             0x59
#define REG_BAT_CURRENT_L       0x5A
#define REG_BAT_CURRENT_H       0x5B
#define REG_NTC1_0              0x5C
#define REG_NTC1_1              0x5D
#define REG_NTC1_2              0x5E
#define REG_NTC1_3              0x5F
#define REG_OVP_PERMANENT       0x60
#define REG_AFE_PROTECT1        0x61
#define REG_AFE_PROTECT2        0x62
#define REG_AFE_PROTECT3        0x63

/* 按键事件 §4.6 (0x70) — 主机 ← 从机 (R) / 主机 → 从机 (W) */
#define REG_KEY_EVENT           0x70

/* BMS 备用寄存器 §4.7 (0x71~0x7F) — 主机 ← 从机 */
#define REG_BMS_SOC             0x71
#define REG_BMS_SOH             0x72
#define REG_BMS_CYCLE_L         0x73
#define REG_BMS_CYCLE_H         0x74
#define REG_BMS_CHARGE_REMAIN_L 0x75
#define REG_BMS_CHARGE_REMAIN_H 0x76
#define REG_BMS_DISCHARGE_REMAIN_L 0x77
#define REG_BMS_DISCHARGE_REMAIN_H 0x78

/* 系统信息 §4.8 (0x80~0x8F) — 主机 ← 从机 */
#define REG_FW_VERSION_L        0x80
#define REG_FW_VERSION_H        0x81
#define REG_TFT_ONLINE_CRC      0x82
#define REG_UPDATE_CRC          0x83

/* ---- 寄存器缓冲区 (协议 V1.1 最大地址 0x8F, 共 144 字节) ---- */
extern volatile uint8_t i2c_reg_map[];

/* ---- 按键事件影子缓冲 (防主机清零竞争) ---- */
extern volatile uint8_t key_event_buf;  /* 协议 §4.6 */

/* ---- 对外接口 ---- */
void i2c_slave_init(void);
void i2c_slave_proc(void);

/* ---- I2C flag 清除辅助函数 (硬件序列清除) ---- */
__STATIC_INLINE void i2c_clear_flag_addr(I2C_TypeDef *i2c)
{
    __IO uint32_t tmpreg;
    tmpreg = i2c->STAT1;
    (void)tmpreg;
    tmpreg = i2c->STAT2;
    (void)tmpreg;
}

__STATIC_INLINE void i2c_clear_flag_stop(I2C_TypeDef *i2c)
{
    __IO uint32_t tmpreg;
    tmpreg = i2c->STAT1;
    (void)tmpreg;
    SET_BIT(i2c->CON1, I2C_CON1_PEN_MSK);
}

__STATIC_INLINE void i2c_clear_smbus_flag_alert(I2C_TypeDef *i2c)
{
    __IO uint32_t tmpreg;
    tmpreg = i2c->STAT1;
    (void)tmpreg;
    SET_BIT(i2c->CON1, I2C_CON1_PEN_MSK);
}

#endif /* __I2C_SLAVE_H */
