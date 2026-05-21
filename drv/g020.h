#ifndef __G020_H
#define __G020_H

#include "global_define.h"

/* G020 I2C 7-bit slave address (placeholder) */
#define G020_SLAVE_ADDR         0x00U

/* Register addresses */
#define G020_REG_BATTERY        0x00U
#define G020_REG_USB1_STATUS    0x01U
#define G020_REG_USB1_POWER     0x02U
#define G020_REG_USB2_STATUS    0x03U
#define G020_REG_USB2_POWER     0x04U
#define G020_REG_USB3_STATUS    0x05U
#define G020_REG_USB3_POWER     0x06U
#define G020_REG_TEMPERATURE    0x07U
#define G020_REG_WARNING        0x08U
#define G020_REG_SLEEP          0x09U

/* 0x00 battery: bit[7] = low battery */
#define G020_BAT_LOW           0x80U
#define G020_BAT_SOC_MSK       0x7FU

/* USB status values */
#define G020_USB_DISCONNECTED  0x00U
#define G020_USB_CHARGING      0x01U
#define G020_USB_DISCHARGING   0x02U

#define G020_POLL_MS  1000U

#pragma pack(1)
typedef struct
{
	uint8_t usb1_status;
	uint8_t usb1_power;
	uint8_t usb2_status;
	uint8_t usb2_power;
	uint8_t usb3_status;
	uint8_t usb3_power;
	uint8_t temperature;
	uint8_t warning;
	uint8_t sleep;
} g020_data_t;
#pragma pack()

extern volatile g020_data_t g020_data;

void    g020_init(void);
uint8_t g020_read_reg(uint8_t reg, uint8_t *buf, uint8_t len);
uint8_t g020_write_reg(uint8_t reg, uint8_t *buf, uint8_t len);
void    g020_proc(uint8_t bat_soc, uint8_t bat_low);

#endif
