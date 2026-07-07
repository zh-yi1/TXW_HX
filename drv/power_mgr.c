#include "global_define.h"
#include "power_mgr.h"

/* ---- 模块静态变量 ---- */
static uint8_t g_in_stop = 0; /* 防止重复进入 STOP */

/* ---- 唤醒原因 (ISR 写入, exit流程读取) ---- */
volatile wakeup_cause_t g_wakeup_cause = WAKEUP_CAUSE_NONE;

/* ---- 唤醒标记: 防止唤醒后秒进SLEEP ---- */
static volatile uint8_t s_just_woke_up = 0;

/* ---- 前向声明 ---- */
static void power_mgr_io_low_power_config(void);
static void power_mgr_exit_stop_lite(void);
static void power_mgr_exit_stop_full(void);
static void screen_off(void);
static void wake_screen(void);

/* ========================================================================
 * screen_off — 灭屏 (不进 STOP，仅关背光+黑屏)
 * ======================================================================== */
static void screen_off(void)
{
    LCD_BLK_HIGH();
    DispColor(BLACK);
}

/* ========================================================================
 * wake_screen — 亮屏恢复
 * ======================================================================== */
static void wake_screen(void)
{
    s_just_woke_up = 1; /* 通知 power_mgr_proc 刷新活动时间 */
    LCD_BLK_LOW();
    ui_data.dev_state = DEV_STATE_NORMAL;
    ui_data.cur_page = PAGE_DEFAULT;
    ui_data.last_page = PAGE_MAX; /* 强制刷新 */
}

/* ========================================================================
 * power_mgr_notify_host_wakeup — 唤醒后通知主机 (预留)
 * ======================================================================== */
void power_mgr_notify_host_wakeup(void)
{
    /* TODO: 通过 I2C 寄存器通知主机 MCU 已唤醒, 协议待定 */
}

/* ========================================================================
 * power_mgr_init — 一次性配置 PA15 EXTI + WWDT
 * ======================================================================== */
void power_mgr_init(void)
{
    /* ---- PA15 EXTI: 下降沿唤醒 ---- */
    md_gpio_set_interrupt_port(KEY_PORT, KEY_PIN);
    md_gpio_enable_trailing_edge_trigger(KEY_PIN);
    md_gpio_enable_external_interrupt(KEY_PIN);
    md_gpio_interrupt_filter_time_set(10U);
    md_gpio_interrupt_filter_enable(KEY_PIN);
    md_mcu_irq_config(EXTI12_15_IRQn, 0, ENABLE);

    /* ---- IWDT: 定时唤醒, 60s, 中断使能(唤醒STOP), 不复位 ---- */
    md_iwdt_init(32000 * POWER_MGR_IWDG_WAKEUP_SEC, ENABLE);
    IWDT_UNLOCK();
    md_iwdt_enable();
    IWDT_LOCK();
    md_mcu_irq_config(IWDT_IRQn, 0, ENABLE);
}

/* ========================================================================
 * power_mgr_io_low_power_config — 进 STOP 前 IO 防漏电配置
 * ======================================================================== */
