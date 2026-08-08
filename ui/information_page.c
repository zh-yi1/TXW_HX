#include "information_page.h"

/* 40 号比例数字 — 0 和 2~9 宽 23, 数字"1"/负号/单位(%/次/℃) 宽 16, 高均 40 */
#define NUM_40_PROP_W 23
#define NUM_40_ONE_W  16
#define NUM_40_NEG_W  16
#define UNIT_40_W     16

/* ---- 信息页1 布局 ----
 * 标签 120x32: 电池健康 (0,20), 循环次数 (120,20), 左右各占半屏
 * 值 40 高, y=75, 各自在标签正下方居中 —— 即左半区 [0,119] / 右半区 [120,239] 居中 */
#define INFO1_LABEL_Y  20
#define INFO1_VAL_Y    75

#define R_HEALTH_VAL  ((range_t){0,   INFO1_VAL_Y, 119, INFO1_VAL_Y + 39})
#define R_CYCLE_VAL   ((range_t){120, INFO1_VAL_Y, 239, INFO1_VAL_Y + 39})

/* ---- 信息页2 布局 ----
 * 标签 电池温度 240x32 @ (0,20), 温度值 40 高 @ y=75, 整屏居中 */
#define INFO2_LABEL_Y  20
#define INFO2_VAL_Y    75

#define R_BAT_TEMP    ((range_t){0, INFO2_VAL_Y, 239, INFO2_VAL_Y + 39})

#define NUM_40_ADDR(d)  (FLASH_ADDR_NUM_40_BASE + (uint32_t)(d) * FLASH_STRIDE_NUM_40)

/* ============================ 温度滤波 ============================ */

#define TEMP_FILTER_WIN 5

static int16_t temp_filter_buf[TEMP_FILTER_WIN];
static uint8_t temp_filter_idx;
static bool    temp_filter_full;

static void temp_filter_push(int16_t value)
{
	uint8_t i = temp_filter_idx;
	temp_filter_buf[i] = value;
	i++;
	if (i >= TEMP_FILTER_WIN) {
		i = 0;
		temp_filter_full = true;
	}
	temp_filter_idx = i;
}

static int16_t temp_filter_get(void)
{
	uint8_t cnt = temp_filter_full ? TEMP_FILTER_WIN : temp_filter_idx;
	int32_t sum = 0;
	uint8_t i;
	if (cnt == 0) return 0;
	for (i = 0; i < cnt; i++)
		sum += temp_filter_buf[i];
	return (int16_t)(sum / cnt);
}

/* ================================================================ */

/* ---- 信息页3 布局 ----
 * 标签 电池电压 240x32 @ (0,0)
 * 4 节电芯每行: 电压串 x=19, 电芯型号串 x=61, 12 号字体 (字符高 10) */
#define INFO3_VOLT_X   19
#define INFO3_CELL_X   61
static const uint8_t info3_row_y[4] = { 42, 56, 70, 84 };

/* 总电压: 标签 (60,99), 数值 (120,99) */
#define VOLT_LABEL_X   60
#define VOLT_LABEL_Y   99
#define VOLT_DIGIT_X   120
#define VOLT_DIGIT_R   239     /* 该行 120~239 只有总电压数值, 擦尾不会碰到别的内容 */

/* 电芯型号: 标签 (31,119) 78x16, 型号串 (109,119) */
#define MODEL_LABEL_X  31
#define MODEL_LABEL_Y  119
#define MODEL_TEXT_X   109

/* 清尾宽度: "XX.XXV" 共 4 位数字, 每位由 11 宽变 "1"(7 宽) 少 4px,
 * 全变 "1" 最多左移 16px。不判断实际有几个 "1", 一律按最坏情况擦 24px */
#define VOLT_ERASE_W   24

/* 40 号数字比例宽度: 数字"1" 较窄 */
static uint8_t num40_prop_w(int d)
{
    return (d == 1) ? NUM_40_ONE_W : NUM_40_PROP_W;
}

/* 在区域内水平居中绘制 40 号比例数值 + 单位, 顶部对齐 r.y1; neg_addr!=0 时支持负数
 * out_x/out_w 非空时回传本次绘制占用的水平跨度 (起点 x, 总宽), 供覆盖式刷新擦边角 */
