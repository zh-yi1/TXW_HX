#include "global_define.h"

/* ============================================================================
 * 端口功率页 —— 从主界面拆分出来, 只显示 3 个端口的状态和功率
 *
 * 每行由 7 张定宽切图横向拼成整屏宽, 三行 45 高铺满 240x135:
 *
 *   x: 0        57   73          143  163  183   203     240
 *      |--------|----|-----------|----|----|----|-------|
 *       ①充电口  ②序号 ③IN/OUT     ④百位 ⑤十位 ⑥个位  ⑦单位w
 *        57      16    70           20   20   20    37
 *
 * 端口 1/2 是 C 口, 端口 3 是 A 口。整行同色: 白色=未使用, 蓝色=正在输入/输出。
 * ④⑤⑥ 三个槽位定宽右对齐, 高位空缺用 blank 切图占位 —— 每个槽位永远被同尺寸
 * 图覆盖, 所以位数变化时不需要像旧主界面那样手动擦残留。
 * ========================================================================== */

#define PWR_ROW_H 45
#define PWR_PORT_CNT 3

/* 各段左边界 (累加自切图宽度, 末段 203+37=240 正好到屏幕右边) */
#define PWR_X_PORT 0	  /* ① 充电口   w=57 */
#define PWR_X_INDEX 57	  /* ② 端口序号 w=16 */
#define PWR_X_DIR 73	  /* ③ IN/OUT   w=70 */
#define PWR_X_DIGIT_H 143 /* ④ 百位     w=20 */
#define PWR_X_DIGIT_T 163 /* ⑤ 十位     w=20 */
#define PWR_X_DIGIT_O 183 /* ⑥ 个位     w=20 */
#define PWR_X_UNIT 203	  /* ⑦ 单位 w   w=37 */

#define PWR_ROW_Y(row) ((row) * PWR_ROW_H)

/* 端口状态 (同 ui_data 的 usb_*_status) */
#define PWR_ST_IDLE 0 /* 未连接/未使用 */
#define PWR_ST_IN 1	  /* 充电中 = 电流流入 = IN  */
#define PWR_ST_OUT 2  /* 放电中 = 电流流出 = OUT */

/* 颜色下标: 0=白(未使用) 1=蓝(工作中) */
#define PWR_C_WHITE 0
#define PWR_C_BLUE 1

/* ---------------------------- 切图地址表 ---------------------------------- */

/* ① 充电口: [颜色] */
static const uint32_t pwr_part1_usb_c[2] = {
	FLASH_ADDR_POWER_PART_1_USB_C_WHITE,
	FLASH_ADDR_POWER_PART_1_USB_C_BLUE,
};
static const uint32_t pwr_part1_usb_a[2] = {
	FLASH_ADDR_POWER_PART_1_USB_A_WHITE,
	FLASH_ADDR_POWER_PART_1_USB_A_BLUE,
};

/* ② 端口序号: [行][颜色] */
static const uint32_t pwr_part2_index[PWR_PORT_CNT][2] = {
	{FLASH_ADDR_POWER_PART_2_PORT_1_WHITE, FLASH_ADDR_POWER_PART_2_PORT_1_BLUE},
	{FLASH_ADDR_POWER_PART_2_PORT_2_WHITE, FLASH_ADDR_POWER_PART_2_PORT_2_BLUE},
	{FLASH_ADDR_POWER_PART_2_PORT_3_WHITE, FLASH_ADDR_POWER_PART_2_PORT_3_BLUE},
};

