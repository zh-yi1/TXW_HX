/**********************************************************************************
 *
 * @file    es32f010x.h
 * @brief   REG Head File
 *
 * @date    30 Apri 2021
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          30 Apri 2021    yanght          the first version
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 **********************************************************************************
 */
#ifndef __ES32F010X_H__
#define __ES32F010X_H__

#define __I  volatile const /* defines 'read only' permissions */
#define __O  volatile /* defines 'write only' permissions */
#define __IO volatile /* defines 'read / write' permissions */

//-----------------------------------------------------------
#define __NVIC_PRIO_BITS	2
#define __Vendor_SysTickConfig	0U


typedef enum IRQn {
	/* Cortex-M0 processor cxceptions index */
	Reset_IRQn        = -15,
	NMI_IRQn          = -14,
	HardFault_IRQn    = -13,
	SVCall_IRQn       = -5,
	PendSV_IRQn       = -2,
	SysTick_IRQn      = -1,

	/* es32f0xx specific interrupt index */
	WWDT_IRQn                                  = 0,
	IWDT_IRQn                                  = 1,
	LVD_IRQn                                   = 2,
	RESERVED0_IRQn                             = 3,
	CMU_IRQn                                   = 4,
	EXTI0_3_IRQn                               = 5,
	EXTI4_7_IRQn                               = 6,
	EXTI8_11_IRQn                              = 7,
	EXTI12_15_IRQn                             = 8,
	DMA_IRQn                                   = 9,
	ACMP0_IRQn         	                       = 10,
	ACMP1_IRQn                                 = 11,
	ADC0_IRQn                                   = 12,
	ADTIM0_BRK_UP_TRIGCOM_IRQn                 = 13,
	ADTIM0_CC_IRQn                             = 14,
	BSTIM0_IRQn                                = 15,
	RESERVED3_IRQn                             = 16,
	GPTIMC0_IRQn                               = 17,
	GPTIMC1_IRQn                               = 18,
	GPTIMC2_IRQn                               = 19,
	RESERVED4_IRQn                             = 20,
	ADTIM0_IRQn                                = 21,
	RESERVED5_IRQn                             = 22,
	I2C0_IRQn                                  = 23,
	I2C1_IRQn                                  = 24,
	SPI0_IRQn                                  = 25,
	RESERVED7_IRQn                             = 26,
	RESERVED8_IRQn                             = 27,
    RESERVED9_IRQn                             = 28,
	USART0_IRQn                                = 29,
	USART1_IRQn                                = 30,
	RESERVED6_IRQn                             = 31,
} IRQn_Type;

#include "core_cm0.h"
#if defined(__CC_ARM)
#pragma anon_unions
#endif

#include <stdint.h> 
#include "reg_i2c.h"
#include "reg_gpio.h"
#include "reg_timer.h"
#include "reg_adc.h"
#include "reg_dma.h"
#include "reg_spi.h"
#include "reg_iwdt.h"
#include "reg_wwdt.h"
#include "reg_crc.h"
#include "reg_usart.h"
#include "reg_cmp.h"
#include "reg_cmu.h"
#include "reg_dbg.h"
#include "reg_msc.h"
#include "reg_pis.h"
#include "reg_pmu.h"
#include "reg_rmu.h"
#include "reg_syscfg.h"


//-----------------------------------------------------------
#define SRAM_BASE (0x20000000UL)
#define APB1_BASE (0x40000000UL)
#define AHB_BASE  (0x40080000UL)

#define SYSCFG_BASE  (AHB_BASE + 0x0000)  //ok
#define CMU_BASE     (AHB_BASE + 0x0400)  //ok
#define RMU_BASE     (AHB_BASE + 0x0800)  //ok
#define PMU_BASE     (AHB_BASE + 0x0C00)  //ok
#define MSC_BASE     (AHB_BASE + 0x1000)  //ok
#define GPIOA_BASE   (AHB_BASE + 0x4000)  //ok
#define GPIOB_BASE   (AHB_BASE + 0x4040)
#define EXTI_BASE    (AHB_BASE + 0x4300)  //ok
#define CRC_BASE     (AHB_BASE + 0x5000)  //ok
#define PIS_BASE     (AHB_BASE + 0x6000)


