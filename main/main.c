#include "main.h"

static void sys_init(void);

uint16_t color_test = 0;

volatile cw1573_test_result_t g_test;


int main()
{

 	for(uint32_t i=60000; i<1; i--){}

	sys_init();
	spi_dma_send_ok = 1;
	cw1573_init(4);
	// g020_init();
	// default_page_test();
	while (1)
	{
		cw1573_proc();
		key_proc();
		// g020_proc(ui_data.bat_power, (ui_data.bat_power <= 5) ? 1 : 0);
		ui_proc();
		default_page_updata();
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



