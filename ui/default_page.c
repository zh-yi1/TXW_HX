#include "default_page.h"

// 固定图片位置 (直接内联, 节省 SRAM)

/* ============================ 小数字功率显示 ============================ */

static const range_t power_range[] = {
	{12, 103, 12 + 55, 103 + 31},
	{92, 103, 92 + 55, 103 + 31},
	{174, 103, 174 + 55, 103 + 31},
};

#define NUM_32_ADDR(d)  (FLASH_ADDR_NUM_32_BASE + (uint32_t)(d) * FLASH_STRIDE_NUM_32)

#define NUM_32_W 20
#define NUM_32_H 32
#define W_W 16
#define W_H 16
#define FREE_H 32
#define FREE_W 50

/* ============================ 功率滤波 ============================ */

#define POWER_FILTER_WIN 5

static uint8_t power_buf[3][POWER_FILTER_WIN];
static uint8_t power_idx[3];
static bool    power_full[3];

static void power_filter_push(power_e port, uint8_t value)
{
	uint8_t i = power_idx[port];
	power_buf[port][i] = value;
	i++;
	if (i >= POWER_FILTER_WIN) {
		i = 0;
		power_full[port] = true;
	}
	power_idx[port] = i;
}

/* 用初始值填满整个窗口, 避免冷启动被 0 拉低 */
static void power_filter_fill(power_e port, uint8_t value)
{
	uint8_t i;
	for (i = 0; i < POWER_FILTER_WIN; i++)
		power_buf[port][i] = value;
	power_idx[port]  = 0;
	power_full[port] = true;
}

static uint8_t power_filter_get(power_e port)
{
	uint8_t cnt = power_full[port] ? POWER_FILTER_WIN : power_idx[port];
	uint16_t sum = 0;
	uint8_t i;
	if (cnt == 0) return 0;
	for (i = 0; i < cnt; i++)
		sum += power_buf[port][i];
	return (uint8_t)(sum / cnt);
}

/* ============================ 电量滤波 ============================ */

#define BAT_FILTER_WIN 5

static uint8_t bat_filter_buf[BAT_FILTER_WIN];
static uint8_t bat_filter_idx;
static bool    bat_filter_full;
static uint8_t bat_filter_last_out = 0xFF;   /* 0xFF=未初始化 */

static void bat_filter_push(uint8_t value)
{
	uint8_t i = bat_filter_idx;
	bat_filter_buf[i] = value;
	i++;
	if (i >= BAT_FILTER_WIN) {
		i = 0;
		bat_filter_full = true;
	}
	bat_filter_idx = i;
}

/* 充电时单调增, 放电时单调减 */
static uint8_t bat_filter_get(bool is_charge)
{
	uint8_t cnt = bat_filter_full ? BAT_FILTER_WIN : bat_filter_idx;
	uint16_t sum = 0;
	uint8_t i, avg;
	if (cnt == 0) return 0;
	for (i = 0; i < cnt; i++)
		sum += bat_filter_buf[i];
	avg = (uint8_t)(sum / cnt);

	/* 单调约束 */
	if (bat_filter_last_out != 0xFF) {
		if (is_charge && avg < bat_filter_last_out)
			avg = bat_filter_last_out;
		else if (!is_charge && avg > bat_filter_last_out)
			avg = bat_filter_last_out;
	}
	bat_filter_last_out = avg;
	return avg;
}

/* ============================ 小数字功率显示 ============================ */

// 显示功率
static uint8_t last_power[3]  = {0xFF, 0xFF, 0xFF};
static uint8_t last_status[3] = {0xFF, 0xFF, 0xFF};

/* 切页时强制重绘, 避免 last_power/last_status 残留导致 skip */
void default_page_power_force_redraw(void)
{
	uint8_t i;
	for (i = 0; i < 3; i++) {
		last_power[i]  = 0xFF;
		last_status[i] = 0xFF;
	}
}

