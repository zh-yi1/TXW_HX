#include "dma.h"

md_dma_descriptor_t g_dma0_ctrl_base[2] __attribute__((aligned(512)));
md_dma_config_t spi_dma_tx_config, spi_dma_rx_config;

uint8_t spi_dma_buf[FLASH_READ_BUF_SIZE] = {0};
uint16_t spi_dma_buf_len = sizeof(spi_dma_buf);

uint8_t spi_dma_send_ok;
uint8_t spi_dma_send_clc;

static void config_dma_struct_tx(void);
static void config_dma_struct_rx(void);

void dma_init(void)
{
    NVIC_SetPriority(DMA_IRQn, 0);
    NVIC_EnableIRQ(DMA_IRQn);

    memset(g_dma0_ctrl_base, 0x0, sizeof(g_dma0_ctrl_base));
    md_dma_set_ctrlbase((uint32_t)&g_dma0_ctrl_base);
    md_dma_enable();

    config_dma_struct_tx();
    config_dma_struct_rx();

    md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &spi_dma_tx_config);
    md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &spi_dma_rx_config);

    md_dma_enable_channel(MD_DMA_CH_1);
    md_dma_enable_channel(MD_DMA_CH_0);

    md_spi_disable_tx_dma(SPI0);
    md_spi_disable_rx_dma(SPI0);
}

void dma_send_enable(uint16_t send_size)
{
    LCD_RS_HIGH();
    LCD_CS_LOW();

    if (send_size > 0 && send_size <= spi_dma_buf_len)
        spi_dma_tx_config.size = send_size;
    else
        spi_dma_tx_config.size = spi_dma_buf_len;

    md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &spi_dma_tx_config);
    md_dma_enable_channel(MD_DMA_CH_0);
    md_spi_enable_tx_dma(SPI0);
}

void buf_swap_bytes(uint16_t size)
{
    uint16_t i;
    uint8_t tmp;

    for (i = 0; i < size; i += 2)
    {
        tmp = spi_dma_buf[i];
        spi_dma_buf[i] = spi_dma_buf[i + 1];
        spi_dma_buf[i + 1] = tmp;
    }
}

static void config_dma_struct_tx(void)
{
    memset(&spi_dma_tx_config, 0x0, sizeof(spi_dma_tx_config));

    md_dma_config_struct(&spi_dma_tx_config);
    spi_dma_tx_config.data_width = MD_DMA_DATA_SIZE_BYTE;
    spi_dma_tx_config.src_inc    = MD_DMA_DATA_INC_BYTE;
    spi_dma_tx_config.dst_inc    = MD_DMA_DATA_INC_NONE;
    spi_dma_tx_config.R_power    = MD_DMA_R_POWER_1;
    spi_dma_tx_config.primary    = ENABLE;
    spi_dma_tx_config.burst      = DISABLE;
    spi_dma_tx_config.high_prio  = DISABLE;
    spi_dma_tx_config.interrupt  = ENABLE;
    spi_dma_tx_config.channel    = 0;
    spi_dma_tx_config.src        = (void *)(spi_dma_buf);
    spi_dma_tx_config.dst        = (void *)(&SPI0->DATA);
    spi_dma_tx_config.size       = spi_dma_buf_len;
    spi_dma_tx_config.msel       = MD_DMA_MSEL_SPI0;
    spi_dma_tx_config.msigsel    = MD_DMA_MSIGSEL_SPI_TXEMPTY;
}

static void config_dma_struct_rx(void)
{
    memset(&spi_dma_rx_config, 0x0, sizeof(spi_dma_rx_config));

    md_dma_config_struct(&spi_dma_rx_config);
    spi_dma_rx_config.data_width = MD_DMA_DATA_SIZE_BYTE;
    spi_dma_rx_config.src_inc    = MD_DMA_DATA_INC_NONE;
    spi_dma_rx_config.dst_inc    = MD_DMA_DATA_INC_BYTE;
    spi_dma_rx_config.R_power    = MD_DMA_R_POWER_1;
    spi_dma_rx_config.primary    = ENABLE;
    spi_dma_rx_config.burst      = DISABLE;
    spi_dma_rx_config.high_prio  = DISABLE;
    spi_dma_rx_config.interrupt  = ENABLE;
    spi_dma_rx_config.channel    = 1;
    spi_dma_rx_config.src        = (void *)(&SPI0->DATA);
    spi_dma_rx_config.dst        = (void *)(spi_dma_buf);
    spi_dma_rx_config.size       = spi_dma_buf_len;
    spi_dma_rx_config.msel       = MD_DMA_MSEL_SPI0;
    spi_dma_rx_config.msigsel    = MD_DMA_MSIGSEL_SPI_RNR;
}
