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
#define KEY_LONG_MIN_MS     2500    /* 主界面长按阈值 (小电流上报, 立即触发不等松手) */
#define KEY_LONG_PAGE_MS    5000    /* 其余页面长按阈值 (切页等) */
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
uint32_t key_get_last_ms(void);  /* 获取最后一次按键时刻, 用于空闲休眠检测 */

/* 按键事件: 仅传事件类型, 由 power_mgr 根据状态决定行为 */
typedef enum {
    KEY_EVENT_NONE   = 0,
    KEY_EVENT_CLICK  = 1,   /* 单击 */
    KEY_EVENT_DOUBLE = 2,   /* 双击 */
    KEY_EVENT_LONG   = 3,   /* 长按 5s */
    KEY_EVENT_COMBO  = 4,   /* 组合键 (5击+长按) */
} key_event_t;

key_event_t key_get_event(void);     /* 获取并清除最近按键事件 */

void key_single_click_cb(void);
void key_double_click_cb(void);
void key_long_press_cb(void);
void key_combo_cb(void);
void key_wake_host(void);       /* 主机休眠+高温 → KEY_PIN 拉低 5ms 唤醒 */

#endif
