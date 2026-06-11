/**********************************************************************************
 *
 * @file    usart.c
 * @brief   USART1 driver — interrupt-based receive, blocking send
 *
 * @note    Ported from ES32_SDK USART Example (01_send_recv_it).
 *          Ring buffer for RX (ISR-driven), polling for TX.
 *          Pins: PB0=RX (AF7), PB1=TX (AF7).
 *
 **********************************************************************************
 */

#include "usart.h"

/* ---- Ring buffer (written by ISR, read by application) ---- */
volatile uint8_t  usart_rx_buf[USART_RX_BUF_SIZE];
volatile uint16_t usart_rx_head = 0;
volatile uint16_t usart_rx_tail = 0;

/* ---- Private ---- */
static md_usart_init_t usart_cfg;

/* ========================================================================== */
/*  Static helpers                                                           */
/* ========================================================================== */

/**
  * @brief  Configure USART1 GPIO pins (PB0=RX, PB1=TX, AF7).
  */
static void usart_pin_init(void)
{
    md_gpio_init_t gpio;

    /* TX — PB1, push-pull output, AF7 */
    md_gpio_init_struct(&gpio);
    gpio.mode = MD_GPIO_MODE_OUTPUT;
    gpio.odos = MD_GPIO_PUSH_PULL;
    gpio.pupd = MD_GPIO_PUSH_UP;
    gpio.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
    gpio.flt  = MD_GPIO_FILTER_DISABLE;
    gpio.type = MD_GPIO_TYPE_CMOS;
    gpio.func = USART1_GPIO_FUNC;
    md_gpio_init(USART1_TX_PORT, USART1_TX_PIN, &gpio);

    /* RX — PB0, input, AF7 */
    gpio.mode = MD_GPIO_MODE_INPUT;
    gpio.odos = MD_GPIO_PUSH_PULL;
    gpio.pupd = MD_GPIO_PUSH_UP;
    gpio.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
    gpio.flt  = MD_GPIO_FILTER_DISABLE;
    gpio.type = MD_GPIO_TYPE_CMOS;
    gpio.func = USART1_GPIO_FUNC;
    md_gpio_init(USART1_RX_PORT, USART1_RX_PIN, &gpio);
}

/* ========================================================================== */
/*  Public API                                                               */
/* ========================================================================== */

/**
  * @brief  Initialize USART1: pins, baud rate (default 115200), 8N1, RXNE interrupt.
  * @param  baud: baud rate (e.g. 115200, 9600)
  */
void usart_init(uint32_t baud)
{
    /* ---- GPIO ---- */
    usart_pin_init();

    /* ---- USART peripheral config ---- */
    md_usart_init_struct(&usart_cfg);
    usart_cfg.baud        = baud;
    usart_cfg.word_length = MD_USART_WORD_LENGTH_8B;
    usart_cfg.stop_bits   = MD_USART_STOP_BITS_1;
    usart_cfg.parity      = MD_USART_PARITY_NONE;
    usart_cfg.fctl        = MD_USART_HW_FLOW_CTL_NONE;
    usart_cfg.mode        = MD_USART_MODE_TX_RX;

    md_usart_init(USART1, &usart_cfg);

    /* ---- Enable RXNE interrupt ---- */
    md_usart_enable_it_rxne(USART1);

    /* ---- NVIC: USART1 IRQ, priority 1 ---- */
    md_mcu_irq_config(USART1_IRQn, 0, ENABLE);
}

/**
  * @brief  Send one byte (blocking, poll TX empty flag).
  */
void usart_send_byte(uint8_t data)
{
    while (!md_usart_is_active_flag_txemp(USART1));
    md_usart_send_data8(USART1, data);
}

/**
  * @brief  Send a buffer (blocking).
  * @param  data: pointer to buffer
  * @param  len: number of bytes
  */
void usart_send_bytes(const uint8_t *data, uint16_t len)
{
    uint16_t i;
    for (i = 0; i < len; i++)
    {
        usart_send_byte(data[i]);
    }
}

/**
  * @brief  Send a null-terminated string (blocking).
  */
void usart_send_string(const char *str)
{
    while (*str)
    {
        usart_send_byte((uint8_t)*str);
        str++;
    }
}

/**
  * @brief  Read one byte from the ring buffer.
  * @retval Byte, or 0 if buffer is empty.
  */
uint8_t usart_recv_byte(void)
{
    uint8_t data = 0;

    if (usart_rx_tail != usart_rx_head)
    {
        data = usart_rx_buf[usart_rx_tail];
        usart_rx_tail = (usart_rx_tail + 1) % USART_RX_BUF_SIZE;
    }

    return data;
}

/**
  * @brief  Get number of bytes available in the ring buffer.
  */
uint16_t usart_recv_available(void)
{
    return (usart_rx_head - usart_rx_tail + USART_RX_BUF_SIZE) % USART_RX_BUF_SIZE;
}
