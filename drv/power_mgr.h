#ifndef __POWER_MGR_H
#define __POWER_MGR_H

/* ---- 调试模式: 灭屏5s进STOP, 20s定时唤醒, 任意唤醒均亮屏 ---- */
// #define DEBUG_STOP
#define UART_DEBUG   /* 调试: STOP 唤醒后立即恢复串口, 唤醒路径打印可见; 发布前注释掉 */

#define POWER_MGR_SLEEP_IDLE_MS     30000U    /* 30s 无操作进 SLEEP */

#ifdef DEBUG_STOP
  #define POWER_MGR_IWDG_WAKEUP_SEC   20U    /* 20s 定时唤醒 */
#else
  #define POWER_MGR_IWDG_WAKEUP_SEC   120U    /* 60s 定时唤醒 */
#endif

/* ---- 设备电源状态 ---- */
typedef enum {
    DEV_STATE_NORMAL        = 0,  /* 正常亮屏 */
    DEV_STATE_SLEEP_ACTIVE  = 1,  /* 主动灭屏 (双击触发) */
    DEV_STATE_SLEEP_PASSIVE = 2,  /* 被动灭屏 (30s超时 或 主动灭屏后USB断开转入) */
    DEV_STATE_STOP          = 3,  /* MCU STOP 低功耗 */
} dev_state_t;

/* ---- 唤醒原因 (ISR 标记, exit流程读取) ---- */
typedef enum {
    WAKEUP_CAUSE_NONE     = 0,
    WAKEUP_CAUSE_KEY      = 1,   /* PA15 下降沿 */
    WAKEUP_CAUSE_IWDG     = 2,   /* IWDT 超时 */
    WAKEUP_CAUSE_I2C_SCL  = 3,   /* PA5(I2C SCL) 下降沿, 主机拉低唤醒 */
} wakeup_cause_t;

/* ---- ISR 可访问 ---- */
extern volatile wakeup_cause_t g_wakeup_cause;

/* ---- 对外 API ---- */
void power_mgr_init(void);                  /* 配置 PA15 EXTI + WWDT(看门狗) + IWDT(唤醒) */
void power_mgr_proc(void);                  /* 主循环调用: 灭屏/唤醒状态机 + 条件检查进STOP */
void power_mgr_enter_stop(void);            /* 进入 STOP (do-while循环) */
void power_mgr_notify_host_wakeup(void);    /* 预留空 API */

#endif /* __POWER_MGR_H */
