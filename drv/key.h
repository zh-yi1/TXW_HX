#ifndef __KEY_H
#define __KEY_H

#include "global_define.h"

#define KEY_PORT            GPIOA
#define KEY_PIN             MD_GPIO_PIN_15

#define KEY_DEBOUNCE_MS     50
#define KEY_SHORT_MS        300
#define KEY_LONG_MS         3000

#define KEY_DEBOUNCE_TICK   (KEY_DEBOUNCE_MS / 10)
#define KEY_SHORT_TICK      (KEY_SHORT_MS / 10)
#define KEY_LONG_TICK       (KEY_LONG_MS / 10)

#define KEY_PRESSED()       (md_gpio_get_pin(KEY_PORT, KEY_PIN) == 0)

typedef enum
{
    KEY_STATE_IDLE = 0,
    KEY_STATE_DEBOUNCE,
    KEY_STATE_PRESS,
    KEY_STATE_LONG,
} key_state_t;

void key_init(void);
void key_proc(void);

void key_short_press_cb(void);
void key_long_press_cb(void);

#endif
