#include "global_define.h"

/* New 240x135 home page. Active ports are compacted in C1/C2/A order. */
#define HM_PORT_COUNT       3
#define HM_IN               1
#define HM_OUT              2
#define HM_TOP_H            20
#define HM_LEFT_W           128
#define HM_EMOJI_X          128
#define HM_EMOJI_Y          20
#define HM_BAT_Y_MULTI      21
#define HM_BAT_Y_SINGLE     40
#define HM_BAT_H            48
#define HM_BAT_W            34
#define HM_BAT_ONE_W        22
#define HM_ICON_X           0
#define HM_POWER_X          60
#define HM_ROW_H            22
#define HM_LOW_TEXT_Y       88
#define HM_LOW_TEXT_W       118
#define HM_LOW_TEXT_H       22
#define HM_COUNT_ICON_W     20
#define HM_NUM18_W          14
#define HM_NUM18_ONE_W      7
#define HM_NUM20_W          12
#define HM_NUM20_ONE_W      8
#define HM_POWER_UNIT_W     19
#define HM_HOUR_W           14
#define HM_MINUTE_W         30
#define HM_WHITE            0
#define HM_ORANGE           1
#define HM_LOW_SOC          10
#define HM_FILTER_WIN       5
#define HM_SAMPLE_MS        100U
#define HM_BAT_SNAP         5
#define HM_POWER_SNAP       10
#define HM_ANIM_FRAME_COUNT 12U
#define HM_ANIM_CYCLE_MS    2000U

typedef struct {
	uint8_t id;       /* 0=C1, 1=C2, 2=A */
	uint8_t status;   /* 1=IN, 2=OUT */
	uint8_t power;
} hm_port_t;

static const uint8_t hm_row_y[3][3] = {
	{88, 0, 0}, {69, 91, 0}, {69, 91, 113}
};

static const uint32_t hm_bat_digit[10][2] = {
	{FLASH_ADDR_NUM_48_0_WHITE, FLASH_ADDR_NUM_48_0_ORANGE},
	{FLASH_ADDR_NUM_48_1_WHITE, FLASH_ADDR_NUM_48_1_ORANGE},
	{FLASH_ADDR_NUM_48_2_WHITE, FLASH_ADDR_NUM_48_2_ORANGE},
	{FLASH_ADDR_NUM_48_3_WHITE, FLASH_ADDR_NUM_48_3_ORANGE},
	{FLASH_ADDR_NUM_48_4_WHITE, FLASH_ADDR_NUM_48_4_ORANGE},
	{FLASH_ADDR_NUM_48_5_WHITE, FLASH_ADDR_NUM_48_5_ORANGE},
	{FLASH_ADDR_NUM_48_6_WHITE, FLASH_ADDR_NUM_48_6_ORANGE},
	{FLASH_ADDR_NUM_48_7_WHITE, FLASH_ADDR_NUM_48_7_ORANGE},
	{FLASH_ADDR_NUM_48_8_WHITE, FLASH_ADDR_NUM_48_8_ORANGE},
	{FLASH_ADDR_NUM_48_9_WHITE, FLASH_ADDR_NUM_48_9_ORANGE},
};
static const uint32_t hm_bat_percent[2] = {
	FLASH_ADDR_NUM_48_PERCENT_WHITE, FLASH_ADDR_NUM_48_PERCENT_ORANGE
};
/* 资源生成器按文件名字典序排地址，必须显式按 0~11 组织播放顺序。 */
static const uint32_t hm_charge_anim[2][HM_ANIM_FRAME_COUNT] = {
	{
		FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_0,
		FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_1,
		FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_2,
		FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_3,
		FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_4,
		FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_5,
		FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_6,
		FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_7,
		FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_8,
		FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_9,
		FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_10,
		FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_11,
	},
	{
		FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_0,
		FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_1,
		FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_2,
		FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_3,
		FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_4,
		FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_5,
		FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_6,
		FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_7,
		FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_8,
		FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_9,
		FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_10,
		FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_11,
	},
};
static const uint32_t hm_port_icon[HM_PORT_COUNT][2] = {
	{FLASH_ADDR_ICON_IN_1_LITTLE, FLASH_ADDR_ICON_OUT_1_LITTLE},
	{FLASH_ADDR_ICON_IN_2_LITTLE, FLASH_ADDR_ICON_OUT_2_LITTLE},
	{FLASH_ADDR_ICON_IN_3_LITTLE, FLASH_ADDR_ICON_OUT_3_LITTLE},
};

