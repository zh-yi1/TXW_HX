#ifndef __GLOBAL_DEFINE_H
#define __GLOBAL_DEFINE_H

#include "md_conf.h"
#include <string.h>
#include <stdio.h>

#include "main.h"
#include "dma.h"
#include "flash.h"
#include "lcd.h"
#include "power_mgr.h"
#include "ui.h"
#include "sw_i2c.h"
#include "ip3561q.h"

#include "sw_i2c_gen.h"
#include "key.h"
#include "i2c_slave.h"
#ifdef UPGRADE_EN
#include "uart_upgrade.h"
#endif
#include "usart.h"

/* 3C 新国标模块 */
#include "rtc_timer.h"
#include "battery_mgr.h"
#include "abnormal_log.h"

#include "ui.h"
#include "flash_image_addr.h"
#include "power_page.h"
#include "home_page.h"
#include "hint_page.h"
#include "information_page.h"
#include "digit_16.h"
#include "rtc_timer.h"
#include "prod_test.h"

/* ========================================================================== */
/*  Debug printf wrapper — 由 md_conf.h 的 DEBUG_EN 统一控制                   */
/* ========================================================================== */
#ifdef DEBUG_EN
#define LOGI(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#else
#define LOGI(fmt, ...)  ((void)0)
#endif
// #define LOGI(fmt, ...)  ((void)0)
#endif /* __GLOBAL_DEFINE_H */

