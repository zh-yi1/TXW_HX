#include "flash.h"

#define FLASH_SPI SPI0

#define FLASH_WRITE_ENABLE	0x06
#define FLASH_ERASE			0x20	// 4KB
#define FLASH_ERASE_256     0x81	// 256B
#define FLASH_PROGRAM		0x02	// 256B
#define FLASH_READ			0x03
#define FLASH_ID			0x9F
#define FLASH_STATUS		0x05
#define FLASH_Block_ERASE	0xD8

md_status_t flash_sector_erase(uint32_t addr)
{
	uint16_t cnt = 5000, temp;
	uint8_t cmd_buf[4];
	uint8_t i = 0U;

	cmd_buf[0] = FLASH_ERASE_256;	  // 256B 页擦除

	if (cmd_buf[0] == FLASH_ERASE_256) {
		/* 0x81 地址格式: 2字节页地址 + 1字节 dummy */
		uint16_t page = (uint16_t)(addr >> 8);  /* addr / 256 */
		cmd_buf[1] = (page >> 8) & 0xff;
		cmd_buf[2] = page & 0xff;
		cmd_buf[3] = 0x00;                     /* dummy byte */
	} else {
		cmd_buf[1] = (addr >> 16) & 0xff;      /* 标准 3字节地址 */
		cmd_buf[2] = (addr >> 8) & 0xff;
		cmd_buf[3] = addr & 0xff;
	}

	/*Choose lower, the selected Flash*/
	FLASH_CS_CLR();

	md_spi_set_data_reg(FLASH_SPI, FLASH_WRITE_ENABLE);

	while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt))
		;

	cnt = 5000;

	while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt))
		;

	temp = md_spi_get_data_reg_value(FLASH_SPI);
	UNUSED(temp);

	/*Pick up and release of Flash*/
	FLASH_CS_SET();

	for (i = 0; i < 100; i++)
	{
		;
	}
	FLASH_CS_CLR();

	/*Send the sector erase instructions and Flash address three bytes*/
	for (i = 0; i < sizeof(cmd_buf); i++)
	{
		cnt = 5000;
		md_spi_set_data_reg(FLASH_SPI, cmd_buf[i]);

		while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt))
			;

		cnt = 5000;

		while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt))
			;

		temp = md_spi_get_data_reg_value(FLASH_SPI);
		UNUSED(temp);
	}

	FLASH_CS_SET();

	LCD_CS_LOW();   /* 恢复 LCD 片选 */

	return MD_OK;
}

md_status_t flash_write(uint32_t addr, unsigned char *buf, uint16_t size)
{
	uint16_t cnt = 500, temp;
	uint8_t cmd_buf[4];
	uint16_t i = 0U;

	if (buf == NULL)
		return MD_ERROR;

	cmd_buf[0] = FLASH_PROGRAM;
	cmd_buf[1] = (addr >> 16) & 0xff;
	cmd_buf[2] = (addr >> 8) & 0xff;
	cmd_buf[3] = addr & 0xff;

	FLASH_CS_CLR(); /*Choose lower, the selected Flash*/

	md_spi_set_data_reg(FLASH_SPI, (uint8_t)FLASH_WRITE_ENABLE);

	while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt))
		;

	cnt = 500;

	while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt))
		;

	temp = md_spi_get_data_reg_value(FLASH_SPI);
	UNUSED(temp);

	FLASH_CS_SET(); /*Pick up and release of Flash*/

	for (i = 0; i < 100; i++)
	{
	}
	FLASH_CS_CLR();

	for (i = 0; i < sizeof(cmd_buf); i++) /*Send the programming instructions and Flash address three bytes*/
	{
		cnt = 500;
		md_spi_set_data_reg(FLASH_SPI, (uint8_t)cmd_buf[i]);

		while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt))
			;

		cnt = 500;

		while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt))
			;

		temp = md_spi_get_data_reg_value(FLASH_SPI);
		UNUSED(temp);
	}

	for (i = 0; i < size; i++) /*To write the data sent to the Flash*/
	{
		cnt = 500;
		md_spi_set_data_reg(FLASH_SPI, (uint8_t)buf[i]);

		while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt))
			;

		cnt = 500;

		while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt))
			;

		temp = md_spi_get_data_reg_value(FLASH_SPI);
		UNUSED(temp);
	}

	FLASH_CS_SET();

	flash_wait_unbusy();  /* 等 Flash 内部写入完成 */

	LCD_CS_LOW();         /* 恢复 LCD 片选 */

	return MD_OK;
}

