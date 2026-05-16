#ifndef __LCD_H
#define __LCD_H

#include "global_define.h"

#define ROW			240 //135
#define COL			135 //240

#define WHITE		0xFFFF
#define BLACK		0x0000

#define SPI_send_data8            \
	{                             \
		SPI0->CON1 &= ~(1 << 6);  \
		SPI0->CON1 &= ~(1 << 11); \
		SPI0->CON1 |= (1 << 6);   \
	}
#define SPI_send_data16          \
	{                            \
		SPI0->CON1 &= ~(1 << 6); \
		SPI0->CON1 |= (1 << 11); \
		SPI0->CON1 |= (1 << 6);  \
	}

void lcd_init(void);

void DispColor(unsigned int color);
void BlockWrite(unsigned int Xstart, unsigned int Xend, unsigned int Ystart, unsigned int Yend);
void Dispphoto_Dispaly_flash(int x, int y, int add, int num);

void spi_buf_send(uint8_t send_size);



#endif