static void default_page_show_power(power_e port, uint8_t power_value, uint8_t status)
{

	/* 滤波: 状态变化时重置窗口(避免空闲/使用切换时旧值拉低), 同状态则滑动平均 */
	if (status != last_status[port])
		power_filter_fill(port, power_value);
	else
		power_filter_push(port, power_value);
	power_value = power_filter_get(port);

	/* 无变化则跳过 */
	if (power_value == last_power[port] && status == last_status[port])
	{
		LOGI("[POWER] port=%d skip: power=%d status=%d unchanged\n", port, power_value, status);
		return;
	}

	/* 状态变化或位数变化时需擦除旧内容, 同级(如个位→个位)不擦 */
	{
		uint8_t lp = last_power[port];
		uint8_t ls = last_status[port];
		bool same_level = (lp != 0xFF) && (ls == status)
		               && ((lp >= 10) == (power_value >= 10));

		if (!same_level)
		{
			range_t r = power_range[port];
			DispBlock(r.x1, r.y1, r.x2 - 1, r.y1 + FREE_H - 1);
		}
	}

	if (status == 0)
	{
		LOGI("[POWER] port=%d draw FREE power=%d\n", port, power_value);
		range_t r = power_range[port];
		int free_x = r.x1 + (r.x2 - r.x1 - FREE_W) / 2;
		Dispphoto_Dispaly_flash(free_x, r.y1, FLASH_ADDR_FREE);
	}
	else
	{
		LOGI("[POWER] port=%d draw num=%d status=%d\n", port, power_value, status);
		int area_x = power_range[port].x1;
		int area_y = power_range[port].y1;
		int area_w = power_range[port].x2 - area_x;
		int total_w, cur_x, cur_y;
		int tens, ones;
		uint8_t pv = (power_value > 99) ? 99 : power_value;

		tens = pv / 10;
		ones = pv % 10;

		total_w = (tens ? 2 : 1) * NUM_32_W + W_W;
		cur_x = area_x + (area_w - total_w + 1) / 2;
		cur_y = area_y;

		if (tens) {
			Dispphoto_Dispaly_flash(cur_x, cur_y, NUM_32_ADDR(tens));
			cur_x += NUM_32_W;
		}
		Dispphoto_Dispaly_flash(cur_x, cur_y, NUM_32_ADDR(ones));
		cur_x += NUM_32_W + 1;
		Dispphoto_Dispaly_flash(cur_x, cur_y + NUM_32_H - W_H, FLASH_ADDR_POWER_W);
	}

	last_power[port]  = power_value;
	last_status[port] = status;
}

/* ============================ 充电百分比动画 ============================ */

#define BLUE_NUM_48_ADDR(d)    (FLASH_ADDR_BLUE_NUM_48_BASE    + (uint32_t)(d) * FLASH_STRIDE_BLUE_NUM_48)
#define ORANGE_NUM_48_ADDR(d)  (FLASH_ADDR_ORANGE_NUM_48_BASE  + (uint32_t)(d) * FLASH_STRIDE_ORANGE_NUM_48)

#define NUM_48_W 40
#define NUM_48_H 48
#define PERCENT_W 24
#define PERCENT_H 24
#define SCREEN_W 240

#define CHARGE_POWER_X 12
#define CHARGE_POWER_Y 4
#define NORMAL_POWER_X 72
#define NORMAL_POWER_Y 4

#define BAR_PROGRESS_Y 65
#include "bar_progress.h"

static void anima_erase_area(int x, int y, int w, int h)
{
	DispBlock(x, y, x + w - 1, y + h - 1);
}

/* 在 (x,y) 绘制电量百分比 (同步阻塞) */
static void anima_draw_bat_power(int x, int y, uint8_t power, uint8_t is_blue)
{
	uint32_t base = is_blue ? FLASH_ADDR_BLUE_NUM_48_BASE : FLASH_ADDR_ORANGE_NUM_48_BASE;
	uint32_t percent_addr = is_blue ? FLASH_ADDR_PERCENT_BLUE : FLASH_ADDR_PERCENT_ORANG;
	int digits[3], n, i, cur_x;

	if (power > 100)
		power = 100;

	/* 拆位 */
	if (power >= 100)
	{
		digits[0] = power / 100;
		digits[1] = (power / 10) % 10;
		digits[2] = power % 10;
		n = 3;
	}
	else if (power >= 10)
	{
		digits[0] = power / 10;
		digits[1] = power % 10;
		n = 2;
	}
	else
	{
		digits[0] = power;
		n = 1;
	}

	cur_x = x;
	for (i = 0; i < n; i++)
	{
		Dispphoto_Dispaly_flash(cur_x, y, base + (uint32_t)digits[i] * FLASH_STRIDE_BLUE_NUM_48);
		cur_x += NUM_48_W;
	}

	/* 百分号, 底部对齐数字 */
	Dispphoto_Dispaly_flash(cur_x, y + NUM_48_H - PERCENT_H, percent_addr);
}

