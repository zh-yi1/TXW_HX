#ifndef __GLOBAL_DEFINE_H
#define __GLOBAL_DEFINE_H

#include "md_conf.h"
#include <string.h>
#include <stdio.h>

#include "main.h"
#include "dma.h"
#include "flash.h"
#include "lcd.h"
#include "ui.h"
#include "sw_i2c.h"
#include "cw1573.h"

#include "sw_i2c_gen.h"
#include "timer.h"
#include "key.h"
#include "i2c_slave.h"
#include "uart_upgrade.h"
#include "usart.h"

#include "ui.h"
#include "bar_progress.h"
#include "flash_image_addr.h"
#include "default_page.h"
#include "hint_page.h"
#include "information_page.h"
#include "digit_16.h"
#include "prod_test.h"

/* ========================================================================== */
/*  Debug printf wrapper — 由 md_conf.h 的 DEBUG_EN 统一控制                   */
/* ========================================================================== */
#ifdef DEBUG_EN
#define LOGI(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#else
#define LOGI(fmt, ...)  ((void)0)
#endif

#endif /* __GLOBAL_DEFINE_H */