/* ④⑤⑥ 功率数字: [数字][颜色], 第 10 项是 blank (高位空缺占位图) */
#define PWR_DIGIT_BLANK 10
static const uint32_t pwr_part4_digit[11][2] = {
	{FLASH_ADDR_POWER_PART_4_0_WHITE, FLASH_ADDR_POWER_PART_4_0_BLUE},
	{FLASH_ADDR_POWER_PART_4_1_WHITE, FLASH_ADDR_POWER_PART_4_1_BLUE},
	{FLASH_ADDR_POWER_PART_4_2_WHITE, FLASH_ADDR_POWER_PART_4_2_BLUE},
	{FLASH_ADDR_POWER_PART_4_3_WHITE, FLASH_ADDR_POWER_PART_4_3_BLUE},
	{FLASH_ADDR_POWER_PART_4_4_WHITE, FLASH_ADDR_POWER_PART_4_4_BLUE},
	{FLASH_ADDR_POWER_PART_4_5_WHITE, FLASH_ADDR_POWER_PART_4_5_BLUE},
	{FLASH_ADDR_POWER_PART_4_6_WHITE, FLASH_ADDR_POWER_PART_4_6_BLUE},
	{FLASH_ADDR_POWER_PART_4_7_WHITE, FLASH_ADDR_POWER_PART_4_7_BLUE},
	{FLASH_ADDR_POWER_PART_4_8_WHITE, FLASH_ADDR_POWER_PART_4_8_BLUE},
	{FLASH_ADDR_POWER_PART_4_9_WHITE, FLASH_ADDR_POWER_PART_4_9_BLUE},
	{FLASH_ADDR_POWER_PART_4_WHITE, FLASH_ADDR_POWER_PART_4_BLUE},
};

/* ⑦ 单位 w: [颜色] */
static const uint32_t pwr_part5_unit[2] = {
	FLASH_ADDR_POWER_PART_5_WHITE,
	FLASH_ADDR_POWER_PART_5_BLUE,
};

/* 三个数字槽位的 x */
static const uint8_t pwr_digit_x[3] = {PWR_X_DIGIT_H, PWR_X_DIGIT_T, PWR_X_DIGIT_O};

/* ---------------------------- 上一轮显示内容 ------------------------------ */

/* 切页/唤醒必定先走 power_page_init() 全量绘制并填好这两个数组, 所以 updata
   里可以直接信任它们 */
static uint8_t pwr_last_status[PWR_PORT_CNT];
static uint8_t pwr_last_power[PWR_PORT_CNT];

/* ============================ 功率滤波 ====================================
 * 功率是本机拿 V×I 算的 (i2c_slave.c apply_host_data), 受电流采样噪声影响会跳,
 * 直接显示个位数字会抖, 所以取滑动平均。
 *
 * 关键: 采样与绘制解耦。apply_host_data() 每轮主循环都刷新 ui_data, 而绘制被
 * ui_proc 限流到 500ms —— 若跟着绘制节奏入窗(旧主界面的做法), 5 点窗口要跨
 * 2.5s。这里改成独立按 PWR_SAMPLE_MS 入窗, 窗口只跨 5×100ms = 0.5s。
 * ========================================================================== */

#define PWR_FILTER_WIN   5
#define PWR_SAMPLE_MS    100
/* 与窗口均值相差超过此值视为插拔/负载突变: 直接用新值填满窗口, 数字一步到位
   不爬坡。小幅噪声仍走平均 */
#define PWR_JUMP_W       10

static uint8_t  pwr_buf[PWR_PORT_CNT][PWR_FILTER_WIN];
static uint8_t  pwr_buf_idx[PWR_PORT_CNT];
static uint8_t  pwr_samp_status[PWR_PORT_CNT];  /* 上次采样时的状态, 用于检测突变 */
static uint32_t pwr_samp_tick;

/* ---------------------------- 内部实现 ------------------------------------ */

/* 取某一行的原始状态和功率 (未滤波, 未套显示规则) */
static void pwr_raw_port(uint8_t row, uint8_t *status, uint8_t *power)
{
	switch (row)
	{
	case 0:
		*status = ui_data.usb_c1_status;
		*power = ui_data.usb_c1_power;
		break;
	case 1:
		*status = ui_data.usb_c2_status;
		*power = ui_data.usb_c2_power;
		break;
	default:
		*status = ui_data.usb_a_status;
		*power = ui_data.usb_a_power;
		break;
	}

	if (*status > PWR_ST_OUT)
		*status = PWR_ST_IDLE; /* 非法状态按未使用处理 */

	if (*status == PWR_ST_IDLE)
		*power = 0; /* 未使用时主机侧也已清 0, 这里再兜一层 */
}

