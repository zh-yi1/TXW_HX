#include "lcd.h"

//-------------------------------------------------

#define Delayms md_delay_1ms

static void SendDataSPI(unsigned char dat)
{
	uint16_t k;

	k = 500;
	while ((md_spi_is_active_flag_txbe(SPI0) == 0) && (k--))
		;

	md_spi_set_data_reg(SPI0, (uint8_t)dat);

	while (md_spi_is_active_flag_busy(SPI0))
	{
	};
}

static void SendDataSPI_16(unsigned char dat_L, unsigned char dat_H)
{

	uint16_t k;

	k = 500;
	while ((md_spi_is_active_flag_txbe(SPI0) == 0) && (k--))
	{
	};

	SPI0->DATA = ((dat_H << 8) | dat_L);

	while (md_spi_is_active_flag_busy(SPI0))
	{
	};
}

void WriteComm(unsigned int i)
{
	LCD_RS_LOW();
	LCD_CS_LOW();

	SendDataSPI(i);

	LCD_CS_HIGH();
}

void WriteData(unsigned int i)
{
	LCD_RS_HIGH();
	LCD_CS_LOW();

	SendDataSPI(i);

	LCD_CS_HIGH();
}

void lcd_init(void)
{
	LCD_RST_HIGH();
	Delayms(20);

	LCD_RST_LOW();
	Delayms(20);

	LCD_RST_HIGH();
	Delayms(120);

	WriteComm(0x11);	// 退出睡眠模式

	Delayms(120);                

	WriteComm(0x36);	// 内存数据访问控制
	WriteData(0xA0);	// 00 竖屏  A0 横屏

	WriteComm(0x3A);	// 设置颜色格式
	WriteData(0x05);	// 8位颜色格式
	
	WriteComm(0x21);

	WriteComm(0xB2);	// 设置帧率控制
	WriteData(0x05);   
	WriteData(0x05);   
	WriteData(0x00);   
	WriteData(0x33);   
	WriteData(0x33);   

	WriteComm(0xB7);	// 设置电源控制
	WriteData(0x23);   

	WriteComm(0xBB);	// 电量控制
	WriteData(0x22);   

	WriteComm(0xC0);	// 电源控制
	WriteData(0x2C);   

	WriteComm(0xC2);	// VDV 和 VRH 设置
	WriteData(0x01);   

	WriteComm(0xC3);	// VRH 设置
	WriteData(0x13);   
	
	WriteComm(0xC4);
	WriteData(0x20);   

	WriteComm(0xC6);	// 帧率控制
	WriteData(0x0F);	// 0x13:60Hz   

//	WriteComm(0xD0);	
//	WriteData(0xA7);   

	WriteComm(0xD0);	// 电源控制
	WriteData(0xA4);   
	WriteData(0xA1);   

	WriteComm(0xD6);     
	WriteData(0xA1);	// sleep in后，gate输出为GND

	WriteComm(0xE0);	// 正极伽玛校正
	WriteData(0x70);
	WriteData(0x06);
	WriteData(0x0C);
	WriteData(0x08);
	WriteData(0x09);
	WriteData(0x27);
	WriteData(0x2E);
	WriteData(0x34);
	WriteData(0x46);
	WriteData(0x37);
	WriteData(0x13);
	WriteData(0x13);
	WriteData(0x25);
	WriteData(0x2A);

	WriteComm(0xE1);	// 负极伽玛校正
	WriteData(0x70);
	WriteData(0x04);
	WriteData(0x08);
	WriteData(0x09);
	WriteData(0x07);
	WriteData(0x03);
	WriteData(0x2C);
	WriteData(0x42);
	WriteData(0x42);
	WriteData(0x38);
	WriteData(0x14);
	WriteData(0x14);
	WriteData(0x27);
	WriteData(0x2C);

	WriteComm(0x29);
	
//	WriteComm(0xE4);
//	WriteData(0x1D);	// 使用240根gate  (N+1)*8
//	WriteData(0x00);	// 设定gate起点位置
//	WriteData(0x00);	// 当gate没有用完时，bit4(TMG)设为0

//	WriteComm(0x21);	// 打开反显
//	WriteComm(0x29);	// 打开显示
//	WriteComm(0x2C);	// 内存写入
}

void BlockWrite(unsigned int Xstart, unsigned int Xend, unsigned int Ystart, unsigned int Yend)
{
	Xstart += 0x28;
	Xend += 0x28;
	
	Ystart += 0x34;
	Yend += 0x34;

	WriteComm(0x2a);   
	WriteData(Xstart >> 8);
	WriteData(Xstart & 0xff);
	WriteData(Xend >> 8);
	WriteData(Xend & 0xff);

	WriteComm(0x2b);   
	WriteData(Ystart >> 8);
	WriteData(Ystart & 0xff);
	WriteData(Yend >> 8);
	WriteData(Yend & 0xff);
	
	WriteComm(0x2c);
}

