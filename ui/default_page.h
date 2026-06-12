#ifndef __DEFAULT_PAGE_H__
#define __DEFAULT_PAGE_H__

#include "global_define.h"
#include "ui.h"
#include "stdbool.h"

typedef enum
{
	TYPE_C1_IMG = 0,
	C1_IMG,
	TYPE_C2_IMG = 1,
	C2_IMG,
	USB_A_IMG = 2,
	A_IMG,
} default_img_e;

typedef enum
{
	C1_POWER,
	C2_POWER,
	A_POWER,
} power_e;


void default_page_init(void);
void start_change_anima(bool is_charge);
void anima_erase_area(int x, int y, int w, int h);
void default_page_show_power(power_e port, uint8_t power_value, uint8_t status);
void default_page_updata(void);

#endif
