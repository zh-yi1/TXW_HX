#ifndef __IIC_H
#define __IIC_H

#include "global_define.h"

typedef enum
{
	IIC_BAT_SOC,
	IIC_DISP_CTRL,
	IIC_C1_WATT_H,
	IIC_C1_WATT_L,
	IIC_C2_WATT_H,
	IIC_C2_WATT_L,
	IIC_CHG_TIME_H,
	IIC_CHG_TIME_M,
	IIC_BAT_CYCLE_H,
	IIC_BAT_CYCLE_L,
	IIC_BAT_HEALTH,
	IIC_BAT_TEMP,
	IIC_SYS_STATUS,
	IIC_LANGUAGE_SET,
	
	IIC_REG_NUM,
}iic_reg_map_t;

#define I2C_SCL_PORT    GPIOA
#define I2C_SCL_PIN     MD_GPIO_PIN_5

#define I2C_SDA_PORT    GPIOA
#define I2C_SDA_PIN     MD_GPIO_PIN_6

__STATIC_INLINE void md_i2c_clear_flag_addr(I2C_TypeDef *i2c)
{
    __IO uint32_t tmpreg;
    tmpreg = i2c->STAT1;
    (void) tmpreg;
    tmpreg = i2c->STAT2;
    (void) tmpreg;
}

__STATIC_INLINE void md_i2c_clear_flag_stop(I2C_TypeDef *i2c)
{
    __IO uint32_t tmpreg;
    tmpreg = i2c->STAT1;
    (void) tmpreg;

    SET_BIT(i2c->CON1, I2C_CON1_PEN_MSK);
}
__STATIC_INLINE void md_i2c_clear_smbus_flag_alert(I2C_TypeDef *i2c)
{
    CLEAR_BIT(i2c->STAT1, I2C_STAT1_SMBALARM_MSK);
}

extern uint8_t iic_recv_buf[];
extern uint32_t iic_recv_len;
extern uint8_t iic_recv_ind;

extern uint8_t iic_send_buf[];
extern uint32_t iic_send_len;
extern uint8_t iic_send_ind;

extern uint8_t iic_send_add;

void iic_init(void);
void clear_buf(uint8_t *p);

#endif 
