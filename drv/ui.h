#ifndef __UI_H
#define __UI_H

#include "global_define.h"

#define SPI_CLK 				GPIOA
#define SPI_CLK_PIN 			MD_GPIO_PIN_10

#define SPI_MOSI 				GPIOA
#define SPI_MOSI_PIN 			MD_GPIO_PIN_11

#define SPI_MISO 				GPIOA
#define SPI_MISO_PIN 			MD_GPIO_PIN_12

#define LCD_RS					GPIOA
#define LCD_RS_PIN				MD_GPIO_PIN_8

#define LCD_RST					GPIOA
#define LCD_RST_PIN				MD_GPIO_PIN_7

#define LCD_CS					GPIOA
#define LCD_CS_PIN				MD_GPIO_PIN_3

#define LCD_BLK					GPIOA
#define LCD_BLK_PIN				MD_GPIO_PIN_1

#define FLASH_CS				GPIOA
#define FLASH_CS_PIN			MD_GPIO_PIN_9

#define TFT_EN					GPIOA
#define TFT_EN_PIN				MD_GPIO_PIN_4

#define LCD_CS_LOW() 			md_gpio_set_pin_low(LCD_CS, LCD_CS_PIN)
#define LCD_CS_HIGH() 			md_gpio_set_pin_high(LCD_CS, LCD_CS_PIN)

#define LCD_RS_LOW() 			md_gpio_set_pin_low(LCD_RS, LCD_RS_PIN)
#define LCD_RS_HIGH() 			md_gpio_set_pin_high(LCD_RS, LCD_RS_PIN)

#define LCD_RST_LOW() 			md_gpio_set_pin_low(LCD_RST, LCD_RST_PIN)
#define LCD_RST_HIGH()			md_gpio_set_pin_high(LCD_RST, LCD_RST_PIN)

#define LCD_BLK_LOW() 			md_gpio_set_pin_low(LCD_BLK, LCD_BLK_PIN)
#define LCD_BLK_HIGH()			md_gpio_set_pin_high(LCD_BLK, LCD_BLK_PIN)

#define FLASH_CS_CLR()			md_gpio_set_pin_low(FLASH_CS, FLASH_CS_PIN)
#define FLASH_CS_SET()			md_gpio_set_pin_high(FLASH_CS, FLASH_CS_PIN)

#define TFT_EN_CLR()			md_gpio_set_pin_low(TFT_EN, TFT_EN_PIN)
#define TFT_EN_SET()			md_gpio_set_pin_high(TFT_EN, TFT_EN_PIN)

#define FLASH_READ_BUF_SIZE		(1024)
#define LCD_POWER_ON_DELAY		(4)



void ui_init(void);
void ui_proc(void);
void ui_task(void);




#endif


