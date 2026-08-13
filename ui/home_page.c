#include "global_define.h"

/* ============================================================================
 * 新主界面 (一级充放电页面)
 *
 *   y=0..23    顶部信息条 (24 高)
 *              (0,0)   TIMER 图标 + 剩余充满时间, 紧邻无间隔   [充电时]
 *              (87,0)  MINI 图标, 纯放电时移到 (0,0)           [小电流模式]
 *              (196,0) OUT 图标, 右边缘正好到 240               [放电时]
 *   y=24..95   电量胶囊 240x72
 *   y=96..134  充放电动画 108x39 @ (66,96), 水平居中, 下边贴屏底
 *
 * 电量胶囊 = [左边框] + [N 个数字] + [%] + [右边框], 边框宽随位数变化, 三种
 * 组合都精确铺满 240, 所以位数变化时不需要擦除:
 *
 *   3 位 (100%)    44 + 36×3 + 44 + 44 = 240
 *   2 位 (10~99%)  62 + 36×2 + 44 + 62 = 240
 *   1 位 (0~9%)    80 + 36×1 + 44 + 80 = 240
 *
 * 配色: 电量 ≤10% 用橙色, >10% 用蓝色。设计只出了实际会出现的边框组合 ——
 * 1 位数必 ≤10% 所以只有橙, 3 位数必 =100% 所以只有蓝。
 * ========================================================================== */

/* ---------------------------- 布局 ---------------------------------------- */

#define HM_TOP_H         24
#define HM_CAP_Y         24    /* 电量胶囊 y */
#define HM_CAP_H         72
#define HM_DIGIT_W       36
#define HM_PCT_W         44

#define HM_TIMER_X       0
#define HM_TIMER_W       20
#define HM_MINI_X        87
#define HM_MINI_W        60
#define HM_OUT_X         196
#define HM_OUT_W         44

#define HM_ANIM_X        66
#define HM_ANIM_Y        96
#define HM_ANIM_W        108
#define HM_ANIM_H        39
#define HM_ANIM_FRAMES   40
#define HM_ANIM_MS       25    /* 每帧间隔, 40 帧一轮 ≈ 1s。单帧 SPI 收发约 11ms */

/* NUM_20 字体: 0 和 1 宽 13, 2~9 宽 12, 冒号宽 8 */
#define HM_NUM20_W(d)    (((d) <= 1) ? 13 : 12)
#define HM_COLON_W       8
#define HM_NUM20_ADDR(d) (FLASH_ADDR_NUM_20_BASE + (uint32_t)(d) * FLASH_STRIDE_NUM_20)

/* 颜色下标 */
#define HM_C_BLUE        0
#define HM_C_ORANGE      1
/* 电量 ≤ 此值用橙色 */
#define HM_ORANGE_SOC    10

/* 充放电模式 */
#define HM_MODE_IDLE     0
#define HM_MODE_CHG      1
#define HM_MODE_DIS      2

/* 边框宽度, 下标 = 数字位数 */
static const uint8_t hm_border_w[4] = { 0, 80, 62, 44 };

/* ---------------------------- 切图地址表 ---------------------------------- */

/* 电量数字: [数字][颜色] */
static const uint32_t hm_digit[10][2] = {
	{ FLASH_ADDR_BAT_0_BLUE, FLASH_ADDR_BAT_0_ORANGE },
	{ FLASH_ADDR_BAT_1_BLUE, FLASH_ADDR_BAT_1_ORANGE },
	{ FLASH_ADDR_BAT_2_BLUE, FLASH_ADDR_BAT_2_ORANGE },
	{ FLASH_ADDR_BAT_3_BLUE, FLASH_ADDR_BAT_3_ORANGE },
	{ FLASH_ADDR_BAT_4_BLUE, FLASH_ADDR_BAT_4_ORANGE },
	{ FLASH_ADDR_BAT_5_BLUE, FLASH_ADDR_BAT_5_ORANGE },
	{ FLASH_ADDR_BAT_6_BLUE, FLASH_ADDR_BAT_6_ORANGE },
	{ FLASH_ADDR_BAT_7_BLUE, FLASH_ADDR_BAT_7_ORANGE },
	{ FLASH_ADDR_BAT_8_BLUE, FLASH_ADDR_BAT_8_ORANGE },
	{ FLASH_ADDR_BAT_9_BLUE, FLASH_ADDR_BAT_9_ORANGE },
};