static uint8_t hm_last_bat, hm_last_color, hm_last_bat_y, hm_last_bat_w;
static uint8_t hm_last_count, hm_last_power_w[HM_PORT_COUNT];
static hm_port_t hm_last_ports[HM_PORT_COUNT];
static uint32_t hm_last_emoji;
static int16_t hm_last_minute;
static bool hm_last_mini;

static uint8_t hm_bat_buf[HM_FILTER_WIN], hm_bat_idx, hm_bat_out;
static uint8_t hm_power_buf[HM_PORT_COUNT][HM_FILTER_WIN];
static uint8_t hm_power_idx[HM_PORT_COUNT], hm_sample_status[HM_PORT_COUNT];
static uint32_t hm_sample_tick;
static uint32_t hm_anim_start_tick;
static uint8_t hm_anim_frame, hm_anim_low;
static bool hm_anim_running;

static uint8_t hm_abs_diff(uint8_t a, uint8_t b)
{
	return (a > b) ? (uint8_t)(a - b) : (uint8_t)(b - a);
}

static uint8_t hm_bat_raw(void)
{
	return (ui_data.bat_power > 100) ? 100 : ui_data.bat_power;
}

static void hm_raw_port(uint8_t id, uint8_t *status, uint8_t *power)
{
	if (id == 0) {
		*status = ui_data.usb_c1_status; *power = ui_data.usb_c1_power;
	} else if (id == 1) {
		*status = ui_data.usb_c2_status; *power = ui_data.usb_c2_power;
	} else {
		*status = ui_data.usb_a_status; *power = ui_data.usb_a_power;
	}
	if (*status != HM_IN && *status != HM_OUT) {
		*status = 0; *power = 0;
	}
}

/* Any IN port selects charging mode, even while another port is OUT. */
static bool hm_any_charge(void)
{
	return ui_data.usb_c1_status == HM_IN
	    || ui_data.usb_c2_status == HM_IN
	    || ui_data.usb_a_status == HM_IN;
}

static void hm_bat_fill(uint8_t v)
{
	uint8_t i;
	for (i = 0; i < HM_FILTER_WIN; i++) hm_bat_buf[i] = v;
	hm_bat_idx = 0; hm_bat_out = v;
}

static void hm_bat_push(uint8_t v)
{
	if (hm_abs_diff(v, hm_bat_out) >= HM_BAT_SNAP) {
		hm_bat_fill(v); return;
	}
	hm_bat_buf[hm_bat_idx++] = v;
	if (hm_bat_idx >= HM_FILTER_WIN) hm_bat_idx = 0;
}

static uint8_t hm_bat_get(void)
{
	uint16_t sum = 0;
	uint8_t i, avg;
	for (i = 0; i < HM_FILTER_WIN; i++) sum += hm_bat_buf[i];
	avg = (uint8_t)((sum + HM_FILTER_WIN / 2) / HM_FILTER_WIN);
	if (hm_any_charge() && avg < hm_bat_out) avg = hm_bat_out;
	else if (!hm_any_charge() && avg > hm_bat_out) avg = hm_bat_out;
	hm_bat_out = avg;
	return avg;
}

static void hm_power_fill(uint8_t id, uint8_t v)
{
	uint8_t i;
	for (i = 0; i < HM_FILTER_WIN; i++) hm_power_buf[id][i] = v;
	hm_power_idx[id] = 0;
}

static void hm_power_push(uint8_t id, uint8_t v)
{
	hm_power_buf[id][hm_power_idx[id]++] = v;
	if (hm_power_idx[id] >= HM_FILTER_WIN) hm_power_idx[id] = 0;
}

static uint8_t hm_power_get(uint8_t id)
{
	uint16_t sum = 0;
	uint8_t i;
	for (i = 0; i < HM_FILTER_WIN; i++) sum += hm_power_buf[id][i];
	return (uint8_t)((sum + HM_FILTER_WIN / 2) / HM_FILTER_WIN);
}

