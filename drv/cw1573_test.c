#include "cw1573_test.h"
#include "cw1573.h"

void cw1573_test_run(cw1573_test_result_t *r)
{
	uint8_t ack;

	if (r == 0) return;
	*r = (cw1573_test_result_t){0};

	/* Init GPIO, leave CW1573 registers alone */
	sw_i2c_init();

	/* Test 1: raw ping -- does any device ACK addr 0x33? */
	ack = sw_i2c_ping((uint8_t)(CW1573_SLAVE_ADDR << 1));
	r->comm_ok = (ack == 0) ? 1 : 0;

	/* Test 2: if ping ok, try a register read with CRC */
	if (r->comm_ok)
	{
		uint8_t buf;
		if (cw1573_read_reg(CW1573_REG_STATE_FLAG2, &buf, 1) == 0)
		{
			r->rst_flag   = (buf & CW1573_RST_FLAG)   ? 1 : 0;
			r->do_pin     = (buf & CW1573_DO_PIN)     ? 1 : 0;
			r->co_pin     = (buf & CW1573_CO_PIN)     ? 1 : 0;
			r->dsg_state  = (buf & CW1573_DSG_STATE)  ? 1 : 0;
			r->chg_state  = (buf & CW1573_CHG_STATE)  ? 1 : 0;
		}
	}

	/* Test 3: if CRC read ok, try a write+readback on BAL_SET */
	if (r->comm_ok)
	{
		uint8_t orig, test_val, rb;
		if (cw1573_read_reg(CW1573_REG_BAL_SET, &orig, 1) != 0)
			return;
		test_val = 0xA5;
		if (cw1573_write_reg(CW1573_REG_BAL_SET, &test_val, 1) != 0)
			return;
		if (cw1573_read_reg(CW1573_REG_BAL_SET, &rb, 1) != 0)
			return;
		cw1573_write_reg(CW1573_REG_BAL_SET, &orig, 1);
		r->write_read_ok = (rb == test_val) ? 1 : 0;
	}
}
