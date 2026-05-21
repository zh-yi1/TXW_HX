#include "g020.h"
#include "sw_i2c_gen.h"

static sw_i2c_gen_t i2c_g020 = {GPIOA, MD_GPIO_PIN_5, GPIOA, MD_GPIO_PIN_6};

volatile g020_data_t g020_data;

void g020_init(void)
{
	sw_i2c_gen_init(&i2c_g020);
}

uint8_t g020_write_reg(uint8_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t sla_w = (uint8_t)(G020_SLAVE_ADDR << 1);
	uint8_t i;

	if (len == 0 || buf == 0)
		return 1;

	sw_i2c_gen_start(&i2c_g020);
	if (sw_i2c_gen_write_byte(&i2c_g020, sla_w))
		goto err;
	if (sw_i2c_gen_write_byte(&i2c_g020, reg))
		goto err;

	for (i = 0; i < len; i++)
	{
		if (sw_i2c_gen_write_byte(&i2c_g020, buf[i]))
			goto err;
	}

	sw_i2c_gen_stop(&i2c_g020);
	return 0;

err:
	sw_i2c_gen_stop(&i2c_g020);
	return 1;
}

uint8_t g020_read_reg(uint8_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t sla_w = (uint8_t)(G020_SLAVE_ADDR << 1);
	uint8_t sla_r = sla_w | 1U;
	uint8_t i;

	if (len == 0 || buf == 0)
		return 1;

	sw_i2c_gen_start(&i2c_g020);
	if (sw_i2c_gen_write_byte(&i2c_g020, sla_w))
		goto err;
	if (sw_i2c_gen_write_byte(&i2c_g020, reg))
		goto err;

	sw_i2c_gen_restart(&i2c_g020);
	if (sw_i2c_gen_write_byte(&i2c_g020, sla_r))
		goto err;

	for (i = 0; i < len; i++)
		buf[i] = sw_i2c_gen_read_byte(&i2c_g020, (i == (len - 1)) ? 0 : 1);

	sw_i2c_gen_stop(&i2c_g020);
	return 0;

err:
	sw_i2c_gen_stop(&i2c_g020);
	return 1;
}

void g020_proc(uint8_t bat_soc, uint8_t bat_low)
{
	static uint32_t last_tick;
	uint32_t now = md_get_tick();
	uint8_t val;

	if (now - last_tick < G020_POLL_MS)
		return;
	last_tick = now;

	/* Write battery: 0x00 */
	val = (bat_soc & G020_BAT_SOC_MSK);
	if (bat_low)
		val |= G020_BAT_LOW;
	g020_write_reg(G020_REG_BATTERY, &val, 1);

	/* Read 0x01-0x09 in one burst */
	g020_read_reg(G020_REG_USB1_STATUS, (uint8_t *)&g020_data, 9);
}
