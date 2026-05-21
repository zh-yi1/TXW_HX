#include "key.h"

static key_state_t key_state = KEY_STATE_IDLE;
static uint16_t    key_tick  = 0;
static uint8_t     key_click_cnt = 0;

void key_init(void)
{
	md_gpio_init_t gpio_init;
	md_gpio_init_struct(&gpio_init);

	gpio_init.mode = MD_GPIO_MODE_INPUT;

	md_gpio_init(KEY_PORT, KEY_PIN, &gpio_init);
}

void key_proc(void)
{
	static uint32_t last_tick = 0;
	uint32_t now = md_get_tick();

	if (now - last_tick < 10)
		return;
	last_tick = now;

	switch (key_state)
	{
	case KEY_STATE_IDLE:
		if (KEY_PRESSED())
		{
			key_state = KEY_STATE_DEBOUNCE;
			key_tick = KEY_DEBOUNCE_TICK;
		}
		break;

	case KEY_STATE_DEBOUNCE:
		if (!KEY_PRESSED())
		{
			key_state = KEY_STATE_IDLE;
		}
		else if (--key_tick == 0)
		{
			key_click_cnt++;
			key_state = KEY_STATE_PRESS;
			key_tick = 0;
		}
		break;

	case KEY_STATE_PRESS:
		if (!KEY_PRESSED())
		{
			if (key_tick >= KEY_SHORT_TICK)
			{
				if (key_click_cnt >= 2)
				{
					key_double_press_cb();
					key_click_cnt = 0;
					key_state = KEY_STATE_IDLE;
				}
				else
				{
					key_state = KEY_STATE_WAIT_DOUBLE;
					key_tick = KEY_DOUBLE_TICK;
				}
			}
			else
			{
				key_click_cnt = 0;
				key_state = KEY_STATE_IDLE;
			}
		}
		else
		{
			key_tick++;
			if (key_tick >= KEY_LONG_TICK)
			{
				key_long_press_cb();
				key_click_cnt = 0;
				key_state = KEY_STATE_LONG;
			}
		}
		break;

	case KEY_STATE_WAIT_DOUBLE:
		if (KEY_PRESSED())
		{
			key_state = KEY_STATE_DEBOUNCE;
			key_tick = KEY_DEBOUNCE_TICK;
		}
		else if (--key_tick == 0)
		{
			key_short_press_cb();
			key_click_cnt = 0;
			key_state = KEY_STATE_IDLE;
		}
		break;

	case KEY_STATE_LONG:
		if (!KEY_PRESSED())
		{
			key_state = KEY_STATE_IDLE;
		}
		break;
	}
}

void key_short_press_cb(void)
{
}

void key_double_press_cb(void)
{
}

void key_long_press_cb(void)
{
}
