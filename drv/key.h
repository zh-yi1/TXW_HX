#ifndef __KEY_H
#define __KEY_H

#include "global_define.h"

#define KEY_PORT            GPIOA
#define KEY_PIN             MD_GPIO_PIN_15

/* sampling period (ms) */
#define KEY_SAMPLE_MS       10

/* timing thresholds (ms) */
#define KEY_DEBOUNCE_MS     30      /* press debounce: must hold 30ms to confirm */
#define KEY_SHORT_MIN_MS    100     /* minimum press for a valid click */
#define KEY_SHORT_MAX_MS    1500    /* maximum press for a click (beyond → long-press) */
#define KEY_DOUBLE_GAP_MS   50     /* minimum gap after release for 2nd click (filters bounce) */
#define KEY_DOUBLE_WAIT_MS  500     /* maximum wait for 2nd click (then confirms single click) */
#define KEY_LONG_MIN_MS     3000    /* minimum hold for long-press */
#define KEY_LONG_MAX_MS     6000    /* maximum hold for long-press (exceed = ignore) */
#define KEY_COMBO_CLICKS    5       /* clicks needed before combo long-press */

#define KEY_PRESSED()       (md_gpio_get_input_data(KEY_PORT, KEY_PIN) == 0)

typedef enum {
	KEY_STATE_IDLE = 0,
	KEY_STATE_DEBOUNCE,
	KEY_STATE_PRESS,
	KEY_STATE_WAIT_DOUBLE,
	KEY_STATE_LONG_HOLD,
} key_state_t;

void key_init(void);
void key_proc(void);

void key_single_click_cb(void);
void key_double_click_cb(void);
void key_long_press_cb(void);
void key_combo_cb(void);

#endif
