#include "cw1573.h"

volatile cw1573_data_t      cw1573_raw;
volatile cw1573_proc_data_t cw1573_info;

uint8_t cw1573_cell_cnt = 4;
static uint8_t cw1573_cfg_done  = 0;

uint8_t cw1573_is_ready(void)
{
	return cw1573_cfg_done;
}

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

static uint8_t cw1573_config_regs(uint8_t cell_count)
{
	uint8_t cfg;
	uint8_t res = 1;
	uint8_t rbuf[2];

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
	cw1573_cell_cnt = cell_count;

	sw_i2c_init();

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

	if (data == NULL)
		return 1;

	/* Read state flags: 0x00-0x02 */
	err |= cw1573_read_reg(CW1573_REG_STATE_FLAG0, &data->state_flag0, 1);
	err |= cw1573_read_reg(CW1573_REG_STATE_FLAG1, &data->state_flag1, 1);
	err |= cw1573_read_reg(CW1573_REG_STATE_FLAG2, &data->state_flag2, 1);

	/* Read VCELL1-7: 14 bytes burst from 0x20 */
	err |= cw1573_read_reg(CW1573_REG_CELL1_H, vcell_buf, cw1573_cell_cnt * 2);
	for (uint8_t i = 0; i < cw1573_cell_cnt; i++)
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

void cw1573_calc_data(cw1573_data_t *raw, cw1573_proc_data_t *p)
{
	if (raw == NULL || p == NULL) return;

	/* 电芯电压: Vcell(mV) = CELL * 78.125uV / 1000 = CELL * 78125 / 1000000 */
	p->pack_mv = 0;
	for (uint8_t i = 0; i < cw1573_cell_cnt; i++)
	{
		p->vcell_mv[i] = (uint16_t)((uint32_t)raw->vcell[i] * 78125UL / 1000000UL);
		p->pack_mv += p->vcell_mv[i];
	}

	/* NTC阻值: TS_ADC → Vntc(mV) → Rntc(Ω) */
	{
		uint16_t ts = raw->ts_adc;
		// 第15位为高，温度有效位
		if (ts & 0x8000U)
		{
			/* Vntc(mV) = TS * 78.125uV / 1000 = TS * 78125 / 1000000 */
			uint32_t vntc = (uint32_t)(ts & 0x7FFFU) * 78125UL / 1000000UL;
			if (vntc > 0 && vntc < 2545)
			{
				/* Rntc(Ω) = 10000 * Vntc / (2545 - Vntc) */
				p->rntc_ohm = 10000UL * vntc / (2545UL - vntc);
			}
		}
	}

	//TODO :确定采样电阻值是否是2.5mR
	/* 电流: I(mA) = IADC * 6.25uV / 2.5mR = IADC * 5 / 2 */
	{
		int16_t iadc_s = (int16_t)raw->iadc;
		p->current_ma = (int32_t)iadc_s * 5 / 2;
	}

	/* 电量: mAh = CC * 6.25uV / 2.5mR / 3600 = CC / 1440 */
	p->cc_mah = raw->cc / 1440UL;
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