/* 计算百分比总宽度 */
static int anima_power_width(uint8_t power)
{
	int n = (power >= 100) ? 3 : (power >= 10) ? 2
											   : 1;
	return n * NUM_48_W + PERCENT_W;
}

#define ANIM_STEPS          40
#define ANIM_STEP_MS        20    /* 动画每帧间隔, 可调 */

/* V1.3 充电剩余时间显示常量 */
#define TIME_ICON_X      136
#define TIME_ICON_Y      20
#define TIME_ICON_W      24
#define TIME_ICON_H      24
#define NUM_24_DIGIT_W   14   /* 数字 14x24 */
#define NUM_24_COLON_W   12   /* 冒号 12x24 */
#define NUM_24_DIGIT_H   24
#define TIME_AREA_W      (TIME_ICON_W + 4 * NUM_24_DIGIT_W + NUM_24_COLON_W)  /* 24+56+12=92 */
#define TIME_AREA_H      TIME_ICON_H

#define NUM_24_ADDR(d)   (FLASH_ADDR_NUM_24_BASE + (uint32_t)(d) * FLASH_STRIDE_NUM_24)
#define NUM_24_COLON_IDX 10

#ifdef ENABLE_CHARGE_ANIM
/* 充放电动画状态 (非阻塞, 由 default_page_updata 驱动) */
static uint8_t  anima_step;
static uint8_t  anima_active;       /* 0=空闲 1=进行中 */
static int      anima_from_x;
static int      anima_to_x;
static int      anima_total_w;
static bool     anima_is_charge;

void start_change_anima(bool is_charge)
{
	anima_active    = 1;
	anima_step      = 0;
	anima_is_charge = is_charge;

	ui_data.anim_power = ui_data.bat_power;
	anima_total_w = anima_power_width(ui_data.anim_power);

	if (is_charge)
	{
		/* 未充电 → 充电: 居中 → 左对齐 */
		anima_from_x = (SCREEN_W - anima_total_w) / 2;
		anima_to_x   = CHARGE_POWER_X;
	}
	else
	{
		/* 充电 → 未充电: 清除充电图标 + 粒子效果, 再左对齐 → 居中 */
		int n = (ui_data.anim_power >= 100) ? 3 : (ui_data.anim_power >= 10) ? 2 : 1;
		int icon_x = ui_data.anim_cur_x + n * NUM_48_W;
		anima_erase_area(icon_x, CHARGE_POWER_Y, NUM_48_W, NUM_48_H);

		/* 清除进度条上/下的充电动画粒子 (不擦进度条本身) */
		anima_erase_area(0, BAR_PROGRESS_Y - CHARGING_ICON_H,
		                 BAR_PROGRESS_W, CHARGING_ICON_H);
		anima_erase_area(0, BAR_PROGRESS_Y + BAR_PROGRESS_H,
		                 BAR_PROGRESS_W, BLUR_H);

		anima_from_x = CHARGE_POWER_X;
		anima_to_x   = (SCREEN_W - anima_total_w) / 2;
	}

	/* 预擦整条移动走廊, 立即画第一帧 (避免擦后黑窗) */
	int left  = (anima_from_x < anima_to_x) ? anima_from_x : anima_to_x;
	int right = (anima_from_x > anima_to_x) ? anima_from_x : anima_to_x;
	right += anima_total_w - 1;
	anima_erase_area(left, CHARGE_POWER_Y, right - left + 1, NUM_48_H);

	ui_data.anim_cur_x = anima_from_x;
	anima_draw_bat_power(anima_from_x, CHARGE_POWER_Y, ui_data.anim_power,
	                     (ui_data.bat_power > 10));
	anima_step = 1;  /* 第 0 帧已画, anima_tick 从第 1 帧开始 */
}

