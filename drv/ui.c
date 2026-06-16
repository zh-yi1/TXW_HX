#include "ui.h"
#include "flash_image_addr.h"

static void ui_gpio_init(void);

static uint32_t hint_enter_tick = 0;  /* 提示页进入时刻, 用于 5s 自动跳转 */

ui_data_t ui_data = {
	.bat_power = 50,
	.is_charge = 1,
	.is_charge_last = 0,
	.usb_c1_status = 0,
	.usb_c1_power = 5,
	.usb_c2_status = 0,
	.usb_c2_power = 30,
	.usb_a_status = 0,
	.usb_a_power = 10,
	.count_down = 0,
	.bat_max_cap = 100,
	.bat_cycle_cnt = 9999,
	.bat_temperature = 62,
	.bat_voltage = 0,
	.bat_current = 0,
	.bat_cc = 0,
	.warning = WARNING_NONE,
	.cur_page = PAGE_DEFAULT,
	.last_page = PAGE_MAX,
	.bat_model_1 = "1234567890_A",
	.bat_model_2 = "BCDEFGHIJKLM",
	.bat_model_3 = "NOPQRSTUVWXY",
	.bat_model_4 = "KJDSALFHJKHU",
	.dev_state = DEV_STATE_NORMAL,
};

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
	// md_delay_1ms(500);
	// Dispphoto_Dispaly_flash(0,0,FLASH_ADDR_BLUE_NUM_64_0);
	// start_change_anima(0);
	// extern void draw_charging_blue_anima();
	// draw_charging_blue_anima();

	// default_page_test();
	// default_page_init();
	ui_data.last_page = PAGE_MAX;
	ui_data.cur_page = PAGE_DEFAULT;
	// information_page_1_init();
	// over_temp_hint_page();
	//获取FLASH芯片 ID
//	ui_ctrl.flash_id = flash_read_id();
}


//处理不同页面内容
void ui_proc(void)
{
	/* 休眠状态下不刷新界面 */
	if (ui_data.dev_state == DEV_STATE_SLEEP)
		return;

	calc_charge_remain_min();  /* V1.3: 剩余充满时间估算 */

	/* 检测界面切换，切换时初始化新界面 */
	if (ui_data.cur_page != ui_data.last_page)
	{
		switch (ui_data.cur_page)
		{
		case PAGE_DEFAULT:
			default_page_init();
			break;
		case PAGE_INFO_1:
			information_page_1_init();
			break;
		case PAGE_INFO_2:
			information_page_2_init();
			break;
		case PAGE_OVER_TEMP:
			over_temp_hint_page();
			hint_enter_tick = md_get_tick();
			break;
		case PAGE_LOW_TEMP:
			low_temp_hint_page();
			hint_enter_tick = md_get_tick();
			break;
		case PAGE_SHORT_CIRCUIT:
			short_circuit_hint_page();
			hint_enter_tick = md_get_tick();
			break;
		case PAGE_VOLTAGE_ABNORMAL:
		{
			abnormal_record_t rec;
			uint8_t total = abnormal_log_voltage_count();
			const char *model = NULL;
			/* 仅在真正切页时复位索引, 强制重绘 (last_page=PAGE_ABNORMAL_UPDATA) 时不复位 */
			if (ui_data.last_page != PAGE_ABNORMAL_UPDATA)
				ui_data.abnormal_idx = 0;
			if (total > 0 && abnormal_log_voltage_read(ui_data.abnormal_idx, &rec) == 0) {
				if      (rec.cell == 0) model = ui_data.bat_model_1;
				else if (rec.cell == 1) model = ui_data.bat_model_2;
				else if (rec.cell == 2) model = ui_data.bat_model_3;
				else if (rec.cell == 3) model = ui_data.bat_model_4;
				abnormal_hint_page(0, ui_data.abnormal_idx + 1, total,
				                   rec.timestamp, rec.value, model);
			}
			// abnormal_hint_page(0, 1, 5,1781605637, 4500, "AURNDIDFKS");
			break;
		}
		case PAGE_TEMP_ABNORMAL:
		{
			abnormal_record_t rec;
			uint8_t total = abnormal_log_temperature_count();
			/* 仅在真正切页时复位索引, 强制重绘 (last_page=PAGE_ABNORMAL_UPDATA) 时不复位 */
			if (ui_data.last_page != PAGE_ABNORMAL_UPDATA)
				ui_data.abnormal_idx = 0;
			if (total > 0 && abnormal_log_temperature_read(ui_data.abnormal_idx, &rec) == 0) {
				abnormal_hint_page(1, ui_data.abnormal_idx + 1, total,
				                   rec.timestamp, rec.value / 10, NULL);
			}
			// abnormal_hint_page(1, 1, 5,1781605637, 60, NULL);
			break;
		}
		default:
			break;
		}
		ui_data.last_page = ui_data.cur_page;
	}

	/* 各界面周期性更新 */
	switch (ui_data.cur_page)
	{
	case PAGE_DEFAULT:
		default_page_updata();
		break;
	case PAGE_INFO_1:
		information_page_1_updata();
		break;
	case PAGE_INFO_2:
		information_page_2_updata();
		break;
	case PAGE_OVER_TEMP:
	case PAGE_LOW_TEMP:
	case PAGE_SHORT_CIRCUIT:
		if (md_get_tick() - hint_enter_tick >= 5000) {
			ui_data.cur_page = (ui_data.cur_page == PAGE_SHORT_CIRCUIT)
			                 ? PAGE_VOLTAGE_ABNORMAL
			                 : PAGE_TEMP_ABNORMAL;
		}
		break;
	default:
		break;
	}
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
	// LCD_BLK_HIGH();
}

