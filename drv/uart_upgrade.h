/**********************************************************************************
 *
 * @file    uart_upgrade.h
 * @brief   Bootloader jump module — key combo triggers direct bootloader entry
 *
 * @note    key_combo_cb sets g_enter_upgrade flag;
 *          main() loop detects it and jumps to bootloader.
 *
 **********************************************************************************
 */

#ifndef __UART_UPGRADE_H
#define __UART_UPGRADE_H

#include "global_define.h"

#define APP_ADDR    0x1400
#define BOOT_ADDR   0x0000
#define CRC_CAL_PAGE_ADDR   0x7E00
#define GO_APP      0xFFFFFFFE
#define GO_BOOT     0xFFFFFFFD


/* Exported variables */
extern volatile uint8_t  g_enter_upgrade;

/* Exported functions */
void uart_upgrade_enter(void);

#endif /* __UART_UPGRADE_H__ */
