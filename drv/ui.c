#include "ui.h"
#include "flash_image_addr.h"

static void 			ui_gpio_init					(void);
static void				ui_iic_data_get					(void);
static void				ui_disp_page_reflash			(void);
static void				ui_disp_light_proc				(void);

static void spi_init(void)
{
	md_spi_init_t h_spi;

	memset(&h_spi, 0, sizeof(h_spi));
	md_spi_struct_init(&h_spi);

	h_spi.baud = MD_SPI_BAUD_4;

	md_spi_init(SPI0, &h_spi);
}

void ui_init(void)
{
	//相关IO初始化
	ui_gpio_init();

	//SPI初始化
	spi_init();

	//LCD 初始化配置
	lcd_init();
	
	//刷黑屏幕
	DispColor(BLACK);
	md_delay_1ms(500);
	// Dispphoto_Dispaly_flash(0,0,FLASH_ADDR_BLUE_NUM_64_0);
	// start_change_anima(0);
	// extern void draw_charging_blue_anima();
	// draw_charging_blue_anima();

	default_page_init();
	//获取FLASH芯片 ID
//	ui_ctrl.flash_id = flash_read_id();
}

void ui_task(void)
{
	//获取IIC读取数据
	ui_iic_data_get();
	
	//处理页面切换
	ui_disp_page_reflash();
	
	//处理LCD背光
	ui_disp_light_proc();
	
}

//处理不同页面内容
void ui_proc(void)
{
#if 0
	switch(ui_ctrl.disp_page)
	{
		case DISP_PAGE_BAT_NUM:
			//电量界面
			ui_bat_soc();
			break;
		
		case DISP_PAGE_BAT_INFO:
			//电池信息
			ui_bat_info();
			break;
		
		case DISP_PAGE_OFF_TIME:
			//设置熄屏时间
			ui_screen_off_time();
			break;
		
		case DISP_PAGE_BRIGHTNESS:
			//设置屏幕亮度
			ui_screen_brightness();
			break;
		
		case DISP_PAGE_PORT_STATUS:
			//设置C1口功能
			ui_c1_port_status();
			break;
		
		case DISP_PAGE_PROTECT:
			//保护界面
			ui_protection();
			break;
		
		default:
			break;
	}
		
#endif
}

static void ui_iic_data_get(void)
{
#if 0
	/**********************************获取IIC数据******************************************/	
	//获取页面内容
	ui_ctrl.iic_data.disp_ctrl_read.byte	= (disp_page_t)iic_send_buf[IIC_DISP_CTRL];
	
	//获取系统设置
	ui_ctrl.iic_data.sys_status_read.byte	= iic_send_buf[IIC_SYS_STATUS];
	
	//获取电量百分比
	ui_ctrl.iic_data.disp_bat_num_read		= iic_send_buf[IIC_BAT_SOC];
	
	//获取C1口功率
	ui_ctrl.iic_data.port_c1_watt_read		= iic_send_buf[IIC_C1_WATT_H] << 8 | iic_send_buf[IIC_C1_WATT_L];
	
	//获取C2口功率
	ui_ctrl.iic_data.port_c2_watt_read		= iic_send_buf[IIC_C2_WATT_H] << 8 | iic_send_buf[IIC_C2_WATT_L];
	
	//获取充电时长-小时
	ui_ctrl.iic_data.chg_time_h_read		= iic_send_buf[IIC_CHG_TIME_H];
	
	//获取充电时长-分钟
	ui_ctrl.iic_data.chg_time_m_read		= iic_send_buf[IIC_CHG_TIME_M];

	//获取电池健康度
	ui_ctrl.iic_data.bat_health_read		= iic_send_buf[IIC_BAT_HEALTH];

	//获取电池循环次数
	ui_ctrl.iic_data.bat_cycle_read			= iic_send_buf[IIC_BAT_CYCLE_H] << 8| iic_send_buf[IIC_BAT_CYCLE_L];
	
	//获取电池温度
	ui_ctrl.iic_data.bat_temp_c_read		= (int16_t)iic_send_buf[IIC_BAT_TEMP] - 40;
	
	//获取当前语音设置
	ui_ctrl.iic_data.language_set			= iic_send_buf[IIC_LANGUAGE_SET];
	
	//限定温度范围
	if(ui_ctrl.iic_data.bat_temp_c_read < -18)
		ui_ctrl.iic_data.bat_temp_c_read = -18;
	
	if(ui_ctrl.iic_data.bat_temp_c_read > 80)
		ui_ctrl.iic_data.bat_temp_c_read = 80;
#endif
}