md_status_t flash_read(uint32_t addr, unsigned char *buf, uint16_t size)
{
	uint16_t cnt = 5, temp;
	uint8_t cmd_buf[4];
	uint16_t i = 0U;

	if (buf == NULL)
		return MD_ERROR;

	cmd_buf[0] = FLASH_READ;
	cmd_buf[1] = (addr >> 16) & 0xff;
	cmd_buf[2] = (addr >> 8) & 0xff;
	cmd_buf[3] = addr & 0xff;

	FLASH_CS_CLR(); /*Choose lower, the selected Flash*/
	for (i = 0; i < sizeof(cmd_buf); i++) /*Send the editor & reader instructions and Flash address three bytes*/
	{
		md_spi_set_data_reg(FLASH_SPI, (uint8_t)cmd_buf[i]);

		while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt))
			;

		cnt = 50;

		while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt))
			;

		temp = md_spi_get_data_reg_value(FLASH_SPI);
		UNUSED(temp);
	}

	for (i = 0; i < size; i++) /*Send the programming instructions and Flash address three bytes*/
	{
		cnt = 5;
		md_spi_set_data_reg(FLASH_SPI, 0xFF);

		while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt))
			;

		cnt = 5;

		while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt))
			;

		buf[i] = md_spi_get_data_reg_value(FLASH_SPI);
		//  md_uart_send(UART1, buf[i] );
	}

	FLASH_CS_SET();
	LCD_CS_LOW();   /* 恢复 LCD 片选 */

	return MD_OK;
}

md_status_t flash_read_dma(uint32_t addr, unsigned char *buf, uint16_t size)
{
	uint16_t cnt = 500, temp;
	uint8_t cmd_buf[4];
	uint8_t i;
	uint32_t timeout;
	TypeFunc tx_int_save, rx_int_save;

	if (buf == NULL || size == 0)
		return MD_ERROR;

	cmd_buf[0] = FLASH_READ;
	cmd_buf[1] = (addr >> 16) & 0xff;
	cmd_buf[2] = (addr >> 8) & 0xff;
	cmd_buf[3] = addr & 0xff;

	FLASH_CS_CLR();

	/* Send command + 3-byte address by polling */
	for (i = 0; i < sizeof(cmd_buf); i++)
	{
		cnt = 500;
		md_spi_set_data_reg(FLASH_SPI, cmd_buf[i]);
		while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt));

		cnt = 500;
		while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt));
		temp = md_spi_get_data_reg_value(FLASH_SPI);
		UNUSED(temp);
	}

	/* Fill TX buffer with dummy bytes to generate SPI clocks */
	memset(spi_dma_buf, 0xFF, size);

	/* Save and disable DMA interrupts — poll completion instead */
	tx_int_save = spi_dma_tx_config.interrupt;
	rx_int_save = spi_dma_rx_config.interrupt;
	spi_dma_tx_config.interrupt = DISABLE;
	spi_dma_rx_config.interrupt = DISABLE;

	/* Configure DMA: TX sends dummy bytes, RX receives flash data */
	spi_dma_tx_config.src  = (void *)spi_dma_buf;
	spi_dma_tx_config.size = size;
	spi_dma_rx_config.dst  = (void *)buf;
	spi_dma_rx_config.size = size;

	md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &spi_dma_tx_config);
	md_dma_config_base(DMA0, MD_DMA_CYCLE_CTRL_BASIC, &spi_dma_rx_config);

	md_dma_enable_channel(MD_DMA_CH_1);
	md_dma_enable_channel(MD_DMA_CH_0);

	md_spi_enable_tx_dma(SPI0);
	md_spi_enable_rx_dma(SPI0);

	/* Wait for TX DMA done */
	timeout = 100000;
	while (!md_dma_is_active_flag_done(MD_DMA_CH_0) && --timeout);
	md_dma_clear_flag_done(MD_DMA_CH_0);

	/* Wait for RX DMA done */
	timeout = 100000;
	while (!md_dma_is_active_flag_done(MD_DMA_CH_1) && --timeout);
	md_dma_clear_flag_done(MD_DMA_CH_1);

	md_spi_disable_tx_dma(SPI0);
	md_spi_disable_rx_dma(SPI0);

	/* Restore interrupt settings */
	spi_dma_tx_config.interrupt = tx_int_save;
	spi_dma_rx_config.interrupt = rx_int_save;

	FLASH_CS_SET();
	LCD_CS_LOW();   /* 恢复 LCD 片选 */
	return MD_OK;
}

