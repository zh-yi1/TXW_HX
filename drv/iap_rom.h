/**********************************************************************************
 *
 * @file    iap_rom.h
 * @brief   IAP ROM function pointer definitions for ES32F010x
 *
 * @note    Ported from ES32 SDK MicroBoot USART_Boot_app_demo
 *
 **********************************************************************************
 */

#ifndef _IAP_ROM_H_
#define _IAP_ROM_H_

#include <stdint.h>

/* Public types ------------------------------------------------------------ */

/**
  *@brief config the multi-words write function support automatic erasing
  */
typedef enum
{
    AUTO_ERASE_FALSE = 0x0U,
    AUTO_ERASE_TRUE  = 0x1U,
} type_auto_erase_t;

/**
  *@brief funtion pointer type for page erase
  */
typedef uint32_t (*iaprom_page_erase_t)(uint32_t, uint32_t, uint32_t);

/**
  *@brief funtion pointer type for simple word write
  */
typedef uint32_t (*iaprom_word_progrm_t)(uint32_t, uint32_t, uint32_t);

/**
  *@brief funtion pointer type for double words write
  */
typedef uint32_t (*iaprom_words_progrm_t)(uint32_t, uint32_t, uint32_t, uint32_t, type_auto_erase_t);

/* Exported Macros ----------------------------------------------------------- */

#define  IAPROM_PAGE_ERASE    ((iaprom_page_erase_t)(*((uint32_t *)0x10000004)))

#define  IAPROM_WORD_PROGRAM  ((iaprom_word_progrm_t)(*((uint32_t *)0x10000008)))

#define  IAPROM_WORDS_PROGRAM ((iaprom_words_progrm_t)(*((uint32_t *)0x10000000)))

#endif /* _IAP_ROM_H_ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
