#ifndef __DMA_H
#define __DMA_H

#include "global_define.h"

typedef enum
{
	DMA_CHAIN_IDLE,
	DMA_CHAIN_FLASH_READ,
	DMA_CHAIN_LCD_PUSH,
} dma_chain_state_t;

extern uint8_t spi_dma_buf[];

extern md_dma_config_t spi_dma_tx_config;
extern md_dma_config_t spi_dma_rx_config;

extern uint8_t spi_dma_send_ok;
extern uint8_t spi_dma_send_clc;

extern dma_chain_state_t dma_chain_state;
extern uint8_t  dma_chain_done;

void dma_init(void);
void dma_send_enable(uint16_t send_size);
void flash_read_dma_start(uint32_t addr, unsigned char *buf, uint16_t size);
void dma_chain_bmp_start(uint32_t addr, int w, int rows, int row_size, uint8_t top_down);
void dma_chain_proc(void);
void buf_swap_bytes(uint16_t size);

#endif
