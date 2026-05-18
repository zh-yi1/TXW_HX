#ifndef __DEFAULT_PAGE_H__
#define __DEFAULT_PAGE_H__

#include "global_define.h"
#include "stdbool.h"

typedef struct
{
	uint8_t bat_power;
    bool is_charge;
    bool usb_c1_is_use;
    uint8_t usb_c1_power;
    bool usb_c2_is_use;
    uint8_t usb_c2_power;
    bool usb_a_is_use;
    uint8_t usb_a_power;
    uint16_t count_down;
} default_page_t;

extern default_page_t default_page;

void default_page_init(void);
void start_change_anima(bool is_charge);
void anima_erase_area(int x, int y, int w, int h);

#endif
