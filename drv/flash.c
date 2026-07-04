#include "flash.h"

#define FLASH_SPI           SPI0
#define FLASH_SPI_TIMEOUT   5000U    /* 统一 SPI 轮询超时 */
#define FLASH_PAGE_SIZE     256U     /* Flash 页大小 */

/* 指令码 */
#define FLASH_WRITE_ENABLE  0x06
#define FLASH_PAGE_PROGRAM  0x02    /* 页编程 (≤256B/页, 不可跨页) */
#define FLASH_READ          0x03
#define FLASH_PAGE_ERASE    0x81    /* 256B 页擦除 (普冉 P25Q 专有指令) */
#define FLASH_ID            0x9F
#define FLASH_STATUS        0x05

/* ---- 保留指令 (当前未使用, 供将来扩展) ---- */
#define FLASH_SECTOR_ERASE_4K  0x20    /* 4KB 扇区擦除 */
#define FLASH_BLOCK_ERASE_64K  0xD8    /* 64KB 块擦除 */

/* 状态寄存器位 */
#define FLASH_SR_BUSY       0x01    /* WIP: Write In Progress */
#define FLASH_SR_WEL        0x02    /* WEL: Write Enable Latch */

/* ========================================================================
 *  内部辅助函数
 * ======================================================================== */

/**
 * @brief  SPI 单字节收发 (发送 data, 返回接收到的字节)
 * @retval MD_OK / MD_ERROR (超时)
 */
static md_status_t spi_xfer_byte(uint8_t tx_data, uint8_t *rx_data)
{
    uint16_t cnt;

    cnt = FLASH_SPI_TIMEOUT;
    md_spi_set_data_reg(FLASH_SPI, tx_data);
    while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt));
    if (cnt == 0) return MD_ERROR;

    cnt = FLASH_SPI_TIMEOUT;
    while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt));
    if (cnt == 0) return MD_ERROR;

    if (rx_data != NULL)
        *rx_data = (uint8_t)md_spi_get_data_reg_value(FLASH_SPI);
    else
        (void)md_spi_get_data_reg_value(FLASH_SPI);

    return MD_OK;
}

/**
 * @brief  读取 Flash 状态寄存器
 * @retval 状态寄存器值 (低 8 位), 或 0xFF 表示超时
 */
static uint8_t flash_read_status(void)
{
    uint8_t status;
    uint8_t dummy;

    FLASH_CS_CLR();

    if (spi_xfer_byte(FLASH_STATUS, &dummy) != MD_OK) {
        FLASH_CS_SET();
        return 0xFF;
    }

    if (spi_xfer_byte(0xFF, &status) != MD_OK) {
        FLASH_CS_SET();
        return 0xFF;
    }

    FLASH_CS_SET();
    return status;
}

/**
 * @brief  发送 Write Enable 指令并校验 WEL 位
 * @retval MD_OK = 写使能成功, MD_ERROR = 超时或 WEL 未置位
 */
static md_status_t flash_write_enable(void)
{
    uint8_t dummy;
    md_status_t ret;
    uint8_t status;

    FLASH_CS_CLR();

    ret = spi_xfer_byte(FLASH_WRITE_ENABLE, &dummy);

    FLASH_CS_SET();

    if (ret != MD_OK)
        return MD_ERROR;

    /* 等待 CS 上升沿锁存后短暂延迟 */
    {
        uint8_t i;
        for (i = 0; i < 100; i++) { ; }
    }

    /* 校验 WEL 位 */
    status = flash_read_status();
    if (!(status & FLASH_SR_WEL)) {
        /* WEL 未置位 — Flash 可能处于保护状态 */
        return MD_ERROR;
    }

    return MD_OK;
}

/* ========================================================================
 *  对外 API
 * ======================================================================== */