static void power_mgr_io_low_power_config(void)
{
    /* ---- 模拟模式 (高阻态) ---- */

    /* PA1(LCD_RS)/PA7/PA8/PA9/PA10(SPI CLK)/PA11(SPI MOSI)/PA12(SPI MISO)/PA14(SW_SDA) */
    GPIOA->MODE &= ~(MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_1) | MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_7) | MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_8) | MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_9) | MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_10) | MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_11) | MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_12) | MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_14));

    /* PA5(I2C1 SCL)/PA6(I2C1 SDA) — 外部上拉, 模拟模式安全 */
    GPIOA->MODE &= ~(MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_5) | MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_6));

    /* PB0(USART RX)/PB1(USART TX)/PB5(SW_SCL) */
    GPIOB->MODE &= ~(MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_0) | MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_1) | MD_GPIO_PIN_TWO_MSK(MD_GPIO_PIN_5));

    /* ---- 推挽输出低 ---- */

    /* PA0 LCD_RST -> 低 (LCD 复位安全态) */
    GPIOA->MODE |= MD_GPIO_PIN_TWO_1_MSK(MD_GPIO_PIN_0);
    CLEAR_BIT(GPIOA->OD, MD_GPIO_PIN_TWO_1_MSK(MD_GPIO_PIN_0));
    md_gpio_set_pin_low(GPIOA, MD_GPIO_PIN_0);

    /* PA4 TFT_EN -> 低 */
    GPIOA->MODE |= MD_GPIO_PIN_TWO_1_MSK(MD_GPIO_PIN_4);
    CLEAR_BIT(GPIOA->OD, MD_GPIO_PIN_TWO_1_MSK(MD_GPIO_PIN_4));
    md_gpio_set_pin_low(GPIOA, MD_GPIO_PIN_4);

    /* PB6 LCD_BLK -> 低 (背光关) */
    GPIOB->MODE |= MD_GPIO_PIN_TWO_1_MSK(MD_GPIO_PIN_6);
    CLEAR_BIT(GPIOB->OD, MD_GPIO_PIN_TWO_1_MSK(MD_GPIO_PIN_6));
    md_gpio_set_pin_low(GPIOB, MD_GPIO_PIN_6);

    /* ---- 推挽输出高 (片选不选中) ---- */

    /* PA3 LCD_CS -> 高 */
    GPIOA->MODE |= MD_GPIO_PIN_TWO_1_MSK(MD_GPIO_PIN_3);
    CLEAR_BIT(GPIOA->OD, MD_GPIO_PIN_TWO_1_MSK(MD_GPIO_PIN_3));
    md_gpio_set_pin_high(GPIOA, MD_GPIO_PIN_3);

    /* PB3 FLASH_CS -> 高 */
    GPIOB->MODE |= MD_GPIO_PIN_TWO_1_MSK(MD_GPIO_PIN_3);
    CLEAR_BIT(GPIOB->OD, MD_GPIO_PIN_TWO_1_MSK(MD_GPIO_PIN_3));
    md_gpio_set_pin_high(GPIOB, MD_GPIO_PIN_3);

    /* PA15 KEY: 保持输入上拉 (唤醒引脚, 不动) */
    /* PA2, PA13(SWDIO): 保持默认模拟模式, 不动 */
}

/* ========================================================================
 * power_mgr_exit_stop_lite — IWDT 唤醒后的轻量恢复 (仅 I2C + AFE)
 * 不亮屏、不恢复 LCD/SPI/背光/PWM
 * ======================================================================== */
static void power_mgr_exit_stop_lite(void)
{
    i2c_slave_init(); /* I2C1 从机: 读取主机数据 */
    ip3561q_init();   /* AFE: 读取电池数据 */
}

/* ========================================================================
 * power_mgr_exit_stop_full — 全恢复 (按键唤醒 或 IWDT 高温告警)
 * ======================================================================== */
static void power_mgr_exit_stop_full(void)
{
    s_just_woke_up = 1;
    dma_init();
    ui_init();
    key_init();
#ifndef UART_DEBUG
    usart_init(115200); // 非调试在此处初始化串口
#endif                  /* !UART_DEBUG */

    LCD_BLK_LOW();
    LOGI("[PWR] exit_stop_full: done\r\n");

    /* 恢复 UI 状态 */
    ui_data.dev_state = DEV_STATE_NORMAL;
    ui_data.cur_page = PAGE_DEFAULT;
    ui_data.last_page = PAGE_MAX; /* 强制刷新 */
}

