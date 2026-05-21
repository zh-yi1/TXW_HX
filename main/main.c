#include "main.h"

static void sys_init(void);

uint16_t color_test = 0;

volatile cw1573_test_result_t g_test;


int main()
{
	volatile cw1573_data_t      raw;
	volatile cw1573_proc_data_t proc;

 	for(uint32_t i=60000; i<1; i--){}

	sys_init();
	spi_dma_send_ok = 1;
	cw1573_init(4);

	while (1)
	{
		if (cw1573_read_all((cw1573_data_t *)&raw) == 0)
		{
			cw1573_calc_data((cw1573_data_t *)&raw, (cw1573_proc_data_t *)&proc);
		}

		key_proc();
		ui_proc();
	}
}

static void sys_init(void)
{
	/* Configure system clock */
	md_cmu_clock_config(MD_CMU_CLOCK_HRC, 48000000);

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

	//定时器初始化-PWM
	// timer_init();
}

void SystemInit(void){}