/* 动画逐帧推进 — 先擦旧残留, 再画新位置, 返回 true 表示动画结束 */
static bool anima_tick(void)
{
	int step = anima_step;
	int prev_x = ui_data.anim_cur_x;
	int x = anima_from_x + (anima_to_x - anima_from_x) * step / ANIM_STEPS;

	ui_data.anim_cur_x = x;

	/* 先擦旧帧不重叠的边角 */
	if (step > 0)
	{
		if (x > prev_x)
			anima_erase_area(prev_x, CHARGE_POWER_Y, x - prev_x, NUM_48_H);
		else if (x < prev_x)
			anima_erase_area(x + anima_total_w, CHARGE_POWER_Y,
			                 prev_x - x, NUM_48_H);
	}

	/* 再画新帧 */
	anima_draw_bat_power(x, CHARGE_POWER_Y, ui_data.anim_power,
	                     (ui_data.bat_power > 10));

	anima_step++;

	if (step >= ANIM_STEPS)
	{
		anima_active = 0;

		/* 动画结束, 充电时在 % 右侧显示充电图标 */
		if (anima_is_charge)
		{
			int n = (ui_data.anim_power >= 100) ? 3 : (ui_data.anim_power >= 10) ? 2 : 1;
			int icon_x = x + n * NUM_48_W;
			uint32_t icon_addr = (ui_data.bat_power > 10)
			                     ? FLASH_ADDR_CHARGING_BLUE
			                     : FLASH_ADDR_CHARGING_ORANGE;
			Dispphoto_Dispaly_flash(icon_x, CHARGE_POWER_Y, icon_addr);
		}
		return true;
	}
	return false;
}
#endif /* ENABLE_CHARGE_ANIM — anima_tick */

/* ========================================================================
 * V1.3 充电剩余时间显示 (与动画解耦, 动画和非动画模式均生效)
 * ======================================================================== */

/* 绘制充电剩余时间 — 图标(24x24) + HH:MM(24px白字) */
static void draw_charge_remain_time(void)
{
	int16_t  min = calc_charge_remain_min();
	uint8_t  h;
	uint8_t  m;
	int x = TIME_ICON_X;

	/* 估算未准备好(-1)不显示 */
	if (min < 0)
		return;

	/* 100% 时电量占 3 位数, 充电图标(x=132..171)与时间区(x=136起)重叠,
	   屏宽也放不下两者; 满电无倒计时意义, 不绘制 */
	if (ui_data.bat_power >= 100)
		return;

	h = (uint16_t)min / 60;
	m = (uint16_t)min % 60;

	Dispphoto_Dispaly_flash(x, TIME_ICON_Y, FLASH_ADDR_TIME);
	x += TIME_ICON_W;

	/* 小时十位 */
	Dispphoto_Dispaly_flash(x, TIME_ICON_Y, NUM_24_ADDR(h / 10));
	x += NUM_24_DIGIT_W;

	/* 小时个位 */
	Dispphoto_Dispaly_flash(x, TIME_ICON_Y, NUM_24_ADDR(h % 10));
	x += NUM_24_DIGIT_W;

	/* 冒号 12x24 */
	Dispphoto_Dispaly_flash(x, TIME_ICON_Y, NUM_24_ADDR(NUM_24_COLON_IDX));
	x += NUM_24_COLON_W;

	/* 分钟十位 */
	Dispphoto_Dispaly_flash(x, TIME_ICON_Y, NUM_24_ADDR(m / 10));
	x += NUM_24_DIGIT_W;

	/* 分钟个位 */
	Dispphoto_Dispaly_flash(x, TIME_ICON_Y, NUM_24_ADDR(m % 10));
}

/* 擦除充电剩余时间区域 (92x24) */
static void erase_charge_remain_time(void)
{
	anima_erase_area(TIME_ICON_X, TIME_ICON_Y, TIME_AREA_W, TIME_AREA_H);
}

/* 上次绘制的剩余分钟数, -1=屏上未显示; 切页 init 清屏后必须复位,
   否则新值与旧值相同时不触发重绘, 时间要等分钟变化才出现 */
static int16_t last_remain_min = -1;


/* ============================ 电量显示 ============================ */
#define BAR_PROGRESS_X 0

static void default_page_show_bar_effect(void);

