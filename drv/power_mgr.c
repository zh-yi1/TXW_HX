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
static void power_mgr_arm_scl_wakeup(void);
static void power_mgr_disarm_scl_wakeup(void);

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
 * power_mgr_arm_scl_wakeup — 进 STOP 前: PA5(I2C1 SCL) 切为输入上拉 +
 *                             下降沿 EXTI, 主机拉低 SCL 即可唤醒 MCU
 * ======================================================================== */
static void power_mgr_arm_scl_wakeup(void)
{
    md_gpio_set_pin_mode_input(GPIOA, MD_GPIO_PIN_5);
    md_gpio_set_pin_push_up(GPIOA, MD_GPIO_PIN_5);
    md_gpio_set_interrupt_port(GPIOA, MD_GPIO_PIN_5);
    md_gpio_enable_trailing_edge_trigger(MD_GPIO_PIN_5);
    md_gpio_enable_external_interrupt(MD_GPIO_PIN_5);
    md_gpio_interrupt_filter_enable(MD_GPIO_PIN_5);
    md_mcu_irq_config(EXTI4_7_IRQn, 0, ENABLE);
}

/* ========================================================================
 * power_mgr_disarm_scl_wakeup — 唤醒后: 关闭 PA5 EXTI, 清标志
 *   避免恢复 I2C 后 SCL 时钟边沿触发中断; i2c_slave_init() 会把 PA5
 *   重新切回 FUNC_2 复用功能。
 * ======================================================================== */
static void power_mgr_disarm_scl_wakeup(void)
{
    md_gpio_disable_external_interrupt(MD_GPIO_PIN_5);
    md_gpio_clear_flag(MD_GPIO_PIN_5);
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
    md_gpio_init_t gi;

    /* ====================================================================
     * 模拟输入 + 无上下拉 = 真正高阻态
     *   适用: SPI 总线、未用脚、外部已有上拉的 I2C 脚
     * ==================================================================== */
    md_gpio_init_struct(&gi);
    gi.mode = MD_GPIO_MODE_CLOSE;
    gi.pupd = MD_GPIO_FLOATING;  /* 无内部上拉/下拉 */

    /* SPI 总线: PA10(SCLK)/PA11(MOSI)/PA12(MISO) */
    md_gpio_init(SPI_CLK,  SPI_CLK_PIN,  &gi);
    md_gpio_init(SPI_MOSI, SPI_MOSI_PIN, &gi);
    md_gpio_init(SPI_MISO, SPI_MISO_PIN, &gi);

    /* PA6(I2C1 SDA) — 外部 4.7k 上拉 */
    md_gpio_init(GPIOA, MD_GPIO_PIN_6, &gi);

    /* PB5(I2C SCL) — 软I2C主机, 外部上拉 */
    md_gpio_init(GPIOB, MD_GPIO_PIN_5, &gi);

    /* PA14(I2C SDA) — 软I2C数据脚, 外部上拉 */
    md_gpio_init(GPIOA, MD_GPIO_PIN_14, &gi);

    /* PA5(I2C1 SCL) — 输入上拉 + 下降沿 EXTI 唤醒 */
    power_mgr_arm_scl_wakeup();

    /* ====================================================================
     * 推挽输出低
     * ==================================================================== */
    md_gpio_init_struct(&gi);
    gi.mode = MD_GPIO_MODE_OUTPUT;
    gi.pupd = 0;

    /* PB0/PB1 — 悬空脚, 输出低防穿通电流 */
    md_gpio_init(GPIOB, MD_GPIO_PIN_0, &gi);
    md_gpio_set_pin_low(GPIOB, MD_GPIO_PIN_0);
    md_gpio_init(GPIOB, MD_GPIO_PIN_1, &gi);
    md_gpio_set_pin_low(GPIOB, MD_GPIO_PIN_1);

    /* PA4(TFT_EN) — SCT2401 EN=低, 关断升压 */
    md_gpio_init(TFT_EN, TFT_EN_PIN, &gi);
    md_gpio_set_pin_low(TFT_EN, TFT_EN_PIN);

    /* ====================================================================
     * 推挽输出高
     * ==================================================================== */

    /* PA1(LCD_RS/DC) — 高, 配合 CS 高确保屏幕接口静止 */
    md_gpio_init(LCD_RS, LCD_RS_PIN, &gi);
    md_gpio_set_pin_high(LCD_RS, LCD_RS_PIN);

    /* PA0(LCD_RST) — 高, 屏幕非复位态省内部上拉电流 */
    md_gpio_init(LCD_RST, LCD_RST_PIN, &gi);
    md_gpio_set_pin_high(LCD_RST, LCD_RST_PIN);

    /* PB6(LCD_BLK) — 高, P-MOS 关断背光灭 */
    md_gpio_init(LCD_BLK, LCD_BLK_PIN, &gi);
    md_gpio_set_pin_high(LCD_BLK, LCD_BLK_PIN);

    /* PA3(LCD_CS) — 高, 屏幕 SPI 取消选中 */
    md_gpio_init(LCD_CS, LCD_CS_PIN, &gi);
    md_gpio_set_pin_high(LCD_CS, LCD_CS_PIN);

    /* PB3(FLASH_CS) — 高, Flash 进入待机模式 */
    md_gpio_init(FLASH_CS, FLASH_CS_PIN, &gi);
    md_gpio_set_pin_high(FLASH_CS, FLASH_CS_PIN);

    /* PA15(KEY) — 保持输入上拉, 唤醒引脚, 不动 */
}