static const uint32_t hm_pct[2] = { FLASH_ADDR_BAT_PER_BLUE, FLASH_ADDR_BAT_PER_ORANGE };

/* 边框: [位数][颜色]。0 = 设计没出这个组合(实际不会出现), 取到时兜底换另一色 */
static const uint32_t hm_left[4][2] = {
	{ 0, 0 },
	{ 0,                      FLASH_ADDR_LEFT_1_ORANGE },
	{ FLASH_ADDR_LEFT_2_BLUE, FLASH_ADDR_LEFT_2_ORANGE },
	{ FLASH_ADDR_LEFT_3_BLUE, 0                        },
};
static const uint32_t hm_right[4][2] = {
	{ 0, 0 },
	{ 0,                       FLASH_ADDR_RIGHT_1_ORANGE },
	{ FLASH_ADDR_RIGHT_2_BLUE, FLASH_ADDR_RIGHT_2_ORANGE },
	{ FLASH_ADDR_RIGHT_3_BLUE, 0                         },
};

/* 充放电动画 40 帧: [帧][颜色] */
static const uint32_t hm_anim[HM_ANIM_FRAMES][2] = {
	{ FLASH_ADDR_BLUE_CHARGING_001, FLASH_ADDR_ORANGE_CHARGING_001 },
	{ FLASH_ADDR_BLUE_CHARGING_002, FLASH_ADDR_ORANGE_CHARGING_002 },
	{ FLASH_ADDR_BLUE_CHARGING_003, FLASH_ADDR_ORANGE_CHARGING_003 },
	{ FLASH_ADDR_BLUE_CHARGING_004, FLASH_ADDR_ORANGE_CHARGING_004 },
	{ FLASH_ADDR_BLUE_CHARGING_005, FLASH_ADDR_ORANGE_CHARGING_005 },
	{ FLASH_ADDR_BLUE_CHARGING_006, FLASH_ADDR_ORANGE_CHARGING_006 },
	{ FLASH_ADDR_BLUE_CHARGING_007, FLASH_ADDR_ORANGE_CHARGING_007 },
	{ FLASH_ADDR_BLUE_CHARGING_008, FLASH_ADDR_ORANGE_CHARGING_008 },
	{ FLASH_ADDR_BLUE_CHARGING_009, FLASH_ADDR_ORANGE_CHARGING_009 },
	{ FLASH_ADDR_BLUE_CHARGING_010, FLASH_ADDR_ORANGE_CHARGING_010 },
	{ FLASH_ADDR_BLUE_CHARGING_011, FLASH_ADDR_ORANGE_CHARGING_011 },
	{ FLASH_ADDR_BLUE_CHARGING_012, FLASH_ADDR_ORANGE_CHARGING_012 },
	{ FLASH_ADDR_BLUE_CHARGING_013, FLASH_ADDR_ORANGE_CHARGING_013 },
	{ FLASH_ADDR_BLUE_CHARGING_014, FLASH_ADDR_ORANGE_CHARGING_014 },
	{ FLASH_ADDR_BLUE_CHARGING_015, FLASH_ADDR_ORANGE_CHARGING_015 },
	{ FLASH_ADDR_BLUE_CHARGING_016, FLASH_ADDR_ORANGE_CHARGING_016 },
	{ FLASH_ADDR_BLUE_CHARGING_017, FLASH_ADDR_ORANGE_CHARGING_017 },
	{ FLASH_ADDR_BLUE_CHARGING_018, FLASH_ADDR_ORANGE_CHARGING_018 },
	{ FLASH_ADDR_BLUE_CHARGING_019, FLASH_ADDR_ORANGE_CHARGING_019 },
	{ FLASH_ADDR_BLUE_CHARGING_020, FLASH_ADDR_ORANGE_CHARGING_020 },
	{ FLASH_ADDR_BLUE_CHARGING_021, FLASH_ADDR_ORANGE_CHARGING_021 },
	{ FLASH_ADDR_BLUE_CHARGING_022, FLASH_ADDR_ORANGE_CHARGING_022 },
	{ FLASH_ADDR_BLUE_CHARGING_023, FLASH_ADDR_ORANGE_CHARGING_023 },
	{ FLASH_ADDR_BLUE_CHARGING_024, FLASH_ADDR_ORANGE_CHARGING_024 },
	{ FLASH_ADDR_BLUE_CHARGING_025, FLASH_ADDR_ORANGE_CHARGING_025 },
	{ FLASH_ADDR_BLUE_CHARGING_026, FLASH_ADDR_ORANGE_CHARGING_026 },
	{ FLASH_ADDR_BLUE_CHARGING_027, FLASH_ADDR_ORANGE_CHARGING_027 },
	{ FLASH_ADDR_BLUE_CHARGING_028, FLASH_ADDR_ORANGE_CHARGING_028 },
	{ FLASH_ADDR_BLUE_CHARGING_029, FLASH_ADDR_ORANGE_CHARGING_029 },
	{ FLASH_ADDR_BLUE_CHARGING_030, FLASH_ADDR_ORANGE_CHARGING_030 },
	{ FLASH_ADDR_BLUE_CHARGING_031, FLASH_ADDR_ORANGE_CHARGING_031 },
	{ FLASH_ADDR_BLUE_CHARGING_032, FLASH_ADDR_ORANGE_CHARGING_032 },
	{ FLASH_ADDR_BLUE_CHARGING_033, FLASH_ADDR_ORANGE_CHARGING_033 },
	{ FLASH_ADDR_BLUE_CHARGING_034, FLASH_ADDR_ORANGE_CHARGING_034 },
	{ FLASH_ADDR_BLUE_CHARGING_035, FLASH_ADDR_ORANGE_CHARGING_035 },
	{ FLASH_ADDR_BLUE_CHARGING_036, FLASH_ADDR_ORANGE_CHARGING_036 },
	{ FLASH_ADDR_BLUE_CHARGING_037, FLASH_ADDR_ORANGE_CHARGING_037 },
	{ FLASH_ADDR_BLUE_CHARGING_038, FLASH_ADDR_ORANGE_CHARGING_038 },
	{ FLASH_ADDR_BLUE_CHARGING_039, FLASH_ADDR_ORANGE_CHARGING_039 },
	{ FLASH_ADDR_BLUE_CHARGING_040, FLASH_ADDR_ORANGE_CHARGING_040 },
};

