#include "timer.h"

static void adt_gpio_init(void);
static void ad16c4t_timer_init(void);

void timer_init(void)
{
	//AD16C4T初始化 使能PWM
	adt_gpio_init();
	ad16c4t_timer_init();
}

static void adt_gpio_init(void)
{
	md_gpio_init_t gpio_init;
	
	md_gpio_init_struct(&gpio_init);
    gpio_init.mode = MD_GPIO_MODE_OUTPUT;
    gpio_init.odos = MD_GPIO_PUSH_PULL;
    gpio_init.pupd = MD_GPIO_FLOATING;
    gpio_init.func = MD_GPIO_FUNC_6;
	
    md_gpio_init(CH2N_PORT, CH2N_PIN, &gpio_init);
}

static void ad16c4t_timer_init(void)
{
    md_timer_base_init_t ad16c4t_init;
    md_timer_oc_init_t oc_init;

    md_timer_base_struct_init(&ad16c4t_init);			/* initialize the ad16c4t_init  */
    ad16c4t_init.prescaler = 24 - 1;					/* clk_count: 1MHz */
    ad16c4t_init.clk_div = MD_TIMER_CLOCK_DIV1;			/* working clock of dead time and filter */
    ad16c4t_init.mode = MD_TIMER_CNT_MODE_CENTER1;		/* count mode is center1 */
    ad16c4t_init.period = 100;							/* period is 10000 count clock */
    ad16c4t_init.re_cnt = 1 - 1;						/* 0 repeat count */
    md_timer_base_set_config(AD16C4T, &ad16c4t_init);

    /* initialize the oc_init  */
    md_timer_oc_struct_init(&oc_init);
    oc_init.ocstate = MD_TIMER_OCSTATE_ENABLE;			/* enable CHxO compare output */
    oc_init.ocnstate = MD_TIMER_OCSTATE_ENABLE;			/* enable CHxON compare output */
    oc_init.oc_mode = MD_TIMER_OC_MODE_PWM2;			/* compare output mode is PWM2 */
    oc_init.oc_polarity = MD_TIMER_OC_POLARITY_HIGH;	/* CHxO compare output polarity is high */
    oc_init.ocn_polarity = MD_TIMER_OCN_POLARITY_HIGH;	/* CHxON compare output polarity is high */
    oc_init.oc_idle = MD_TIMER_OC_IDLE_RESET;			/* CHxO idle is low */
    oc_init.ocn_idle = MD_TIMER_OCN_IDLE_RESET;			/* CHxON idle is low */
    oc_init.pulse = 0;									/* CH2 compare value is 3000 - 1 */
    md_timer_oc_init(AD16C4T, MD_TIMER_CHANNEL_2, &oc_init);

	md_timer_enable_cc2it_interrupt(AD16C4T);			/* enable CC2 interrupt request */
    md_timer_enable_uit_interrupt(AD16C4T);				/* update interrupt request */

    md_mcu_irq_config(ADTIM0_CC_IRQn, 0, ENABLE);		/* enable NVIC AD16C4T capture and compare interrupt */
    md_mcu_irq_config(ADTIM0_BRK_UP_TRIGCOM_IRQn, 0, ENABLE);	/* enable NVIC AD16C4T updata interrupt */

    /* enable AD16C4T1 */
    md_timer_enable_counter_cnten(AD16C4T);
    md_timer_set_main_output_enable(AD16C4T, 1);		/* enable output */
}

void ad16c4t_timer_pwm_set(uint8_t pwm_duty)
{
	if(pwm_duty >= 100)
		pwm_duty = 100;
	
	md_timer_set_capture_compare2_value_ccrv2(AD16C4T, pwm_duty);

}

