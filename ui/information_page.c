#include "information_page.h"

#define NUM_40_W 24
#define NUM_40_H 40
#define LITTLE_PERCENT_W 16
#define LITTLE_PERCENT_H 16
#define CI_W 16
#define CI_H 16
#define DEGREE_CENTIGRDE_W 16
#define DEGREE_CENTIGRDE_H 16

#define R_MAX_CAP     ((range_t){0,   48, 119, 87})
#define R_CYCLE_CNT   ((range_t){120, 48, 239, 87})
#define R_BAT_TEMP    ((range_t){0,   48, 239, 87})

#define NUM_40_ADDR(d)  (FLASH_ADDR_NUM_40_BASE + (uint32_t)(d) * FLASH_STRIDE_NUM_40)

/* 总电压显示固定布局 (按 "00-00V" 最大宽度 61px 居中于 240 屏) */
#define VOLT_LABEL_X   60
#define VOLT_LABEL_Y   95
#define VOLT_DIGIT_X   118     /* 60 + 53(label) + 5(gap) */

/* 在指定区域居中绘制数值 + 单位图标 (支持负数) */
static void draw_value_in_area(range_t r, int16_t value, uint32_t unit_addr,
                               uint8_t unit_w, uint8_t unit_h, uint32_t neg_addr)
{
    int digits[4], n, i, cur_x, cur_y;
    int total_w;
    uint8_t neg_w = 0;

    /* 处理负数 */
    if (value < 0) {
        value = -value;
        if (neg_addr != 0)
            neg_w = NUM_40_W;  /* 负号占一个数字宽度 */
    }

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

    total_w = neg_w + n * NUM_40_W + unit_w;
    cur_x = r.x1 + (int)(r.x2 - r.x1 - total_w) / 2;
    cur_y = r.y1;

    /* 负号 */
    if (neg_w)
        Dispphoto_Dispaly_flash(cur_x, cur_y, neg_addr);
    cur_x += neg_w;

    for (i = 0; i < n; i++)
    {
        Dispphoto_Dispaly_flash(cur_x, cur_y, NUM_40_ADDR(digits[i]));
        cur_x += NUM_40_W;
    }

    Dispphoto_Dispaly_flash(cur_x, cur_y + NUM_40_H - unit_h, unit_addr);
}

/* 将 mV 值格式化为电压字符串 "XX<sep>XXV" (buf 至少 8 字节) */
static void fmt_voltage(char *buf, uint16_t mv, char sep)
{
    uint8_t v_int = mv / 1000;
    uint8_t v_dec = (mv % 1000) / 10;
    uint8_t p = 0;

    if (v_int >= 10) { buf[p++] = '0' + v_int / 10; v_int %= 10; }
    buf[p++] = '0' + v_int;
    buf[p++] = sep;
    buf[p++] = '0' + v_dec / 10;
    buf[p++] = '0' + v_dec % 10;
    buf[p++] = 'V';
    buf[p]   = '\0';
}

void information_page_1_init(void)
{
    DispBlock(0, 0, ROW - 1, COL - 1);

    // 最大容量
    Dispphoto_Dispaly_flash(32, 12, FLASH_ADDR_MAX_CAP);
    // 循环次数
    Dispphoto_Dispaly_flash(144, 12, FLASH_ADDR_CYCLE_INDEX);
    //最大容量值
    draw_value_in_area(R_MAX_CAP, ui_data.bat_max_cap,
                       FLASH_ADDR_PERCENT_SMALL, LITTLE_PERCENT_W, LITTLE_PERCENT_H, 0);
    //循环次数值
    draw_value_in_area(R_CYCLE_CNT, ui_data.bat_cycle_cnt,
                       FLASH_ADDR_CI, CI_W, CI_H, 0);
}

void information_page_2_init(void)
{
    DispBlock(0, 0, ROW - 1, COL - 1);

    // 电池温度
    Dispphoto_Dispaly_flash(88, 12, FLASH_ADDR_BAT_TMP);
    //电池温度值
    draw_value_in_area(R_BAT_TEMP, ui_data.bat_temperature / 10,
                       FLASH_ADDR_DEGREE, DEGREE_CENTIGRDE_W, DEGREE_CENTIGRDE_H, FLASH_ADDR_NUM_40);
    //运行时间
    Dispphoto_Dispaly_flash(36, 113, FLASH_ADDR_RUN_TIME);
    // TODO ：运行时间值,当前是假的
    Dispphoto_Dispaly_flash(116, 113, FLASH_ADDR_TIME_FAKE);
}