/* ---------------------------- 上一轮显示内容 ------------------------------ */

static uint8_t  hm_last_power  = 0xFF;
static uint8_t  hm_last_color  = 0xFF;
static bool     hm_last_dis;      /* 上次 OUT 图标是否在显示 */
static bool     hm_last_mini;
static uint8_t  hm_last_mini_x;   /* MINI 上次绘制的 x, 位置变动需擦旧 */
static int16_t  hm_last_min    = -1;
static uint8_t  hm_time_w;        /* 上次时间区(含图标)总宽, 用于擦右侧残留 */

static uint8_t  hm_anim_step;     /* 0..39, 播放进度 */
static uint8_t  hm_anim_mode;     /* anim_proc 上次看到的模式 (含 IDLE) */
static uint8_t  hm_anim_idx;      /* 最后画出的那帧 (视觉帧号) */
static bool     hm_anim_first;    /* init 置位: 首次播放从第一帧/最后一帧起 */
static uint32_t hm_anim_tick;

/* ============================ 电量滤波 ====================================
 * 与端口功率页同一套路: 采样(100ms)与绘制(500ms)解耦, 5 点窗口只跨 0.5s,
 * 而不是跟着绘制节奏走的 2.5s。
 *
 * 另外保留旧主页两条硬约束 (都是实测出来的):
 *   单调约束 —— 充电不许降、放电不许升, 防平均值回摆让电量倒退
 *   SNAP    —— 与屏上值相差 ≥5 直接整窗对齐。息屏期间 ui_proc 不跑但主机仍在
 *              刷新 SOC, 亮屏后若继续平滑, 屏上会花 5 个周期从旧值爬到实时值
 * ========================================================================== */

#define HM_BAT_WIN        5
#define HM_BAT_SAMPLE_MS  100
#define HM_BAT_SNAP       5

static uint8_t  hm_bat_buf[HM_BAT_WIN];
static uint8_t  hm_bat_idx;
static uint8_t  hm_bat_out = 0xFF;   /* 上次输出值, 兼作 SNAP 和单调约束的基准 */
static uint32_t hm_bat_tick;

/* ---------------------------- 内部实现 ------------------------------------ */

static uint8_t hm_bat_raw(void)
{
	return (ui_data.bat_power > 100) ? 100 : ui_data.bat_power;
}

static void hm_bat_fill(uint8_t v)
{
	uint8_t i;
	for (i = 0; i < HM_BAT_WIN; i++)
		hm_bat_buf[i] = v;
	hm_bat_idx = 0;
	hm_bat_out = v;
}

