#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "global_define.h"


 typedef struct
{
	uint8_t	timer_1ms;
	uint8_t	timer_10ms;
	uint8_t	timer_100ms;
	uint8_t	timer_1s;

	uint8_t count_10ms;
	uint8_t count_100ms;
	uint8_t count_1s;

}FUNC_VAR_WORK_TICK;

extern FUNC_VAR_WORK_TICK work_time;


#endif /*__MAIN_H__*/

