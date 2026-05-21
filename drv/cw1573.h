#ifndef __CW1573_H
#define __CW1573_H

#include "global_define.h"

/* CW1573 I2C 7-bit slave address */
#define CW1573_SLAVE_ADDR       0x33U

/* --- Register addresses --- */
#define CW1573_REG_STATE_FLAG0  0x00U
#define CW1573_REG_STATE_FLAG1  0x01U
#define CW1573_REG_STATE_FLAG2  0x02U
#define CW1573_REG_INT_SET      0x03U
#define CW1573_REG_BAL_SET      0x04U
#define CW1573_REG_CONFIG0      0x05U
#define CW1573_REG_CONFIG1      0x06U
#define CW1573_REG_CONFIG2      0x07U
#define CW1573_REG_VOV          0x08U
#define CW1573_REG_VOVR         0x09U
#define CW1573_REG_VUV          0x0AU
#define CW1573_REG_VUVR         0x0BU
#define CW1573_REG_COT_H        0x0CU
#define CW1573_REG_COTR_HYS     0x0DU
#define CW1573_REG_CUT_H        0x0EU
#define CW1573_REG_CUTR_HYS     0x0FU
#define CW1573_REG_DOT_H        0x10U
#define CW1573_REG_DOTR_HYS     0x11U
#define CW1573_REG_DUT_H        0x12U
#define CW1573_REG_DUTR_HYS     0x13U
#define CW1573_REG_VDOC1        0x14U
#define CW1573_REG_VDOC2        0x15U
#define CW1573_REG_VCOC         0x16U
#define CW1573_REG_IADC_DET     0x17U
#define CW1573_REG_VSC_TSC      0x18U
#define CW1573_REG_TOV_TUV      0x19U
#define CW1573_REG_CELL1_H      0x20U
#define CW1573_REG_CELL1_L      0x21U
#define CW1573_REG_CELL2_H      0x22U
#define CW1573_REG_CELL2_L      0x23U
#define CW1573_REG_CELL3_H      0x24U
#define CW1573_REG_CELL3_L      0x25U
#define CW1573_REG_CELL4_H      0x26U
#define CW1573_REG_CELL4_L      0x27U
#define CW1573_REG_CELL5_H      0x28U
#define CW1573_REG_CELL5_L      0x29U
#define CW1573_REG_CELL6_H      0x2AU
#define CW1573_REG_CELL6_L      0x2BU
#define CW1573_REG_CELL7_H      0x2CU
#define CW1573_REG_CELL7_L      0x2DU
#define CW1573_REG_TS_H         0x2EU
#define CW1573_REG_TS_L         0x2FU
#define CW1573_REG_IADC_H       0x30U
#define CW1573_REG_IADC_L       0x31U
#define CW1573_REG_CC3          0x32U
#define CW1573_REG_CC2          0x33U
#define CW1573_REG_CC1          0x34U
#define CW1573_REG_CC0          0x35U

/* --- STATE_FLAG0 (0x00) bits --- */
#define CW1573_OV_FLAG          0x80U
#define CW1573_UV_FLAG          0x40U
#define CW1573_TS_FLAG          0x20U
#define CW1573_SC_FLAG          0x10U
#define CW1573_DOC_FLAG         0x08U
#define CW1573_COC_FLAG         0x04U
#define CW1573_I2C_FLAG         0x02U
#define CW1573_WDT_FLAG         0x01U

/* --- STATE_FLAG1 (0x01) bits --- */
#define CW1573_DCTL_PIN         0x80U
#define CW1573_VM_PIN           0x40U
#define CW1573_SLEEP_FLAG       0x20U

/* --- STATE_FLAG2 (0x02) bits --- */
#define CW1573_DO_PIN           0x80U
#define CW1573_CO_PIN           0x40U
#define CW1573_DSG_STATE        0x20U
#define CW1573_CHG_STATE        0x10U
#define CW1573_CHG_IN           0x08U
#define CW1573_TEMP_FLAG        0x02U
#define CW1573_RST_FLAG         0x01U

/* --- INT_SET (0x03) bits --- */
#define CW1573_OVUV_INT         0x80U
#define CW1573_IDET_INT         0x40U
#define CW1573_DOCCOCSC_INT     0x20U
#define CW1573_TS_INT           0x10U
#define CW1573_VADC_INT         0x08U
#define CW1573_IADC_INT         0x04U
#define CW1573_IIC_INT          0x02U
#define CW1573_WDT_INT          0x01U

/* --- BAL_SET (0x04) bits --- */
#define CW1573_EN_BAL           0x80U

/* --- CONFIG0 (0x05) bits --- */
#define CW1573_EN_ICN           0x80U
#define CW1573_EN_WDT           0x40U
#define CW1573_EN_TS            0x10U
#define CW1573_CC_CLR           0x08U
#define CW1573_CN_3S            0x03U
#define CW1573_CN_4S            0x04U
#define CW1573_CN_5S            0x05U
#define CW1573_CN_6S            0x06U
#define CW1573_CN_7S            0x07U

/* --- CONFIG1 (0x06) bits --- */
#define CW1573_RST              0x80U
#define CW1573_LD               0x20U
#define CW1573_EXIT_SLEEP       0x10U
#define CW1573_EN_CO            0x08U
#define CW1573_EN_DO            0x04U
#define CW1573_EN_VADC          0x02U
#define CW1573_EN_IADC          0x01U

/* --- CONFIG2 (0x07) bits --- */
#define CW1573_EN_DCTL          0x80U
#define CW1573_EN_OT            0x40U
#define CW1573_EN_DOC_COC       0x20U
#define CW1573_EN_SC            0x10U
#define CW1573_UVR_LD           0x08U
#define CW1573_DTR_LD           0x04U
#define CW1573_CHG_DOV_HYS      0x02U
#define CW1573_DSG_COV_HYS      0x01U

/* --- CRC-8 polynomial: X^8 + X^2 + X + 1 --- */
#define CW1573_CRC8_POLY        0x07U

/* --- Data structure for reading all CW1573 data --- */
#pragma pack(1)
typedef struct
{
	uint8_t  state_flag0;
	uint8_t  state_flag1;
	uint8_t  state_flag2;
	uint16_t vcell[7];
	uint16_t ts_adc;
	uint16_t iadc;
	uint32_t cc;
} cw1573_data_t;
#pragma pack()

/* INT/SLEEP pin */
#define CW1573_INT_PORT         GPIOA
#define CW1573_INT_PIN          MD_GPIO_PIN_13

/* Processed data (human-readable) */
typedef struct
{
	float    vcell_v[7];
	float    pack_v;
	int16_t  temp_01c;
	int32_t  current_ma;
	uint32_t cc_mah;
} cw1573_proc_data_t;

void cw1573_init(uint8_t cell_count);
uint8_t cw1573_read_reg(uint8_t reg, uint8_t *buf, uint8_t len);
uint8_t cw1573_write_reg(uint8_t reg, uint8_t *buf, uint8_t len);
uint8_t cw1573_read_all(cw1573_data_t *data);
void cw1573_calc_data(cw1573_data_t *raw, cw1573_proc_data_t *proc);

#define CW1573_POLL_MS  500U

extern volatile cw1573_data_t      cw1573_raw;
extern volatile cw1573_proc_data_t cw1573_proc;

void cw1573_proc(void);

#endif
