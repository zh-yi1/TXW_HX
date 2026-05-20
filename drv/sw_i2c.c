#include "sw_i2c.h"

#define I2C_TIMEOUT  1000U

static void i2c_scl_set(uint8_t val)
{
	if (val)
		md_gpio_set_pin_high(SW_I2C_SCL_PORT, SW_I2C_SCL_PIN);
	else
		md_gpio_set_pin_low(SW_I2C_SCL_PORT, SW_I2C_SCL_PIN);
}

static void i2c_sda_set(uint8_t val)
{
	if (val)
		md_gpio_set_pin_high(SW_I2C_SDA_PORT, SW_I2C_SDA_PIN);
	else
		md_gpio_set_pin_low(SW_I2C_SDA_PORT, SW_I2C_SDA_PIN);
}

static uint8_t i2c_sda_get(void)
{
	return md_gpio_get_input_data(SW_I2C_SDA_PORT, SW_I2C_SDA_PIN);
}

static uint8_t i2c_scl_get(void)
{
	return md_gpio_get_input_data(SW_I2C_SCL_PORT, SW_I2C_SCL_PIN);
}

#define I2C_DELAY_HALF()   md_delay_1us(1)
#define I2C_DELAY_FULL()   md_delay_1us(2)

static int32_t i2c_scl_high(void)
{
	uint32_t start;

	i2c_scl_set(1);
	start = md_get_tick();
	while (!i2c_scl_get())
	{
		if ((md_get_tick() - start) > I2C_TIMEOUT)
			return -1;
		I2C_DELAY_HALF();
	}
	I2C_DELAY_FULL();
	return 0;
}

void sw_i2c_init(void)
{
	md_gpio_init_t g;

	md_gpio_init_struct(&g);
	g.odos = MD_GPIO_OPEN_DRAIN;
	g.odrv = MD_GPIO_OUT_DRIVE_STRONG;
	md_gpio_init(SW_I2C_SCL_PORT, SW_I2C_SCL_PIN, &g);
	md_gpio_init(SW_I2C_SDA_PORT, SW_I2C_SDA_PIN, &g);

	i2c_sda_set(1);
	i2c_scl_set(1);
}

void sw_i2c_start(void)
{
	i2c_sda_set(0);
	I2C_DELAY_HALF();
	i2c_scl_set(0);
}

void sw_i2c_restart(void)
{
	i2c_sda_set(1);
	i2c_scl_set(1);
	I2C_DELAY_HALF();
	I2C_DELAY_HALF();
	i2c_sda_set(0);
	I2C_DELAY_HALF();
	i2c_scl_set(0);
}

void sw_i2c_stop(void)
{
	i2c_sda_set(0);
	I2C_DELAY_HALF();
	i2c_scl_high();
	i2c_sda_set(1);
	I2C_DELAY_FULL();
}

uint8_t sw_i2c_write_byte(uint8_t data)
{
	uint8_t bit, ack;

	for (int32_t i = 7; i >= 0; i--)
	{
		i2c_scl_set(0);
		bit = (data >> i) & 1;
		i2c_sda_set(bit);
		I2C_DELAY_HALF();
		i2c_scl_high();
	}
	i2c_scl_set(0);
	I2C_DELAY_HALF();

	i2c_sda_set(1);
	I2C_DELAY_HALF();
	i2c_scl_high();
	ack = i2c_sda_get();
	i2c_scl_set(0);

	return ack;
}

uint8_t sw_i2c_read_byte(uint8_t ack)
{
	uint8_t data = 0;

	i2c_sda_set(1);
	I2C_DELAY_HALF();

	for (uint8_t i = 0; i < 8; i++)
	{
		data <<= 1;
		i2c_scl_high();
		if (i2c_sda_get())
			data |= 1;
		i2c_scl_set(0);
		I2C_DELAY_HALF();
	}

	if (ack)
		i2c_sda_set(0);
	I2C_DELAY_HALF();
	i2c_scl_high();
	i2c_scl_set(0);

	return data;
}

uint8_t sw_i2c_ping(uint8_t sla)
{
	uint8_t ack;

	sw_i2c_start();
	ack = sw_i2c_write_byte(sla);
	sw_i2c_stop();

	return ack;
}
