#include "information_page.h"

/* Information page 1: per-port voltage/current. */
#define INFO_PORT_COUNT       3
#define INFO_PORT_VALUE_X     103
#define INFO_PORT_VOLT_X      145
#define INFO_PORT_SLASH_X     159
#define INFO_PORT_CURRENT_X   175
#define INFO_PORT_AMPERE_X    205

static const uint8_t info_port_icon_y[INFO_PORT_COUNT] = {8, 48, 88};
static const uint8_t info_port_value_y[INFO_PORT_COUNT] = {17, 57, 97};
static const uint32_t info_port_icon[INFO_PORT_COUNT][3] = {
    {FLASH_ADDR_ICON_NORMAL_1_BIG, FLASH_ADDR_ICON_IN_1_BIG, FLASH_ADDR_ICON_OUT_1_BIG},
    {FLASH_ADDR_ICON_NORMAL_2_BIG, FLASH_ADDR_ICON_IN_2_BIG, FLASH_ADDR_ICON_OUT_2_BIG},
    {FLASH_ADDR_ICON_NORMAL_3_BIG, FLASH_ADDR_ICON_IN_3_BIG, FLASH_ADDR_ICON_OUT_3_BIG},
};

static uint8_t info_port_last_status[INFO_PORT_COUNT];
static uint16_t info_port_last_voltage[INFO_PORT_COUNT];
static uint16_t info_port_last_current[INFO_PORT_COUNT];

static uint32_t info_port_digit_addr(uint8_t digit)
{
    if (digit == 1)
        return FLASH_ADDR_NUM_20_1_S;
    return FLASH_ADDR_NUM_20_BASE + (uint32_t)digit * FLASH_STRIDE_NUM_20;
}

static void info_port_get(uint8_t row, uint8_t *status,
                          uint16_t *voltage_mv, uint16_t *current_ma)
{
    if (row == 0) {
        *status = ui_data.usb_c1_status;
        *voltage_mv = ui_data.usb_c1_voltage_mv;
        *current_ma = ui_data.usb_c1_current_ma;
    } else if (row == 1) {
        *status = ui_data.usb_c2_status;
        *voltage_mv = ui_data.usb_c2_voltage_mv;
        *current_ma = ui_data.usb_c2_current_ma;
    } else {
        *status = ui_data.usb_a_status;
        *voltage_mv = ui_data.usb_a_voltage_mv;
        *current_ma = ui_data.usb_a_current_ma;
    }
    if (*status != 1 && *status != 2)
        *status = 0;
}

static void info_port_draw_row(uint8_t row, uint8_t status,
                               uint16_t voltage_mv, uint16_t current_ma)
{
    uint8_t y = info_port_value_y[row];
    uint16_t voltage = (uint16_t)(((uint32_t)voltage_mv + 50U) / 100U);
    uint16_t current = (uint16_t)(((uint32_t)current_ma + 50U) / 100U);

    Dispphoto_Dispaly_flash(0, info_port_icon_y[row], info_port_icon[row][status]);

    if (status == 0) {
        Dispphoto_Dispaly_flash(INFO_PORT_VALUE_X, y, FLASH_ADDR_STRIGULA_THREE_DARK);
        Dispphoto_Dispaly_flash(INFO_PORT_VOLT_X, y, FLASH_ADDR_VOLT_DARK);
        Dispphoto_Dispaly_flash(INFO_PORT_SLASH_X, y, FLASH_ADDR_OBLIQUE_LINE_DARK);
        Dispphoto_Dispaly_flash(INFO_PORT_CURRENT_X, y, FLASH_ADDR_STRIGULA_TWO_DARK);
        Dispphoto_Dispaly_flash(INFO_PORT_AMPERE_X, y, FLASH_ADDR_AMPERE_DARK);
        return;
    }

    if (voltage > 999) voltage = 999; /* 99.9V */
    if (current > 99) current = 99;   /* 9.9A */

    Dispphoto_Dispaly_flash(INFO_PORT_VALUE_X, y,
        (voltage >= 100) ? info_port_digit_addr((uint8_t)(voltage / 100))
                         : FLASH_ADDR_NUM_20_1_NULL);
    Dispphoto_Dispaly_flash(INFO_PORT_VALUE_X + 12, y,
        info_port_digit_addr((uint8_t)((voltage / 10) % 10)));
    Dispphoto_Dispaly_flash(INFO_PORT_VALUE_X + 24, y, FLASH_ADDR_POINT);
    Dispphoto_Dispaly_flash(INFO_PORT_VALUE_X + 30, y,
        info_port_digit_addr((uint8_t)(voltage % 10)));
    Dispphoto_Dispaly_flash(INFO_PORT_VOLT_X, y, FLASH_ADDR_VOLT);
    Dispphoto_Dispaly_flash(INFO_PORT_SLASH_X, y, FLASH_ADDR_OBLIQUE_LINE);
    Dispphoto_Dispaly_flash(INFO_PORT_CURRENT_X, y,
        info_port_digit_addr((uint8_t)(current / 10)));
    Dispphoto_Dispaly_flash(INFO_PORT_CURRENT_X + 12, y, FLASH_ADDR_POINT);
    Dispphoto_Dispaly_flash(INFO_PORT_CURRENT_X + 18, y,
        info_port_digit_addr((uint8_t)(current % 10)));
    Dispphoto_Dispaly_flash(INFO_PORT_AMPERE_X, y, FLASH_ADDR_AMPERE);
}