static uint8_t hm_collect_ports(hm_port_t ports[HM_PORT_COUNT])
{
	uint8_t id, count = 0;
	for (id = 0; id < HM_PORT_COUNT; id++) {
		uint8_t status, power;
		hm_raw_port(id, &status, &power);
		if (status == 0) continue;
		ports[count].id = id;
		ports[count].status = status;
		ports[count].power = hm_power_get(id);
		count++;
	}
	return count;
}

static uint8_t hm_bat_digit_w(uint8_t d) { return d == 1 ? HM_BAT_ONE_W : HM_BAT_W; }
static uint8_t hm_num18_w(uint8_t d) { return d == 1 ? HM_NUM18_ONE_W : HM_NUM18_W; }
static uint8_t hm_num20_w(uint8_t d) { return d == 1 ? HM_NUM20_ONE_W : HM_NUM20_W; }

static uint8_t hm_split(uint8_t v, uint8_t d[3])
{
	if (v >= 100) { d[0] = v / 100; d[1] = (v / 10) % 10; d[2] = v % 10; return 3; }
	if (v >= 10) { d[0] = v / 10; d[1] = v % 10; return 2; }
	d[0] = v; return 1;
}

static uint8_t hm_draw_battery(uint8_t power, uint8_t color, uint8_t y)
{
	uint8_t d[3], n = hm_split(power, d), i;
	int x = 0;
	for (i = 0; i < n; i++) {
		Dispphoto_Dispaly_flash(x, y, hm_bat_digit[d[i]][color]);
		x += hm_bat_digit_w(d[i]);
	}
	Dispphoto_Dispaly_flash(x, y, hm_bat_percent[color]);
	return (uint8_t)(x + HM_BAT_W);
}

static uint8_t hm_draw_power(uint8_t power, uint8_t y)
{
	uint8_t d[3], n = hm_split(power, d), i;
	int x = HM_POWER_X;
	for (i = 0; i < n; i++) {
		Dispphoto_Dispaly_flash(x, y,
			FLASH_ADDR_NUM_20_BASE + (uint32_t)d[i] * FLASH_STRIDE_NUM_20);
		x += hm_num20_w(d[i]);
	}
	/* 功率数字使用 20 号字，单位 W 使用现有 16 号字并垂直居中。 */
	Dispphoto_Dispaly_flash(x, y + 2, FLASH_ADDR_NUM_16_W);
	x += HM_POWER_UNIT_W;
	return (uint8_t)(x - HM_POWER_X);
}

static uint32_t hm_emoji_addr(uint8_t count, uint8_t power)
{
	if (power <= HM_LOW_SOC)
		return FLASH_ADDR_EMOJI_LOW_POWER;
	if (count == 0)
		return FLASH_ADDR_EMOJI_NORMAL;
	return hm_any_charge() ? FLASH_ADDR_EMOJI_CHARGING : FLASH_ADDR_EMOJI_NORMAL;
}

static void hm_draw_emoji(uint32_t addr)
{
	if (addr != hm_last_emoji) {
		Dispphoto_Dispaly_flash(HM_EMOJI_X, HM_EMOJI_Y, addr);
		hm_last_emoji = addr;
	}
}

static int hm_draw_num18(int x, uint8_t value)
{
	uint8_t d[3], n = hm_split(value, d), i;
	for (i = 0; i < n; i++) {
		Dispphoto_Dispaly_flash(x, 0,
			FLASH_ADDR_NUM_18_BASE + (uint32_t)d[i] * FLASH_STRIDE_NUM_18);
		x += hm_num18_w(d[i]);
	}
	return x;
}