void default_page_show_battery(void)
{
	int total_w, x, old_x, old_w;

	total_w = anima_power_width(ui_data.bat_power);

	if (ui_data.is_charge)
	{
		x = CHARGE_POWER_X;
		total_w = total_w - PERCENT_W + NUM_48_W;
	}
	else
	{
		x = (SCREEN_W - total_w) / 2;
	}

	old_x = ui_data.prev_disp_x;
	old_w = ui_data.prev_disp_w;

	/* 位数减少(3→2, 2→1): 先整块擦除旧区域, 再画新帧 */
	if (old_w > 0 && old_w > total_w)
		anima_erase_area(old_x, CHARGE_POWER_Y, old_w, NUM_48_H);

	/* 画新帧 */
	anima_draw_bat_power(x, CHARGE_POWER_Y, ui_data.bat_power, (ui_data.bat_power > 10));

	if (ui_data.is_charge)
	{
		int n = (ui_data.bat_power >= 100) ? 3 : (ui_data.bat_power >= 10) ? 2
																		   : 1;
		int icon_x = x + n * NUM_48_W;
		uint32_t icon_addr = (ui_data.bat_power > 10)
								 ? FLASH_ADDR_CHARGING_BLUE
								 : FLASH_ADDR_CHARGING_ORANGE;
		Dispphoto_Dispaly_flash(icon_x, CHARGE_POWER_Y, icon_addr);
	}

	/* 更新追踪 */
	ui_data.prev_disp_x = x;
	ui_data.prev_disp_w = total_w;

	if (old_w == 0 || old_w > total_w)
		goto draw_bar;

	/* 同位数或位数增加: 只擦不重叠的边角 (先画后擦, 无闪烁) */
	if (old_x < x)
		anima_erase_area(old_x, CHARGE_POWER_Y, x - old_x, NUM_48_H);

	if (old_x + old_w > x + total_w)
		anima_erase_area(x + total_w, CHARGE_POWER_Y,
						 (old_x + old_w) - (x + total_w), NUM_48_H);

draw_bar:
	default_page_show_bar_effect();
}

#define BAR_EFFECT_UP_Y (BAR_PROGRESS_Y - CHARGING_ICON_H)
#define BAR_EFFECT_DN_Y (BAR_PROGRESS_Y + BAR_PROGRESS_H)
#define BAR_EFFECT_AREA_H (CHARGING_ICON_H + BAR_PROGRESS_H + BLUR_H)