static void draw_value_prop(range_t r, int value, uint32_t unit_addr,
                           uint8_t unit_w, uint32_t neg_addr,
                           int *out_x, int *out_w)
{
    int digits[4], n, i, cur_x, start_x, total_w = 0;
    uint8_t neg_w = 0;

    if (value < 0)
    {
        value = -value;
        if (neg_addr != 0)
            neg_w = NUM_40_NEG_W;
    }
    if (value > 9999) value = 9999;

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

    for (i = 0; i < n; i++)
        total_w += num40_prop_w(digits[i]);
    total_w += neg_w + unit_w;

    start_x = r.x1 + (int)(r.x2 - r.x1 - total_w) / 2;
    cur_x = start_x;
    if (neg_w)
    {
        Dispphoto_Dispaly_flash(cur_x, r.y1, neg_addr);
        cur_x += neg_w;
    }
    for (i = 0; i < n; i++)
    {
        Dispphoto_Dispaly_flash(cur_x, r.y1, NUM_40_ADDR(digits[i]));
        cur_x += num40_prop_w(digits[i]);
    }
    Dispphoto_Dispaly_flash(cur_x, r.y1, unit_addr);

    if (out_x) *out_x = start_x;
    if (out_w) *out_w = total_w;
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

/* 温度值当前占用的水平像素跨度 (起点 x, 总宽), 供覆盖式刷新只擦左右边角 */
static int temp_val_x;
static int temp_val_w;

/* 页3 电芯电压串当前宽度, 供先写后擦只擦右侧残留 */
static uint8_t cell_v_w[4];

void information_page_1_init(void)
{
    DispBlock(0, 0, ROW - 1, COL - 1);

    // 电池健康 (0,20, 120x32)
    Dispphoto_Dispaly_flash(0, INFO1_LABEL_Y, FLASH_ADDR_HEALTH);
    // 循环次数 (120,20, 120x32)
    Dispphoto_Dispaly_flash(120, INFO1_LABEL_Y, FLASH_ADDR_CYCLE_INDEX);
    // 健康值 (电池健康正下方居中, 单位 %)
    draw_value_prop(R_HEALTH_VAL, ui_data.bat_max_cap, FLASH_ADDR_NUM_40_PERCENT, UNIT_40_W, 0, NULL, NULL);
    // 次数值 (循环次数正下方居中, 单位 次)
    draw_value_prop(R_CYCLE_VAL, ui_data.bat_cycle_cnt, FLASH_ADDR_CI, UNIT_40_W, 0, NULL, NULL);
}

void information_page_2_init(void)
{
    DispBlock(0, 0, ROW - 1, COL - 1);

    /* 填满温度滤波窗口, 避免冷启动被零值拉低 */
    uint8_t fi;
    for (fi = 0; fi < TEMP_FILTER_WIN; fi++)
        temp_filter_push(ui_data.bat_temperature);
    

    // 电池温度 (0,20, 240x32)
    Dispphoto_Dispaly_flash(0, INFO2_LABEL_Y, FLASH_ADDR_BAT_TMP);
    //电池温度值 (整屏居中, y=75, 40 号字体, 单位 ℃, 支持负号)
    draw_value_prop(R_BAT_TEMP, temp_filter_get() / 10,
                    FLASH_ADDR_NUM_40_DEGREE, UNIT_40_W, FLASH_ADDR_NUM_40,
                    &temp_val_x, &temp_val_w);
}

void information_page_3_init(void)
{
    DispBlock(0, 0, ROW - 1, COL - 1);

    // 电芯电压 (0,0, 240x32)
    Dispphoto_Dispaly_flash(0, 0, FLASH_ADDR_A_CELL_VOLTAGE);

    /* 4 节电芯: 电压 + 型号, 12 号字体 */
    {
        uint8_t i;
        char buf[8];

        for (i = 0; i < 4; i++)
        {
            const char *model;
            uint16_t mv = ui_data.cell_voltage_mv[i];

            fmt_voltage(buf, mv, '.');

            if      (i == 0) model = ui_data.bat_model_1;
            else if (i == 1) model = ui_data.bat_model_2;
            else if (i == 2) model = ui_data.bat_model_3;
            else             model = ui_data.bat_model_4;

            digit_display_string(buf, INFO3_VOLT_X, info3_row_y[i], DIGIT_HEIGHT_12);
            cell_v_w[i] = (uint8_t)digit_string_width(buf, DIGIT_HEIGHT_12);
            digit_display_string(model, INFO3_CELL_X, info3_row_y[i], DIGIT_HEIGHT_12);
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
        digit_display_string(buf, VOLT_DIGIT_X, VOLT_LABEL_Y, DIGIT_HEIGHT_16);
    }

    /* 电芯型号 (标签 31,119 78x16, 型号串 109,119) */
    Dispphoto_Dispaly_flash(MODEL_LABEL_X, MODEL_LABEL_Y, FLASH_ADDR_BAT_NUM);
    digit_display_string("506578AFU", MODEL_TEXT_X, MODEL_LABEL_Y, DIGIT_HEIGHT_16);
}

/* ============================ 数据更新 ============================ */

void information_page_1_updata(void)
{
    static uint8_t  last_max_cap = 0xFF;
    static uint16_t last_cycle   = 0xFFFF;

    /* 健康值 — 变化时先擦除再重绘 (比例宽度, 居中位置随数值变化) */
    if (ui_data.bat_max_cap != last_max_cap)
    {
        DispBlock(R_HEALTH_VAL.x1, R_HEALTH_VAL.y1, R_HEALTH_VAL.x2, R_HEALTH_VAL.y2);
        draw_value_prop(R_HEALTH_VAL, ui_data.bat_max_cap, FLASH_ADDR_NUM_40_PERCENT, UNIT_40_W, 0, NULL, NULL);
        last_max_cap = ui_data.bat_max_cap;
    }

    /* 次数值 — 变化时先擦除再重绘 */
    if (ui_data.bat_cycle_cnt != last_cycle)
    {
        DispBlock(R_CYCLE_VAL.x1, R_CYCLE_VAL.y1, R_CYCLE_VAL.x2, R_CYCLE_VAL.y2);
        draw_value_prop(R_CYCLE_VAL, ui_data.bat_cycle_cnt, FLASH_ADDR_CI, UNIT_40_W, 0, NULL, NULL);
        last_cycle = ui_data.bat_cycle_cnt;
    }
}

void information_page_2_updata(void)
{
    static int16_t last_temp_c = 0x7FFF;

    /* 电池温度 — 滤波后个位(℃)变化才刷新 */
    temp_filter_push(ui_data.bat_temperature);
    {
        int16_t filtered = temp_filter_get();
        int16_t temp_c   = filtered / 10;
        if (temp_c != last_temp_c)
        {
            /* 覆盖式刷新: 先画新值 (不透明, 盖住重叠区), 再只擦旧值比新值多出的左右边角,
             * 避免整区先黑后写造成的闪烁 */
            int old_l = temp_val_x;
            int old_r = temp_val_x + temp_val_w;
            int nx, nw;
            draw_value_prop(R_BAT_TEMP, temp_c,
                            FLASH_ADDR_NUM_40_DEGREE, UNIT_40_W, FLASH_ADDR_NUM_40,
                            &nx, &nw);
            if (temp_val_w > 0)
            {
                if (old_l < nx)                 /* 左边角: 旧值左端露出部分 */
                    DispBlock(old_l, R_BAT_TEMP.y1, nx - 1, R_BAT_TEMP.y2);
                if (nx + nw < old_r)            /* 右边角: 旧值右端露出部分 */
                    DispBlock(nx + nw, R_BAT_TEMP.y1, old_r - 1, R_BAT_TEMP.y2);
            }
            temp_val_x = nx;
            temp_val_w = nw;
            last_temp_c = temp_c;
        }
    }
}

void information_page_3_updata(void)
{
    /* 比较用百分位 (10mV), 与显示精度一致, 避免 mV 级抖动触发无意义刷新 */
    static uint16_t last_mv_cv[4] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    uint8_t i;

    for (i = 0; i < 4; i++)
    {
        uint16_t mv_cv = ui_data.cell_voltage_mv[i] / 10;

        if (mv_cv != last_mv_cv[i])
        {
            char buf[8];
            uint8_t neww;

            fmt_voltage(buf, ui_data.cell_voltage_mv[i], '.');

            /* 先写后擦 (左对齐, 防闪): 新串覆盖重叠区, 再擦旧串右侧露出的残留,
             * 消除 "1"(宽5) 与其他数字(宽8) 位移带来的残影 */
            digit_display_string(buf, INFO3_VOLT_X, info3_row_y[i], DIGIT_HEIGHT_12);
            neww = (uint8_t)digit_string_width(buf, DIGIT_HEIGHT_12);
            if (cell_v_w[i] > neww)
                DispBlock(INFO3_VOLT_X + neww, info3_row_y[i],
                          INFO3_VOLT_X + cell_v_w[i] - 1,
                          info3_row_y[i] + DIGIT_12_LINE_H - 1);
            cell_v_w[i] = neww;
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
            uint8_t neww;

            fmt_voltage(buf, (uint16_t)total_mv, '.');

            /* 先覆盖后擦尾: 新串盖住重叠区, 再固定擦掉右侧 VOLT_ERASE_W 像素。
             * 不判断旧串有几个 "1", 直接按 4 位数字全是 "1" 的最坏情况算位移,
             * 一定能盖住旧串 V 留下的残条 */
            digit_display_string(buf, VOLT_DIGIT_X, VOLT_LABEL_Y, DIGIT_HEIGHT_16);

            neww = (uint8_t)digit_string_width(buf, DIGIT_HEIGHT_16);
            {
                int ex1 = VOLT_DIGIT_X + neww;
                int ex2 = ex1 + VOLT_ERASE_W - 1;
                if (ex2 > VOLT_DIGIT_R) ex2 = VOLT_DIGIT_R;
                if (ex1 <= ex2)
                    DispBlock(ex1, VOLT_LABEL_Y, ex2,
                              VOLT_LABEL_Y + DIGIT_16_LINE_H - 1);
            }
            last_total_cv = total_cv;
        }
    }
}
