/**********************************************************************************
 *
 * @file    usart.h
 * @brief   USART1 driver — interrupt-based send/receive with ring buffer
 *
 * @note    USART1: PB0=RX, PB1=TX, 115200-8-N-1
 *          Uses RXNE interrupt for reception, blocking for transmission.
 *
 **********************************************************************************
 */

#ifndef __USART_H
#define __USART_H

#include "global_define.h"

/* ---- Pin definitions ---- */
#define USART1_TX_PORT      GPIOB
#define USART1_TX_PIN       MD_GPIO_PIN_1
#define USART1_RX_PORT      GPIOB
#define USART1_RX_PIN       MD_GPIO_PIN_0
#define USART1_GPIO_FUNC    MD_GPIO_FUNC_7

/* ---- Ring buffer ---- */
#define USART_RX_BUF_SIZE   256

/* ---- Exported variables ---- */
extern volatile uint8_t  usart_rx_buf[USART_RX_BUF_SIZE];
extern volatile uint16_t usart_rx_head;   /* ISR writes here */
extern volatile uint16_t usart_rx_tail;   /* app reads from here */

/* ---- Public API ---- */
void usart_init(uint32_t baud);
void usart_send_byte(uint8_t data);
void usart_send_bytes(const uint8_t *data, uint16_t len);
void usart_send_string(const char *str);
uint8_t  usart_recv_byte(void);
uint16_t usart_recv_available(void);

#endif /* __USART_H__ */