static void ui_disp_page_reflash(void)
{
#if 0
	if(ui_ctrl.disp_page != ui_ctrl.iic_data.disp_ctrl_read.disp_page)
	{
		ui_ctrl.disp_page = (disp_page_t)ui_ctrl.iic_data.disp_ctrl_read.disp_page;
		
		//如果存在界面切换，则更新屏幕
		ui_ctrl.disp_step = DISP_STEP_REFLASH;
		ui_ctrl.disp_pos = 0;
	}
#endif
}

static void ui_disp_light_proc(void)
{
#if 0
	if(ui_ctrl.power_on < LCD_POWER_ON_DELAY)
	{
		ui_ctrl.power_on++;
	}
	
	if((ui_ctrl.iic_data.disp_ctrl_read.disp_flag) && (ui_ctrl.power_on >= LCD_POWER_ON_DELAY))
	{
		ui_ctrl.disp_flag = 1;
	}
	else
	{
		ui_ctrl.disp_flag = 0;
	}

	if(ui_ctrl.disp_flag)
	{
		if(ui_ctrl.iic_data.sys_status_read.screen_brightness)
		{
			if(ui_ctrl.disp_pwm_duty_bk > 30)
			{
				ui_ctrl.disp_pwm_duty_bk -= 5;
			}
			else
			{
				ui_ctrl.disp_pwm_duty_bk = 30;
			}
		}
		else
		{
			if(ui_ctrl.disp_pwm_duty_bk < 100 && ui_ctrl.disp_pwm_duty_bk != 0)
			{
				ui_ctrl.disp_pwm_duty_bk += 5;
			}
			else
			{
				ui_ctrl.disp_pwm_duty_bk = 100;
			}
		}
		
		ui_ctrl.disp_pwm_duty = ui_ctrl.disp_pwm_duty_bk;
	}
	else
	{
		ui_ctrl.disp_pwm_duty = 0;
	}
	
	ad16c4t_timer_pwm_set(ui_ctrl.disp_pwm_duty);
#endif
}

static void ui_gpio_init(void)
{
	md_gpio_init_t gpio_init;
	md_gpio_init_struct(&gpio_init);
	
	md_gpio_init(LCD_RS, LCD_RS_PIN, &gpio_init);
	md_gpio_init(LCD_CS, LCD_CS_PIN, &gpio_init);
	md_gpio_init(LCD_RST, LCD_RST_PIN, &gpio_init);
	md_gpio_init(LCD_BLK, LCD_BLK_PIN, &gpio_init);
	md_gpio_init(FLASH_CS, FLASH_CS_PIN, &gpio_init);
	md_gpio_init(TFT_EN, TFT_EN_PIN, &gpio_init);
	
	gpio_init.func = MD_GPIO_FUNC_2;
	md_gpio_init(SPI_CLK, SPI_CLK_PIN, &gpio_init);
	md_gpio_init(SPI_MISO, SPI_MISO_PIN, &gpio_init);
	md_gpio_init(SPI_MOSI, SPI_MOSI_PIN, &gpio_init);

	LCD_CS_HIGH();
	LCD_RS_HIGH();
	FLASH_CS_SET();
	
	TFT_EN_SET();
//	LCD_BLK_HIGH();
}



