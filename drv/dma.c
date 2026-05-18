#include "dma.h"

md_dma_descriptor_t g_dma0_ctrl_base[2] __attribute__((aligned(512)));
md_dma_config_t spi_dma_tx_config, spi_dma_rx_config;

uint8_t spi_dma_buf[FLASH_READ_BUF_SIZE] = {0};
uint16_t spi_dma_buf_len = sizeof(spi_dma_buf);

uint8_t spi_dma_send_ok;
uint8_t spi_dma_send_clc;

dma_chain_state_t dma_chain_state;
uint8_t  dma_chain_done;

/* BMP 逐行链状态 */
static int      bmp_width, bmp_rows, bmp_row_size;
static int      bmp_row;
static uint32_t bmp_addr;
static uint8_t  bmp_top_down;		/* 1 = 需恢复 MADCTL 至 0xA0 */

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

void flash_read_dma_start(uint32_t addr, unsigned char *buf, uint16_t size)
{
    uint16_t cnt, temp;
    uint8_t cmd_buf[4];
    uint8_t i;

    cmd_buf[0] = 0x03;
    cmd_buf[1] = (addr >> 16) & 0xff;
    cmd_buf[2] = (addr >> 8) & 0xff;
    cmd_buf[3] = addr & 0xff;

    FLASH_CS_CLR();
    LCD_CS_HIGH();

    for (i = 0; i < sizeof(cmd_buf); i++)
    {
        cnt = 500;
        md_spi_set_data_reg(SPI0, cmd_buf[i]);
        while ((md_spi_is_active_flag_txbe(SPI0) == 0) && (--cnt));

        cnt = 500;
        while ((!((md_spi_is_active_flag_rxbne(SPI0)))) && (--cnt));
        temp = md_spi_get_data_reg_value(SPI0);
        UNUSED(temp);
    }

    memset(spi_dma_buf, 0xFF, size);

    spi_dma_tx_config.interrupt = ENABLE;
    spi_dma_tx_config.src       = (void *)spi_dma_buf;
    spi_dma_tx_config.size      = size;

    spi_dma_rx_config.interrupt = ENABLE;
    spi_dma_rx_config.dst       = (void *)buf;
    spi_dma_rx_config.size      = size;

    md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &spi_dma_tx_config);
    md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &spi_dma_rx_config);

    md_dma_enable_channel(MD_DMA_CH_1);
    md_dma_enable_channel(MD_DMA_CH_0);

    md_spi_enable_tx_dma(SPI0);
    md_spi_enable_rx_dma(SPI0);

    dma_chain_state = DMA_CHAIN_FLASH_READ;
}

/* BMP 逐行异步链: 首行读完 → 换字节 → 推屏 → 下一行 */
void dma_chain_bmp_start(uint32_t addr, int w, int rows, int row_size, uint8_t top_down)
{
    bmp_width    = w;
    bmp_rows     = rows;
    bmp_row_size = row_size;
    bmp_row      = 0;
    bmp_addr     = addr;
    bmp_top_down = top_down;

    flash_read_dma_start(bmp_addr, spi_dma_buf, bmp_row_size);
}

/* 字节对交换: BMP [低,高] → LCD [高,低] */
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

/* 主循环调用: 推进 DMA 链 */
void dma_chain_proc(void)
{
    if (!dma_chain_done)
        return;
    dma_chain_done = 0;

    if (dma_chain_state == DMA_CHAIN_FLASH_READ)
    {
        /* Flash 读完成 → 释放 Flash → 字节交换 → 推屏 */
        FLASH_CS_SET();
        buf_swap_bytes(bmp_width * 2);
        dma_send_enable(bmp_width * 2);
        dma_chain_state = DMA_CHAIN_LCD_PUSH;
    }
    else if (dma_chain_state == DMA_CHAIN_LCD_PUSH)
    {
        /* 推屏完成 → 下一行 */
        bmp_row++;
        bmp_addr += bmp_row_size;

        spi_dma_send_ok = 1;

        if (bmp_row < bmp_rows)
        {
            flash_read_dma_start(bmp_addr, spi_dma_buf, bmp_row_size);
        }
        else
        {
            dma_chain_state = DMA_CHAIN_IDLE;
            LCD_CS_HIGH();
            if (bmp_top_down)
            {
                WriteComm(0x36);
                WriteData(0xA0);
            }
        }
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