static void hm_bat_push(uint8_t v)
{
	uint8_t diff = (v > hm_bat_out) ? (uint8_t)(v - hm_bat_out)
	                                : (uint8_t)(hm_bat_out - v);

	/* 差得太多 = 显示中断过(息屏/STOP 期间电量已经变了), 直接对齐不做平滑。
	   hm_bat_out 初值 0xFF 时 diff 必然超阈值, 首次 push 自动走这条兜底 */
	if (diff >= HM_BAT_SNAP)
	{
		hm_bat_fill(v);
		return;
	}

	hm_bat_buf[hm_bat_idx] = v;
	hm_bat_idx++;
	if (hm_bat_idx >= HM_BAT_WIN)
		hm_bat_idx = 0;
}

/* 窗口均值(四舍五入) + 单调约束。窗口恒为满, init 已填满 */
static uint8_t hm_bat_get(void)
{
	uint16_t sum = 0;   /* 100 × 5 = 500, uint16 够 */
	uint8_t i, avg;

	for (i = 0; i < HM_BAT_WIN; i++)
		sum += hm_bat_buf[i];
	avg = (uint8_t)((sum + HM_BAT_WIN / 2) / HM_BAT_WIN);

	if (ui_data.is_charge && avg < hm_bat_out)
		avg = hm_bat_out;               /* 充电中不许降 */
	else if (!ui_data.is_charge && avg > hm_bat_out)
		avg = hm_bat_out;               /* 非充电不许升 */

	hm_bat_out = avg;
	return avg;
}

static uint8_t hm_color(uint8_t power)
{
	return (power <= HM_ORANGE_SOC) ? HM_C_ORANGE : HM_C_BLUE;
}

static uint8_t hm_digit_cnt(uint8_t power)
{
	if (power >= 100) return 3;
	if (power >= 10)  return 2;
	return 1;
}

/* 设计只出了实际会出现的边框组合, 取不到就兜底换另一色, 避免落到地址 0 */
static uint32_t hm_border_addr(const uint32_t tbl[4][2], uint8_t n, uint8_t c)
{
	uint32_t a = tbl[n][c];
	return (a != 0) ? a : tbl[n][c ^ 1];
}

static void hm_split(uint8_t power, uint8_t n, uint8_t d[3])
{
	if (n == 3) { d[0] = power / 100; d[1] = (power / 10) % 10; d[2] = power % 10; }
	else if (n == 2) { d[0] = power / 10; d[1] = power % 10; }
	else { d[0] = power; }
}

/* 电量胶囊全绘 (位数或颜色变化时整条换, 三种位数都铺满 240 故无需擦除) */
static void hm_draw_capsule(uint8_t power, uint8_t c)
{
	uint8_t n = hm_digit_cnt(power);
	uint8_t d[3];
	int x = hm_border_w[n];
	uint8_t i;

	hm_split(power, n, d);

	Dispphoto_Dispaly_flash(0, HM_CAP_Y, hm_border_addr(hm_left, n, c));
	for (i = 0; i < n; i++)
	{
		Dispphoto_Dispaly_flash(x, HM_CAP_Y, hm_digit[d[i]][c]);
		x += HM_DIGIT_W;
	}
	Dispphoto_Dispaly_flash(x, HM_CAP_Y, hm_pct[c]);
	x += HM_PCT_W;
	Dispphoto_Dispaly_flash(x, HM_CAP_Y, hm_border_addr(hm_right, n, c));
}

/* 位数和颜色都没变时, 只补被改动的数字槽位 */
static void hm_draw_capsule_digits(uint8_t power, uint8_t old_power, uint8_t c)
{
	uint8_t n = hm_digit_cnt(power);
	uint8_t d_new[3], d_old[3];
	int x = hm_border_w[n];
	uint8_t i;

	hm_split(power, n, d_new);
	hm_split(old_power, n, d_old);

	for (i = 0; i < n; i++)
	{
		if (d_new[i] != d_old[i])
			Dispphoto_Dispaly_flash(x, HM_CAP_Y, hm_digit[d_new[i]][c]);
		x += HM_DIGIT_W;
	}
}

/* 是否有放电口在放电 */
static bool hm_is_dis(void)
{
	return (ui_data.usb_c1_status == 2 || ui_data.usb_c2_status == 2 || ui_data.usb_a_status == 2);
}

/* 充放同时存在时按充电处理 (动画用充电正放) */
static uint8_t hm_mode(void)
{
	if (ui_data.is_charge)
		return HM_MODE_CHG;
	if (hm_is_dis())
		return HM_MODE_DIS;
	return HM_MODE_IDLE;
}