/**
 * @brief  擦除 Flash 的 256 字节页 (普冉 P25Q 0x81 页擦除指令)
 * @param  addr  页内任意地址 (函数自动对齐到页边界)
 * @retval MD_OK / MD_ERROR
 *
 * @note   P25Q64SH 支持 256B 细粒度擦除。addr 按 256B 对齐，
 *         擦除范围为 [addr & ~0xFF, addr & ~0xFF + 255]。
 *         始终使用 0x81 页擦除指令，不需要 4KB 扇区擦除 (0x20)。
 */
md_status_t flash_page_erase(uint32_t addr)
{
    uint8_t cmd_buf[4];
    uint16_t page;
    uint8_t i;

    /* Write Enable */
    if (flash_write_enable() != MD_OK)
        return MD_ERROR;

    /* 构造 0x81 页擦除指令: [0x81, page_hi, page_lo, dummy] */
    cmd_buf[0] = FLASH_PAGE_ERASE;
    page       = (uint16_t)(addr >> 8);   /* addr / 256, 15-bit page number */
    cmd_buf[1] = (page >> 8) & 0xFF;
    cmd_buf[2] = page & 0xFF;
    cmd_buf[3] = 0x00;                    /* dummy byte */

    FLASH_CS_CLR();

    for (i = 0; i < sizeof(cmd_buf); i++) {
        if (spi_xfer_byte(cmd_buf[i], NULL) != MD_OK) {
            FLASH_CS_SET();
            LCD_CS_LOW();
            return MD_ERROR;
        }
    }

    FLASH_CS_SET();

    /* 等待内部擦除完成 (tSE ≈ 20ms for 256B page erase) */
    flash_wait_unbusy();

    LCD_CS_LOW();
    return MD_OK;
}

/**
 * @brief  页编程 (Page Program 0x02)
 * @param  addr  写入起始地址
 * @param  buf   数据源
 * @param  size  字节数
 * @retval MD_OK / MD_ERROR
 *
 * @note   单次写入不可跨越 256 字节页边界 (跨页会导致地址回绕)。
 *         本函数不做自动拆分; 调用者须自行保证 addr+size 不跨页。
 */
md_status_t flash_write(uint32_t addr, unsigned char *buf, uint16_t size)
{
    uint8_t cmd_buf[4];
    uint16_t i;

    if (buf == NULL || size == 0)
        return MD_ERROR;

    /* 页边界安全检查 */
    if (((addr & (FLASH_PAGE_SIZE - 1)) + size) > FLASH_PAGE_SIZE)
        return MD_ERROR;

    /* Write Enable */
    if (flash_write_enable() != MD_OK)
        return MD_ERROR;

    /* 构造指令: [0x02, addr[23:16], addr[15:8], addr[7:0]] */
    cmd_buf[0] = FLASH_PAGE_PROGRAM;
    cmd_buf[1] = (addr >> 16) & 0xFF;
    cmd_buf[2] = (addr >> 8) & 0xFF;
    cmd_buf[3] = addr & 0xFF;

    FLASH_CS_CLR();

    /* 发送指令 + 地址 */
    for (i = 0; i < sizeof(cmd_buf); i++) {
        if (spi_xfer_byte(cmd_buf[i], NULL) != MD_OK) {
            FLASH_CS_SET();
            LCD_CS_LOW();
            return MD_ERROR;
        }
    }

    /* 发送数据 */
    for (i = 0; i < size; i++) {
        if (spi_xfer_byte(buf[i], NULL) != MD_OK) {
            FLASH_CS_SET();
            LCD_CS_LOW();
            return MD_ERROR;
        }
    }

    FLASH_CS_SET();

    /* 等待内部编程完成 (tPP ≈ 3ms) */
    flash_wait_unbusy();

    LCD_CS_LOW();
    return MD_OK;
}

/**
 * @brief  读取 Flash 数据 (轮询方式)
 * @param  addr  读取起始地址
 * @param  buf   接收缓冲区
 * @param  size  字节数
 * @retval MD_OK / MD_ERROR
 */
