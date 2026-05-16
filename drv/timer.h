#ifndef __TIMER_H
#define __TIMER_H

#include "global_define.h"

#define CH2N_PORT   GPIOA
#define CH2N_PIN    MD_GPIO_PIN_4

void timer_init(void);
void ad16c4t_timer_pwm_set(uint8_t pwm_duty);


#endif 
