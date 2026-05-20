#include "default_page.h"

// 固定图片位置
static const pos_and_addr_t default_img_pos[] = {
	{14, 83, FLASH_ADDR_TYPE_C},
	{46, 83, FLASH_ADDR_USB_1},
	{95, 83, FLASH_ADDR_TYPE_C},
	{127, 83, FLASH_ADDR_USB_2},
	{176, 83, FLASH_ADDR_USB},
	{208, 83, FLASH_ADDR_USB_3},
};

/* ============================ 小数字功率显示 ============================ */

static const range_t power_range[] = {
	{12, 103, 12 + 55, 103 + 31},
	{92, 103, 92 + 55, 103 + 31},
	{174, 103, 174 + 55, 103 + 31},
};

static const uint32_t num_32_addrs[10] = {
	FLASH_ADDR_NUM_32_0,
	FLASH_ADDR_NUM_32_1,
	FLASH_ADDR_NUM_32_2,
	FLASH_ADDR_NUM_32_3,
	FLASH_ADDR_NUM_32_4,
	FLASH_ADDR_NUM_32_5,
	FLASH_ADDR_NUM_32_6,
	FLASH_ADDR_NUM_32_7,
	FLASH_ADDR_NUM_32_8,
	FLASH_ADDR_NUM_32_9,
};

#define NUM_32_W 20
#define NUM_32_H 32
#define W_W 16
#define W_H 16
#define FREE_H 50
#define FREE_W 32

// 显示功率（is_use 为 false 时居中显示空闲图标）
static void default_page_show_power(power_e port, uint8_t power_value, bool is_use)
{
	int area_x, area_y, area_w;
	int total_w, cur_x, cur_y;
	int tens, ones;

	area_x = power_range[port].x1;
	area_y = power_range[port].y1;
	area_w = power_range[port].x2 - area_x;


	if (!is_use)
	{
		int free_x = area_x + (area_w - FREE_W) / 2;
		int free_y = area_y;
		Dispphoto_Dispaly_flash(free_x, free_y, FLASH_ADDR_FREE);
		return;
	}

	if (power_value > 99)
		power_value = 99;

	tens = power_value / 10;
	ones = power_value % 10;

	total_w = (tens ? 2 : 1) * NUM_32_W + W_W;
	cur_x = area_x + (area_w - total_w + 1) / 2;
	cur_y = area_y;

	if (tens)
	{
		Dispphoto_Dispaly_flash(cur_x, cur_y, num_32_addrs[tens]);
		cur_x += NUM_32_W;
	}

	Dispphoto_Dispaly_flash(cur_x, cur_y, num_32_addrs[ones]);
	cur_x += NUM_32_W + 1;

	Dispphoto_Dispaly_flash(cur_x, cur_y + NUM_32_H - W_H, FLASH_ADDR_W);
}

/* ============================ 充电百分比动画 ============================ */

static const uint32_t blue_num64_addrs[10] = {
	FLASH_ADDR_BLUE_NUM_48_0,
	FLASH_ADDR_BLUE_NUM_48_1,
	FLASH_ADDR_BLUE_NUM_48_2,
	FLASH_ADDR_BLUE_NUM_48_3,
	FLASH_ADDR_BLUE_NUM_48_4,
	FLASH_ADDR_BLUE_NUM_48_5,
	FLASH_ADDR_BLUE_NUM_48_6,
	FLASH_ADDR_BLUE_NUM_48_7,
	FLASH_ADDR_BLUE_NUM_48_8,
	FLASH_ADDR_BLUE_NUM_48_9,
};

static const uint32_t orange_num64_addrs[10] = {
	FLASH_ADDR_ORANGE_NUM_48_0,
	FLASH_ADDR_ORANGE_NUM_48_1,
	FLASH_ADDR_ORANGE_NUM_48_2,
	FLASH_ADDR_ORANGE_NUM_48_3,
	FLASH_ADDR_ORANGE_NUM_48_4,
	FLASH_ADDR_ORANGE_NUM_48_5,
	FLASH_ADDR_ORANGE_NUM_48_6,
	FLASH_ADDR_ORANGE_NUM_48_7,
	FLASH_ADDR_ORANGE_NUM_48_8,
	FLASH_ADDR_ORANGE_NUM_48_9,
};

#define NUM_48_W 40
#define NUM_48_H 48
#define PERCENT_W 24
#define PERCENT_H 24
#define ANIM_STEPS 30
#define SCREEN_W 240