/* 左上角剩余充满时间: TIMER 图标 + HH:MM, 各段紧邻无间隔 */
static void hm_draw_time(int16_t minute)
{
	int x = HM_TIMER_X;
	uint8_t hh, mm, d;

	if (minute < 0) minute = 0;
	hh = (uint8_t)(minute / 60);
	mm = (uint8_t)(minute % 60);
	if (hh > 99) { hh = 99; mm = 59; }

	Dispphoto_Dispaly_flash(x, 0, FLASH_ADDR_TIMER);
	x += HM_TIMER_W;

	d = hh / 10;  Dispphoto_Dispaly_flash(x, 0, HM_NUM20_ADDR(d)); x += HM_NUM20_W(d);
	d = hh % 10;  Dispphoto_Dispaly_flash(x, 0, HM_NUM20_ADDR(d)); x += HM_NUM20_W(d);
	Dispphoto_Dispaly_flash(x, 0, FLASH_ADDR_NUM_20_COLON); x += HM_COLON_W;
	d = mm / 10;  Dispphoto_Dispaly_flash(x, 0, HM_NUM20_ADDR(d)); x += HM_NUM20_W(d);
	d = mm % 10;  Dispphoto_Dispaly_flash(x, 0, HM_NUM20_ADDR(d)); x += HM_NUM20_W(d);

	/* NUM_20 是变宽字体(0/1 宽 13, 其余 12), 位宽变窄时右侧会留旧像素 */
	if (hm_time_w > (uint8_t)x)
		DispBlock(x, 0, hm_time_w - 1, HM_TOP_H - 1);
	hm_time_w = (uint8_t)x;
}

static void hm_erase_time(void)
{
	if (hm_time_w > 0)
	{
		DispBlock(HM_TIMER_X, 0, HM_TIMER_X + hm_time_w - 1, HM_TOP_H - 1);
		hm_time_w = 0;
	}
}

/* 顶部三个图标按当前状态刷新 (各自做变化检测, 无变化不重画) */
static void hm_update_top(uint8_t mode)
{
	int16_t cur_min;
	bool    dis = hm_is_dis();

	/* 右上角 OUT: 有放电口就显示, 与充电状态无关 (充放同时存在也显示) */
	if (dis != hm_last_dis)
	{
		hm_last_dis = dis;
		if (dis)
			Dispphoto_Dispaly_flash(HM_OUT_X, 0, FLASH_ADDR_OUT);
		else
			DispBlock(HM_OUT_X, 0, HM_OUT_X + HM_OUT_W - 1, HM_TOP_H - 1);
	}

	/* 左上角剩余充满时间 (仅充电且估算有效时显示) 与 MINI 小电流标志共用
	   顶部空间: 充电时倒计时占 (0,0), MINI 让位到 87; 纯放电时 MINI 画在
	   (0,0)。顺序固定为 [擦倒计时]->[MINI 搬家]->[画倒计时], 保证两个方向
	   的位置交换都先擦旧内容再画新内容, 不互相覆盖 */
	cur_min = (mode == HM_MODE_CHG) ? calc_charge_remain_min() : -1;
	if (cur_min < 0 && hm_last_min >= 0)
		hm_erase_time();

	/* MINI: 由主机下发的 low_current_flag 驱动; 消失或搬家先擦旧位置 */
	{
		bool    mini   = ui_data.low_current_flag;
		uint8_t mini_x = ui_data.is_charge ? HM_MINI_X : 0;

		if (mini != hm_last_mini || (mini && mini_x != hm_last_mini_x))
		{
			if (hm_last_mini)
				DispBlock(hm_last_mini_x, 0,
				          hm_last_mini_x + HM_MINI_W - 1, HM_TOP_H - 1);
			if (mini)
				Dispphoto_Dispaly_flash(mini_x, 0, FLASH_ADDR_MINI);
			hm_last_mini   = mini;
			hm_last_mini_x = mini_x;
		}
	}

	if (cur_min >= 0 && cur_min != hm_last_min)
		hm_draw_time(cur_min);
	hm_last_min = cur_min;
}

static void hm_erase_anim(void)
{
	DispBlock(HM_ANIM_X, HM_ANIM_Y, HM_ANIM_X + HM_ANIM_W - 1, HM_ANIM_Y + HM_ANIM_H - 1);
}

/* ---------------------------- 对外接口 ------------------------------------ */

