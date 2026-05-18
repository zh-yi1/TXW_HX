#include "default_page.h"

default_page_t default_page = {
    .bat_power = 50,
    .is_charge = 1,
    .usb_c1_is_use = true,
    .usb_c1_power = 5,
    .usb_c2_is_use = true,
    .usb_c2_power = 30,
    .usb_a_is_use = true,
    .usb_a_power = 10,
    .count_down = 0,
};

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

typedef enum
{
	TYPE_C1_IMG = 0,
	C1_IMG,
	TYPE_C2_IMG = 1,
	C2_IMG,
	USB_A_IMG = 2,
	A_IMG,
} default_img_e;

pos_and_addr_t default_img_pos[] = {
	{12,  69,  FLASH_ADDR_TYPE_C},
	{48,  77,  FLASH_ADDR_C_1},
	{91,  69,  FLASH_ADDR_TYPE_C},
	{123, 77,  FLASH_ADDR_C_2},
	{174, 69,   FLASH_ADDR_USB},
	{206, 77,  FLASH_ADDR_A},  // TODO
};

/* ============================ 小数字功率显示 ============================ */

typedef enum
{
	C1_POWER,
	C2_POWER,
	A_POWER,
} power_e;

range_t power_range[] = {
	{12,  99,  12 + 55,  99 + 31},
	{91,  99,  91 + 55,  99 + 31},
	{174, 99,  174 + 55, 99 + 31},
};

static const uint32_t num_32_addrs[10] = {
	FLASH_ADDR_NUM_32_0, FLASH_ADDR_NUM_32_1, FLASH_ADDR_NUM_32_2,
	FLASH_ADDR_NUM_32_3, FLASH_ADDR_NUM_32_4, FLASH_ADDR_NUM_32_5,
	FLASH_ADDR_NUM_32_6, FLASH_ADDR_NUM_32_7, FLASH_ADDR_NUM_32_8,
	FLASH_ADDR_NUM_32_9,
};

#define NUM_32_W   20
#define NUM_32_H   32
#define W_W        16
#define W_H        16

// 显示功率
void default_page_show_power(power_e port, uint8_t power_value)
{
	int area_x, area_y, area_w, area_h;
	int total_w, cur_x, cur_y;
	int tens, ones;

	if (power_value > 99) power_value = 99;

	area_x = power_range[port].x1;
	area_y = power_range[port].y1;
	area_w = power_range[port].x2 - area_x;
	area_h = power_range[port].y2 - area_y;

	tens = power_value / 10;
	ones = power_value % 10;

	total_w = (tens ? 2 : 1) * NUM_32_W + W_W;
	cur_x   = area_x + (area_w - total_w + 1) / 2;
	cur_y   = area_y;

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
	FLASH_ADDR_BLUE_NUM_64_0, FLASH_ADDR_BLUE_NUM_64_1, FLASH_ADDR_BLUE_NUM_64_2,
	FLASH_ADDR_BLUE_NUM_64_3, FLASH_ADDR_BLUE_NUM_64_4, FLASH_ADDR_BLUE_NUM_64_5,
	FLASH_ADDR_BLUE_NUM_64_6, FLASH_ADDR_BLUE_NUM_64_7, FLASH_ADDR_BLUE_NUM_64_8,
	FLASH_ADDR_BLUE_NUM_64_9,
};

static const uint32_t orange_num64_addrs[10] = {
	FLASH_ADDR_ORANGE_NUM_64_0, FLASH_ADDR_ORANGE_NUM_64_1, FLASH_ADDR_ORANGE_NUM_64_2,
	FLASH_ADDR_ORANGE_NUM_64_3, FLASH_ADDR_ORANGE_NUM_64_4, FLASH_ADDR_ORANGE_NUM_64_5,
	FLASH_ADDR_ORANGE_NUM_64_6, FLASH_ADDR_ORANGE_NUM_64_7, FLASH_ADDR_ORANGE_NUM_64_8,
	FLASH_ADDR_ORANGE_NUM_64_9,
};

#define NUM_64_W     40
#define NUM_64_H     64
#define PERCENT_W    24
#define PERCENT_H    24
#define ANIM_STEPS   30
#define SCREEN_W     240

static int      anim_cur_x;		/* 当前 X 位置 */
static uint8_t  anim_power;		/* 电量值 1-100 */
static uint8_t  anim_is_blue;		/* 蓝色/橙色 */

void anima_erase_area(int x, int y, int w, int h)
{
	DispBlock(x, y, x + w - 1, y + h - 1);
}

/* 在 (x,y) 绘制电量百分比 (同步阻塞) */
static void anima_draw_power(int x, int y, uint8_t power, uint8_t is_blue)
{
	const uint32_t *addrs = is_blue ? blue_num64_addrs : orange_num64_addrs;
	uint32_t percent_addr = is_blue ? FLASH_ADDR_PERCENT_BLUE : FLASH_ADDR_PERCENT_ORANG;
	int digits[3], n, i, cur_x;

	if (power > 100) power = 100;
	if (power == 0) power = 1;

	/* 拆位 */
	if (power >= 100) { digits[0] = power/100; digits[1] = (power/10)%10; digits[2] = power%10; n = 3; }
	else if (power >= 10) { digits[0] = power/10; digits[1] = power%10; n = 2; }
	else { digits[0] = power; n = 1; }

	cur_x = x;
	for (i = 0; i < n; i++)
	{
		Dispphoto_Dispaly_flash(cur_x, y, addrs[digits[i]]);
		cur_x += NUM_64_W;
	}

	/* 百分号 */
	Dispphoto_Dispaly_flash(cur_x, y + 31, percent_addr);
}

