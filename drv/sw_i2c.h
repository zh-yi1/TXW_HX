#ifndef __SW_I2C_H
#define __SW_I2C_H

#include "global_define.h"

#define SW_I2C_SCL_PORT     GPIOA
#define SW_I2C_SCL_PIN      MD_GPIO_PIN_5

#define SW_I2C_SDA_PORT     GPIOA
#define SW_I2C_SDA_PIN      MD_GPIO_PIN_14

#define SW_I2C_DELAY_US     5U

void sw_i2c_init(void);
void sw_i2c_start(void);
void sw_i2c_restart(void);
void sw_i2c_stop(void);
uint8_t sw_i2c_write_byte(uint8_t data);
uint8_t sw_i2c_read_byte(uint8_t ack);
uint8_t sw_i2c_ping(uint8_t sla);

#endif
