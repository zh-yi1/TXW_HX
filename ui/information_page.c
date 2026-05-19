#include "information_page.h"

#define NUM_40_W 24
#define NUM_40_H 40
#define LITTLE_PERCENT_W 16
#define LITTLE_PERCENT_H 16
#define CI_W 16
#define CI_H 16
#define DEGREE_CENTIGRDE_W 16
#define DEGREE_CENTIGRDE_H 16

typedef enum
{
    INFO_MAX_CAP,     /* 最大容量 */
    INFO_CYCLE_CNT,   /* 循环次数 */
    INFO_BAT_TEMP,    /* 电池温度 */
    INFO_BAT_MODEL,   /* 电池型号 */
    INFO_RUN_TIME,    /* 运行时间 */
    INFO_LAST_DISCHG, /* 上次放电电量 */

    INFO_ITEM_MAX,
} bat_info_e;

// TODO :文字切图出来后替换
static const pos_and_addr_t bat_info_text_img[] = {
    {32, 12, FLASH_ADDR_TEMP_BLUE},
    {144, 12, FLASH_ADDR_TEMP_BLUE},
    {88, 12, FLASH_ADDR_TEMP_BLUE},
    {80, 4, FLASH_ADDR_TEMP_BLUE}, // 位置未知
    {80, 4, FLASH_ADDR_TEMP_BLUE}, // 位置未知
    {80, 4, FLASH_ADDR_TEMP_BLUE}, // 位置未知
};

static const range_t bat_info_range[] = {
    {0, 48, 0 + 119, 48 + 39},
    {120, 48, 120 + 119, 48 + 39},
    {0, 48, 0 + 239, 48 + 39},
};

static const uint32_t num_40_addrs[] = {
    FLASH_ADDR_NUM_40_0,
    FLASH_ADDR_NUM_40_1,
    FLASH_ADDR_NUM_40_2,
    FLASH_ADDR_NUM_40_3,
    FLASH_ADDR_NUM_40_4,
    FLASH_ADDR_NUM_40_5,
    FLASH_ADDR_NUM_40_6,
    FLASH_ADDR_NUM_40_7,
    FLASH_ADDR_NUM_40_8,
    FLASH_ADDR_NUM_40_9,
};

/* 在指定区域居中绘制数值 + 单位图标 */
static void draw_value_in_area(range_t r, uint16_t value, uint32_t unit_addr, uint8_t unit_w, uint8_t unit_h)
{
    int digits[4], n, i, cur_x, cur_y;
    int total_w;

    if (value > 9999)
        value = 9999;

    if (value >= 1000)
    {
        digits[0] = value / 1000;
        digits[1] = (value / 100) % 10;
        digits[2] = (value / 10) % 10;
        digits[3] = value % 10;
        n = 4;
    }
    else if (value >= 100)
    {
        digits[0] = value / 100;
        digits[1] = (value / 10) % 10;
        digits[2] = value % 10;
        n = 3;
    }
    else if (value >= 10)
    {
        digits[0] = value / 10;
        digits[1] = value % 10;
        n = 2;
    }
    else
    {
        digits[0] = value;
        n = 1;
    }

    total_w = n * NUM_40_W + unit_w;
    cur_x = r.x1 + (int)(r.x2 - r.x1 - total_w) / 2;
    cur_y = r.y1;

    for (i = 0; i < n; i++)
    {
        Dispphoto_Dispaly_flash(cur_x, cur_y, num_40_addrs[digits[i]]);
        cur_x += NUM_40_W;
    }

    Dispphoto_Dispaly_flash(cur_x, cur_y + NUM_40_H - unit_h, unit_addr);
}

/* 绘制电池信息数值 */
void information_page_show(void)
{
    draw_value_in_area(bat_info_range[INFO_MAX_CAP], ui_data.bat_max_cap,
                       FLASH_ADDR_PERCENT_SMALL, LITTLE_PERCENT_W, LITTLE_PERCENT_H);

    draw_value_in_area(bat_info_range[INFO_CYCLE_CNT], ui_data.bat_cycle_cnt,
                       FLASH_ADDR_CI, CI_W, CI_H);

    draw_value_in_area(bat_info_range[INFO_BAT_TEMP], ui_data.bat_temperature,
                       FLASH_ADDR_DEGREE, DEGREE_CENTIGRDE_W, DEGREE_CENTIGRDE_H);
}

void information_page_1_init(void)
{
    DispBlock(0, 0, ROW - 1, COL - 1);

    // // 最大容量
    Dispphoto_Dispaly_flash(bat_info_text_img[INFO_MAX_CAP].x,
                            bat_info_text_img[INFO_MAX_CAP].y, bat_info_text_img[INFO_MAX_CAP].img_addr);
    // 循环次数
    Dispphoto_Dispaly_flash(bat_info_text_img[INFO_CYCLE_CNT].x,
                            bat_info_text_img[INFO_CYCLE_CNT].y, bat_info_text_img[INFO_CYCLE_CNT].img_addr);
    //最大容量值
    draw_value_in_area(bat_info_range[INFO_MAX_CAP], ui_data.bat_max_cap,
                       FLASH_ADDR_PERCENT_SMALL, LITTLE_PERCENT_W, LITTLE_PERCENT_H);
    //循环次数值
    draw_value_in_area(bat_info_range[INFO_CYCLE_CNT], ui_data.bat_cycle_cnt,
                       FLASH_ADDR_CI, CI_W, CI_H);
    //电池型号
    Dispphoto_Dispaly_flash(bat_info_text_img[INFO_BAT_MODEL].x,
                            bat_info_text_img[INFO_BAT_MODEL].y, bat_info_text_img[INFO_BAT_MODEL].img_addr);
}

void information_page_2_init(void)
{
    DispBlock(0, 0, ROW - 1, COL - 1);

    // 电池温度
    Dispphoto_Dispaly_flash(bat_info_text_img[INFO_BAT_TEMP].x,
                            bat_info_text_img[INFO_BAT_TEMP].y, bat_info_text_img[INFO_BAT_TEMP].img_addr);
    //电池温度值
    draw_value_in_area(bat_info_range[INFO_BAT_TEMP], ui_data.bat_temperature,
                       FLASH_ADDR_DEGREE, DEGREE_CENTIGRDE_W, DEGREE_CENTIGRDE_H);
    //运行时间
    Dispphoto_Dispaly_flash(bat_info_text_img[INFO_RUN_TIME].x,
                            bat_info_text_img[INFO_RUN_TIME].y, bat_info_text_img[INFO_RUN_TIME].img_addr);
    // TODO ：运行时间值

    // 上次放电电量
    Dispphoto_Dispaly_flash(bat_info_text_img[INFO_LAST_DISCHG].x,
                            bat_info_text_img[INFO_LAST_DISCHG].y, bat_info_text_img[INFO_LAST_DISCHG].img_addr);
    // TODO ：上次放电电量值
}
