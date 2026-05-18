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

void Dispphoto_Dispaly_flash(int x, int y, int add)
{
	int w, h, row_size, total_rows;
	uint32_t pixel_offset;
	uint16_t bpp;
	int bottom_up;

	/* 读 BMP 文件头 + BITMAPINFOHEADER (最多 66 字节含 BI_BITFIELDS 掩码) */
	flash_read_dma(add, spi_dma_buf, 66);

	/* BM 签名校验 */
	if (spi_dma_buf[0] != 'B' || spi_dma_buf[1] != 'M')
		return;

	/* 位图像素数据偏移 (字节 10-13, uint32 LE) */
	pixel_offset = (uint32_t)spi_dma_buf[10]
		| ((uint32_t)spi_dma_buf[11] << 8)
		| ((uint32_t)spi_dma_buf[12] << 16)
		| ((uint32_t)spi_dma_buf[13] << 24);

	/* 宽度 (字节 18-21, int32 LE) */
	w = spi_dma_buf[18]
		| (spi_dma_buf[19] << 8)
		| (spi_dma_buf[20] << 16)
		| (spi_dma_buf[21] << 24);

	/* 高度 (字节 22-25, int32 LE) */
	h = spi_dma_buf[22]
		| (spi_dma_buf[23] << 8)
		| (spi_dma_buf[24] << 16)
		| (spi_dma_buf[25] << 24);

	/* 位深 (字节 28-29, uint16 LE) */
	bpp = spi_dma_buf[28] | (spi_dma_buf[29] << 8);

	/* 只支持 16-bit RGB */
	if (bpp != 16 || w <= 0 || w > 240)
		return;

	/* 正高度 = 自底向上, 负高度 = 自顶向下 */
	bottom_up = (h > 0);
	if (h < 0) h = -h;
	total_rows = h;

	/* 含 4 字节对齐的行大小 */
	row_size = ((w * 2) + 3) & ~3;

	/* 设置 LCD 显示窗口 */
	BlockWrite(x, x + w - 1, y, y + h - 1);

	/* MADCTL 默认 0xA0 (MY=1 自底向上). 标准 BMP 首行是底部, 匹配.
	   自顶向下 BMP 需翻转 MY 位 */
	if (!bottom_up)
	{
		WriteComm(0x36);
		WriteData(0x20);
	}

	/* 启动异步链: 逐行 Flash读 → 字节交换 → LCD推 */
	dma_chain_bmp_start(add + pixel_offset, w, total_rows, row_size, !bottom_up);
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
