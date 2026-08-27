#ifndef __SW_I2C_GEN_H
#define __SW_I2C_GEN_H

#include "global_define.h"

typedef struct
{
	GPIO_TypeDef *scl_port;
	uint32_t      scl_pin;
	GPIO_TypeDef *sda_port;
	uint32_t      sda_pin;
} sw_i2c_gen_t;

void     sw_i2c_gen_init(sw_i2c_gen_t *i2c);
void     sw_i2c_gen_start(sw_i2c_gen_t *i2c);
void     sw_i2c_gen_restart(sw_i2c_gen_t *i2c);
void     sw_i2c_gen_stop(sw_i2c_gen_t *i2c);
uint8_t  sw_i2c_gen_write_byte(sw_i2c_gen_t *i2c, uint8_t data);
uint8_t  sw_i2c_gen_read_byte(sw_i2c_gen_t *i2c, uint8_t ack);
uint8_t  sw_i2c_gen_ping(sw_i2c_gen_t *i2c, uint8_t sla);

#endif