/* 用同一个值填满整个窗口 (冷启动/切页/突变) */
static void pwr_filter_fill(uint8_t row, uint8_t value)
{
	uint8_t i;
	for (i = 0; i < PWR_FILTER_WIN; i++)
		pwr_buf[row][i] = value;
	pwr_buf_idx[row] = 0;
}

static void pwr_filter_push(uint8_t row, uint8_t value)
{
	uint8_t i = pwr_buf_idx[row];
	pwr_buf[row][i] = value;
	i++;
	if (i >= PWR_FILTER_WIN)
		i = 0;
	pwr_buf_idx[row] = i;
}

/* 窗口均值, 四舍五入 (窗口恒为满, init 时已填满) */
static uint8_t pwr_filter_get(uint8_t row)
{
	uint16_t sum = 0;   /* 255 × 5 = 1275, uint16 够 */
	uint8_t i;
	for (i = 0; i < PWR_FILTER_WIN; i++)
		sum += pwr_buf[row][i];
	return (uint8_t)((sum + PWR_FILTER_WIN / 2) / PWR_FILTER_WIN);
}

static uint8_t pwr_abs_diff(uint8_t a, uint8_t b)
{
	return (a > b) ? (uint8_t)(a - b) : (uint8_t)(b - a);
}

static uint8_t pwr_raw_status(uint8_t row)
{
	uint8_t status, power;
	pwr_raw_port(row, &status, &power);
	return status;
}

/* 取某一行最终要显示的状态和功率 (滤波后 + 显示规则) */
static void pwr_disp_port(uint8_t row, uint8_t *status, uint8_t *power)
{
	*status = pwr_raw_status(row);
	*power  = pwr_filter_get(row);

	if (*status == PWR_ST_IDLE)
		*power = 0; /* 未使用固定显示 0w */
	/* 0/1 门限已在源头处理 (i2c_slave.c port_power_w): <0.2W 判 0, 0.2W~1W 判 1 */
}

/* ③ 段: 未使用时是那张空白胶囊(只有白色一版) */
static uint32_t pwr_dir_addr(uint8_t status)
{
	if (status == PWR_ST_IN)
		return FLASH_ADDR_POWER_PART_3_IN_BLUE;
	if (status == PWR_ST_OUT)
		return FLASH_ADDR_POWER_PART_3_OUT_BLUE;
	return FLASH_ADDR_POWER_PART_3_WHITE;
}

/* 拆成三位定宽槽位, 右对齐, 高位空缺填 blank */
static void pwr_split_digits(uint8_t power, uint8_t d[3])
{
	d[2] = (uint8_t)(power % 10);
	d[1] = (power >= 10) ? (uint8_t)((power / 10) % 10) : PWR_DIGIT_BLANK;
	d[0] = (power >= 100) ? (uint8_t)(power / 100) : PWR_DIGIT_BLANK;
}

/* 整行 7 段全绘 (状态变化时颜色整行翻转, 只能全绘) */
static void pwr_draw_row(uint8_t row, uint8_t status, uint8_t power)
{
	int y = PWR_ROW_Y(row);
	uint8_t c = (status == PWR_ST_IDLE) ? PWR_C_WHITE : PWR_C_BLUE;
	uint8_t d[3];
	uint8_t i;

	/* ① 端口 1/2 是 C 口, 端口 3 是 A 口 */
	Dispphoto_Dispaly_flash(PWR_X_PORT, y,
							(row == 2) ? pwr_part1_usb_a[c] : pwr_part1_usb_c[c]);

	/* ② 端口序号 */
	Dispphoto_Dispaly_flash(PWR_X_INDEX, y, pwr_part2_index[row][c]);

	/* ③ IN / OUT / 空白 */
	Dispphoto_Dispaly_flash(PWR_X_DIR, y, pwr_dir_addr(status));

	/* ④⑤⑥ 功率数字 */
	pwr_split_digits(power, d);
	for (i = 0; i < 3; i++)
		Dispphoto_Dispaly_flash(pwr_digit_x[i], y, pwr_part4_digit[d[i]][c]);

	/* ⑦ 单位 w */
	Dispphoto_Dispaly_flash(PWR_X_UNIT, y, pwr_part5_unit[c]);
}

