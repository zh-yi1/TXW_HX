#include "ui.h"
#include "flash_image_addr.h"

#define DISABLE_PAGE_RETURN_MS	(30000U)	/* 禁用状态下离开禁用界面 30s 后自动返回 */

static void ui_gpio_init(void);

static uint32_t hint_enter_tick = 0;  /* 提示页进入时刻, 用于 5s 自动跳转 */
static uint32_t disabled_leave_tick = 0;  /* 离开禁用界面的时刻, 用于 30s 自动返回 */

ui_data_t ui_data = {
	.bat_power = 50,
	.is_charge = 1,
	.usb_c1_status = 0,
	.usb_c1_power = 5,
	.usb_c2_status = 0,
	.usb_c2_power = 30,
	.usb_a_status = 0,
	.usb_a_power = 10,
	.bat_max_cap = 100,
	.bat_cycle_cnt = 9999,
	.bat_temperature = 250,   /* 25.0℃ */
	.bat_voltage = 0,
	.bat_current = 0,

	.warning = WARNING_NONE,
	.cur_page = PAGE_HOME,
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
	ui_data.last_page = PAGE_MAX;
	ui_data.cur_page = PAGE_HOME;
	// information_page_1_init();
	// over_temp_hint_page();
	//获取FLASH芯片 ID
//	ui_ctrl.flash_id = flash_read_id();

	//开机从 factory_cfg 恢复 SOC/SOH/循环, 回填 0x71~0x74 + 密码位
	i2c_slave_restore_bat_backup();
}