/* 动画驱动: 由 ui_proc 每轮调用, 不受 500ms 绘制限流, 内部按帧间隔节流。
   充电 001→040 正放, 放电 040→001 倒放, 空闲不放 */
/* 电量采样: 由 ui_proc 每轮调用(不受 500ms 绘制限流), 内部按 HM_BAT_SAMPLE_MS
   节流。采样快、绘制慢, 窗口才只跨 0.5s */
void home_page_sample(void)
{
	if (md_get_tick() - hm_bat_tick < HM_BAT_SAMPLE_MS)
		return;
	hm_bat_tick = md_get_tick();

	hm_bat_push(hm_bat_raw());
}

void home_page_anim_proc(void)
{
	uint8_t mode = hm_mode();
	uint8_t c = hm_color(hm_bat_out);   /* 跟屏上数字同色, 不用未滤波的实时值 */
	uint8_t idx;

	/* 模式变化在这里处理 (每轮主循环都跑, 不受 updata 500ms 限流):
	   - 变空闲: 立即擦画面但记住最后一帧
	   - 进页面后首次播放: 充电第一帧 / 放电倒数第一帧
	   - 之后无论变充电还是放电 (含经过空闲): 都从最后画出的那帧接着播 */
	if (mode != hm_anim_mode)
	{
		if (mode == HM_MODE_IDLE)
			hm_erase_anim();
		else if (hm_anim_first)
			hm_anim_step = 0;
		else
			hm_anim_step = (mode == HM_MODE_CHG)
			             ? hm_anim_idx
			             : (uint8_t)(HM_ANIM_FRAMES - 1 - hm_anim_idx);
		hm_anim_mode = mode;
	}

	if (mode == HM_MODE_IDLE)
		return;

	if (md_get_tick() - hm_anim_tick < HM_ANIM_MS)
		return;
	hm_anim_tick = md_get_tick();

	idx = (mode == HM_MODE_CHG) ? hm_anim_step
	                            : (uint8_t)(HM_ANIM_FRAMES - 1 - hm_anim_step);
	Dispphoto_Dispaly_flash(HM_ANIM_X, HM_ANIM_Y, hm_anim[idx][c]);

	hm_anim_first = false;   /* 首播基准已消费, 之后都接续播放 */
	hm_anim_idx   = idx;
	hm_anim_step++;
	if (hm_anim_step >= HM_ANIM_FRAMES)
		hm_anim_step = 0;
}

void home_page_init(void)
{
	uint8_t power, c, mode;

	/* 窗口用当前实时电量填满: 切页/亮屏首帧即真值, 不从旧值爬坡 */
	hm_bat_fill(hm_bat_raw());
	hm_bat_tick = md_get_tick();

	power = hm_bat_get();
	c     = hm_color(power);
	mode  = hm_mode();

	DispBlock(0, 0, ROW - 1, COL - 1);

	/* 清屏后所有变化检测基准归零, 否则 updata 里"无变化"会让内容画不出来 */
	hm_last_power = 0xFF;
	hm_last_color = 0xFF;
	hm_last_dis   = false;
	hm_last_mini  = false;
	hm_last_mini_x = 0;
	hm_last_min   = -1;
	hm_time_w     = 0;
	hm_anim_step  = 0;
	hm_anim_mode  = mode;
	hm_anim_idx   = 0;
	hm_anim_first = true;   /* 进页面首次播放: 充电从第一帧 / 放电从倒数第一帧 */
	hm_anim_tick  = md_get_tick();

	LOGI("[HOME] init power=%d color=%d mode=%d\r\n", power, c, mode);

	hm_draw_capsule(power, c);
	hm_update_top(mode);

	hm_last_power = power;
	hm_last_color = c;
}

void home_page_updata(void)
{
	uint8_t power = hm_bat_get();
	uint8_t c     = hm_color(power);
	uint8_t mode  = hm_mode();

	/* 电量胶囊 */
	if (power != hm_last_power || c != hm_last_color)
	{
		if (c != hm_last_color || hm_digit_cnt(power) != hm_digit_cnt(hm_last_power))
			hm_draw_capsule(power, c);        /* 换色或位数变 → 整条重绘 */
		else
			hm_draw_capsule_digits(power, hm_last_power, c);  /* 只补变的数字 */

		hm_last_power = power;
		hm_last_color = c;
	}

	/* 顶部图标 (动画的模式切换/擦除在 anim_proc 里处理, 那边不受 500ms 限流) */
	hm_update_top(mode);
}
