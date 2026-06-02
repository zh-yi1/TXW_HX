#include "cw1573.h"

volatile cw1573_data_t      cw1573_raw;
volatile cw1573_proc_data_t cw1573_info;

static uint8_t cw1573_cell_cnt  = 4;
static uint8_t cw1573_cfg_done  = 0;

static uint8_t crc8_update(uint8_t crc, uint8_t data)
{
	crc ^= data;
	for (uint8_t i = 0; i < 8; i++)
	{
		if (crc & 0x80)
			crc = (uint8_t)((crc << 1) ^ CW1573_CRC8_POLY);
		else
			crc <<= 1;
	}
	return crc;
}

static uint8_t cw1573_config_regs_ref(uint8_t cell_count)
{
	uint8_t cfg;
	uint8_t res = 1;
	uint8_t rbuf[2];

	cfg = 0x94;
	cw1573_write_reg(0x05, &cfg, 1);
	if (cw1573_read_reg(0x05, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	// cfg = 0x97;
	cfg = 0x9F;
	cw1573_write_reg(0x06, &cfg, 1);
	if (cw1573_read_reg(0x06, rbuf, 1) || rbuf[0] != cfg)
		res = 0;
	
	// cfg = 0x17;
	cfg = 0x1F;
	cw1573_write_reg(0x06, &cfg, 1);
	if (cw1573_read_reg(0x06, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	cfg = 0x84;
	cw1573_write_reg(0x0A, &cfg, 1);
	if (cw1573_read_reg(0x0A, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	cfg = 0x55;
	cw1573_write_reg(0x14, &cfg, 1);
	if (cw1573_read_reg(0x14, rbuf, 1) || rbuf[0] != cfg)
		res = 0;
	
	cfg = 0x1A;
	cw1573_write_reg(0x16, &cfg, 1);
	if (cw1573_read_reg(0x16, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	return res;
}

static uint8_t cw1573_config_regs(uint8_t cell_count)
{
	uint8_t cfg;
	uint8_t res = 1;
	uint8_t rbuf[2];

	/* Wake up from sleep */
	md_gpio_set_pin_high(CW1573_INT_PORT, CW1573_INT_PIN);

	/* Exit any existing sleep state */
	// cfg = CW1573_EXIT_SLEEP;
	// cw1573_write_reg(CW1573_REG_CONFIG1, &cfg, 1);
	// if (cw1573_read_reg(CW1573_REG_CONFIG1, rbuf, 1) || rbuf[0] != cfg)
	// 	res = 0;

	/* INT_SET: enable OV/UV, DOC/COC/SC, TS, VADC, IADC interrupts */
	cfg = CW1573_OVUV_INT | CW1573_DOCCOCSC_INT | CW1573_TS_INT
	    | CW1573_VADC_INT | CW1573_IADC_INT;
	cw1573_write_reg(CW1573_REG_INT_SET, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_INT_SET, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* BAL_SET: disable balance by default */
	cfg = 0x00;
	cw1573_write_reg(CW1573_REG_BAL_SET, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_BAL_SET, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* CONFIG0: enable IC, TS, set cell count. WDT disabled (off). */
	cfg = 0x94;
	cw1573_write_reg(CW1573_REG_CONFIG0, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_CONFIG0, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* CONFIG1: exit sleep, enable VADC, IADC, CO, DO */
	// cfg = CW1573_RST | CW1573_EXIT_SLEEP | CW1573_EN_VADC | CW1573_EN_IADC | CW1573_EN_CO | CW1573_EN_DO;
	cfg = 0x9F;
	cw1573_write_reg(CW1573_REG_CONFIG1, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_CONFIG1, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* CONFIG1: exit sleep, enable VADC, IADC, CO, DO */
	// cfg = CW1573_EXIT_SLEEP | CW1573_EN_VADC | CW1573_EN_IADC | CW1573_EN_CO | CW1573_EN_DO;
	cfg = 0x1F;
	cw1573_write_reg(CW1573_REG_CONFIG1, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_CONFIG1, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* CONFIG2: enable DCTL, DOC/COC, SC, hysteresis */
	cfg = CW1573_EN_DCTL | CW1573_EN_DOC_COC | CW1573_EN_SC
	    | CW1573_CHG_DOV_HYS | CW1573_DSG_COV_HYS;
	cw1573_write_reg(CW1573_REG_CONFIG2, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_CONFIG2, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* VOV = 4.50V per cell (3300mV + 240*5mV) */
	cfg = 0xF0;
	cw1573_write_reg(CW1573_REG_VOV, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_VOV, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* VOVR = 4.20V per cell (3300mV + 180*5mV) */
	cfg = 0xB4;
	cw1573_write_reg(CW1573_REG_VOVR, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_VOVR, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* VUV = 2.72V per cell (1280mV + 144*10mV) */
	cfg = 0x90;
	cw1573_write_reg(CW1573_REG_VUV, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_VUV, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* VUVR = 3.00V per cell (1280mV + 172*10mV) */
	cfg = 0xAC;
	cw1573_write_reg(CW1573_REG_VUVR, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_VUVR, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* COT: charge over-temp threshold */
	cfg = 0x95;
	cw1573_write_reg(CW1573_REG_COT_H, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_COT_H, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* COTR: charge over-temp recovery hysteresis */
	cfg = 0x12;
	cw1573_write_reg(CW1573_REG_COTR_HYS, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_COTR_HYS, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* CUT: charge under-temp threshold */
	cfg = 0x7B;
	cw1573_write_reg(CW1573_REG_CUT_H, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_CUT_H, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* CUTR: charge under-temp recovery hysteresis */
	cfg = 0x97;
	cw1573_write_reg(CW1573_REG_CUTR_HYS, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_CUTR_HYS, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* DOT: discharge over-temp threshold */
	cfg = 0x5C;
	cw1573_write_reg(CW1573_REG_DOT_H, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_DOT_H, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* DOTR: discharge over-temp recovery hysteresis */
	cfg = 0x8C;
	cw1573_write_reg(CW1573_REG_DOTR_HYS, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_DOTR_HYS, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* DUT: discharge under-temp threshold */
	cfg = 0xC5;
	cw1573_write_reg(CW1573_REG_DUT_H, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_DUT_H, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* DUTR: discharge under-temp recovery hysteresis */
	cfg = 0x8F;
	cw1573_write_reg(CW1573_REG_DUTR_HYS, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_DUTR_HYS, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* DOC1: dischg OC1 27.5mV/11A (2s) */
	cfg = 0x42;
	cw1573_write_reg(CW1573_REG_VDOC1, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_VDOC1, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* DOC2: dischg OC2 38.4mV/15A (56ms) */
	cfg = 0x2C;
	cw1573_write_reg(CW1573_REG_VDOC2, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_VDOC2, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* COC: charge OC 14.4mV/5.76A (96ms) */
	cfg = 0x09;
	cw1573_write_reg(CW1573_REG_VCOC, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_VCOC, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* IDET: charge/discharge detection ~80mA */
	cfg = 0x77;
	cw1573_write_reg(CW1573_REG_IADC_DET, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_IADC_DET, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* SC/TSC/TDOCR/WDT: VSC=100mV, tSC=280us, tDOCR=64ms, tWDT=256s */
	cfg = 0x30;
	cw1573_write_reg(CW1573_REG_VSC_TSC, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_VSC_TSC, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	/* TOV/TUV: tOV=1s, tUV=1s, tBAL=16s */
	cfg = 0x50;
	cw1573_write_reg(CW1573_REG_TOV_TUV, &cfg, 1);
	if (cw1573_read_reg(CW1573_REG_TOV_TUV, rbuf, 1) || rbuf[0] != cfg)
		res = 0;

	return res;
}

void cw1573_init(uint8_t cell_count)
{
	md_gpio_init_t g;

	cw1573_cell_cnt = cell_count;

	sw_i2c_init();

	/* INT/SLEEP pin (PA13): output low to prevent Sleep3 entry */
	md_gpio_init_struct(&g);
	md_gpio_init(CW1573_INT_PORT, CW1573_INT_PIN, &g);
	md_gpio_set_pin_high(CW1573_INT_PORT, CW1573_INT_PIN);

	if (cw1573_config_regs(cell_count) != 0)
		cw1573_cfg_done = 1;
}

uint8_t cw1573_write_reg(uint8_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t i;
	uint8_t crc;
	uint8_t sla_w = (uint8_t)(CW1573_SLAVE_ADDR << 1);

	if (len == 0 || buf == 0)
		return 1;

	sw_i2c_start();
	if (sw_i2c_write_byte(sla_w))
	{
		sw_i2c_stop();
		return 1;
	}
	if (sw_i2c_write_byte(reg))
	{
		sw_i2c_stop();
		return 1;
	}

	crc = 0;
	crc = crc8_update(crc, sla_w);
	crc = crc8_update(crc, reg);

	for (i = 0; i < len; i++)
	{
		if (sw_i2c_write_byte(buf[i]))
		{
			sw_i2c_stop();
			return 1;
		}
		crc = crc8_update(crc, buf[i]);
		if (sw_i2c_write_byte(crc))
		{
			sw_i2c_stop();
			return 1;
		}
	}

	sw_i2c_stop();
	md_delay_1us(100);
	return 0;
}

uint8_t cw1573_read_reg(uint8_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t i;
	uint8_t crc, crc_rcvd;
	uint8_t sla_w = (uint8_t)(CW1573_SLAVE_ADDR << 1);
	uint8_t sla_r = sla_w | 1U;

	if (len == 0 || buf == 0)
		return 1;

	sw_i2c_start();
	if (sw_i2c_write_byte(sla_w))
	{
		sw_i2c_stop();
		return 1;
	}
	if (sw_i2c_write_byte(reg))
	{
		sw_i2c_stop();
		return 1;
	}

	/* Repeated start */
	sw_i2c_restart();
	if (sw_i2c_write_byte(sla_r))
	{
		sw_i2c_stop();
		return 1;
	}

	crc = 0;
	for (i = 0; i < len; i++)
	{
		buf[i] = sw_i2c_read_byte(1);
		crc = crc8_update(crc, buf[i]);
		crc_rcvd = sw_i2c_read_byte((i == (len - 1)) ? 0 : 1);
		if (crc != crc_rcvd)
		{
			sw_i2c_stop();
			return 1;
		}
	}

	sw_i2c_stop();
	md_delay_1us(100);
	return 0;
}

uint8_t cw1573_read_all(cw1573_data_t *data)
{
	uint8_t vcell_buf[14];
	uint8_t err = 0;

	if (data == 0)
		return 1;

	/* Read state flags: 0x00-0x02 */
	err |= cw1573_read_reg(CW1573_REG_STATE_FLAG0, &data->state_flag0, 1);
	err |= cw1573_read_reg(CW1573_REG_STATE_FLAG1, &data->state_flag1, 1);
	err |= cw1573_read_reg(CW1573_REG_STATE_FLAG2, &data->state_flag2, 1);

	/* Read VCELL1-7: 14 bytes burst from 0x20 */
	err |= cw1573_read_reg(CW1573_REG_CELL1_H, vcell_buf, 14);
	for (uint8_t i = 0; i < 7; i++)
		data->vcell[i] = (uint16_t)(((uint16_t)vcell_buf[i * 2] << 8) | vcell_buf[i * 2 + 1]);

	/* Read TS: 0x2E-0x2F */
	{
		uint8_t ts[2];
		err |= cw1573_read_reg(CW1573_REG_TS_H, ts, 2);
		data->ts_adc = (uint16_t)(((uint16_t)(ts[0] & 0x7F) << 8) | ts[1]);
	}

	/* Read IADC: 0x30-0x31 */
	{
		uint8_t ia[2];
		err |= cw1573_read_reg(CW1573_REG_IADC_H, ia, 2);
		data->iadc = (uint16_t)(((uint16_t)ia[0] << 8) | ia[1]);
	}

	/* Read CC: 0x32-0x35 (4 bytes burst) */
	{
		uint8_t cc[4];
		err |= cw1573_read_reg(CW1573_REG_CC3, cc, 4);
		data->cc = ((uint32_t)cc[0] << 24) | ((uint32_t)cc[1] << 16)
		         | ((uint32_t)cc[2] << 8)  |  cc[3];
	}

	return err;
}

static float cw1573_ln(float x)
{
	float r = 0.0f;
	while (x > 2.0f) { x /= 2.0f; r += 0.693147f; }
	while (x < 0.5f) { x *= 2.0f; r -= 0.693147f; }
	x -= 1.0f;
	r += x * (1.0f - x * (0.5f - x * (0.333333f - x * 0.25f)));
	return r;
}

void cw1573_calc_data(cw1573_data_t *raw, cw1573_proc_data_t *p)
{
	if (raw == 0 || p == 0) return;

	/* 电芯电压: Vcell = CELL * 78.125uV / 1000000 */
	p->pack_v = 0.0f;
	for (uint8_t i = 0; i < 7; i++)
	{
		p->vcell_v[i] = (float)raw->vcell[i] * 78.125f / 1000000.0f;
		p->pack_v += p->vcell_v[i];
	}

	/* NTC温度: TS_ADC -> Vntc(mV) -> Rn tc(ohm) -> Beta方程 -> °C */
	{
		uint16_t ts = raw->ts_adc & 0x7FFFU;                    /* 去掉bit15符号位 */
		float vntc = (float)ts * 78.125f / 1000.0f;              /* ADC值 -> mV */
		if (vntc > 0.0f && vntc < 2545.0f)
		{
			/* Rn tc = 10k * Vntc / (VREF - Vntc) , VREF=2545mV */
			float rntc = 10000.0f * vntc / (2545.0f - vntc);
			if (rntc > 0.0f)
			{
				/* Beta方程: 1/Tk = 1/298.15 + ln(R/10k)/3435 , B=3435, T25=25°C */
				float tk = 1.0f / (1.0f / 298.15f + cw1573_ln(rntc / 10000.0f) / 3435.0f);
				p->temp_01c = (int16_t)((tk - 273.15f) * 10.0f);  /* 开尔文 -> 0.1°C */
			}
		}
	}

	/* 电流: I(mA) = IADC(有符号) * 6.25uV / 2.5mR */
	{
		int16_t iadc_s = (int16_t)raw->iadc;
		p->current_ma = (int32_t)((float)iadc_s * 6.25f / 2.5f);
	}

	/* 电量: mAh = CC * 6.25uV / 2.5mR / 3600 */
	p->cc_mah = (uint32_t)((float)raw->cc * 6.25f / 2.5f / 3600.0f);
}

void cw1573_proc(void)
{
	static uint32_t last_tick;
	static uint32_t last_cfg_tick;
	uint32_t now = md_get_tick();

	/* Retry config if slave not responding */
	if (!cw1573_cfg_done)
	{
		if (now - last_cfg_tick >= CW1573_CFG_RETRY_MS)
		
		{
			last_cfg_tick = now;
			if (cw1573_config_regs(cw1573_cell_cnt) != 0)
				cw1573_cfg_done = 1;
			else
				return;
		}
		else
			return;
	}

	if (now - last_tick < CW1573_POLL_MS)
		return;
	last_tick = now;

	cw1573_read_all((cw1573_data_t *)&cw1573_raw);
}