void DispColor(unsigned int color)
{
	unsigned int i, j;
	
	BlockWrite(0, ROW, 0, COL);
	LCD_CS_LOW();
	LCD_RS_HIGH();

	for(i = 0; i <= ROW; i++)
	{
		for(j = 0; j < COL; j++)
		{
			SendDataSPI(color >> 8);
			SendDataSPI(color & 0xFF);
		}
	}

	LCD_CS_HIGH();
}

void WriteOneDot(unsigned int color)
{

	LCD_CS_LOW();

	LCD_RS_HIGH();

	SendDataSPI(color >> 8);
	SendDataSPI(color);

	LCD_CS_HIGH();
}

void PutPixel(unsigned int x, unsigned int y, unsigned int color)
{
	BlockWrite(x, x, y, y);

	LCD_CS_LOW();

	LCD_RS_HIGH();
	SPI_send_data16;

	SendDataSPI_16(color, color >> 8);

	SPI_send_data8;
	LCD_CS_HIGH();
}

void PutPoint(unsigned int x, unsigned int y, unsigned char col_H, unsigned char col_L)
{
	BlockWrite(x, x, y, y);

	LCD_CS_LOW();

	LCD_RS_HIGH();
	SPI_send_data16;
	SendDataSPI_16(col_L, col_H);
	SPI_send_data8;
	LCD_CS_HIGH();
}

void DrawLine(unsigned int Xstart, unsigned int Ystart, unsigned int Xend, unsigned int Yend, unsigned int color)
{
	unsigned int i, j;

	BlockWrite(Xstart, Xend, Ystart, Yend);

	for (i = Ystart; i < Yend + 1; i++)
	{
		for (j = Xstart; j < Xend + 1; j++)
		{
			WriteOneDot(color);
		}
	}
}

void Dispphoto_Dispaly(int x, int y, unsigned char *buf)
{
	unsigned int i, j;
	unsigned char *p;
	unsigned char h, w;
	unsigned char picH, picL;

	p = buf;

	w = buf[3];
	h = buf[5];
	p += 8;
	BlockWrite(x, x + w - 1, y, y + h - 1);

	LCD_CS_LOW();
	LCD_RS_HIGH();
	SPI_send_data16;

	for (i = 0; i < w; i++)
	{

		for (j = 0; j < h; j++)
		{
			picL = *(p + 1);
			picH = *(p);
			while (0 == md_spi_is_active_flag_txbe(SPI0))
			{
			};
			SPI0->DATA = ((picH << 8) | picL);
			while (md_spi_is_active_flag_busy(SPI0))
			{
			};
			p = p + 2;
		}
	}
	SPI_send_data8;
	LCD_CS_HIGH();
}

void Dispphoto_Dispaly_flash(int x, int y, int add, int num)
{
	unsigned short h, w;
	uint32_t addr_offset;
	int remaining;
	uint16_t chunk_size;
	uint32_t timeout;


	/* DMA 读取 8 字节位图头 */
	flash_read_dma(add, spi_dma_buf, 8);

	w = spi_dma_buf[3];
	h = spi_dma_buf[5];

	BlockWrite(x, x + w - 1, y, y + h - 1);

	remaining = num - 8;
	addr_offset = add + 8;

	while (remaining > 0)
	{
		chunk_size = (remaining > READ_BUFFER_MAX) ? READ_BUFFER_MAX : remaining;

		/* DMA 读 Flash 像素数据 */
		flash_read_dma(addr_offset, spi_dma_buf, chunk_size);

		/* DMA 推屏到 LCD */
		spi_dma_send_ok = 0;
		dma_send_enable(chunk_size);

		/* 等待 LCD 推屏 DMA 完成 */
		timeout = 100000;
		while (spi_dma_send_ok == 0 && --timeout)
			;

		addr_offset += chunk_size;
		remaining -= chunk_size;
	}

	LCD_CS_HIGH();
}

extern uint16_t spi_dma_buf_len;

void spi_buf_send(uint8_t send_size)
{
	uint16_t *send_data;
	
	send_data = (uint16_t *)spi_dma_buf;
	LCD_CS_LOW();
	LCD_RS_HIGH();
	SPI_send_data16;
	
	if(send_size > 0 && send_size <= spi_dma_buf_len)
		send_size = send_size / 2;
	else
		send_size = spi_dma_buf_len / 2;

	for (uint8_t i = 0; i < send_size; i++)
	{
		while (0 == md_spi_is_active_flag_txbe(SPI0));
		SPI0->DATA = *send_data;
//		while (md_spi_is_active_flag_busy(SPI0));
		send_data = send_data + 1;
	}
	SPI_send_data8;
	LCD_CS_HIGH();
}