/* ========================================================================
 * power_mgr_exit_stop_lite — IWDT 唤醒后的轻量恢复 (仅 I2C + AFE)
 * 不亮屏、不恢复 LCD/SPI/背光/PWM
 * ======================================================================== */
static void power_mgr_exit_stop_lite(void)
{
    power_mgr_disarm_scl_wakeup(); /* 关 PA5 EXTI, 避免恢复 I2C 后误触发 */
    i2c_slave_init();              /* I2C1 从机: 读取主机数据 */
}

/* ========================================================================
 * power_mgr_exit_stop_full — 全恢复 (按键唤醒 或 IWDT 高温告警)
 * ======================================================================== */
static void power_mgr_exit_stop_full(void)
{
    s_just_woke_up = 1;
    ip3561q_init();   /* AFE: 读取电池数据 (亮屏/UI 显示需要) */
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

        // 强制记录时间
        rtc_save_checkpoint();

        /* 进STOP前喂狗, 确保计数器从满载开始.
           注意: md_iwdt_clear_flag_interrupt() 只清中断标志, 不重载下计数器;
           计数器是自由包裹的, 进STOP时停在任意相位, 会导致STOP后第一次
           IWDG唤醒提前到来(实测7~16s)却被按20s补偿, 时间累积偏快.
           这里重写LOAD触发计数器重装到满刻度, 保证第一次唤醒=20s. */
        IWDT_UNLOCK();
        md_iwdt_set_count_overload(32000UL * POWER_MGR_IWDG_WAKEUP_SEC);
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
        rtc_timer_proc();

        if (g_wakeup_cause == WAKEUP_CAUSE_KEY)
        {
            LOGI("[PWR] KEY wakeup -> exit_stop_full START\r\n");
            power_mgr_exit_stop_lite();
            power_mgr_exit_stop_full();
            LOGI("[PWR] exit_stop_full DONE, back to main\r\n");
            g_in_stop = 0;
        }
        else if (g_wakeup_cause == WAKEUP_CAUSE_I2C_SCL)
        {
            LOGI("[PWR] I2C SCL wakeup -> exit_stop_full START\r\n");
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
            ip3561q_init();   /* AFE: 采样温度需要 (lite 不再初始化) */
            for (int i = 0; i < 5; i++)
            {
                ip3561q_proc();
                ip3561q_calc_data((ip3561q_data_t *)&ip3561q_raw,
                                  (ip3561q_proc_data_t *)&ip3561q_info);
                LOGI("[PWR] rntc1 = %d rntc2 = %d\r\n",
                     ip3561q_info.rntc1_ohm, ip3561q_info.rntc2_ohm);
                md_delay_1ms(100);
            }
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
                ui_data.cur_page = PAGE_DEFAULT;
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
        if (prod_test_is_sleep_blocked())
            break; /* 场测模式 3min 内不灭屏 */
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
        if (prod_test_is_sleep_blocked())
        {
            wake_screen();
            last_activity_ms = now;
            LOGI("[PWR] -> NORMAL (test mode)\r\n");
            break;
        }
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
        if (prod_test_is_sleep_blocked())
        {
            wake_screen();
            last_activity_ms = now;
            LOGI("[PWR] -> NORMAL (test mode)\r\n");
            break;
        }
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
