#include "main.h"

FUNC_VAR_WORK_TICK work_time;
static void sys_init(void);

uint16_t color_test = 0;

int main()
{
 	for(uint32_t i=60000; i<1; i--){}

	sys_init();
	spi_dma_send_ok = 1;

	while (1)
	{
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

	//从机IIC初始化
//	iic_init();

	//DMA初始化
	dma_init();

	//TFT初始化
	ui_init();

	//定时器初始化-PWM
//	timer_init();
}

void SystemInit(void){}