void key_single_click_ui_proc(void)
{
	switch (ui_data.cur_page)
	{
	case PAGE_DEFAULT:
		ui_data.last_page = PAGE_DEFAULT;
		ui_data.cur_page = PAGE_INFO_1;
		break;
	case PAGE_INFO_1:
		ui_data.last_page = PAGE_INFO_1;
		ui_data.cur_page = PAGE_INFO_2;
		break;
	case PAGE_INFO_2:
		ui_data.last_page = PAGE_INFO_2;
		ui_data.cur_page = PAGE_INFO_3;
		break;
	case PAGE_INFO_3:
		ui_data.last_page = PAGE_INFO_3;
		ui_data.cur_page = PAGE_DEFAULT;
		break;
	case PAGE_VOLTAGE_ABNORMAL:
		{
			uint8_t cnt = abnormal_log_voltage_count();
			ui_data.abnormal_idx++;
			if (ui_data.abnormal_idx >= cnt) {
				ui_data.abnormal_idx = 0;
			} 
			ui_data.last_page = PAGE_ABNORMAL_UPDATA;  /* 强制重绘 */
			
		}
		break;
	case PAGE_TEMP_ABNORMAL:
		{
			uint8_t cnt = abnormal_log_temperature_count();
			ui_data.abnormal_idx++;
			if (ui_data.abnormal_idx >= cnt) {
				ui_data.abnormal_idx = 0;
			} 
			ui_data.last_page = PAGE_ABNORMAL_UPDATA;  /* 强制重绘 */
			
		}
		break;
	default:
		break;
	}	
}

void key_double_click_ui_proc(void)
{
	switch (ui_data.cur_page)
	{
		case PAGE_DEFAULT:
		case PAGE_INFO_1:
		case PAGE_INFO_2:
		case PAGE_INFO_3:
			LCD_BLK_HIGH();
			DispColor(BLACK);
			ui_data.dev_state = DEV_STATE_SLEEP;
			break;

		default:
			break;
	}
}

bool key_long_press_ui_proc(void)
{
	bool ret = false;
	switch (ui_data.cur_page)
	{
		case PAGE_DEFAULT:
		case PAGE_INFO_1:
			ret = true;
			break;
		case PAGE_INFO_2:
			ui_data.last_page = PAGE_INFO_2;
			ui_data.cur_page = PAGE_TEMP_ABNORMAL;
			break;
		case PAGE_INFO_3:
			ui_data.last_page =PAGE_INFO_3;
			ui_data.cur_page = PAGE_VOLTAGE_ABNORMAL;
			break;
		case PAGE_TEMP_ABNORMAL:
			ui_data.last_page = PAGE_TEMP_ABNORMAL;
			ui_data.cur_page = PAGE_INFO_2;
			break;
		case PAGE_VOLTAGE_ABNORMAL:
			ui_data.last_page =PAGE_VOLTAGE_ABNORMAL;
			ui_data.cur_page = PAGE_INFO_3;
			break;
		default:
			break;
	}
	return ret;
}