static void default_page_show_bar_effect(void)
{
	int bat = ui_data.bat_power;

	/* 电量范围保护: 1-100, 防止数组越界 */
	if (bat < 1)
		bat = 1;
	else if (bat > 100)
		bat = 100;

	if (ui_data.prev_bar_effect > 0)
	{
		int cur_effect = ui_data.is_charge ? 1 : 2;
		if (ui_data.prev_bar_effect != cur_effect)
		{
			anima_erase_area(0, BAR_EFFECT_UP_Y, BAR_PROGRESS_W, BAR_EFFECT_AREA_H);
			ui_data.prev_icon_x = 0;
		}
	}
	ui_data.prev_bar_effect = ui_data.is_charge ? 1 : 2;

	Dispphoto_Dispaly_flash(BAR_PROGRESS_X, BAR_PROGRESS_Y,
		FLASH_ADDR_BAR_PROGRESS_BASE + (uint32_t)(bat - 1) * FLASH_STRIDE_BAR_PROGRESS);

#ifdef ENABLE_CHARGE_ANIM
	int fill_x;

	fill_x = bat * BAR_PROGRESS_W / 100;

	if (ui_data.is_charge)
	{
		int icon_x = fill_x - CHARGING_ICON_W;
		if (icon_x < 0)
			icon_x = 0;
		int is_blue = (bat > 10);
		int f = ui_data.charge_anim_frame;
		int px = ui_data.prev_icon_x;

		/* 先画新帧 (偏移 = BASE + frame * STRIDE) */
		if (is_blue)
		{
			Dispphoto_Dispaly_flash(icon_x, BAR_EFFECT_UP_Y,
				FLASH_ADDR_CHARGING_BLUE_UP_BASE + (uint32_t)f * FLASH_STRIDE_CHARGING_BLUE_UP);
			Dispphoto_Dispaly_flash(icon_x, BAR_EFFECT_DN_Y,
				FLASH_ADDR_CHARGING_BLUE_DOWN_BASE + (uint32_t)f * FLASH_STRIDE_CHARGING_BLUE_DOWN);
		}
		else
		{
			Dispphoto_Dispaly_flash(icon_x, BAR_EFFECT_UP_Y,
				FLASH_ADDR_CHARGING_ORANGE_UP_BASE + (uint32_t)f * FLASH_STRIDE_CHARGING_ORANGE_UP);
			Dispphoto_Dispaly_flash(icon_x, BAR_EFFECT_DN_Y,
				FLASH_ADDR_CHARGING_ORANGE_DOWN_BASE + (uint32_t)f * FLASH_STRIDE_CHARGING_ORANGE_DOWN);
		}

		/* 擦除旧图标不重叠部分 (先画后擦, 无闪烁) */
		if (px > 0)
		{
			if (icon_x > px)
			{
				anima_erase_area(px, BAR_EFFECT_UP_Y, icon_x - px, CHARGING_ICON_H);
				anima_erase_area(px, BAR_EFFECT_DN_Y, icon_x - px, CHARGING_ICON_H);
			}
			else if (icon_x < px)
			{
				anima_erase_area(icon_x + CHARGING_ICON_W, BAR_EFFECT_UP_Y,
								 px - icon_x, CHARGING_ICON_H);
				anima_erase_area(icon_x + CHARGING_ICON_W, BAR_EFFECT_DN_Y,
								 px - icon_x, CHARGING_ICON_H);
			}
		}
		ui_data.prev_icon_x = icon_x;

		ui_data.charge_anim_frame = (f + 1) % 25;
	}
	else
	{
		int idx = bat - 1;
		Dispphoto_Dispaly_flash(0, BAR_EFFECT_UP_Y,
			FLASH_ADDR_BLUR_UP_BASE + (uint32_t)idx * FLASH_STRIDE_BLUR_UP);
		Dispphoto_Dispaly_flash(0, BAR_EFFECT_DN_Y,
			FLASH_ADDR_BLUR_DOWN_BASE + (uint32_t)idx * FLASH_STRIDE_BLUR_DOWN);
	}
#endif /* ENABLE_CHARGE_ANIM */
}

void default_page_init()
{
	// 清除屏幕
	DispBlock(0, 0, ROW - 1, COL - 1);

	default_page_show_battery();

	// 显示固定位置图标
	Dispphoto_Dispaly_flash(14, 83, FLASH_ADDR_TYPE_C);
	Dispphoto_Dispaly_flash(46, 83, FLASH_ADDR_USB_1);
	Dispphoto_Dispaly_flash(95, 83, FLASH_ADDR_TYPE_C);
	Dispphoto_Dispaly_flash(127, 83, FLASH_ADDR_USB_2);
	Dispphoto_Dispaly_flash(176, 83, FLASH_ADDR_USB);
	Dispphoto_Dispaly_flash(208, 83, FLASH_ADDR_USB_3);

	// 显示USB功率 (先填满滤波窗口, 避免冷启动被 0 拉低)
	default_page_power_force_redraw(); /* 切页强制重绘 */
		power_filter_fill(C1_POWER, ui_data.usb_c1_power);
	power_filter_fill(C2_POWER, ui_data.usb_c2_power);
	power_filter_fill(A_POWER, ui_data.usb_a_power);
	default_page_show_power(C1_POWER, ui_data.usb_c1_power, ui_data.usb_c1_status);
	default_page_show_power(C2_POWER, ui_data.usb_c2_power, ui_data.usb_c2_status);
	default_page_show_power(A_POWER, ui_data.usb_a_power, ui_data.usb_a_status);

	/* 小电流模式图标: 切页时 init 清屏后需补绘, 否则 updata 里仅变化检测不会触发 */
	if (ui_data.low_current_flag)
		Dispphoto_Dispaly_flash(12, 4, FLASH_ADDR_BATTERY);

	/* 充电剩余时间: 清屏后立即补绘并同步变化检测基准,
	   否则要等分钟数变化才会重新显示 */
	last_remain_min = -1;
	if (ui_data.is_charge)
	{
		int16_t m = calc_charge_remain_min();
		if (m >= 0 && ui_data.bat_power < 100)
		{
			draw_charge_remain_time();
			last_remain_min = m;
		}
	}
}

