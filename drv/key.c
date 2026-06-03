#include "key.h"

static key_state_t key_state       = KEY_STATE_IDLE;
static uint32_t    state_entry_ms  = 0;
static uint32_t    press_start_ms  = 0;
static uint32_t    last_press_ms   = 0;
static uint8_t     burst_cnt       = 0;   /* presses in current burst, for single/double resolution */
static uint8_t     combo_cnt       = 0;   /* total presses for combo tracking */
static bool        is_2nd_click    = false;
static bool        combo_fired     = false;

#define KEY_IDLE_RESET_MS   3000    /* reset combo_cnt after 3s idle */

void key_init(void)
{
	md_gpio_init_t gpio_init;
	md_gpio_init_struct(&gpio_init);
	gpio_init.mode = MD_GPIO_MODE_INPUT;
	md_gpio_init(KEY_PORT, KEY_PIN, &gpio_init);
}

void key_proc(void)
{
	static uint32_t last_ms = 0;
	uint32_t now = md_get_tick();

	if (now - last_ms < KEY_SAMPLE_MS)
		return;
	last_ms = now;

	uint32_t elapsed = now - state_entry_ms;
	uint32_t held    = now - press_start_ms;

	switch (key_state)
	{
	/* ---- IDLE ---- */
	case KEY_STATE_IDLE:
		combo_fired = false;
		if (now - last_press_ms > KEY_IDLE_RESET_MS)
			combo_cnt = 0;
		if (KEY_PRESSED())
		{
			key_state       = KEY_STATE_DEBOUNCE;
			state_entry_ms  = now;
			press_start_ms  = now;
			is_2nd_click    = false;
		}
		break;

	/* ---- DEBOUNCE: confirm press is real ---- */
	case KEY_STATE_DEBOUNCE:
		if (!KEY_PRESSED())
		{
			if (is_2nd_click)
				key_state = KEY_STATE_WAIT_DOUBLE;
			else
				key_state = KEY_STATE_IDLE;
		}
		else if (elapsed >= KEY_DEBOUNCE_MS)
		{
			burst_cnt++;
			combo_cnt++;
			last_press_ms  = now;
			key_state      = KEY_STATE_PRESS;
			state_entry_ms = now;
		}
		break;

	/* ---- PRESS: waiting for release or long-press threshold ---- */
	case KEY_STATE_PRESS:
		if (!KEY_PRESSED())
		{
			/* ----- key released ----- */
			if (held >= KEY_SHORT_MIN_MS && held < KEY_SHORT_MAX_MS)
			{
				/* always go back to WAIT_DOUBLE, don't resolve yet */
				is_2nd_click = false;
				key_state      = KEY_STATE_WAIT_DOUBLE;
				state_entry_ms = now;
			}
			else if (held >= KEY_LONG_MIN_MS
			         && held < KEY_LONG_MAX_MS
			         && !combo_fired)
			{
				key_long_press_cb();
				burst_cnt = 0;
				combo_cnt = 0;
				key_state = KEY_STATE_IDLE;
			}
			else
			{
				/* too short, dead zone, or combo already fired */
				burst_cnt    = 0;
				combo_cnt    = 0;
				is_2nd_click = false;
				key_state    = KEY_STATE_IDLE;
			}
		}
		else if (held >= KEY_LONG_MIN_MS && held < KEY_LONG_MAX_MS)
		{
			/* ----- long-press threshold reached ----- */
			if (!combo_fired && combo_cnt >= KEY_COMBO_CLICKS)
			{
				key_combo_cb();
				combo_fired = true;
				key_state   = KEY_STATE_LONG_HOLD;
			}
			/* else: stay in PRESS, long-press fires on release */
		}
		else if (held >= KEY_LONG_MAX_MS)
		{
			/* exceeded max hold — discard */
			burst_cnt = 0;
			combo_cnt = 0;
			key_state = KEY_STATE_LONG_HOLD;
		}
		break;

	/* ---- WAIT_DOUBLE: waiting for more clicks ---- */
	case KEY_STATE_WAIT_DOUBLE:
		if (KEY_PRESSED())
		{
			press_start_ms = now;
			if (elapsed >= KEY_DOUBLE_GAP_MS)
			{
				is_2nd_click    = true;
				key_state       = KEY_STATE_DEBOUNCE;
				state_entry_ms  = now;
			}
		}
		else if (elapsed >= KEY_DOUBLE_WAIT_MS)
		{
			/* timeout: resolve burst */
			if (burst_cnt == 1)
				key_single_click_cb();
			else if (burst_cnt == 2)
				key_double_click_cb();
			/* burst_cnt >= 3: no click event, just accumulate for combo */

			burst_cnt = 0;
			key_state = KEY_STATE_IDLE;
		}
		break;

	/* ---- LONG_HOLD: combo fired or max hold exceeded, waiting for release ---- */
	case KEY_STATE_LONG_HOLD:
		if (!KEY_PRESSED())
		{
			burst_cnt = 0;
			combo_cnt = 0;
			key_state = KEY_STATE_IDLE;
		}
		break;
	}
}

void key_single_click_cb(void)
{
	if (ui_data.dev_state == DEV_STATE_SLEEP)
	{
		/* 休眠 → 唤醒: 开背光, 进入主界面 */
		LCD_BLK_LOW();
		ui_data.dev_state = DEV_STATE_NORMAL;
		ui_data.cur_page  = PAGE_DEFAULT;
		ui_data.last_page = PAGE_MAX;  /* 强制触发界面重刷 */
	}
	else
	{
		//TODO: 处理切换界面的逻辑
		/* 正常状态: 切换显示界面 (循环) */
		ui_data.cur_page = (page_t)((ui_data.cur_page + 1) % PAGE_MAX);
	}

	/* 设置按键事件 bit0: 单击 (写入影子缓冲, 由 i2c_slave_proc 原子交换) */
	key_event_buf |= 0x01;
}

void key_double_click_cb(void)
{
	/* 休眠状态下忽略双击 */
	if (ui_data.dev_state == DEV_STATE_SLEEP)
		return;

	/* 刷黑屏幕, 关背光, 进入休眠 */
	LCD_BLK_HIGH();
	DispColor(BLACK);
	ui_data.dev_state = DEV_STATE_SLEEP;

	/* 设置按键事件 bit1: 双击 (写入影子缓冲) */
	key_event_buf |= 0x02;
}

void key_long_press_cb(void)
{
	/* 休眠状态下忽略长按 */
	if (ui_data.dev_state == DEV_STATE_SLEEP)
		return;

	/* 进入/退出 USB-A 小电流模式 */
	ui_data.low_current_flag = !ui_data.low_current_flag;

	/* 设置按键事件 bit4: 长按3S (写入影子缓冲) */
	key_event_buf |= 0x10;
}

void key_combo_cb(void)
{
	/* 触发升级模式: 设置标志位, main() 循环中处理 */
	g_enter_upgrade = 1;
}