//处理不同页面内容
void ui_proc(void)
{
	/* 灭屏状态下不刷新界面 */
	if (ui_data.dev_state == DEV_STATE_SLEEP_ACTIVE
	    || ui_data.dev_state == DEV_STATE_SLEEP_PASSIVE)
		return;

	calc_charge_remain_min();  /* V1.3: 剩余充满时间估算 */

	/* 禁用状态下, 若当前不在禁用界面, 30s 后自动返回禁用界面 */
	if (ui_data.disable_flag && ui_data.cur_page != PAGE_DISABLED)
	{
		if (disabled_leave_tick == 0)
			disabled_leave_tick = md_get_tick();
		if (md_get_tick() - disabled_leave_tick >= DISABLE_PAGE_RETURN_MS)
			ui_data.cur_page = PAGE_DISABLED;
	}
	else
	{
		disabled_leave_tick = 0;
	}

	/* 检测界面切换，切换时初始化新界面 */
	if (ui_data.cur_page != ui_data.last_page)
	{
		LOGI("[UI] ui_proc: cur_page=%d, last_page=%d\r\n", ui_data.cur_page, ui_data.last_page);
		switch (ui_data.cur_page)
		{
		case PAGE_HOME:
			home_page_init();
			break;
		case PAGE_POWER:
			power_page_init();
			break;
		case PAGE_INFO_1:
			information_page_1_init();
			break;
		case PAGE_INFO_2:
			information_page_2_init();
			break;
		case PAGE_INFO_3:
			information_page_3_init();
			break;
		case PAGE_OFF_TIME:
			off_time_page_init();
			break;
		case PAGE_OVER_TEMP:
			high_temp_pro(battery_mgr_get_warning_chg_state());
			hint_enter_tick = md_get_tick();
			break;
		case PAGE_DISABLED:
			disabled_hint_page();
			break;
		case PAGE_SHORT_CIRCUIT:
			short_circuit_hint_page();
			hint_enter_tick = md_get_tick();
			break;
		case PAGE_VOLTAGE_ABNORMAL:
		{
			abnormal_record_t rec;
			uint8_t total = abnormal_log_voltage_count();
			/* 仅在真正切页时复位索引, 强制重绘 (last_page=PAGE_ABNORMAL_UPDATA) 时不复位 */
			if (ui_data.last_page != PAGE_ABNORMAL_UPDATA)
				ui_data.abnormal_idx = 0;
			if (total == 0) {
				abnormal_hint_page(0, 0, 0, 0, 0, NULL, 0);
			} else if (abnormal_log_voltage_read(ui_data.abnormal_idx, &rec) == 0) {
				const char *model = NULL;
				if      (rec.cell == 0) model = ui_data.bat_model_1;
				else if (rec.cell == 1) model = ui_data.bat_model_2;
				else if (rec.cell == 2) model = ui_data.bat_model_3;
				else if (rec.cell == 3) model = ui_data.bat_model_4;
				abnormal_hint_page(0, ui_data.abnormal_idx + 1, total,
				                   rec.timestamp, rec.value, model, rec.chg_state);
			}
			break;
		}
		case PAGE_TEMP_ABNORMAL:
		{
			abnormal_record_t rec;
			uint8_t total = abnormal_log_temperature_count();
			/* 仅在真正切页时复位索引, 强制重绘 (last_page=PAGE_ABNORMAL_UPDATA) 时不复位 */
			if (ui_data.last_page != PAGE_ABNORMAL_UPDATA)
				ui_data.abnormal_idx = 0;
			if (total == 0) {
				abnormal_hint_page(1, 0, 0, 0, 0, NULL, 0);
			} else if (abnormal_log_temperature_read(ui_data.abnormal_idx, &rec) == 0) {
				abnormal_hint_page(1, ui_data.abnormal_idx + 1, total,
				                   rec.timestamp, rec.value / 10, NULL, rec.chg_state);
			}
			break;
		}
		default:
			break;
		}
		ui_data.last_page = ui_data.cur_page;
	}

	/* 端口功率采样: 必须放在 500ms 限流之外, 否则滤波窗口跟着绘制节奏走,
	   5 点窗口要跨 2.5s 才填满 */
	if (ui_data.cur_page == PAGE_POWER)
		power_page_sample();

	/* 主页电量采样 + 充放电动画: 两者节奏都远快于 500ms, 同样不能受限流 */
	if (ui_data.cur_page == PAGE_HOME)
	{
		home_page_sample();
		home_page_anim_proc();
	}

	/* 息屏时长页: 双击换选项要立刻看到反馈, 等 500ms 太迟钝。没变化时它直接返回 */
	if (ui_data.cur_page == PAGE_OFF_TIME)
		off_time_page_updata();

	/* 各界面周期性更新, 统一 500ms 限流 */
	static uint32_t last_updata_ms = 0;
	uint32_t _now = md_get_tick();
	if (_now - last_updata_ms < 500)
		return;
	last_updata_ms = _now;
	
	switch (ui_data.cur_page)
	{
	case PAGE_HOME:
		home_page_updata();
		break;
	case PAGE_POWER:
		power_page_updata();
		break;
	case PAGE_INFO_1:
		information_page_1_updata();
		break;
	case PAGE_INFO_2:
		information_page_2_updata();
		break;
	case PAGE_INFO_3:
		information_page_3_updata();
		break;
	case PAGE_OVER_TEMP:
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
	case PAGE_HOME:
		ui_data.last_page = PAGE_HOME;
		ui_data.cur_page = PAGE_POWER;
		break;
	case PAGE_POWER:
		ui_data.last_page = PAGE_POWER;
		ui_data.cur_page = PAGE_INFO_1;
		break;
	case PAGE_INFO_1:
		ui_data.last_page = PAGE_INFO_1;
		ui_data.cur_page = PAGE_INFO_2;
		break;
	case PAGE_INFO_2:
		ui_data.last_page = PAGE_INFO_2;
		ui_data.cur_page = PAGE_HOME;
		break;
	case PAGE_INFO_3:
		/* 电压界面单击 -> 息屏时长设置界面 */
		ui_data.last_page = PAGE_INFO_3;
		ui_data.cur_page = PAGE_OFF_TIME;
		break;
	case PAGE_OFF_TIME:
		/* 息屏时长界面单击 -> 温度异常界面 (原来电压界面的下一站) */
		ui_data.last_page = PAGE_OFF_TIME;
		ui_data.cur_page = PAGE_TEMP_ABNORMAL;
		break;
	case PAGE_DISABLED:
		ui_data.last_page = PAGE_DISABLED;
		ui_data.cur_page = PAGE_HOME;
		break;
	case PAGE_TEMP_ABNORMAL:
		/* 温度异常界面单击 -> 电压异常界面 */
		ui_data.last_page = PAGE_TEMP_ABNORMAL;
		ui_data.cur_page = PAGE_VOLTAGE_ABNORMAL;
		break;
	case PAGE_VOLTAGE_ABNORMAL:
		/* 电压异常界面单击 -> 电压界面 */
		ui_data.last_page = PAGE_VOLTAGE_ABNORMAL;
		ui_data.cur_page = PAGE_INFO_3;
		break;
	default:
		break;
	}
}