/* Draws: countdown icon + compact time such as 1h40m. */
static int hm_draw_countdown(int16_t minute)
{
	uint8_t hour, min;
	int x = 0;
	if (minute > 5999) minute = 5999;
	hour = (uint8_t)(minute / 60); min = (uint8_t)(minute % 60);
	Dispphoto_Dispaly_flash(x, 0, FLASH_ADDR_ICON_COUNT_DOWN);
	x += HM_COUNT_ICON_W;
	if (hour > 0) {
		x = hm_draw_num18(x, hour);
		Dispphoto_Dispaly_flash(x, 0, FLASH_ADDR_NUM_18_HOUR);
		x += HM_HOUR_W;
	}
	x = hm_draw_num18(x, min);
	Dispphoto_Dispaly_flash(x, 0, FLASH_ADDR_NUM_18_MINUTE);
	return x + HM_MINUTE_W;
}

static void hm_update_top(void)
{
	int16_t minute = hm_any_charge() ? calc_charge_remain_min() : -1;
	bool mini = ui_data.low_current_flag;
	int x = 0;
	if (minute == hm_last_minute && mini == hm_last_mini) return;

	DispBlock(0, 0, ROW - 1, HM_TOP_H - 1);
	if (minute >= 0) x = hm_draw_countdown(minute);
	if (mini) Dispphoto_Dispaly_flash(x, 0, FLASH_ADDR_TEXT_MINI);
	hm_last_minute = minute; hm_last_mini = mini;
}

static bool hm_port_equal(const hm_port_t *a, const hm_port_t *b)
{
	return a->id == b->id && a->status == b->status && a->power == b->power;
}

static void hm_draw_ports(const hm_port_t ports[HM_PORT_COUNT], uint8_t count, bool force)
{
	uint8_t row;
	for (row = 0; row < count; row++) {
		uint8_t y = hm_row_y[count - 1][row], new_w;
		if (!force && row < hm_last_count && hm_port_equal(&ports[row], &hm_last_ports[row]))
			continue;
		if (force || row >= hm_last_count
		    || ports[row].id != hm_last_ports[row].id
		    || ports[row].status != hm_last_ports[row].status)
		{
			Dispphoto_Dispaly_flash(HM_ICON_X, y,
				hm_port_icon[ports[row].id][ports[row].status - 1]);
		}
		new_w = hm_draw_power(ports[row].power, y);
		/* The new value covers from x=60; erase only an uncovered old tail. */
		if (!force && row < hm_last_count && hm_last_power_w[row] > new_w)
			DispBlock(HM_POWER_X + new_w, y,
			          HM_POWER_X + hm_last_power_w[row] - 1, y + HM_ROW_H - 1);
		hm_last_ports[row] = ports[row]; hm_last_power_w[row] = new_w;
	}
}

static void hm_render(bool first)
{
	hm_port_t ports[HM_PORT_COUNT];
	uint8_t count = hm_collect_ports(ports);
	uint8_t power = hm_bat_get();
	uint8_t bat_y = count >= 2 ? HM_BAT_Y_MULTI : HM_BAT_Y_SINGLE;
	uint8_t color = power <= HM_LOW_SOC ? HM_ORANGE : HM_WHITE;
	bool layout_changed = first || count != hm_last_count;
	bool low_text = count == 0 && power <= HM_LOW_SOC;
	bool old_low_text = hm_last_count == 0 && hm_last_bat <= HM_LOW_SOC;

	if (layout_changed) {
		/* x=128..239 belongs to the emoji, so only rebuild the left panel. */
		DispBlock(0, HM_BAT_Y_MULTI, HM_LEFT_W - 1, COL - 1);
		hm_last_bat_w = 0;
	} else if (old_low_text && !low_text) {
		DispBlock(0, HM_LOW_TEXT_Y, HM_LOW_TEXT_W - 1,
		          HM_LOW_TEXT_Y + HM_LOW_TEXT_H - 1);
	}

	if (layout_changed || power != hm_last_bat || color != hm_last_color || bat_y != hm_last_bat_y) {
		uint8_t new_w = hm_draw_battery(power, color, bat_y);
		/* Same origin: overwrite first, erase only a right tail when narrower. */
		if (!layout_changed && bat_y == hm_last_bat_y && hm_last_bat_w > new_w)
			DispBlock(new_w, bat_y, hm_last_bat_w - 1, bat_y + HM_BAT_H - 1);
		hm_last_bat_w = new_w;
	}

	if (low_text && (layout_changed || !old_low_text))
		Dispphoto_Dispaly_flash(0, HM_LOW_TEXT_Y, FLASH_ADDR_TEXT_LOW_POWER);
	hm_draw_ports(ports, count, layout_changed);
	/* 充电时表情区域由 home_page_anim_proc() 独占，避免 500ms 刷新覆盖动画帧。 */
	if (!hm_any_charge())
		hm_draw_emoji(hm_emoji_addr(count, power));
	hm_update_top();

	hm_last_bat = power; hm_last_color = color; hm_last_bat_y = bat_y;
	hm_last_count = count;
}

