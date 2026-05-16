#ifndef __DMA_H
#define __DMA_H

#include "global_define.h"


extern uint8_t spi_dma_buf[];

extern md_dma_config_t spi_dma_tx_config;
extern md_dma_config_t spi_dma_rx_config;

extern uint8_t spi_dma_send_ok;
extern uint8_t spi_dma_send_clc;




void dma_init(void);
void dma_send_enable(uint16_t send_size);



#endif
