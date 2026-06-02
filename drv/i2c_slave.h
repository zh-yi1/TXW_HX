#ifndef __I2C_SLAVE_H
#define __I2C_SLAVE_H

#include "global_define.h"

/* ---- I2C 从机地址 (7-bit) ---- */
#define I2C_SLAVE_ADDR          0x2D

/* ---- 寄存器地址定义 ---- */

/* 主机信息 (W) */
#define REG_HOST_FW_VER_L       0x00
#define REG_HOST_FW_VER_H       0x01
#define REG_ONLINE_CRC          0x02

/* 电池数据 (W) */
#define REG_SOC                 0x10
#define REG_SOH                 0x11
#define REG_CYCLE_L             0x12
#define REG_CYCLE_H             0x13
#define REG_RUN_TIME_L          0x14
#define REG_RUN_TIME_H          0x15
#define REG_V1_L                0x16
#define REG_V1_H                0x17
#define REG_V2_L                0x18
#define REG_V2_H                0x19
#define REG_V3_L                0x1A
#define REG_V3_H                0x1B
#define REG_V4_L                0x1C
#define REG_V4_H                0x1D
#define REG_VPACK_L             0x1E
#define REG_VPACK_H             0x1F
#define REG_BAT_CURRENT_L       0x20
#define REG_BAT_CURRENT_H       0x21
#define REG_NTC1_L              0x22
#define REG_NTC1_H              0x23
#define REG_NTC2_L              0x24
#define REG_NTC2_H              0x25
#define REG_AFE_PROTECT         0x26
#define REG_OVP_PERMANENT       0x27

/* 端口数据 (W) */
#define REG_C1_STATUS           0x50
#define REG_C1_VOLTAGE_L        0x51
#define REG_C1_VOLTAGE_H        0x52
#define REG_C1_CURRENT_L        0x53
#define REG_C1_CURRENT_H        0x54
#define REG_C2_STATUS           0x55
#define REG_C2_VOLTAGE_L        0x56
#define REG_C2_VOLTAGE_H        0x57
#define REG_C2_CURRENT_L        0x58
#define REG_C2_CURRENT_H        0x59
#define REG_USBA_STATUS         0x5A
#define REG_USBA_VOLTAGE_L      0x5B
#define REG_USBA_VOLTAGE_H      0x5C
#define REG_USBA_CURRENT_L      0x5D
#define REG_USBA_CURRENT_H      0x5E

/* 保护状态 (W/R) */
#define REG_PROTECT_FLAG_L      0x60
#define REG_PROTECT_FLAG_H      0x61

/* 按键事件 (R, 可被主机读后清零对应 bit) */
#define REG_KEY_EVENT           0x70

/* 系统信息 (R) */
#define REG_FW_VERSION_L        0xF0
#define REG_FW_VERSION_H        0xF1
#define REG_TFT_ONLINE_CRC      0xF2

/* ---- 寄存器缓冲区 ---- */
extern volatile uint8_t i2c_reg_map[256];

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

#endif /* __I2C_SLAVE_H */
