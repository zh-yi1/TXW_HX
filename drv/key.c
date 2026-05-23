#include "key.h"

static key_state_t key_state      = KEY_STATE_IDLE;
static uint32_t    state_entry_ms = 0;
static uint8_t     key_click_cnt  = 0;

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

	/* 1ms sampling: fast enough for response, slow enough to skip bounce */
	if (now - last_ms < 1)
		return;
	last_ms = now;

	uint32_t elapsed = now - state_entry_ms;

	switch (key_state)
	{
	case KEY_STATE_IDLE:
		if (KEY_PRESSED())
		{
			key_state      = KEY_STATE_DEBOUNCE;
			state_entry_ms = now;
		}
		break;

	case KEY_STATE_DEBOUNCE:
		if (!KEY_PRESSED())
		{
			key_click_cnt = 0;
			key_state     = KEY_STATE_IDLE;
		}
		else if (elapsed >= KEY_DEBOUNCE_MS)
		{
			key_click_cnt++;
			key_state      = KEY_STATE_PRESS;
			state_entry_ms = now;
		}
		break;

	case KEY_STATE_PRESS:
		if (!KEY_PRESSED())
		{
			if (elapsed >= KEY_SHORT_MS)
			{
				if (key_click_cnt >= 2)
				{
					key_double_press_cb();
					key_click_cnt = 0;
					key_state     = KEY_STATE_IDLE;
				}
				else
				{
					key_state      = KEY_STATE_WAIT_DOUBLE;
					state_entry_ms = now;
				}
			}
			else
			{
				if (key_click_cnt >= 2)
				{
					key_short_press_cb();
				}
				key_click_cnt = 0;
				key_state     = KEY_STATE_IDLE;
			}
		}
		else
		{
			if (elapsed >= KEY_LONG_MS)
			{
				key_long_press_cb();
				key_click_cnt = 0;
				key_state     = KEY_STATE_LONG;
			}
		}
		break;

	case KEY_STATE_WAIT_DOUBLE:
		if (KEY_PRESSED())
		{
			key_state      = KEY_STATE_DEBOUNCE;
			state_entry_ms = now;
		}
		else if (elapsed >= KEY_DOUBLE_MS)
		{
			key_short_press_cb();
			key_click_cnt = 0;
			key_state     = KEY_STATE_IDLE;
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
	static uint8_t bl_on = 1;

	if (bl_on)
	{
		LCD_BLK_HIGH();
		bl_on = 0;
	}
	else
	{
		LCD_BLK_LOW();
		bl_on = 1;
	}
}

void key_double_press_cb(void)
{
}

void key_long_press_cb(void)
{
}