md_status_t flash_read(uint32_t addr, unsigned char *buf, uint16_t size)
{
    uint8_t cmd_buf[4];
    uint16_t i;

    if (buf == NULL || size == 0)
        return MD_ERROR;

    cmd_buf[0] = FLASH_READ;
    cmd_buf[1] = (addr >> 16) & 0xFF;
    cmd_buf[2] = (addr >> 8) & 0xFF;
    cmd_buf[3] = addr & 0xFF;

    FLASH_CS_CLR();

    /* 发送指令 + 地址 */
    for (i = 0; i < sizeof(cmd_buf); i++) {
        if (spi_xfer_byte(cmd_buf[i], NULL) != MD_OK) {
            FLASH_CS_SET();
            LCD_CS_LOW();
            return MD_ERROR;
        }
    }

    /* 读取数据 */
    for (i = 0; i < size; i++) {
        if (spi_xfer_byte(0xFF, &buf[i]) != MD_OK) {
            FLASH_CS_SET();
            LCD_CS_LOW();
            return MD_ERROR;
        }
    }

    FLASH_CS_SET();
    LCD_CS_LOW();
    return MD_OK;
}

/**
 * @brief  读取 Flash 数据 (DMA 方式, 速度快于轮询)
 * @param  addr  读取起始地址
 * @param  buf   接收缓冲区
 * @param  size  字节数 (≤ 1024)
 * @retval MD_OK / MD_ERROR
 */
md_status_t flash_read_dma(uint32_t addr, unsigned char *buf, uint16_t size)
{
    uint8_t cmd_buf[4];
    uint8_t i;
    uint32_t timeout;

    /* 保存并禁用 DMA 中断 — 用轮询等待完成 */
    TypeFunc tx_int_save, rx_int_save;

    /* 保存原始 DMA 配置字段, 函数结束后恢复 */
    void    *tx_src_save, *rx_dst_save;
    uint32_t tx_size_save, rx_size_save;

    if (buf == NULL || size == 0)
        return MD_ERROR;

    cmd_buf[0] = FLASH_READ;
    cmd_buf[1] = (addr >> 16) & 0xFF;
    cmd_buf[2] = (addr >> 8) & 0xFF;
    cmd_buf[3] = addr & 0xFF;

    FLASH_CS_CLR();

    /* 发送指令 + 地址 (轮询, 短小操作无需 DMA) */
    for (i = 0; i < sizeof(cmd_buf); i++) {
        if (spi_xfer_byte(cmd_buf[i], NULL) != MD_OK) {
            FLASH_CS_SET();
            LCD_CS_LOW();
            return MD_ERROR;
        }
    }

    /* 填充 TX DMA 缓冲区 */
    memset(spi_dma_buf, 0xFF, size);

    /* ---- 保存 DMA 配置 ---- */
    tx_int_save  = spi_dma_tx_config.interrupt;
    rx_int_save  = spi_dma_rx_config.interrupt;
    tx_src_save  = spi_dma_tx_config.src;
    tx_size_save = spi_dma_tx_config.size;
    rx_dst_save  = spi_dma_rx_config.dst;
    rx_size_save = spi_dma_rx_config.size;

    spi_dma_tx_config.interrupt = DISABLE;
    spi_dma_rx_config.interrupt = DISABLE;

    /* 配置 DMA: TX 发送 dummy 字节, RX 接收 Flash 数据 */
    spi_dma_tx_config.src  = (void *)spi_dma_buf;
    spi_dma_tx_config.size = size;
    spi_dma_rx_config.dst  = (void *)buf;
    spi_dma_rx_config.size = size;

    md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &spi_dma_tx_config);
    md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &spi_dma_rx_config);

    /* 先使能 RX 通道, 再使能 TX 通道 (避免丢数据) */
    md_dma_enable_channel(MD_DMA_CH_1);   /* RX */
    md_dma_enable_channel(MD_DMA_CH_0);   /* TX */

    md_spi_enable_tx_dma(SPI0);
    md_spi_enable_rx_dma(SPI0);

    /* 等待 TX DMA 完成 */
    timeout = 100000U;
    while (!md_dma_is_active_flag_done(MD_DMA_CH_0) && --timeout);
    md_dma_clear_flag_done(MD_DMA_CH_0);

    /* 等待 RX DMA 完成 */
    timeout = 100000U;
    while (!md_dma_is_active_flag_done(MD_DMA_CH_1) && --timeout);
    md_dma_clear_flag_done(MD_DMA_CH_1);

    md_spi_disable_tx_dma(SPI0);
    md_spi_disable_rx_dma(SPI0);

    /* ---- 恢复 DMA 配置 ---- */
    spi_dma_tx_config.interrupt = tx_int_save;
    spi_dma_rx_config.interrupt = rx_int_save;
    spi_dma_tx_config.src       = tx_src_save;
    spi_dma_tx_config.size      = tx_size_save;
    spi_dma_rx_config.dst       = rx_dst_save;
    spi_dma_rx_config.size      = rx_size_save;

    FLASH_CS_SET();
    LCD_CS_LOW();
    return MD_OK;
}