void home_page_sample(void)
{
	uint8_t id;
	if (md_get_tick() - hm_sample_tick < HM_SAMPLE_MS) return;
	hm_sample_tick = md_get_tick();
	hm_bat_push(hm_bat_raw());
	for (id = 0; id < HM_PORT_COUNT; id++) {
		uint8_t status, power, filtered;
		hm_raw_port(id, &status, &power); filtered = hm_power_get(id);
		if (status != hm_sample_status[id] || hm_abs_diff(power, filtered) >= HM_POWER_SNAP)
			hm_power_fill(id, power);
		else
			hm_power_push(id, power);
		hm_sample_status[id] = status;
	}
}

void home_page_anim_proc(void)
{
	uint32_t now = md_get_tick();
	uint32_t elapsed;
	uint8_t frame;
	uint8_t low;

	if (!hm_any_charge()) {
		if (hm_anim_running) {
			hm_anim_running = false;
			hm_anim_frame = 0xFFU;
			hm_last_emoji = 0;
			/* 动画结束：立即同步端口、电量和静态表情，之后恢复 500ms 节拍。 */
			hm_render(false);
		}
		return;
	}

	low = (hm_bat_out <= HM_LOW_SOC) ? 1U : 0U;
	if (!hm_anim_running || low != hm_anim_low) {
		/* 动画开始或高/低电切换：先同步端口、电量，再显示第 0 帧。 */
		hm_render(false);
		hm_anim_running = true;
		hm_anim_low = low;
		hm_anim_frame = 0U;
		hm_anim_start_tick = now;
		Dispphoto_Dispaly_flash(HM_EMOJI_X, HM_EMOJI_Y, hm_charge_anim[low][0]);
		hm_last_emoji = hm_charge_anim[low][0];
		return;
	}

	elapsed = now - hm_anim_start_tick;
	if (elapsed >= HM_ANIM_CYCLE_MS) {
		hm_anim_start_tick += (elapsed / HM_ANIM_CYCLE_MS) * HM_ANIM_CYCLE_MS;
		elapsed %= HM_ANIM_CYCLE_MS;
	}
	frame = (uint8_t)((elapsed * HM_ANIM_FRAME_COUNT) / HM_ANIM_CYCLE_MS);
	if (frame != hm_anim_frame) {
		hm_anim_frame = frame;
		Dispphoto_Dispaly_flash(HM_EMOJI_X, HM_EMOJI_Y, hm_charge_anim[low][frame]);
		hm_last_emoji = hm_charge_anim[low][frame];
	}
}

void home_page_init(void)
{
	uint8_t id;
	DispBlock(0, 0, ROW - 1, COL - 1);
	hm_bat_fill(hm_bat_raw());
	for (id = 0; id < HM_PORT_COUNT; id++) {
		uint8_t status, power;
		hm_raw_port(id, &status, &power);
		hm_power_fill(id, power); hm_sample_status[id] = status;
	}
	hm_sample_tick = md_get_tick();
	hm_anim_start_tick = hm_sample_tick;
	hm_anim_frame = 0xFFU;
	hm_anim_low = 0U;
	hm_anim_running = false;
	hm_last_bat = hm_last_color = hm_last_bat_y = hm_last_count = 0xFF;
	hm_last_bat_w = 0; hm_last_emoji = 0; hm_last_minute = -2;
	hm_last_mini = !ui_data.low_current_flag;
	memset(hm_last_ports, 0xFF, sizeof(hm_last_ports));
	memset(hm_last_power_w, 0, sizeof(hm_last_power_w));
	hm_render(true);
}

void home_page_updata(void)
{
	hm_render(false);
}
