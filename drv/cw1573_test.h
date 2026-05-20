#ifndef __CW1573_TEST_H
#define __CW1573_TEST_H

#include "global_define.h"

typedef struct
{
	uint8_t comm_ok;       /* 1 = I2C communication OK */
	uint8_t write_read_ok; /* 1 = write+readback matched */
	uint8_t rst_flag;      /* STATE_FLAG2 bit0: 1 = power-on reset detected */
	uint8_t sleep_flag;    /* STATE_FLAG1 bit5: 1 = chip in sleep */
	uint8_t do_pin;        /* STATE_FLAG2 bit7: 1 = DO on */
	uint8_t co_pin;        /* STATE_FLAG2 bit6: 1 = CO on */
	uint8_t chg_state;     /* STATE_FLAG2 bit4: 1 = charging */
	uint8_t dsg_state;     /* STATE_FLAG2 bit5: 1 = discharging */

	uint16_t vcell[7];     /* cell voltages, raw ADC */
	uint16_t ts_adc;       /* TS ADC value */
	int16_t  ts_temp;      /* TS temperature in 0.1C (NTC 103AT B=3435) */
	uint16_t iadc;         /* current ADC */
	int32_t  current_ma;   /* current in mA (RSENSE=2.5mR) */
	uint32_t cc;           /* coulomb counter raw */
	uint32_t cc_mah;       /* coulomb counter in mAh */

	uint8_t read_all_ok;   /* 1 = read_all passed */
} cw1573_test_result_t;

void cw1573_test_run(cw1573_test_result_t *r);

#endif