/* ========================================================================
 * power_mgr_enter_stop — STOP 进入/退出循环
 *
 * 流程:
 *   首次: 关背光 + LCD 休眠
 *   循环: IO 低功耗 -> WFI -> 判断唤醒源 -> 不同恢复路径
 *
 *   按键唤醒 -> 全恢复 -> 退出循环
 *   IWDT 唤醒 + 无高温 -> 轻量恢复 -> 重进 STOP
 *   IWDT 唤醒 + 有高温 -> 全恢复 + 告警页 -> 退出循环
 * ======================================================================== */
void power_mgr_enter_stop(void)
{
    g_in_stop = 1;

    LOGI("[PWR] enter STOP\r\n");

    /* 首次进入: 关显示 (只执行一次) */
    LCD_BLK_HIGH();
    WriteComm(0x28); /* Display OFF */
    WriteComm(0x10); /* Sleep In */

    do
    {
        /* IO 低功耗配置 (防漏电) */
        power_mgr_io_low_power_config();

        /* 清零唤醒原因 */
        g_wakeup_cause = WAKEUP_CAUSE_NONE;

        /* 进STOP前喂狗, 确保计数器从满载开始 */
        IWDT_UNLOCK();
        md_iwdt_clear_flag_interrupt();
        IWDT_LOCK();

        md_pmu_stop_enter(); /* PMU配置 + SLEEPDEEP + __WFI() */

        /* ─── 唤醒后 ─── */
        md_pmu_clear_flag_cwuf();
#ifdef UART_DEBUG
        usart_init(115200); /* 调试: 提前初始化串口看日志 */
        LOGI("[PWR] === WFI exit, cause=%d ===\r\n", g_wakeup_cause);
#endif

        /* 补偿 STOP 期间丢失的时间 */
        if (g_wakeup_cause == WAKEUP_CAUSE_IWDG)
        {
            rtc_timer_compensate_stop(POWER_MGR_IWDG_WAKEUP_SEC);
            rtc_save_checkpoint(); /* 立刻存盘, 防止下次进STOP前丢数据 */
        }
        else
        {
            /* 按键唤醒: 用 IWDT 计数器估算 */
            uint32_t iwdt_load = 32000UL * POWER_MGR_IWDG_WAKEUP_SEC;
            uint32_t iwdt_val = md_iwdt_get_count_value();
            uint32_t elapsed = (iwdt_load - iwdt_val) / 32000UL;
            if (elapsed > 0 && elapsed < POWER_MGR_IWDG_WAKEUP_SEC * 2)
                rtc_timer_compensate_stop(elapsed);
        }

        if (g_wakeup_cause == WAKEUP_CAUSE_KEY)
        {
            LOGI("[PWR] KEY wakeup -> exit_stop_full START\r\n");
            power_mgr_exit_stop_lite();
            power_mgr_exit_stop_full();
            LOGI("[PWR] exit_stop_full DONE, back to main\r\n");
            g_in_stop = 0;
        }
        else if (g_wakeup_cause == WAKEUP_CAUSE_IWDG)
        {
            LOGI("[PWR] wakeup: IWDG\r\n");
            /* IWDT 唤醒: 读 AFE -> 计算 -> 判断 */
            power_mgr_exit_stop_lite();
            ip3561q_proc();
            ip3561q_calc_data((ip3561q_data_t *)&ip3561q_raw,
                              (ip3561q_proc_data_t *)&ip3561q_info);
#ifdef DEBUG_STOP
            LOGI("[PWR] DEBUG: full restore\r\n");
            /* 调试模式: 任意唤醒都亮屏 */
            power_mgr_exit_stop_full();
            g_in_stop = 0;
#else
            if (g_bat_high_temp)
            {
                LOGI("[PWR] high temp! -> full restore\r\n");
                /* 高温: 全恢复 + 告警页 -> 退出 */
                power_mgr_exit_stop_full();
                ui_data.cur_page = PAGE_OVER_TEMP;
                ui_data.dev_state = DEV_STATE_NORMAL;
                g_in_stop = 0;
            }
            else
            {
                LOGI("[PWR] normal -> back to STOP (tick=%lu)\r\n", md_get_tick());
            }
            /* 无高温: do-while 循环回 STOP */
#endif
        }
        else
        {
            LOGI("[PWR] wakeup: UNKNOWN -> full restore\r\n");
            /* 未知唤醒源: 全恢复 (安全兜底) */
            power_mgr_exit_stop_lite();
            power_mgr_exit_stop_full();
            g_in_stop = 0;
        }
    } while (g_in_stop);
}

