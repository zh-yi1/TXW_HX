#ifndef __UI_H
#define __UI_H

#include "global_define.h"
#include <stdbool.h>

#define SPI_CLK 				GPIOA
#define SPI_CLK_PIN 			MD_GPIO_PIN_10

#define SPI_MOSI 				GPIOA
#define SPI_MOSI_PIN 			MD_GPIO_PIN_11

#define SPI_MISO 				GPIOA
#define SPI_MISO_PIN 			MD_GPIO_PIN_12

#define LCD_RS					GPIOA
#define LCD_RS_PIN				MD_GPIO_PIN_8

#define LCD_RST					GPIOA
#define LCD_RST_PIN				MD_GPIO_PIN_7

#define LCD_CS					GPIOA
#define LCD_CS_PIN				MD_GPIO_PIN_3

#define LCD_BLK					GPIOA
#define LCD_BLK_PIN				MD_GPIO_PIN_1

#define FLASH_CS				GPIOA
#define FLASH_CS_PIN			MD_GPIO_PIN_9

#define TFT_EN					GPIOA
#define TFT_EN_PIN				MD_GPIO_PIN_4

#define LCD_CS_LOW() 			md_gpio_set_pin_low(LCD_CS, LCD_CS_PIN)
#define LCD_CS_HIGH() 			md_gpio_set_pin_high(LCD_CS, LCD_CS_PIN)

#define LCD_RS_LOW() 			md_gpio_set_pin_low(LCD_RS, LCD_RS_PIN)
#define LCD_RS_HIGH() 			md_gpio_set_pin_high(LCD_RS, LCD_RS_PIN)

#define LCD_RST_LOW() 			md_gpio_set_pin_low(LCD_RST, LCD_RST_PIN)
#define LCD_RST_HIGH()			md_gpio_set_pin_high(LCD_RST, LCD_RST_PIN)

#define LCD_BLK_LOW() 			md_gpio_set_pin_low(LCD_BLK, LCD_BLK_PIN)
#define LCD_BLK_HIGH()			md_gpio_set_pin_high(LCD_BLK, LCD_BLK_PIN)

#define FLASH_CS_CLR()			md_gpio_set_pin_low(FLASH_CS, FLASH_CS_PIN)
#define FLASH_CS_SET()			md_gpio_set_pin_high(FLASH_CS, FLASH_CS_PIN)

#define TFT_EN_CLR()			md_gpio_set_pin_low(TFT_EN, TFT_EN_PIN)
#define TFT_EN_SET()			md_gpio_set_pin_high(TFT_EN, TFT_EN_PIN)

#define FLASH_READ_BUF_SIZE		(1024)
#define LCD_POWER_ON_DELAY		(4)


typedef struct
{
	uint8_t x;
	uint8_t y;
	uint32_t img_addr;
} pos_and_addr_t;

typedef struct
{
	uint8_t x1;
	uint8_t y1;
	uint8_t x2;
	uint8_t y2;
} range_t;

/* 界面名称 */
typedef enum
{
	PAGE_DEFAULT            = 0,  /* 默认主页 (电量/端口功率) */
	PAGE_INFO_1             = 1,  /* 电池信息页1 (最大容量/循环次数/电池编号) */
	PAGE_INFO_2             = 2,  /* 电池信息页2 (温度/运行时间) */
	PAGE_OVER_TEMP          = 3,  /* 过温提示页 */
	PAGE_LOW_TEMP           = 4,  /* 低温提示页 */
	PAGE_SHORT_CIRCUIT      = 5,  /* 短路提示页 */

	PAGE_MAX,
} page_t;

/* 设备状态 */
typedef enum
{
	DEV_STATE_NORMAL = 0,  /* 正常状态 */
	DEV_STATE_SLEEP  = 1,  /* 休眠状态 */
} dev_state_t;

/* 警告类型 */
typedef enum
{
	WARNING_NONE           = 0,
	WARNING_OVER_TEMP      = 1,
	WARNING_LOW_TEMP       = 2,
	WARNING_SHORT_CIRCUIT  = 3,
} warning_t;

/* ================================================================
 * ui_data_t — 全 UI 通用数据体
 *
 * 由 I2C 从机接收主控下发的电池/端口状态数据，各页面共用此结构体
 * ================================================================ */
typedef struct
{
	uint8_t  bat_power;		/* 电池电量 0-100% */
	bool     is_charge;		/* 是否充电中 */
	bool     is_charge_last;	/* 上一轮的充电状态，用于检测变化 */
	uint8_t  usb_c1_status;		/* USB-C1 端口状态: 0=未连接 1=充电 2=放电 (协议 §4.3) */
	uint8_t  usb_c1_power;		/* USB-C1 实时功率 0-99W */
	uint8_t  usb_c1_status_last;	/* USB-C1 上一轮状态 */
	uint8_t  usb_c1_power_last;	/* USB-C1 上一轮功率 */
	uint8_t  usb_c2_status;		/* USB-C2 端口状态: 0=未连接 1=充电 2=放电 (协议 §4.3) */
	uint8_t  usb_c2_power;		/* USB-C2 实时功率 0-99W */
	uint8_t  usb_c2_status_last;	/* USB-C2 上一轮状态 */
	uint8_t  usb_c2_power_last;	/* USB-C2 上一轮功率 */
	uint8_t  usb_a_status;		/* USB-A  端口状态: 0=未连接 1=充电 2=放电 (协议 §4.3) */
	uint8_t  usb_a_power;		/* USB-A  实时功率 0-99W */
	uint8_t  usb_a_status_last;	/* USB-A  上一轮状态 */
	uint8_t  usb_a_power_last;	/* USB-A  上一轮功率 */
	uint16_t count_down;		/* 倒计时剩余秒数（0=无倒计时） */
	uint8_t  bat_max_cap;		/* 电池最大容量 0-100% */
	uint16_t bat_cycle_cnt;	/* 循环次数 0-9999 */
	uint8_t  bat_temperature;	/* 电池温度 0-100℃ */
	uint16_t bat_voltage;		/* 电池包电压 0.1V (来自CW1573) */
	int16_t  bat_current;		/* 电池电流 mA (来自CW1573,充电为正) */
	uint32_t bat_cc;		/* 库伦量 mAh (来自CW1573) */
	warning_t warning;		/* 警告状态 */
	uint16_t anim_cur_x;		/* 电量百分比动画当前 X 偏移 */
	uint8_t  anim_power;		/* 动画当前显示的电量值 1-100 */
	uint16_t prev_disp_x;		/* 上一轮电量显示 X 坐标 */
	uint8_t  prev_disp_w;		/* 上一轮电量显示总宽度 */
	uint8_t  charge_anim_frame;	/* 充电图标动画当前帧 0-24 */
	uint8_t  prev_bar_effect;	/* 上一轮进度条效果 0=初始 1=充电 2=放电 */
	uint16_t prev_icon_x;		/* 上一轮充电图标 X 坐标 */
	uint8_t  bat_power_last;	/* 上一轮电量值，检测变化 */
	page_t   cur_page;		/* 当前界面 */
	page_t   last_page;		/* 上一界面，用于检测切换 */
	char     bat_model_1[16];	/* 电池型号 1 */
	char     bat_model_2[16];	/* 电池型号 2 */
	char     bat_model_3[16];	/* 电池型号 3 */
	char     bat_model_4[16];	/* 电池型号 4 */
	dev_state_t dev_state;		/* 设备运行状态 */
	bool       low_current_flag;	/* USB-A 小电流模式标志 */

} ui_data_t;

extern ui_data_t ui_data;

void ui_init(void);
void ui_proc(void);






#endif


