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
	static bool single_flag = false;
	single_flag = !single_flag;
}

void key_double_click_cb(void)
{
	static bool double_flag = false;
	double_flag = !double_flag;
}

void key_long_press_cb(void)
{
	static bool long_flag = false;
	long_flag = !long_flag;
}

void key_combo_cb(void)
{
	static bool combo_flag = false;
	combo_flag = !combo_flag;
}