/* 计算百分比总宽度 */
static int anima_power_width(uint8_t power)
{
	int n = (power >= 100) ? 3 : (power >= 10) ? 2 : 1;
	return n * NUM_64_W + PERCENT_W;
}

void start_change_anima(bool is_charge)
{
	int to_x, from_x, total_w, step;

	anim_power   = default_page.bat_power;
	anim_is_blue = (anim_power > 10);

	total_w = anima_power_width(anim_power);

	if (is_charge)
	{
		/* 未充电 → 充电: 中心 → 左对齐 */
		from_x = (SCREEN_W - total_w) / 2;
		to_x   = 12;
	}
	else
	{
		/* 充电 → 未充电: 先擦充电图标, 再左对齐 → 中心 */
		int n = (anim_power >= 100) ? 3 : (anim_power >= 10) ? 2 : 1;
		int icon_x = anim_cur_x + n * NUM_64_W;
		anima_erase_area(icon_x, 0, NUM_64_W, NUM_64_H);

		from_x = 12;
		to_x   = (SCREEN_W - total_w) / 2;
	}

	for (step = 0; step <= ANIM_STEPS; step++)
	{
		int prev_x = anim_cur_x;

		anim_cur_x = from_x + (to_x - from_x) * step / ANIM_STEPS;

		/* 先画新帧 */
		anima_draw_power(anim_cur_x, 0, anim_power, anim_is_blue);

		/* 擦除旧帧不重叠的边角 (先画后擦, 无闪烁) */
		if (step > 0)
		{
			if (anim_cur_x > prev_x)
				anima_erase_area(prev_x, 0, anim_cur_x - prev_x, NUM_64_H);
			else if (anim_cur_x < prev_x)
				anima_erase_area(anim_cur_x + total_w, 0, prev_x - anim_cur_x, NUM_64_H);
		}

		if (step < ANIM_STEPS)
			md_delay_1ms(10);
	}

	/* 动画结束, 充电时在 % 相同 x, y=0 显示充电图标 */
	if (is_charge)
	{
		int n = (anim_power >= 100) ? 3 : (anim_power >= 10) ? 2 : 1;
		int icon_x = anim_cur_x + n * NUM_64_W;
		uint32_t icon_addr = anim_is_blue ? FLASH_ADDR_CHARGING_BLUE : FLASH_ADDR_CHARGING_ORANGE;
		Dispphoto_Dispaly_flash(icon_x, 0, icon_addr);
	}
}


static const uint32_t charging_blue_anima[25] = {
	FLASH_ADDR_CHARGING_BLUE_0001, FLASH_ADDR_CHARGING_BLUE_0002, FLASH_ADDR_CHARGING_BLUE_0003,
	FLASH_ADDR_CHARGING_BLUE_0004, FLASH_ADDR_CHARGING_BLUE_0005, FLASH_ADDR_CHARGING_BLUE_0006,
	FLASH_ADDR_CHARGING_BLUE_0007, FLASH_ADDR_CHARGING_BLUE_0008, FLASH_ADDR_CHARGING_BLUE_0009,
	FLASH_ADDR_CHARGING_BLUE_0010, FLASH_ADDR_CHARGING_BLUE_0011, FLASH_ADDR_CHARGING_BLUE_0012,
	FLASH_ADDR_CHARGING_BLUE_0013, FLASH_ADDR_CHARGING_BLUE_0014, FLASH_ADDR_CHARGING_BLUE_0015,
	FLASH_ADDR_CHARGING_BLUE_0016, FLASH_ADDR_CHARGING_BLUE_0017, FLASH_ADDR_CHARGING_BLUE_0018,
	FLASH_ADDR_CHARGING_BLUE_0019, FLASH_ADDR_CHARGING_BLUE_0020, FLASH_ADDR_CHARGING_BLUE_0021, 
    FLASH_ADDR_CHARGING_BLUE_0022, FLASH_ADDR_CHARGING_BLUE_0023, FLASH_ADDR_CHARGING_BLUE_0024, 
    FLASH_ADDR_CHARGING_BLUE_0025,
};

void draw_charging_blue_anima()
{
    int frame = 0;
    while(1)
    {
        Dispphoto_Dispaly_flash(0, 0, charging_blue_anima[frame]);
        md_delay_1ms(10);

        frame++;
        if(frame >= 25)
        {
            frame = 0;
        }
    }
}

void default_page_init()
{
	DispBlock(0, 0, 240, 135);

    //显示固定位置
    for(int i=0; i<sizeof(default_img_pos)/sizeof(default_img_pos[0]); i++)
    {
        Dispphoto_Dispaly_flash(default_img_pos[i].x, default_img_pos[i].y, default_img_pos[i].img_addr);
    }

    default_page_show_power(C1_POWER, default_page.usb_c1_power);
    default_page_show_power(C2_POWER, default_page.usb_c2_power);
    default_page_show_power(A_POWER, default_page.usb_a_power);
    
    // start_change_anima(default_page.is_charge);
    anima_draw_power(12, 0, 50, 1);
    start_change_anima(0);
}
