#include "main.h"

FUNC_VAR_WORK_TICK work_time;
static void sys_init(void);

uint16_t color_test = 0;

volatile cw1573_test_result_t g_test;

static void io_test(void)
{
	md_gpio_init_t gpio_init;
	md_gpio_init_struct(&gpio_init);

	md_gpio_init(GPIOA, MD_GPIO_PIN_5, &gpio_init);
	md_gpio_init(GPIOA, MD_GPIO_PIN_14, &gpio_init);

	md_gpio_set_pin_low(GPIOA, MD_GPIO_PIN_5);
	md_gpio_set_pin_low(GPIOA, MD_GPIO_PIN_14);

	md_gpio_set_pin_high(GPIOA, MD_GPIO_PIN_5);
	md_gpio_set_pin_high(GPIOA, MD_GPIO_PIN_14);
}

/* Breakpoint-friendly test: set BP on each "step = N" line */
static void cw1573_test(void)
{
	volatile int32_t  step  = 0;
	volatile int32_t  err   = 0;
	volatile uint8_t  ack;
	volatile uint8_t  reg8;
	volatile uint8_t  test_val, rb;
	volatile cw1573_data_t data;

	/* Step 1: software I2C init */
	sw_i2c_init();
	step = 1;

	/* Step 2: ping slave address */
	ack = sw_i2c_ping((uint8_t)(CW1573_SLAVE_ADDR << 1));
	g_test.comm_ok = (ack == 0) ? 1 : 0;
	step = 2;
	if (!g_test.comm_ok) return;

	/* Step 3: read STATE_FLAG2 with CRC */
	err = cw1573_read_reg(CW1573_REG_STATE_FLAG2, (uint8_t *)&reg8, 1);
	g_test.comm_ok = (err == 0) ? 1 : 0;
	g_test.rst_flag  = (reg8 & CW1573_RST_FLAG)  ? 1 : 0;
	g_test.do_pin    = (reg8 & CW1573_DO_PIN)    ? 1 : 0;
	g_test.co_pin    = (reg8 & CW1573_CO_PIN)    ? 1 : 0;
	g_test.dsg_state = (reg8 & CW1573_DSG_STATE) ? 1 : 0;
	g_test.chg_state = (reg8 & CW1573_CHG_STATE) ? 1 : 0;
	step = 3;
	if (err) return;

	/* Step 4: write BAL_SET=0xA5, readback, verify, restore */
	err = cw1573_read_reg(CW1573_REG_BAL_SET, (uint8_t *)&reg8, 1);
	if (err) return;
	test_val = 0xA5;
	err = cw1573_write_reg(CW1573_REG_BAL_SET, (uint8_t *)&test_val, 1);
	if (err) return;
	err = cw1573_read_reg(CW1573_REG_BAL_SET, (uint8_t *)&rb, 1);
	if (err) return;
	cw1573_write_reg(CW1573_REG_BAL_SET, (uint8_t *)&reg8, 1);
	g_test.write_read_ok = (rb == test_val) ? 1 : 0;
	step = 4;
	if (!g_test.write_read_ok) return;

	/* Step 5: read all data */
	err = cw1573_read_all((cw1573_data_t *)&data);
	if (err) return;
	g_test.read_all_ok = 1;
	g_test.vcell[0] = data.vcell[0];
	g_test.vcell[1] = data.vcell[1];
	g_test.vcell[2] = data.vcell[2];
	g_test.vcell[3] = data.vcell[3];
	g_test.ts_adc = data.ts_adc;
	g_test.iadc   = data.iadc;
	g_test.cc     = data.cc;
	step = 5;
}

int main()
{
 	for(uint32_t i=60000; i<1; i--){}

	sys_init();
	spi_dma_send_ok = 1;
	cw1573_init(4);

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

	//DMA初始化
	dma_init();

	//TFT初始化
	//ui_init();

	//定时器初始化-PWM
//	timer_init();
}

void SystemInit(void){}