//APB
#define AD16C4T_BASE   (APB1_BASE + 0X0000)  //ADTIM 
#define BS16TN_BASE  (APB1_BASE + 0X0400)  //bstim
#define GP16C2T0_BASE (APB1_BASE + 0X0800)  //GPTIMC0
#define GP16C2T1_BASE (APB1_BASE + 0X0C00)  //GPTIMC1  
#define GP16C2T2_BASE (APB1_BASE + 0X1000)  //GPTIMC2
//usart-----------------------------------
#define USART0_BASE	(APB1_BASE + 0x5000)
#define USART1_BASE	(APB1_BASE + 0x5400)         
/*!< SPI memory map */
#define SPI0_BASE (APB1_BASE + 0X6000)          
/*!< IIC memory map */
#define I2C0_BASE (APB1_BASE + 0X8000)
#define I2C1_BASE (APB1_BASE + 0X8400)             
//iwdt_wwdt------------------------------
#define WWDT_BASE	(APB1_BASE + 0x8800)
#define IWDT_BASE	(APB1_BASE + 0x8c00)             
//dbgc-----------------------------------
#define DBGCON_BASE	(APB1_BASE + 0x9000) 
//adc        
#define ADC0_BASE     (APB1_BASE + 0x9400)  
//ACMP
#define ACMP0_BASE     (APB1_BASE + 0x9800)      
#define ACMP1_BASE     (APB1_BASE + 0x9C00)             
//dma             
#define DMA_BASE     (APB1_BASE + 0xC000)  //ok
       

//AHB
/******************************************************************************/
/* SYSCFG Peripheral_declaration */
/******************************************************************************/
#define SYSCFG ((SYSCFG_TypeDef *)SYSCFG_BASE)
/******************************************************************************/
/* CMU Peripheral_declaration */
/******************************************************************************/
#define CMU ((CMU_TypeDef *) CMU_BASE )
/******************************************************************************/
/* RMU Peripheral_declaration */
/******************************************************************************/
#define RMU ((RMU_TypeDef *) RMU_BASE )
/******************************************************************************/
/* PMU Peripheral_declaration */
/******************************************************************************/
#define PMU ((PMU_TypeDef *) PMU_BASE )
/******************************************************************************/
/* MSC Peripheral_declaration */
/******************************************************************************/
#define MSC ((MSC_TypeDef *) MSC_BASE )
/******************************************************************************/
/* GPIO Peripheral_declaration */
/******************************************************************************/
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *) GPIOB_BASE)

#define EXTI  ((EXTI_TypeDef *) EXTI_BASE)
/******************************************************************************/
/* CRC Peripheral_declaration */
/******************************************************************************/
#define CRC   ((CRC_TypeDef  *) CRC_BASE)

//APB
/******************************************************************************/    
/* TIMER Peripheral_declaration */                                                  
/******************************************************************************/ 
 #define AD16C4T  ((TIMER_TypeDef *) AD16C4T_BASE)	//6: ADTIM 
 #define BS16TN   ((TIMER_TypeDef *) BS16TN_BASE)	//6: BSTIM0
 #define GP16C2T0 ((TIMER_TypeDef *) GP16C2T0_BASE)	//6: GPTIMC0 
 #define GP16C2T1 ((TIMER_TypeDef *) GP16C2T1_BASE)	//6: GPTIMC1 
 #define GP16C2T2 ((TIMER_TypeDef *) GP16C2T2_BASE)	//6: GPTIMC2 
 
 #define TIMER0 AD16C4T   
 #define TIMER1 BS16TN    
 #define TIMER2 GP16C2T0   
 #define TIMER3 GP16C2T1  
 #define TIMER4 GP16C2T2
/******************************************************************************/
/* UART Peripheral_declaration */
/******************************************************************************/
#define USART0 ((USART_TypeDef *) USART0_BASE)
#define USART1 ((USART_TypeDef *) USART1_BASE)
/******************************************************************************/
/* SPI Peripheral_declaration */
/******************************************************************************/
#define SPI0   ((SPI_TypeDef *)SPI0_BASE)
/******************************************************************************/
/* IIC Peripheral_declaration */
/******************************************************************************/
#define I2C0   ((I2C_TypeDef *)I2C0_BASE)
#define I2C1   ((I2C_TypeDef *)I2C1_BASE)
/******************************************************************************/
/* IWDT WWDT Peripheral_declaration */
/******************************************************************************/
#define WWDT ((WWDT_TypeDef *) WWDT_BASE)
#define IWDT ((IWDT_TypeDef *) IWDT_BASE)
/******************************************************************************/
/* DBGC Peripheral_declaration */
/******************************************************************************/
#define DBGCON ((DBGC_TypeDef *)DBGCON_BASE)
/******************************************************************************/
/* ADC Peripheral_declaration */
/******************************************************************************/
#define ADC0 ((ADC_TypeDef *) ADC0_BASE )

/******************************************************************************/
/* CMP Peripheral_declaration */
/******************************************************************************/
#define ACMP0 ((ACMP_TypeDef *) ACMP0_BASE )
#define ACMP1 ((ACMP_TypeDef *) ACMP1_BASE )
/******************************************************************************/

/******************************************************************************/
/* DMA Peripheral_declaration */
/******************************************************************************/
#define DMA0  ((DMA_TypeDef *) DMA_BASE)
 
/******************************************************************************/
/*P16T Peripheral_declaration */
/******************************************************************************/
#define PIS     ((PIS_TypeDef *) PIS_BASE)
 

#ifdef __cplusplus
}
#endif  
      
#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
