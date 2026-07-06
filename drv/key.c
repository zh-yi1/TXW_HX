#include "key.h"

static key_state_t key_state       = KEY_STATE_IDLE;
static uint32_t    state_entry_ms  = 0;
static uint32_t    press_start_ms  = 0;
static uint32_t    last_press_ms   = 0;
static uint8_t     burst_cnt       = 0;   /* presses in current burst, for single/double resolution */
static uint8_t     combo_cnt       = 0;   /* total presses for combo tracking */
static bool        is_2nd_click    = false;
static bool        combo_fired     = false;
static key_event_t g_key_event     = KEY_EVENT_NONE;   /* 按键事件, 供 power_mgr 使用 */

#define KEY_IDLE_RESET_MS   3000    /* reset combo_cnt after 3s idle */

void key_init(void)
{
	md_gpio_init_t gpio_init;
	md_gpio_init_struct(&gpio_init);
	gpio_init.mode = MD_GPIO_MODE_INPUT;
	md_gpio_init(KEY_PORT, KEY_PIN, &gpio_init);
	last_press_ms = md_get_tick();  /* 初始化空闲计时基准 */
}

uint32_t key_get_last_ms(void)
{
	return last_press_ms;
}

key_event_t key_get_event(void)
{
	key_event_t ev = g_key_event;
	g_key_event = KEY_EVENT_NONE;
	return ev;
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
			else
			{
				/* too short, dead zone, or long-press already fired */
				burst_cnt    = 0;
				combo_cnt    = 0;
				is_2nd_click = false;
				key_state    = KEY_STATE_IDLE;
			}
		}
		else if (held >= KEY_LONG_MIN_MS && !combo_fired)
		{
			/* ----- 5s threshold reached, fire immediately (no wait for release) ----- */
			if (combo_cnt >= KEY_COMBO_CLICKS)
			{
				key_combo_cb();
			}
			else
			{
				key_long_press_cb();
			}
			combo_fired = true;
			key_state   = KEY_STATE_LONG_HOLD;
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
	g_key_event = KEY_EVENT_CLICK;  /* 通知 power_mgr */

	key_single_click_ui_proc();
	/* 设置按键事件 bit0: 单击 (写入影子缓冲, 由 i2c_slave_proc 原子交换) */
	key_event_buf |= 0x01;
}

void key_double_click_cb(void)
{
	g_key_event = KEY_EVENT_DOUBLE;  /* 通知 power_mgr */
}

void key_long_press_cb(void)
{
	g_key_event = KEY_EVENT_LONG;

	/* 灭屏状态下忽略长按 */
	if (ui_data.dev_state == DEV_STATE_SLEEP_ACTIVE
	    || ui_data.dev_state == DEV_STATE_SLEEP_PASSIVE)
		return;

	bool ret = key_long_press_ui_proc();
	if(ret)
	{
		/* 设置按键事件 bit4: 长按3S (写入影子缓冲) */
		key_event_buf |= 0x10;
	}
}

void key_combo_cb(void)
{
	g_key_event = KEY_EVENT_COMBO;

#ifdef UPGRADE_EN
	/* 仅充电时允许触发升级模式: 设置标志位, main() 循环中处理 */
	if (ui_data.is_charge) {
		g_enter_upgrade = 1;
	}
#endif
}

/* ========================================================================
 * key_wake_host — 主机休眠且电芯高温时, KEY_PIN 拉低 5ms 唤醒主机
 *
 * 条件: (1) I2C 连续 5s 无地址匹配 → 主机休眠
 *       (2) IP3561Q NTC 阻值 ≤ 26kΩ → 电芯高温 (NTC 阻值越低温度越高)
 * 动作: KEY_PIN 切为输出 → 拉低 5ms → key_init() 恢复输入上拉
 *       重置 I2C 地址匹配计时, 避免短时间内重复唤醒
 * ======================================================================== */
void key_wake_host(void)
{
	if (!i2c_is_host_sleeping() && !g_bat_high_temp)
		return;

	/* KEY_PIN 切输出, 拉低 5ms 产生唤醒脉冲 */
	md_gpio_set_pin_mode_output(KEY_PORT, KEY_PIN);
	md_gpio_set_pin_low(KEY_PORT, KEY_PIN);
	md_delay_1ms(5);

	/* 恢复 KEY_PIN 为输入上拉 */
	key_init();

	/* 重置计时, 避免主机未就绪前重复唤醒 */
	g_i2c_addr_match_tick = md_get_tick();
}