void information_page_3_init(void)
{
    DispBlock(0, 0, ROW - 1, COL - 1);

    // 电芯电压
    Dispphoto_Dispaly_flash(88, 12, FLASH_ADDR_A_CELL_VOLTAGE);

    /* 4 节电芯: 电压 + 型号, 12 高度蓝色字体 */
    {
        uint8_t i;
        char buf[8];

        const uint8_t cell_y[] = {38, 52, 66, 80};

        for (i = 0; i < 4; i++)
        {
            const char *model;
            uint16_t mv = ui_data.cell_voltage_mv[i];

            fmt_voltage(buf, mv, '.');

            if      (i == 0) model = ui_data.bat_model_1;
            else if (i == 1) model = ui_data.bat_model_2;
            else if (i == 2) model = ui_data.bat_model_3;
            else             model = ui_data.bat_model_4;

            digit_display_string(buf, 13, cell_y[i], DIGIT_16_COLOR_BLUE, DIGIT_HEIGHT_12);
            digit_display_string(model, 55, cell_y[i], DIGIT_16_COLOR_BLUE, DIGIT_HEIGHT_12);
        }
    }

    /* 总电压 = 4 节电芯之和 (mV), 固定位置, 标签不动 */
    {
        uint32_t total_mv;
        char buf[8];

        total_mv = (uint32_t)ui_data.cell_voltage_mv[0] + ui_data.cell_voltage_mv[1]
                 + ui_data.cell_voltage_mv[2] + ui_data.cell_voltage_mv[3];

        fmt_voltage(buf, (uint16_t)total_mv, '.');

        Dispphoto_Dispaly_flash(VOLT_LABEL_X, VOLT_LABEL_Y, FLASH_ADDR_TOTAL_VOLTAGE);
        digit_display_string(buf, VOLT_DIGIT_X, VOLT_LABEL_Y,
                             DIGIT_16_COLOR_WHITE, DIGIT_HEIGHT_16);
    }

    /* 电池型号 */

    Dispphoto_Dispaly_flash(34, 113, FLASH_ADDR_CELL_MODEL);
    digit_display_string("506578AFU", 114, 116,
                             DIGIT_16_COLOR_WHITE, DIGIT_HEIGHT_16);
}

/* ============================ 数据更新 ============================ */

#define BAT_MODEL_X      (98)
#define BAT_MODEL_Y      (113)
#define UPDATE_INTERVAL_MS (3000)

void information_page_1_updata(void)
{
    static uint32_t last_ms       = 0;
    static uint8_t  last_max_cap  = 0xFF;
    static uint16_t last_cycle    = 0xFFFF;
    uint32_t now = md_get_tick();

    /* 首次调用初始化计时 */
    if (last_ms == 0)
        last_ms = now;

    /* 最大容量 — 变化时刷新 */
    if (ui_data.bat_max_cap != last_max_cap)
    {
        draw_value_in_area(R_MAX_CAP, ui_data.bat_max_cap,
                           FLASH_ADDR_PERCENT_SMALL, LITTLE_PERCENT_W, LITTLE_PERCENT_H, 0);
        last_max_cap = ui_data.bat_max_cap;
    }

    /* 循环次数 — 变化时刷新 */
    if (ui_data.bat_cycle_cnt != last_cycle)
    {
        draw_value_in_area(R_CYCLE_CNT, ui_data.bat_cycle_cnt,
                           FLASH_ADDR_CI, CI_W, CI_H, 0);
        last_cycle = ui_data.bat_cycle_cnt;
    }

}

void information_page_2_updata(void)
{
    static int16_t last_temp = 0x7FFF;

    /* 电池温度 — 变化时刷新 */
    if (ui_data.bat_temperature != last_temp)
    {
        /* 先擦除旧值区域, 防止位数变化时残影 */
        DispBlock(0, 48, 239, 87);
        draw_value_in_area(R_BAT_TEMP, ui_data.bat_temperature/10,
                           FLASH_ADDR_DEGREE, DEGREE_CENTIGRDE_W, DEGREE_CENTIGRDE_H,
                           FLASH_ADDR_NUM_40);
        last_temp = ui_data.bat_temperature;
    }

    /* TODO: 刷新运行时间值*/
}

void information_page_3_updata(void)
{
    /* 比较用百分位 (10mV), 与显示精度一致, 避免 mV 级抖动触发无意义刷新 */
    static uint16_t last_mv_cv[4] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    const uint8_t cell_y[] = {38, 52, 66, 80};
    uint8_t i;

    for (i = 0; i < 4; i++)
    {
        uint16_t mv_cv = ui_data.cell_voltage_mv[i] / 10;

        if (mv_cv != last_mv_cv[i])
        {
            char buf[8];

            fmt_voltage(buf, ui_data.cell_voltage_mv[i], '.');

            digit_display_string(buf, 13, cell_y[i],
                                 DIGIT_16_COLOR_BLUE, DIGIT_HEIGHT_12);
            last_mv_cv[i] = mv_cv;
        }
    }

    /* 总电压 — 总和变化时更新 */
    {
        static uint32_t last_total_cv = 0xFFFFFFFF;
        uint32_t total_mv;
        uint32_t total_cv;

        total_mv = (uint32_t)ui_data.cell_voltage_mv[0] + ui_data.cell_voltage_mv[1]
                 + ui_data.cell_voltage_mv[2] + ui_data.cell_voltage_mv[3];
        total_cv = total_mv / 10;

        if (total_cv != last_total_cv)
        {
            char buf[8];

            fmt_voltage(buf, (uint16_t)total_mv, '.');

            digit_display_string(buf, VOLT_DIGIT_X, VOLT_LABEL_Y,
                                 DIGIT_16_COLOR_WHITE, DIGIT_HEIGHT_16);

            last_total_cv = total_cv;
        }
    }
}