/* ========================================================================
 * power_mgr_proc — 主循环每 tick 调用，灭屏/唤醒状态机
 * ======================================================================== */
void power_mgr_proc(void)
{
    uint32_t now = md_get_tick();
    static uint32_t last_activity_ms = 0;
    static uint32_t sleep_entry_tick = 0;

    uint8_t usb_active = (ui_data.usb_c1_status != 0 || ui_data.usb_c2_status != 0 || ui_data.usb_a_status != 0);

    key_event_t key_ev = key_get_event();

    /* 刚从 STOP/SLEEP 唤醒 → 刷新时间戳, 防止秒进 SLEEP */
    if (s_just_woke_up)
    {
        s_just_woke_up = 0;
        last_activity_ms = now;
    }

    /* 有 USB 活动或按键事件 -> 刷新活动时间戳 */
    if (usb_active || key_ev != KEY_EVENT_NONE)
        last_activity_ms = now;

    /* ====================================================================
     * 状态机: 灭屏/唤醒转换
     * ==================================================================== */
    switch (ui_data.dev_state)
    {

    /* ---- NORMAL: 正常亮屏 ---- */
    case DEV_STATE_NORMAL:
        if (key_ev == KEY_EVENT_DOUBLE)
        {
            screen_off();
            ui_data.dev_state = DEV_STATE_SLEEP_ACTIVE;
            sleep_entry_tick = now;
            LOGI("[PWR] -> SLEEP_ACTIVE\r\n");
        }
        else if (now - last_activity_ms >= POWER_MGR_SLEEP_IDLE_MS)
        {
            screen_off();
            ui_data.dev_state = DEV_STATE_SLEEP_PASSIVE;
            sleep_entry_tick = now;
            LOGI("[PWR] -> SLEEP_PASSIVE\r\n");
        }
        break;

    /* ---- SLEEP_ACTIVE: 主动灭屏 (双击触发) ---- */
    case DEV_STATE_SLEEP_ACTIVE:
        if (key_ev == KEY_EVENT_CLICK)
        {
            wake_screen();
            last_activity_ms = now;
            LOGI("[PWR] -> NORMAL (click)\r\n");
        }
        else if (!usb_active)
        {
            ui_data.dev_state = DEV_STATE_SLEEP_PASSIVE;
            sleep_entry_tick = now;
            LOGI("[PWR] -> SLEEP_PASSIVE\r\n");
        }
        break;

    /* ---- SLEEP_PASSIVE: 被动灭屏 ---- */
    case DEV_STATE_SLEEP_PASSIVE:
        if (key_ev == KEY_EVENT_CLICK)
        {
            wake_screen();
            last_activity_ms = now;
            LOGI("[PWR] -> NORMAL (click)\r\n");
        }
        else if (usb_active)
        {
            wake_screen();
            last_activity_ms = now;
            LOGI("[PWR] -> NORMAL (USB)\r\n");
        }
#ifdef DEBUG_STOP
        else if (now - sleep_entry_tick >= 5000)
        {
            ui_data.dev_state = DEV_STATE_STOP;
            LOGI("[PWR] -> STOP\r\n");
        }
#else
        else if (i2c_is_host_sleeping())
        {
            ui_data.dev_state = DEV_STATE_STOP;
            LOGI("[PWR] host sleeping -> STOP\r\n");
        }
#endif
        break;

    /* ---- STOP: MCU 低功耗 ---- */
    case DEV_STATE_STOP:
        power_mgr_enter_stop();
        break;
    }
}
