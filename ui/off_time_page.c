#include "global_define.h"

/* ============================================================================
 * 息屏时长设置页
 *
 *   y=0     240x32   息屏时长 (标题)
 *   y=40    240x19   请双击按键进行切换
 *   y=70    112x28   30秒  @x=4      60秒   @x=124
 *   y=106   112x28   5分钟 @x=4      30分钟 @x=124
 *
 * 四个选项每张切图都有普通/暗色两版, 选中用普通版。双击切到下一项并轮回,
 * 新时长立刻生效 (双击本身也会刷新 power_mgr 的活动时间戳, 计时从头开始)。
 *
 * 时长的唯一真值在 power_mgr, 本页进来时反查它决定选中项 —— 这样息屏后再
 * 进来选中的还是上次那项, 本页不用自己记状态。
 * ========================================================================== */

#define OFT_TITLE_X   0
#define OFT_TITLE_Y   0
#define OFT_HINT_X    0
#define OFT_HINT_Y    40

#define OFT_OPT_CNT   4
#define OFT_COL_L_X   4     /* 左列 x, 4+112=116 */
#define OFT_COL_R_X   124   /* 右列 x, 124+112=236 */
#define OFT_ROW_1_Y   70
#define OFT_ROW_2_Y   106

/* 图片下标: 0=暗色(未选中) 1=普通(选中) */
#define OFT_UNSELECTED  0
#define OFT_SELECTED    1

typedef struct
{
	uint8_t  x;
	uint8_t  y;
	uint32_t addr[2];   /* [未选中, 选中] */
	uint32_t ms;        /* 对应的息屏时长 */
} oft_opt_t;

static const oft_opt_t oft_opt[OFT_OPT_CNT] = {
	{ OFT_COL_L_X, OFT_ROW_1_Y, { FLASH_ADDR_BTN_30S_DARK,   FLASH_ADDR_BTN_30S   },   30000UL },
	{ OFT_COL_R_X, OFT_ROW_1_Y, { FLASH_ADDR_BTN_60S_DARK,   FLASH_ADDR_BTN_60S   },   60000UL },
	{ OFT_COL_L_X, OFT_ROW_2_Y, { FLASH_ADDR_BTN_300S_DARK,  FLASH_ADDR_BTN_300S  },  300000UL },
	{ OFT_COL_R_X, OFT_ROW_2_Y, { FLASH_ADDR_BTN_1800S_DARK, FLASH_ADDR_BTN_1800S },  1800000UL },
};

static uint8_t oft_sel;     /* 当前选中项 */
static uint8_t oft_drawn;   /* 屏上正显示为选中状态的那一项 */

/* ---------------------------- 内部实现 ------------------------------------ */

/* 由当前生效的息屏时长反推选中项, 匹配不上(被别处改过)就回到 30 秒那项 */
static uint8_t oft_idx_from_ms(uint32_t ms)
{
	uint8_t i;
	for (i = 0; i < OFT_OPT_CNT; i++)
	{
		if (oft_opt[i].ms == ms)
			return i;
	}
	return 0;
}

static void oft_draw_opt(uint8_t i, uint8_t c)
{
	Dispphoto_Dispaly_flash(oft_opt[i].x, oft_opt[i].y, oft_opt[i].addr[c]);
}

/* ---------------------------- 对外接口 ------------------------------------ */

void off_time_page_init(void)
{
	uint8_t i;

	DispBlock(0, 0, ROW - 1, COL - 1);

	oft_sel = oft_idx_from_ms(power_mgr_get_sleep_ms());

	Dispphoto_Dispaly_flash(OFT_TITLE_X, OFT_TITLE_Y, FLASH_ADDR_TITLE_SCREEN_OFF_DURATION);
	Dispphoto_Dispaly_flash(OFT_HINT_X,  OFT_HINT_Y,  FLASH_ADDR_DOUBLE_CLICK_SWITCH);

	for (i = 0; i < OFT_OPT_CNT; i++)
		oft_draw_opt(i, (i == oft_sel) ? OFT_SELECTED : OFT_UNSELECTED);

	oft_drawn = oft_sel;
}

/* 双击切下一项。这里只改选中项和生效时长, 绘制留给 off_time_page_updata,
   按键回调里不做 SPI 长传输。
   新时长立刻生效, 且从这一刻重新计时 —— 后者靠 key_double_click_ui_proc 返回
   false 走 KEY_EVENT_CLICK, power_mgr 收到按键事件就把 last_activity_ms 推到当前,
   所以 30S 双击进 60S 是从按下起算 60 秒, 已空转的时间不计。改这条返回值前先想想 */
void off_time_page_next(void)
{
	oft_sel++;
	if (oft_sel >= OFT_OPT_CNT)
		oft_sel = 0;

	power_mgr_set_sleep_ms(oft_opt[oft_sel].ms);
	LOGI("[OFT] sel=%d ms=%d\r\n", oft_sel, (int)oft_opt[oft_sel].ms);
}

/* 只有选中项变了才动屏: 旧项刷暗色、新项刷普通版, 标题和提示行一张都不碰 */
void off_time_page_updata(void)
{
	if (oft_sel == oft_drawn)
		return;

	oft_draw_opt(oft_drawn, OFT_UNSELECTED);
	oft_draw_opt(oft_sel,   OFT_SELECTED);
	oft_drawn = oft_sel;
}