/* ============================ 数据更新 ============================ */


#ifdef ENABLE_CHARGE_ANIM
/* 主界面动画高频驱动 — ui_proc 每次主循环调用, 不受 500ms 限流,
 * 内部按 ANIM_STEP_MS 自限帧率 (充放电切换动画逐帧 / 充电粒子效果) */
void default_page_anim_proc(void)
{
	static uint32_t anim_ms = 0;
	uint32_t now = md_get_tick();

	if (now - anim_ms < ANIM_STEP_MS)
		return;
	anim_ms = now;

	if (anima_active)
	{
		if (anima_tick())
		{
			/* 动画结束, 最终全量重绘 */
			default_page_show_battery();

			/* V1.3: 充电完成时显示剩余时间 (在 battery 之后绘制, 避免被覆盖) */
			if (anima_is_charge)
				draw_charge_remain_time();
		}
	}
	else if (ui_data.is_charge)
	{
		/* 充电粒子效果逐帧推进 */
		default_page_show_bar_effect();
	}
}
#endif /* ENABLE_CHARGE_ANIM */

void default_page_updata(void)
{
#ifdef ENABLE_CHARGE_ANIM
	/* ---- 充放电切换动画进行中: 帧推进由 default_page_anim_proc 高频驱动,
	        此处暂停普通数据更新 ---- */
	if (anima_active)
		return;
#endif


	int charge_changed = (ui_data.is_charge_last != ui_data.is_charge);

	/* 电量滤波: 滑动平均 + 充电单调增 / 放电单调减 */
	bat_filter_push(ui_data.bat_power);
	ui_data.bat_power = bat_filter_get(ui_data.is_charge);

	int power_changed = (ui_data.bat_power_last != ui_data.bat_power);

	/* 充放电切换: 启动非阻塞动画 (或直接重绘) */
	if (charge_changed) {
		ui_data.prev_disp_w = 0;
		ui_data.is_charge_last = ui_data.is_charge;
		ui_data.bat_power_last = ui_data.bat_power;

		/* V1.3: 充电结束时擦除剩余时间 (动画/非动画路径均需先擦除) */
		if (!ui_data.is_charge)
			erase_charge_remain_time();

#ifdef ENABLE_CHARGE_ANIM
		start_change_anima(ui_data.is_charge);
		return;
#else
		/* 无动画时充放电切换: 擦除电量区(全宽×48) + 进度条周边动画残留 */
		anima_erase_area(0, CHARGE_POWER_Y, SCREEN_W, NUM_48_H);
		anima_erase_area(0, BAR_EFFECT_UP_Y, BAR_PROGRESS_W, BAR_EFFECT_AREA_H);
		default_page_show_battery();

		/* V1.3: 非动画模式充电时立即显示剩余时间 (battery 之后以防覆盖) */
		if (ui_data.is_charge)
			draw_charge_remain_time();

		/* 继续执行USB功率更新, 不return */
#endif
	}

	ui_data.is_charge_last = ui_data.is_charge;
	ui_data.bat_power_last = ui_data.bat_power;

	/* 电量变化时重绘电池+进度条, 充电时每帧更新动画, 否则不更新 */
	if (power_changed || charge_changed)
	{
		/* 满电时 3 位数电量+充电图标会盖到时间区: 先擦时间再重绘电池,
		   图标在擦除之后绘制, 不会被切掉 */
		if (ui_data.is_charge && ui_data.bat_power >= 100)
			erase_charge_remain_time();
		default_page_show_battery();
		/* battery 重绘可能与时间区域重叠, 充电中补绘时间 */
		if (ui_data.is_charge)
			draw_charge_remain_time();
	}
	/* 充电粒子效果已由 default_page_anim_proc 按 ANIM_STEP_MS 高频驱动 */

	/* V1.3: 充电剩余时间每分钟刷新 (动画/非动画模式统一处理) */
	if (ui_data.is_charge)
	{
		int16_t cur_min = calc_charge_remain_min();
		/* 满电时时间区已让位给充电图标, 这里的擦除/重绘都会切掉图标;
		   -1 表示估算未准备好, 不显示 */
		if (ui_data.bat_power < 100 && cur_min >= 0 && cur_min != last_remain_min)
		{
			erase_charge_remain_time();
			draw_charge_remain_time();
			last_remain_min = cur_min;
		}
		else if (ui_data.bat_power < 100 && cur_min < 0 && last_remain_min >= 0)
		{
			/* 估算失效(-1): 清掉残留的旧时间, 恢复有效后会重绘 */
			erase_charge_remain_time();
			last_remain_min = -1;
		}
	}

	/* 各端口功率区域 (变化检测 + 擦除 + 绘制均在函数内部处理) */
	default_page_show_power(C1_POWER, ui_data.usb_c1_power, ui_data.usb_c1_status);
	default_page_show_power(C2_POWER, ui_data.usb_c2_power, ui_data.usb_c2_status);
	default_page_show_power(A_POWER, ui_data.usb_a_power, ui_data.usb_a_status);

	/* 小电流模式标志: 在 (12,4) 显示/清除电池图标 */
	{
		static bool last_flag = false;
		if (ui_data.low_current_flag != last_flag)
		{
			last_flag = ui_data.low_current_flag;
			if (ui_data.low_current_flag)
				Dispphoto_Dispaly_flash(12, 4, FLASH_ADDR_BATTERY);
			else
				anima_erase_area(12, 4, NUM_48_W, NUM_48_H);
		}
	}
}