#define CHARGE_POWER_X 12
#define CHARGE_POWER_Y 4
#define NORMAL_POWER_X 72
#define NORMAL_POWER_Y 4

static void anima_erase_area(int x, int y, int w, int h)
{
	DispBlock(x, y, x + w - 1, y + h - 1);
}

/* 在 (x,y) 绘制电量百分比 (同步阻塞) */
static void anima_draw_bat_power(int x, int y, uint8_t power, uint8_t is_blue)
{
	const uint32_t *addrs = is_blue ? blue_num64_addrs : orange_num64_addrs;
	uint32_t percent_addr = is_blue ? FLASH_ADDR_PERCENT_BLUE : FLASH_ADDR_PERCENT_ORANG;
	int digits[3], n, i, cur_x;

	if (power > 100)
		power = 100;
	if (power == 0)
		power = 1;

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
		Dispphoto_Dispaly_flash(cur_x, y, addrs[digits[i]]);
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

void start_change_anima(bool is_charge)
{
	int to_x, from_x, total_w, step;

	ui_data.anim_power = ui_data.bat_power;

	total_w = anima_power_width(ui_data.anim_power);

	if (is_charge)
	{
		/* 未充电 → 充电: 居中 → 左对齐 */
		from_x = (SCREEN_W - total_w) / 2;
		to_x = CHARGE_POWER_X;
	}
	else
	{
		/* 充电 → 未充电: 先擦充电图标, 再左对齐 → 居中 */
		int n = (ui_data.anim_power >= 100) ? 3 : (ui_data.anim_power >= 10) ? 2
																			 : 1;
		int icon_x = ui_data.anim_cur_x + n * NUM_48_W;
		anima_erase_area(icon_x, CHARGE_POWER_Y, NUM_48_W, NUM_48_H);

		from_x = CHARGE_POWER_X;
		to_x = (SCREEN_W - total_w) / 2;
	}

	for (step = 0; step <= ANIM_STEPS; step++)
	{
		int prev_x = ui_data.anim_cur_x;

		ui_data.anim_cur_x = from_x + (to_x - from_x) * step / ANIM_STEPS;

		/* 先画新帧 */
		anima_draw_bat_power(ui_data.anim_cur_x, CHARGE_POWER_Y,
							 ui_data.anim_power, (ui_data.bat_power > 10));

		/* 擦除旧帧不重叠的边角 (先画后擦, 无闪烁) */
		if (step > 0)
		{
			if (ui_data.anim_cur_x > prev_x)
				anima_erase_area(prev_x, CHARGE_POWER_Y, ui_data.anim_cur_x - prev_x, NUM_48_H);
			else if (ui_data.anim_cur_x < prev_x)
				anima_erase_area(ui_data.anim_cur_x + total_w, CHARGE_POWER_Y,
								 prev_x - ui_data.anim_cur_x, NUM_48_H);
		}

		if (step < ANIM_STEPS)
			md_delay_1ms(5);
	}

	/* 动画结束, 充电时在 % 右侧显示充电图标 */
	if (is_charge)
	{
		int n = (ui_data.anim_power >= 100) ? 3 : (ui_data.anim_power >= 10) ? 2
																			 : 1;
		int icon_x = ui_data.anim_cur_x + n * NUM_48_W;
		uint32_t icon_addr = (ui_data.bat_power > 10)
								 ? FLASH_ADDR_CHARGING_BLUE
								 : FLASH_ADDR_CHARGING_ORANGE;
		Dispphoto_Dispaly_flash(icon_x, CHARGE_POWER_Y, icon_addr);
	}
}

static const uint32_t charging_blue_anima[25] = {
	// FLASH_ADDR_CHARGING_BLUE_0001,
	// FLASH_ADDR_CHARGING_BLUE_0002,
	// FLASH_ADDR_CHARGING_BLUE_0003,
	// FLASH_ADDR_CHARGING_BLUE_0004,
	// FLASH_ADDR_CHARGING_BLUE_0005,
	// FLASH_ADDR_CHARGING_BLUE_0006,
	// FLASH_ADDR_CHARGING_BLUE_0007,
	// FLASH_ADDR_CHARGING_BLUE_0008,
	// FLASH_ADDR_CHARGING_BLUE_0009,
	// FLASH_ADDR_CHARGING_BLUE_0010,
	// FLASH_ADDR_CHARGING_BLUE_0011,
	// FLASH_ADDR_CHARGING_BLUE_0012,
	// FLASH_ADDR_CHARGING_BLUE_0013,
	// FLASH_ADDR_CHARGING_BLUE_0014,
	// FLASH_ADDR_CHARGING_BLUE_0015,
	// FLASH_ADDR_CHARGING_BLUE_0016,
	// FLASH_ADDR_CHARGING_BLUE_0017,
	// FLASH_ADDR_CHARGING_BLUE_0018,
	// FLASH_ADDR_CHARGING_BLUE_0019,
	// FLASH_ADDR_CHARGING_BLUE_0020,
	// FLASH_ADDR_CHARGING_BLUE_0021,
	// FLASH_ADDR_CHARGING_BLUE_0022,
	// FLASH_ADDR_CHARGING_BLUE_0023,
	// FLASH_ADDR_CHARGING_BLUE_0024,
	// FLASH_ADDR_CHARGING_BLUE_0025,
};

void draw_charging_blue_anima()
{
	int frame = 0;
	while (1)
	{
		Dispphoto_Dispaly_flash(0, 0, charging_blue_anima[frame]);
		md_delay_1ms(10);

		frame++;
		if (frame >= 25)
		{
			frame = 0;
		}
	}
}

/* ============================ 电量显示 ============================ */
#define BAR_PROGRESS_X 0
#define BAR_PROGRESS_Y 65

#include "bar_progress.h"

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
		int n = (ui_data.bat_power >= 100) ? 3 : (ui_data.bat_power >= 10) ? 2 : 1;
		int icon_x = x + n * NUM_48_W;
		uint32_t icon_addr = (ui_data.bat_power > 10)
		                     ? FLASH_ADDR_CHARGING_BLUE : FLASH_ADDR_CHARGING_ORANGE;
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

#define BAR_EFFECT_UP_Y   (BAR_PROGRESS_Y - CHARGING_ICON_H)
#define BAR_EFFECT_DN_Y   (BAR_PROGRESS_Y + BAR_PROGRESS_H)
#define BAR_EFFECT_AREA_H (CHARGING_ICON_H + BAR_PROGRESS_H + BLUR_H)

static void default_page_show_bar_effect(void)
{
	int bat = ui_data.bat_power;
	int fill_x;

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

	Dispphoto_Dispaly_flash(BAR_PROGRESS_X, BAR_PROGRESS_Y, progress_bar[bat - 1]);

	fill_x = bat * BAR_PROGRESS_W / 100;

	if (ui_data.is_charge)
	{
		int icon_x = fill_x - CHARGING_ICON_W;
		if (icon_x < 0) icon_x = 0;
		int is_blue = (bat > 10);
		int f = ui_data.charge_anim_frame;
		int px = ui_data.prev_icon_x;

		/* 先画新帧 */
		if (is_blue)
		{
			Dispphoto_Dispaly_flash(icon_x, BAR_EFFECT_UP_Y, charging_blue_up[f]);
			Dispphoto_Dispaly_flash(icon_x, BAR_EFFECT_DN_Y, charging_blue_down[f]);
		}
		else
		{
			Dispphoto_Dispaly_flash(icon_x, BAR_EFFECT_UP_Y, charging_orange_up[f]);
			Dispphoto_Dispaly_flash(icon_x, BAR_EFFECT_DN_Y, charging_orange_down[f]);
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
		Dispphoto_Dispaly_flash(0, BAR_EFFECT_UP_Y, blur_up[idx]);
		Dispphoto_Dispaly_flash(0, BAR_EFFECT_DN_Y, blur_down[idx]);
	}
}


void default_page_init()
{
	// 清除屏幕
	DispBlock(0, 0, ROW - 1, COL - 1);

	default_page_show_battery();

	// 显示固定位置图标
	for (int i = 0; i < sizeof(default_img_pos) / sizeof(default_img_pos[0]); i++)
	{
		Dispphoto_Dispaly_flash(default_img_pos[i].x, default_img_pos[i].y, default_img_pos[i].img_addr);
	}

	// 显示USB功率
	default_page_show_power(C1_POWER, ui_data.usb_c1_power, ui_data.usb_c1_is_use);
	default_page_show_power(C2_POWER, ui_data.usb_c2_power, ui_data.usb_c2_is_use);
	default_page_show_power(A_POWER, ui_data.usb_a_power, ui_data.usb_a_is_use);
}

/* ============================ 数据更新 ============================ */

void default_page_updata(void)
{
	int charge_changed = (ui_data.is_charge_last != ui_data.is_charge);
	int power_changed  = (ui_data.bat_power_last != ui_data.bat_power);

	/* 充放电切换时重置追踪, 强制全量重绘避免位置偏差 */
	if (charge_changed)
		ui_data.prev_disp_w = 0;

	ui_data.is_charge_last = ui_data.is_charge;
	ui_data.bat_power_last = ui_data.bat_power;

	/* 电量百分比只在数值变化或充放电切换时重绘, 动画每帧更新进度条区域 */
	if (power_changed || charge_changed)
		default_page_show_battery();
	else
		default_page_show_bar_effect();

	/* 仅状态或数值变化时才擦除并重绘各端口功率区域 */
	if (ui_data.usb_c1_is_use != ui_data.usb_c1_is_use_last
		|| ui_data.usb_c1_power != ui_data.usb_c1_power_last)
	{
		const range_t *r = &power_range[C1_POWER];
		anima_erase_area(r->x1, r->y1, r->x2 - r->x1, r->y2 - r->y1);
		default_page_show_power(C1_POWER, ui_data.usb_c1_power, ui_data.usb_c1_is_use);
		ui_data.usb_c1_is_use_last = ui_data.usb_c1_is_use;
		ui_data.usb_c1_power_last = ui_data.usb_c1_power;
	}

	if (ui_data.usb_c2_is_use != ui_data.usb_c2_is_use_last
		|| ui_data.usb_c2_power != ui_data.usb_c2_power_last)
	{
		const range_t *r = &power_range[C2_POWER];
		anima_erase_area(r->x1, r->y1, r->x2 - r->x1, r->y2 - r->y1);
		default_page_show_power(C2_POWER, ui_data.usb_c2_power, ui_data.usb_c2_is_use);
		ui_data.usb_c2_is_use_last = ui_data.usb_c2_is_use;
		ui_data.usb_c2_power_last = ui_data.usb_c2_power;
	}

	if (ui_data.usb_a_is_use != ui_data.usb_a_is_use_last
		|| ui_data.usb_a_power != ui_data.usb_a_power_last)
	{
		const range_t *r = &power_range[A_POWER];
		anima_erase_area(r->x1, r->y1, r->x2 - r->x1, r->y2 - r->y1);
		default_page_show_power(A_POWER, ui_data.usb_a_power, ui_data.usb_a_is_use);
		ui_data.usb_a_is_use_last = ui_data.usb_a_is_use;
		ui_data.usb_a_power_last = ui_data.usb_a_power;
	}

}

/* ============================ 测试函数 ============================ */

void default_page_test(void)
{
	int frame_cnt = 0;

	/* 设置测试数据 */
	ui_data.bat_power     = 5;
	ui_data.is_charge     = 0;
	ui_data.usb_c1_is_use = true;
	ui_data.usb_c1_power  = 60;
	ui_data.usb_c2_is_use = false;
	ui_data.usb_c2_power  = 0;
	ui_data.usb_a_is_use  = true;
	ui_data.usb_a_power   = 10;

	default_page_init();

	ui_data.is_charge = 1;
	start_change_anima(ui_data.is_charge);

	/* 模拟充电过程 5→100, 动画持续播放 */
	while (ui_data.bat_power < 100)
	{
		md_delay_1ms(20);
		frame_cnt++;

		if (frame_cnt >= 15)
		{
			frame_cnt = 0;
			if (ui_data.bat_power < 10)
				ui_data.bat_power += 1;
			else
				ui_data.bat_power += 10;
			if (ui_data.bat_power > 100)
				ui_data.bat_power = 100;
		}

		default_page_updata();
	}

	/* 充满, 播放充电结束动画 */
	ui_data.is_charge = 0;
	// default_page_updata();
	Dispphoto_Dispaly_flash(0, BAR_EFFECT_UP_Y, blur_up[ui_data.bat_power-1]);
	Dispphoto_Dispaly_flash(0, BAR_EFFECT_DN_Y, blur_down[ui_data.bat_power-1]);
	start_change_anima(ui_data.is_charge);

	frame_cnt = 0;

	/* 模拟掉电过程 100→1, 动画持续播放 */
	while (ui_data.bat_power > 1)
	{
		md_delay_1ms(20);
		frame_cnt++;

		if (frame_cnt >= 15)
		{
			frame_cnt = 0;
			if (ui_data.bat_power > 10)
				ui_data.bat_power -= 5;
			else
				ui_data.bat_power -= 1;
			if (ui_data.bat_power < 1)
				ui_data.bat_power = 1;
		}

		default_page_updata();
	}
}
