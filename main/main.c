#include "main.h"

static void sys_init(void);

int main()
{
	sys_init();
	spi_dma_send_ok = 1;

	while (1)
	{
	#ifdef UPGRADE_EN
		/* 升级模式: 按键组合触发后直接跳转 Bootloader */
		if (g_enter_upgrade)
		{
			g_enter_upgrade = 0;
			uart_upgrade_enter();
		}
	#endif

		/* ---- 产测协议处理 (USART1) ---- */
#ifndef DEBUG_EN
		// prod_test_proc();
#endif /* !DEBUG_EN */

		ip3561q_proc();
		rtc_timer_proc();
		i2c_slave_proc();          /* 主机数据 → ui_data (先于 battery_mgr) */
		battery_mgr_proc();        /* OV/UV + NTC 温度换算 */
		battery_mgr_sync_to_ui();  /* 同步结果 → ui_data */

		key_wake_host();           /* 主机休眠+高温 → KEY_PIN 拉低唤醒 */
		key_proc();
		ui_proc();
	}
}

static void sys_init(void)
{
	/* Configure system clock */
	md_cmu_clock_config(MD_CMU_CLOCK_HRC, 52000000);

	/* Initialize SysTick Interrupt */
	md_init_1ms_tick();

	/* Enable ALL peripheral */
	SYSCFG_UNLOCK();
	md_cmu_enable_perh_all();
	SYSCFG_LOCK();

	//DMA初始化
	dma_init();

	//TFT初始化
	ui_init();

	//按键初始化
	key_init();

	//I2C从机初始化
	i2c_slave_init();

	//IP3561Q初始化
	ip3561q_init();

	//TODO : 测试用，临时写入场测需要的数据
	// static_cfg_erasure();
	// static_cfg_save_test();

	//3C 新国标模块初始化
	rtc_timer_init();
	abnormal_log_init();
	battery_mgr_init();

	//USART1初始化 (测试回环)
	// usart_init(115200);

	//定时器初始化-PWM
	// timer_init();

	//产测模块初始化
#ifndef DEBUG_EN
	// prod_test_init();
#endif /* !DEBUG_EN */

	LOGI("Hello World!\n");
}

void SystemInit(void){}