void information_page_1_init(void)
{
    uint8_t row;

    DispBlock(0, 0, ROW - 1, COL - 1);
    memset(info_port_last_status, 0xFF, sizeof(info_port_last_status));
    memset(info_port_last_voltage, 0xFF, sizeof(info_port_last_voltage));
    memset(info_port_last_current, 0xFF, sizeof(info_port_last_current));
    information_page_1_updata();
}

void information_page_1_updata(void)
{
    uint8_t row;

    for (row = 0; row < INFO_PORT_COUNT; row++) {
        uint8_t status;
        uint16_t voltage_mv, current_ma;
        uint16_t voltage, current;

        info_port_get(row, &status, &voltage_mv, &current_ma);
        voltage = (uint16_t)(((uint32_t)voltage_mv + 50U) / 100U);
        current = (uint16_t)(((uint32_t)current_ma + 50U) / 100U);
        if (status == info_port_last_status[row]
            && voltage == info_port_last_voltage[row]
            && current == info_port_last_current[row])
            continue;

        info_port_draw_row(row, status, voltage_mv, current_ma);
        info_port_last_status[row] = status;
        info_port_last_voltage[row] = voltage;
        info_port_last_current[row] = current;
    }
}

/* Merged battery health / temperature page. */
#define INFO1_VALUE_X          188
#define INFO1_VALUE_H          22
#define INFO1_HEALTH_Y         15
#define INFO1_TEMP_Y           45
#define INFO1_CYCLE_Y          75
#define INFO1_NUM_W            12
#define INFO1_NUM_ONE_W        8
#define INFO1_MINUS_W          8
#define INFO1_PERCENT_W        14
#define INFO1_DEGREE_C_W       24
#define INFO1_CI_W             18

typedef struct {
    uint8_t x;
    uint8_t w;
} info1_span_t;

static info1_span_t info1_health_span;
static info1_span_t info1_temp_span;
static info1_span_t info1_cycle_span;
static uint8_t  info1_last_health;
static int16_t  info1_last_temp_c;
static uint16_t info1_last_cycle;

/* ============================ 温度滤波 ============================
 * 与主页电量、端口功率同一套路: 采样与绘制解耦。绘制被 ui_proc 限流到 500ms,
 * 若跟着绘制节奏入窗, 5 点窗口要跨 2.5s, 升温时屏上温度明显滞后。
 * 这里按 TEMP_SAMPLE_MS 独立入窗, 窗口只跨 5×100ms = 0.5s。
 * ================================================================ */

#define TEMP_FILTER_WIN 5
#define TEMP_SAMPLE_MS  100

static int16_t  temp_filter_buf[TEMP_FILTER_WIN];
static uint8_t  temp_filter_idx;
static bool     temp_filter_full;
static uint32_t temp_samp_tick;

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