/* ---------------------------- 对外接口 ------------------------------------ */

/* 功率采样 —— 由 ui_proc 每轮调用(不受 500ms 绘制限流), 内部自己按
   PWR_SAMPLE_MS 节流。采样快、绘制慢, 才能既平滑又不拖延迟 */
void power_page_sample(void)
{
	uint8_t row;

	if (md_get_tick() - pwr_samp_tick < PWR_SAMPLE_MS)
		return;
	pwr_samp_tick = md_get_tick();

	for (row = 0; row < PWR_PORT_CNT; row++)
	{
		uint8_t status, power;
		pwr_raw_port(row, &status, &power);

		/* 插拔或负载突变: 整个窗口换成新值, 否则要 5 个采样周期才爬到位 */
		if (status != pwr_samp_status[row]
		    || pwr_abs_diff(power, pwr_filter_get(row)) >= PWR_JUMP_W)
			pwr_filter_fill(row, power);
		else
			pwr_filter_push(row, power);

		pwr_samp_status[row] = status;
	}
}

void power_page_init(void)
{
	uint8_t row;

	/* 七段刚好铺满整屏, 理论上不清屏也能盖住; 但切页残留的容错成本更高, 先清干净 */
	DispBlock(0, 0, ROW - 1, COL - 1);

	/* 窗口用当前值填满, 避免刚切进来时被上一页期间的陈旧值/0 拉低 */
	for (row = 0; row < PWR_PORT_CNT; row++)
	{
		uint8_t status, power;
		pwr_raw_port(row, &status, &power);
		pwr_filter_fill(row, power);
		pwr_samp_status[row] = status;
	}
	pwr_samp_tick = md_get_tick();

	for (row = 0; row < PWR_PORT_CNT; row++)
	{
		uint8_t status, power;
		pwr_disp_port(row, &status, &power);
		LOGI("[PWR] init row=%d status=%d power=%d\r\n", row, status, power);
		pwr_draw_row(row, status, power);
		pwr_last_status[row] = status;
		pwr_last_power[row] = power;
	}
}

void power_page_updata(void)
{
	uint8_t row;

	for (row = 0; row < PWR_PORT_CNT; row++)
	{
		uint8_t status, power;
		pwr_disp_port(row, &status, &power);

		if (status == pwr_last_status[row] && power == pwr_last_power[row])
			continue;

		if (status != pwr_last_status[row])
		{
			/* 状态变了 → 整行换色, 7 段全部重绘 */
			LOGI("[PWR] row=%d redraw status=%d power=%d\r\n", row, status, power);
			pwr_draw_row(row, status, power);
		}
		else
		{
			/* 只有功率变了 → 颜色不变, 只补被改动的数字槽位 */
			uint8_t d_new[3], d_old[3];
			int y = PWR_ROW_Y(row);
			uint8_t c = (status == PWR_ST_IDLE) ? PWR_C_WHITE : PWR_C_BLUE;
			uint8_t i;

			pwr_split_digits(power, d_new);
			pwr_split_digits(pwr_last_power[row], d_old);

			for (i = 0; i < 3; i++)
			{
				if (d_new[i] != d_old[i])
					Dispphoto_Dispaly_flash(pwr_digit_x[i], y, pwr_part4_digit[d_new[i]][c]);
			}
		}

		pwr_last_status[row] = status;
		pwr_last_power[row] = power;
	}
}
