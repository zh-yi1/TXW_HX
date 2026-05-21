#include "sw_i2c_gen.h"

#define I2C_TIMEOUT  1000U

static void i2c_scl_set(sw_i2c_gen_t *i2c, uint8_t val)
{
	if (val)
		md_gpio_set_pin_high(i2c->scl_port, i2c->scl_pin);
	else
		md_gpio_set_pin_low(i2c->scl_port, i2c->scl_pin);
}

static void i2c_sda_set(sw_i2c_gen_t *i2c, uint8_t val)
{
	if (val)
		md_gpio_set_pin_high(i2c->sda_port, i2c->sda_pin);
	else
		md_gpio_set_pin_low(i2c->sda_port, i2c->sda_pin);
}

static uint8_t i2c_sda_get(sw_i2c_gen_t *i2c)
{
	return md_gpio_get_input_data(i2c->sda_port, i2c->sda_pin);
}

static uint8_t i2c_scl_get(sw_i2c_gen_t *i2c)
{
	return md_gpio_get_input_data(i2c->scl_port, i2c->scl_pin);
}

#define I2C_DELAY_HALF()   md_delay_1us(1)
#define I2C_DELAY_FULL()   md_delay_1us(2)

static int32_t i2c_scl_high(sw_i2c_gen_t *i2c)
{
	uint32_t start;

	i2c_scl_set(i2c, 1);
	start = md_get_tick();
	while (!i2c_scl_get(i2c))
	{
		if ((md_get_tick() - start) > I2C_TIMEOUT)
			return -1;
		I2C_DELAY_HALF();
	}
	I2C_DELAY_FULL();
	return 0;
}

void sw_i2c_gen_init(sw_i2c_gen_t *i2c)
{
	md_gpio_init_t g;

	md_gpio_init_struct(&g);
	g.odos = MD_GPIO_OPEN_DRAIN;
	g.odrv = MD_GPIO_OUT_DRIVE_STRONG;
	md_gpio_init(i2c->scl_port, i2c->scl_pin, &g);
	md_gpio_init(i2c->sda_port, i2c->sda_pin, &g);

	i2c_sda_set(i2c, 1);
	i2c_scl_set(i2c, 1);
}

void sw_i2c_gen_start(sw_i2c_gen_t *i2c)
{
	i2c_sda_set(i2c, 0);
	I2C_DELAY_HALF();
	i2c_scl_set(i2c, 0);
}

void sw_i2c_gen_restart(sw_i2c_gen_t *i2c)
{
	i2c_sda_set(i2c, 1);
	i2c_scl_set(i2c, 1);
	I2C_DELAY_HALF();
	I2C_DELAY_HALF();
	i2c_sda_set(i2c, 0);
	I2C_DELAY_HALF();
	i2c_scl_set(i2c, 0);
}

void sw_i2c_gen_stop(sw_i2c_gen_t *i2c)
{
	i2c_sda_set(i2c, 0);
	I2C_DELAY_HALF();
	i2c_scl_high(i2c);
	i2c_sda_set(i2c, 1);
	I2C_DELAY_FULL();
}

uint8_t sw_i2c_gen_write_byte(sw_i2c_gen_t *i2c, uint8_t data)
{
	uint8_t bit, ack;

	for (int32_t i = 7; i >= 0; i--)
	{
		i2c_scl_set(i2c, 0);
		bit = (data >> i) & 1;
		i2c_sda_set(i2c, bit);
		I2C_DELAY_HALF();
		i2c_scl_high(i2c);
	}
	i2c_scl_set(i2c, 0);
	I2C_DELAY_HALF();

	i2c_sda_set(i2c, 1);
	I2C_DELAY_HALF();
	i2c_scl_high(i2c);
	ack = i2c_sda_get(i2c);
	i2c_scl_set(i2c, 0);

	return ack;
}

uint8_t sw_i2c_gen_read_byte(sw_i2c_gen_t *i2c, uint8_t ack)
{
	uint8_t data = 0;

	i2c_sda_set(i2c, 1);
	I2C_DELAY_HALF();

	for (uint8_t i = 0; i < 8; i++)
	{
		data <<= 1;
		i2c_scl_high(i2c);
		if (i2c_sda_get(i2c))
			data |= 1;
		i2c_scl_set(i2c, 0);
		I2C_DELAY_HALF();
	}

	if (ack)
		i2c_sda_set(i2c, 0);
	I2C_DELAY_HALF();
	i2c_scl_high(i2c);
	i2c_scl_set(i2c, 0);

	return data;
}

uint8_t sw_i2c_gen_ping(sw_i2c_gen_t *i2c, uint8_t sla)
{
	uint8_t ack;

	sw_i2c_gen_start(i2c);
	ack = sw_i2c_gen_write_byte(i2c, sla);
	sw_i2c_gen_stop(i2c);

	return ack;
}
