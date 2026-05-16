#ifndef __UI_H
#define __UI_H

#include "global_define.h"

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

typedef enum
{
//	DISP_PAGE_NULL,
	DISP_PAGE_PROTECT		= (uint8_t)0x0,
	DISP_PAGE_BAT_NUM		= (uint8_t)0x1,
	DISP_PAGE_BAT_INFO		= (uint8_t)0x2,
	DISP_PAGE_OFF_TIME		= (uint8_t)0x3,
	DISP_PAGE_BRIGHTNESS	= (uint8_t)0x4,
	DISP_PAGE_PORT_STATUS	= (uint8_t)0x5,
	
	DISP_PAGE_MAX,
}disp_page_t;

typedef enum
{
	//用于界面切换时刷新
	DISP_STEP_REFLASH		= (uint8_t)0x0,
	DISP_STEP_DISP			= (uint8_t)0x1,
	DISP_STEP_WAITCMD		= (uint8_t)0x2,
	
	DISP_STEP_MAX,
}disp_step_t;

typedef enum
{
	//用于能量环界面
	DISP_STEP_BLACK,		//刷黑屏
	DISP_STEP_PROTECT,		//保护图标
	DISP_STEP_BAT_NUM,		//电量百分比
	DISP_STEP_C1_WATT,		//C1口功率
	DISP_STEP_C1_LOGO,		//C1口图标
	DISP_STEP_C2_WATT,		//C2口功率
	DISP_STEP_C2_LOGO,		//C2口图标
	DISP_STEP_CHG_TIME,		//充电时长
	DISP_STEP_CYCLE,
}disp_bat_num_step_t;

typedef union
{
	struct
	{
		uint8_t disp_page		    : 3;    //0:PORTECT 1: BAT_SOC 2:BAT_INFO 3:SRCEEN_OFF_TIME 4:SRCEEN_BRIGHTNESS 5:C1_PORT_STATUS
		uint8_t prot_c1_disp	    : 1;    //0: ENABLE_C1_DISP 1: DISABLE_C1_DISP
		uint8_t prot_c2_disp	    : 1;    //0: ENABLE_C2_DISP 1: DISABLE_C2_DISP
		uint8_t temp_protect	    : 1;    //0: DISABLE_TEMP_PROT_DISP 1: ENABLE_TEMP_PROT_DISP
		uint8_t chg_time_disp	    : 1;    //0: DISABLE_CHARGE_TIME_DISP 1: ENABLE_CHARGE_TIME_DISP
		uint8_t disp_flag		    : 1;    //0: DISABLE_LCD_DISP 1: ENABLE_LCD_DISP
	};
	uint8_t byte;
}disp_ctrl_t;

typedef union
{
	struct
	{
		uint8_t screen_off_time		: 2;	//0:30s 1:1Min 2:5Min 3:30Min
		uint8_t screen_brightness	: 1;	//0:high 1:low
		uint8_t port_c1_set			: 1;	//0:input&output 1:output only
		uint8_t port_c1_status		: 2;	//0: No Connect 1:Charge 2:Discharge 3:Protect
		uint8_t port_c2_status		: 2;	//0: No Connect 1:Charge 2:Discharge 3:Protect
	};
	uint8_t byte;
}sys_status_t;

typedef struct
{
	uint8_t				disp_bat_num_read;
	
	uint16_t			port_c1_watt_read;
	uint16_t			port_c2_watt_read;
	
	uint8_t				chg_time_h_read;
	uint8_t				chg_time_m_read;
	
	uint8_t				key_value;
	uint8_t				err_read;
	
	disp_ctrl_t			disp_ctrl_read;
	sys_status_t		sys_status_read;
	
	uint16_t			bat_cycle_read;			//电池循环次数
	uint8_t				bat_health_read;		//电池健康度
	int8_t				bat_temp_c_read;		//摄氏度
	
	uint8_t				language_set;
}iic_get_value_t;

typedef struct
{
	disp_bat_num_step_t	disp_bat_soc_step;
	
	uint8_t				disp_bat_num;
	uint8_t				disp_bat_num_state;
	
	uint16_t			port_c1_watt;
	uint16_t			port_c2_watt;
	
	uint8_t				chg_time_h;
	uint8_t				chg_time_m;
	
	disp_ctrl_t			disp_ctrl;
	sys_status_t		sys_status;
	
	uint8_t				temp_prot_disp_flag;
	uint8_t				chg_time_disp_flag;
	
}ui_bat_soc_t;

typedef struct
{
	uint8_t				disp_bat_info_step;
	uint8_t				bat_temp_state;
	
	uint16_t			bat_cycle;			//电池循环次数
	uint8_t 			bat_health;			//电池健康度
	int8_t				bat_temp_c;			//摄氏度
	int16_t				bat_temp_f;			//华氏度
}ui_bat_info_t;


typedef struct
{
	disp_page_t			disp_page;
	
	disp_step_t			disp_step;
	uint16_t			disp_pos;
	uint8_t				disp_block;
	uint8_t				reflash_disp;
	
	uint16_t			ui_reset_cnt;
	
	uint8_t				disp_pwm_duty;
	uint8_t				disp_pwm_duty_bk;
	uint8_t				disp_flag;
	uint32_t			disp_ticker;
	
	uint8_t				input_output_flag;	//0:输入与输出 1:仅输出
	uint8_t				brightness_flag;	//0:高亮度 1:低亮度
	uint8_t				off_time_level;		//0:30S 1:1Min 2:5Min 3:30Min

	uint32_t			flash_id;
	uint8_t				power_on;
	
	iic_get_value_t		iic_data;				

	ui_bat_soc_t		bat_soc;
	ui_bat_info_t		bat_info;
}ui_t;

extern ui_t ui_ctrl;

void ui_init(void);
void ui_proc(void);
void ui_task(void);




#endif