/* ========================================================================
 * V1.3 剩余充满时间估算 (1s 更新一次, 返回分钟)
 * ======================================================================== */
#define IBAT_BUF_SIZE  10U

static int32_t ibat_buf[IBAT_BUF_SIZE];   /* 电流环形缓冲 */

/* 电池循环降额系数 (%) */
static uint8_t bat_cycle_derate(uint16_t cycle_times)
{
    if (cycle_times >= 210) return 90;
    if (cycle_times >= 140) return 93;
    if (cycle_times >= 70)  return 97;
    return 100;
}

int16_t calc_charge_remain_min(void)
{
    static uint32_t last_ms   = 0;
    static uint8_t  ibat_idx  = 0;
    static uint8_t  ibat_full = 0;

    uint32_t total_cap_mah;         /* 折算后总容量 (mAh)    */
    uint32_t remain_cap;            /* 剩余容量 (mAh)        */
    uint32_t seconds;               /* 剩余时间 (秒)         */
    uint32_t ibat_avg;              /* 平滑电流 (mA)         */
    uint32_t now;
    int32_t  ibat;
    uint8_t  derate;

	if (!ui_data.is_charge || ui_data.bat_power > 100)
	{
		ibat_idx  = 0;              /* 停充清缓冲，避免下次用旧电流 */
		ibat_full = 0;
		return -1;
	}

    /* ---- 1 秒采样 ---- */
    now = md_get_tick();
    if (now - last_ms >= 1000U) {
        last_ms = now;
        ibat = (int32_t)ip3561q_info.current_ma;
        ibat_buf[ibat_idx] = (ibat < 0) ? -ibat : ibat;
        ibat_idx++;
        if (ibat_idx >= IBAT_BUF_SIZE) {
            ibat_idx  = 0;
            ibat_full = 1;
        }
    }

    if (!ibat_full)
        return -1;

    /* 平滑电流（10 点环形缓冲平均） */
    {
        int32_t sum = 0;
        uint8_t i;
        for (i = 0; i < IBAT_BUF_SIZE; i++)
            sum += ibat_buf[i];
        ibat_avg = (uint32_t)(sum / IBAT_BUF_SIZE);
    }
    if (ibat_avg < 50) ibat_avg = 50;   /* 最小电流下限，防除零及极端值 */

    /* 总容量 = 标称容量(5000mAh) * 循环降额系数 */
    derate        = bat_cycle_derate(ui_data.bat_cycle_cnt);
    total_cap_mah = 5000UL * derate / 100U;

    /* ----- 充电剩余时间（秒）----- */
    if (ip3561q_info.current_ma <= 0)
        return -1;

    remain_cap = (uint32_t)(100U - ui_data.bat_power) * total_cap_mah / 100U;
    seconds    = remain_cap * 3600UL / ibat_avg;

    if (seconds > 5999UL * 60U)         /* HH:MM 两位小时, 上限 99:59 */
        seconds = 5999UL * 60U;

    return (int16_t)(seconds / 60U);
}