/**
 * @brief  wait until flash unbusy.
 * @retval Status, see @ref md_status_t.
 */
md_status_t flash_wait_unbusy(void)
{
	uint16_t cnt = 500, temp;
	uint8_t status;

	FLASH_CS_CLR(); /*Choose lower, the selected Flash*/

	md_spi_set_data_reg(FLASH_SPI, (uint8_t)FLASH_STATUS);

	while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt))
		;

	cnt = 500;

	while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt))
		;

	temp = md_spi_get_data_reg_value(FLASH_SPI);
	UNUSED(temp);

	do
	{
		cnt = 500;
		md_spi_set_data_reg(FLASH_SPI, 0xFF);

		while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt))
			;

		cnt = 500;

		while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt))
			;

		status = md_spi_get_data_reg_value(FLASH_SPI);
	} while (status & 0x01);

	FLASH_CS_SET();

	return MD_OK;
}

/**
 * @brief  Read flash id in blocking mode.
 * @retval flash id.
 */
uint32_t flash_read_id(void)
{
	uint16_t cnt = 500;
	uint16_t temp;

	uint8_t i;

	uint8_t flash_id[4] = {0U};

	flash_id[0] = FLASH_ID;

	FLASH_CS_CLR(); /*Choose lower, the selected Flash*/

	for (i = 0; i < sizeof(flash_id); i++)
	{
		md_spi_set_data_reg(FLASH_SPI, flash_id[i]);

		while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt))
			;

		cnt = 5000;

		while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt))
			;

		temp = md_spi_get_data_reg_value(FLASH_SPI);
		UNUSED(temp);
	}

	for (i = 0; i < 3; i++)
	{
		cnt = 500;
		md_spi_set_data_reg(FLASH_SPI, 0xFF);

		while ((md_spi_is_active_flag_txbe(FLASH_SPI) == 0) && (--cnt))
			;

		cnt = 500;

		while ((!((md_spi_is_active_flag_rxbne(FLASH_SPI)))) && (--cnt))
			;

		flash_id[i] = md_spi_get_data_reg_value(FLASH_SPI);
	}

	FLASH_CS_SET();
	LCD_CS_LOW();   /* 恢复 LCD 片选 */

	return ((flash_id[0] << 16) | (flash_id[1] << 8) | (flash_id[2])); /*Manufacturer ID flash_id [0] and device ID flash_id [1]*/
}

void flash_read_buf(uint32_t addr, uint8_t* read_buf, uint16_t size)
{
	md_status_t status;

	if (size > READ_BUFFER_MAX)
		size = READ_BUFFER_MAX;

	status = flash_read_dma(addr, read_buf, size);

	if (status == MD_OK)
	{
		flash_wait_unbusy();
	}

	LCD_CS_LOW();   /* flash_wait_unbusy 拉高了 LCD_CS，恢复 */

	return;
}