static void temp_filter_fill(int16_t value)
{
	uint8_t i;
	for (i = 0; i < TEMP_FILTER_WIN; i++)
		temp_filter_buf[i] = value;
	temp_filter_idx = 0;
	temp_filter_full = true;
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

static uint8_t info1_num_w(uint8_t digit)
{
    return (digit == 1) ? INFO1_NUM_ONE_W : INFO1_NUM_W;
}

static uint8_t info1_split_u16(uint16_t value, uint8_t digits[4])
{
    if (value >= 1000) {
        digits[0] = (uint8_t)(value / 1000);
        digits[1] = (uint8_t)((value / 100) % 10);
        digits[2] = (uint8_t)((value / 10) % 10);
        digits[3] = (uint8_t)(value % 10);
        return 4;
    }
    if (value >= 100) {
        digits[0] = (uint8_t)(value / 100);
        digits[1] = (uint8_t)((value / 10) % 10);
        digits[2] = (uint8_t)(value % 10);
        return 3;
    }
    if (value >= 10) {
        digits[0] = (uint8_t)(value / 10);
        digits[1] = (uint8_t)(value % 10);
        return 2;
    }
    digits[0] = (uint8_t)value;
    return 1;
}

/* Values always use the 20px font and start exactly at x=188. Draw the new
 * value first, then erase only an old right fragment. */
static void info1_draw_value(int value, uint8_t y, uint32_t unit_addr,
                             uint8_t unit_w, info1_span_t *span)
{
    uint8_t digits[4];
    uint8_t count, i, neg = 0;
    uint16_t magnitude;
    uint8_t total_w = unit_w;
    int x, cur_x;
    int old_r = span->x + span->w;

    if (value < 0) {
        neg = 1;
        magnitude = (uint16_t)(-value);
        total_w += INFO1_MINUS_W;
    } else {
        magnitude = (uint16_t)value;
    }
    if (magnitude > 9999) magnitude = 9999;

    count = info1_split_u16(magnitude, digits);
    for (i = 0; i < count; i++)
        total_w += info1_num_w(digits[i]);

    x = INFO1_VALUE_X;
    cur_x = x;

    if (neg) {
        Dispphoto_Dispaly_flash(cur_x, y + 3, FLASH_ADDR_NUM_16);
        cur_x += INFO1_MINUS_W;
    }
    for (i = 0; i < count; i++) {
        Dispphoto_Dispaly_flash(cur_x, y,
            FLASH_ADDR_NUM_20_BASE + (uint32_t)digits[i] * FLASH_STRIDE_NUM_20);
        cur_x += info1_num_w(digits[i]);
    }
    Dispphoto_Dispaly_flash(cur_x, y, unit_addr);

    if (span->w > 0) {
        if (x + total_w < old_r)
            DispBlock(x + total_w, y, old_r - 1, y + INFO1_VALUE_H - 1);
    }
    span->x = (uint8_t)x;
    span->w = total_w;
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

/* 页3 电芯电压串当前宽度, 供先写后擦只擦右侧残留 */
static uint8_t cell_v_w[4];

void information_page_2_init(void)
{
    DispBlock(0, 0, ROW - 1, COL - 1);

    temp_filter_fill(ui_data.bat_temperature);
    temp_samp_tick = md_get_tick();

    Dispphoto_Dispaly_flash(0,   20,  FLASH_ADDR_EMOJI_HEALTHY);
    Dispphoto_Dispaly_flash(112, 11,  FLASH_ADDR_TEXT_BAT_HEALTH);
    Dispphoto_Dispaly_flash(112, 41,  FLASH_ADDR_TEXT_BAT_TEMP);
    Dispphoto_Dispaly_flash(112, 71,  FLASH_ADDR_TEXT_CYCLE_INDEX);
    Dispphoto_Dispaly_flash(112, 101, FLASH_ADDR_TEXT_PRESS_5S_TO_SETTING);

    memset(&info1_health_span, 0, sizeof(info1_health_span));
    memset(&info1_temp_span,   0, sizeof(info1_temp_span));
    memset(&info1_cycle_span,  0, sizeof(info1_cycle_span));

    info1_draw_value(ui_data.bat_max_cap, INFO1_HEALTH_Y,
                     FLASH_ADDR_PERCENT, INFO1_PERCENT_W, &info1_health_span);
    info1_draw_value(temp_filter_get() / 10, INFO1_TEMP_Y,
                     FLASH_ADDR_DEGREE_CENTIGRADE, INFO1_DEGREE_C_W, &info1_temp_span);
    info1_draw_value(ui_data.bat_cycle_cnt, INFO1_CYCLE_Y,
                     FLASH_ADDR_CI, INFO1_CI_W, &info1_cycle_span);

    info1_last_health = ui_data.bat_max_cap;
    info1_last_temp_c = temp_filter_get() / 10;
    info1_last_cycle  = ui_data.bat_cycle_cnt;

    // 电池健康 (0,20, 120x32)
    // 循环次数 (120,20, 120x32)
    // 健康值 (电池健康正下方居中, 单位 %)
    // 次数值 (循环次数正下方居中, 单位 次)
}

void information_page_3_init(void)
{
    DispBlock(0, 0, ROW - 1, COL - 1);

    // 电芯电压 (0,0, 240x32)
    Dispphoto_Dispaly_flash(0, 0, FLASH_ADDR_TITLE_CELL_VOLTAGE);

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

        Dispphoto_Dispaly_flash(VOLT_LABEL_X, VOLT_LABEL_Y, FLASH_ADDR_TEXTTOTAL_VOLTAGE);
        digit_display_string(buf, VOLT_DIGIT_X, VOLT_LABEL_Y, DIGIT_HEIGHT_16);
    }

    /* 电芯型号 (标签 31,119 78x16, 型号串 109,119) */
    Dispphoto_Dispaly_flash(MODEL_LABEL_X, MODEL_LABEL_Y, FLASH_ADDR_CELL_MODEL);
    digit_display_string("506578AFU", MODEL_TEXT_X, MODEL_LABEL_Y, DIGIT_HEIGHT_16);
}

static uint16_t software_last_pd_version;

#define SOFTWARE_VERSION_LABEL_W  54U
#define SOFTWARE_VERSION_GAP       3U

/* 拼成“MCU版本号: x.x.x”或“PD版本号: x.x”。 */
static void software_draw_version(const char *prefix, const char *version, uint8_t y)
{
    uint16_t prefix_w = digit_string_width(prefix, DIGIT_HEIGHT_16);
    uint16_t colon_w  = digit_string_width(":", DIGIT_HEIGHT_16);
    uint16_t version_w = digit_string_width(version, DIGIT_HEIGHT_16);
    uint16_t total_w = prefix_w + SOFTWARE_VERSION_GAP
                     + SOFTWARE_VERSION_LABEL_W + colon_w
                     + SOFTWARE_VERSION_GAP + version_w;
    uint16_t x = (total_w < ROW) ? (uint16_t)((ROW - total_w) / 2) : 0;

    digit_display_string(prefix, x, y, DIGIT_HEIGHT_16);
    x += prefix_w + SOFTWARE_VERSION_GAP;
    Dispphoto_Dispaly_flash(x, y, FLASH_ADDR_TEXT_VERSION_NUMBER);
    x += SOFTWARE_VERSION_LABEL_W;
    digit_display_string(":", x, y, DIGIT_HEIGHT_16);
    x += colon_w + SOFTWARE_VERSION_GAP;
    digit_display_string(version, x, y, DIGIT_HEIGHT_16);
}

static uint8_t software_append_bcd(uint8_t bcd, char *out)
{
    uint8_t n = 0;
    uint8_t high = (uint8_t)((bcd >> 4) & 0x0F);
    uint8_t low = (uint8_t)(bcd & 0x0F);

    if (high <= 9 && low <= 9) {
        if (high != 0)
            out[n++] = (char)('0' + high);
        out[n++] = (char)('0' + low);
    } else {
        out[n++] = '-';
    }
    return n;
}

static void software_pd_version_string(uint16_t value, char out[8])
{
    uint8_t n = 0;

    out[n++] = 'V';

    if (value == 0) {
        out[n++] = '-'; out[n++] = '-'; out[n++] = '-'; out[n++] = '-'; out[n] = '\0';
        return;
    }
    n += software_append_bcd((uint8_t)(value >> 8), &out[n]);
    out[n++] = '.';
    n += software_append_bcd((uint8_t)value, &out[n]);
    out[n] = '\0';
}

void software_version_page_init(void)
{
    const char *mcu_version = VERSION;

    DispBlock(0, 0, ROW - 1, COL - 1);
    Dispphoto_Dispaly_flash(0, 0, FLASH_ADDR_TITLE_SOFTWARE_VERSION);
    software_draw_version("MCU", mcu_version, 55);

    software_last_pd_version = 0xFFFF;
    software_version_page_updata();
}

void software_version_page_updata(void)
{
    char pd_version[8];

    if (ui_data.host_fw_ver == software_last_pd_version)
        return;

    software_pd_version_string(ui_data.host_fw_ver, pd_version);
    DispBlock(0, 85, ROW - 1, 85 + DIGIT_16_LINE_H - 1);
    software_draw_version("PD", pd_version, 85);
    software_last_pd_version = ui_data.host_fw_ver;
}

/* ============================ 数据更新 ============================ */

void information_page_2_updata(void)
{
    int16_t temp_c = temp_filter_get() / 10;

    if (ui_data.bat_max_cap != info1_last_health) {
        info1_draw_value(ui_data.bat_max_cap, INFO1_HEALTH_Y,
                         FLASH_ADDR_PERCENT, INFO1_PERCENT_W, &info1_health_span);
        info1_last_health = ui_data.bat_max_cap;
    }
    if (temp_c != info1_last_temp_c) {
        info1_draw_value(temp_c, INFO1_TEMP_Y,
                         FLASH_ADDR_DEGREE_CENTIGRADE, INFO1_DEGREE_C_W, &info1_temp_span);
        info1_last_temp_c = temp_c;
    }
    if (ui_data.bat_cycle_cnt != info1_last_cycle) {
        info1_draw_value(ui_data.bat_cycle_cnt, INFO1_CYCLE_Y,
                         FLASH_ADDR_CI, INFO1_CI_W, &info1_cycle_span);
        info1_last_cycle = ui_data.bat_cycle_cnt;
    }
}

void information_page_2_sample(void)
{
    if (md_get_tick() - temp_samp_tick < TEMP_SAMPLE_MS)
        return;
    temp_samp_tick = md_get_tick();
    temp_filter_push(ui_data.bat_temperature);
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