/**
 * @brief  等待 Flash 内部操作完成 (查询 BUSY/WIP 位)
 * @retval MD_OK / MD_ERROR (超时)
 */
md_status_t flash_wait_unbusy(void)
{
    uint8_t status;
    uint32_t timeout = 100000U;   /* 防止死循环 */
    uint8_t dummy;

    FLASH_CS_CLR();

    /* 发送 Read Status Register 指令 */
    if (spi_xfer_byte(FLASH_STATUS, &dummy) != MD_OK) {
        FLASH_CS_SET();
        return MD_ERROR;
    }

    /* 循环读取状态寄存器, 直到 BUSY 位清零 */
    do {
        if (spi_xfer_byte(0xFF, &status) != MD_OK) {
            FLASH_CS_SET();
            return MD_ERROR;
        }
    } while ((status & FLASH_SR_BUSY) && --timeout);

    FLASH_CS_SET();

    if (timeout == 0)
        return MD_ERROR;

    return MD_OK;
}

/**
 * @brief  读取 Flash JEDEC ID
 * @retval 24-bit ID (Manufacturer[15:8] | MemoryType[7:0] | Capacity[7:0])
 *          超时返回 0
 */
uint32_t flash_read_id(void)
{
    uint8_t flash_id[3] = {0};
    uint8_t dummy;
    uint8_t i;

    FLASH_CS_CLR();

    /* 发送 JEDEC ID 指令 */
    if (spi_xfer_byte(FLASH_ID, &dummy) != MD_OK) {
        FLASH_CS_SET();
        LCD_CS_LOW();
        return 0;
    }

    /* 读取 3 字节 ID */
    for (i = 0; i < 3; i++) {
        if (spi_xfer_byte(0xFF, &flash_id[i]) != MD_OK) {
            FLASH_CS_SET();
            LCD_CS_LOW();
            return 0;
        }
    }

    FLASH_CS_SET();
    LCD_CS_LOW();

    /* Manufacturer ID | Memory Type | Capacity */
    return ((uint32_t)flash_id[0] << 16)
         | ((uint32_t)flash_id[1] << 8)
         |  (uint32_t)flash_id[2];
}

/**
 * @brief  便捷读取接口 — DMA 读 Flash 数据到缓冲区
 * @param  addr      Flash 源地址
 * @param  read_buf  接收缓冲区
 * @param  size      字节数 (超过 READ_BUFFER_MAX 会被截断)
 *
 * @note   读操作不会使 Flash 进入 busy 状态, 无需 wait_unbusy
 */
void flash_read_buf(uint32_t addr, uint8_t *read_buf, uint16_t size)
{
    if (size > READ_BUFFER_MAX)
        size = READ_BUFFER_MAX;

    if (flash_read_dma(addr, read_buf, size) == MD_OK) {
        /* 读操作无需 wait_unbusy — Flash 读完后立即可用 */
    }

    LCD_CS_LOW();   /* 确保 LCD CS 恢复 */
}