/* 双击处理.
 * 息屏时长页: 切到下一个时长选项 (轮回), 返回 0 保持亮屏;
 * 异常记录页: 切换到下一条记录 (轮回, 播放完最后一条回到第一条), 返回 0 保持亮屏;
 * 其余界面: 返回 true 表示需主动灭屏 */
bool key_double_click_ui_proc(void)
{
	switch (ui_data.cur_page)
	{
	case PAGE_OFF_TIME:
		/* 设置页双击是换选项, 不灭屏 */
		off_time_page_next();
		return false;
	case PAGE_TEMP_ABNORMAL:
		{
			uint8_t cnt = abnormal_log_temperature_count();
			ui_data.abnormal_idx++;
			if (ui_data.abnormal_idx >= cnt)
				ui_data.abnormal_idx = 0;
			ui_data.last_page = PAGE_ABNORMAL_UPDATA;  /* 强制重绘, 保留 idx */
		}
		return false;
	case PAGE_VOLTAGE_ABNORMAL:
		{
			uint8_t cnt = abnormal_log_voltage_count();
			ui_data.abnormal_idx++;
			if (ui_data.abnormal_idx >= cnt)
				ui_data.abnormal_idx = 0;
			ui_data.last_page = PAGE_ABNORMAL_UPDATA;  /* 强制重绘, 保留 idx */
		}
		return false;
	default:
		break;
	}
	return true;  /* 非异常页: 双击灭屏 */
}

bool key_long_press_ui_proc(void)
{
	bool ret = false;
	switch (ui_data.cur_page)
	{
		case PAGE_HOME:
		case PAGE_POWER:
		case PAGE_INFO_1:
			ret = true;
			break;
		case PAGE_INFO_2:
			/* 温度界面长按 -> 电压界面 */
			ui_data.last_page = PAGE_INFO_2;
			ui_data.cur_page = PAGE_INFO_3;
			break;
		case PAGE_INFO_3:
			/* 电压界面长按 -> 温度界面 */
			ui_data.last_page = PAGE_INFO_3;
			ui_data.cur_page = PAGE_INFO_2;
			break;
		case PAGE_OFF_TIME:
			/* 息屏时长界面长按 -> 温度界面 */
			ui_data.last_page = PAGE_OFF_TIME;
			ui_data.cur_page = PAGE_INFO_2;
			break;
		case PAGE_TEMP_ABNORMAL:
			/* 温度异常界面长按 -> 温度界面 */
			ui_data.last_page = PAGE_TEMP_ABNORMAL;
			ui_data.cur_page = PAGE_INFO_2;
			break;
		case PAGE_VOLTAGE_ABNORMAL:
			/* 电压异常界面长按 -> 温度界面 */
			ui_data.last_page = PAGE_VOLTAGE_ABNORMAL;
			ui_data.cur_page = PAGE_INFO_2;
			break;
		default:
			break;
	}
	return ret;
}





