/**********************************************************************************
 *
 * @file    md_pis.h
 * @brief   Header file of PIS module driver.
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

#ifndef __MD_PIS_H__
#define __MD_PIS_H__

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------ */
#include "md_utils.h"
#include "es32f010x.h"

/**
  * @addtogroup Micro_Driver
  * @{
  */

/**
  * @defgroup MD_PIS PIS
  * @brief PIS micro driver
  * @{
  */

/** @defgroup MD_PIS_Public_Types PIS Public Types
  * @{
  */

/**
  * @brief Producer entry
  */
typedef enum
{
    MD_PIS_NON                 = 0x0U,  /**< No async */
    MD_PIS_GPIOA_PIN0          = 0x10U, /**< Pin0, level */
    MD_PIS_GPIOA_PIN1          = 0x11U, /**< Pin1, level */
    MD_PIS_GPIOA_PIN2          = 0x12U, /**< Pin2, level */
    MD_PIS_GPIOA_PIN3          = 0x13U, /**< Pin3, level */
    MD_PIS_GPIOA_PIN4          = 0x14U, /**< Pin4, level */
    MD_PIS_GPIOA_PIN5          = 0x15U, /**< Pin5, level */
    MD_PIS_GPIOA_PIN6          = 0x16U, /**< Pin6, level */
    MD_PIS_GPIOA_PIN7          = 0x17U, /**< Pin7, level */
    MD_PIS_GPIOA_PIN8          = 0x18U, /**< Pin8, level */
    MD_PIS_GPIOA_PIN9          = 0x19U, /**< Pin9, level */
    MD_PIS_GPIOA_PIN10         = 0x1aU, /**< Pin10, level */
    MD_PIS_GPIOA_PIN11         = 0x1bU, /**< Pin11, level */
    MD_PIS_GPIOA_PIN12         = 0x1cU, /**< Pin12, level */
    MD_PIS_GPIOA_PIN13         = 0x1dU, /**< Pin13, level */
    MD_PIS_GPIOA_PIN14         = 0x1eU, /**< Pin14, level */
    MD_PIS_GPIOA_PIN15         = 0x1fU, /**< Pin15, level */
    MD_PIS_GPIOB_PIN0          = 0x20U, /**< Pin0, level */
    MD_PIS_GPIOB_PIN1          = 0x21U, /**< Pin1, level */
    MD_PIS_GPIOB_PIN2          = 0x22U, /**< Pin2, level */
    MD_PIS_GPIOB_PIN3          = 0x23U, /**< Pin3, level */
    MD_PIS_GPIOB_PIN4          = 0x24U, /**< Pin4, level */
    MD_PIS_GPIOB_PIN5          = 0x25U, /**< Pin5, level */
    MD_PIS_GPIOB_PIN6          = 0x26U, /**< Pin6, level */
    MD_PIS_LVD_OUT             = 0x30U, /**< LVD output, level */
    MD_PIS_ACMP_OUT0           = 0x31U, /**< Acmp0 output, level */
    MD_PIS_ACMP_OUT1           = 0x32U, /**< Acmp1 output, level */
    MD_PIS_USART0_RXNE         = 0x40U, /**< USART0 RXNE, pulse */
    MD_PIS_USART0_TXE          = 0x41U, /**< USART0 TXE, pulse */
    MD_PIS_USART0_TX_OUTPUT    = 0x42U, /**< USART0 TX, pulse */
    MD_PIS_USART1_RXNE         = 0x50U, /**< USART1 RXNE, pulse */
    MD_PIS_USART1_TXE          = 0x51U, /**< USART1 TXE, pulse */
    MD_PIS_USART1_TX_OUTPUT    = 0x52U, /**< USART1 TX, pulse */
    MD_PIS_I2C1_RXNE           = 0x60U, /**< I2C1 RXNE, level */
    MD_PIS_I2C1_TXE            = 0x61U, /**< I2C1 TXE, level */
    MD_PIS_SPI_RXNE            = 0x70U, /**< SPI RXNE, pulse */
    MD_PIS_SPI_TXE             = 0x71U, /**< SPI TXE, pulse */
    MD_PIS_LCD_CSS             = 0x71U, /**< SPI CSS, pulse*/
    MD_PIS_I2C0_RXNE           = 0x80U, /**< I2C0 RXNE, level */
    MD_PIS_I2C0_TXE            = 0x81U, /**< I2C0 TXE, level */
    MD_PIS_GP16C2T0_UPDATE       = 0x90U,   /**< GP16C2T0 UPDATE,pulse */
    MD_PIS_GP16C2T0_TRIG         = 0x91U,   /**< GP16C2T0 TRIG,pulse*/
    MD_PIS_GP16C2T0_IC_OC_CH1    = 0x92U,   /**< GP16C2T0 chan1 input catch output compare,pulse*/
    MD_PIS_GP16C2T0_IC_OC_CH2    = 0x93U,   /**< GP16C2T0 chan2 input catch output compare,pulse*/
    MD_PIS_GP16C2T0_TRGOUT       = 0x96U,   /**< GP16C2T0 TRGOUT,level */
    MD_PIS_GP16C2T1_UPDATE       = 0xa0U,   /**< GP16C2T1 UPDATE,pulse */
    MD_PIS_GP16C2T1_TRIG         = 0xa1U,   /**< GP16C2T1 TRIG,pulse */
    MD_PIS_GP16C2T1_IC_OC_CH1    = 0xa2U,   /**< GP16C2T1 chan1 input catch output compare,pulse */
    MD_PIS_GP16C2T1_IC_OC_CH2    = 0xa3U,   /**< GP16C2T1 chan2 input catch output compare,pulse */
    MD_PIS_GP16C2T1_TRGOUT       = 0xa6U,   /**< GP16C2T1 TRGOUT,level*/
    MD_PIS_GP16C2T2_UPDATE       = 0xb0U,   /**< GP16C2T2 UPDATE,pulse  */
    MD_PIS_GP16C2T2_TRIG         = 0xb1U,   /**< GP16C2T2 TRIG,pulse */
    MD_PIS_GP16C2T2_IC_OC_CH1    = 0xb2U,   /**< GP16C2T2 chan1 input catch output compare,pulse */
    MD_PIS_GP16C2T2_IC_OC_CH2    = 0xb3U,   /**< GP16C2T2 chan2 input catch output compare,pulse */
    MD_PIS_GP16C2T2_TRGOUT       = 0xb6U,   /**< GP16C2T2 TRGOUT,level*/
    MD_PIS_AD16C4T_UPDATE       = 0xc0U,    /**< GP16C2T2 UPDATE,pulse  */
    MD_PIS_AD16C4T_TRIG         = 0xc1U,    /**< GP16C2T2 TRIG,pulse */
    MD_PIS_AD16C4T_IC_OC_CH1    = 0xc2U,    /**< GP16C2T2 chan1 input catch output compare,pulse */
    MD_PIS_AD16C4T_IC_OC_CH2    = 0xc3U,    /**< GP16C2T2 chan2 input catch output compare,pulse */
    MD_PIS_AD16C4T_IC_OC_CH3    = 0xc4U,    /**< GP16C2T2 chan3 input catch output compare,pulse */
    MD_PIS_AD16C4T_IC_OC_CH4    = 0xc5U,    /**< GP16C2T2 chan4 input catch output compare,pulse */
    MD_PIS_AD16C4T_TRGOUT       = 0xc6U,    /**< GP16C2T2 TRGOUT,level*/
    MD_PIS_DMA                 = 0xd0U, /**< Dma, pulse ,pulse */
    MD_PIS_ADC_INSERT          = 0xe0U, /**< Adc insert,pulse */
    MD_PIS_ADC_NORMAL          = 0xe1U, /**< Adc normal, pulse */
    MD_PIS_ADC_WDT             = 0xe2U, /**< Adc WDT */
    MD_PIS_BS16TN_UPDATE       = 0xf0U, /**< BS16TN UPDATE ,pulse */
} md_pis_src_t;

/**
  * @brief Consumer entry
  */
typedef enum
{
    MD_PIS_CH1_USART0_RX     = 0x0011U, /** USART0 RX INPUT */
    MD_PIS_CH4_USART1_RX     = 0x0114U, /** USART1 RX INPUT*/
    MD_PIS_CH0_SPI_MISO_INPUT  = 0x0810U,   /** SPI MISO INPUT*/
    MD_PIS_CH0_SPI_MOSI_INPUT  = 0x0810U,   /** SPI_MOSI INPUT */
    MD_PIS_CH1_SPI_CLK         = 0x0911U,   /** SPI_CLK INPUT */

    MD_PIS_CH3_AD16C4T_ITR0  = 0x0033U, /** Tim0 internal trigger 0 */
    MD_PIS_CH3_AD16C4T_ITR1  = 0x0033U, /** Tim0 internal trigger 1 */
    MD_PIS_CH3_AD16C4T_ITR2  = 0x0033U, /** Tim0 internal trigger 2 */
    MD_PIS_CH3_AD16C4T_ITR3  = 0x0033U, /** Tim0 internal trigger 3 */
    MD_PIS_CH0_AD16C4T_CH1  = 0x0000U,  /** Tim0 chan1 input catch*/
    MD_PIS_CH1_AD16C4T_CH2  = 0x0101U,  /** Tim0 chan2 input catch*/
    MD_PIS_CH2_AD16C4T_CH3  = 0x0202U,  /** Tim0 chan3 input catch */
    MD_PIS_CH3_AD16C4T_CH4  = 0x0303U,  /** Tim0 chan4 input catch */
    MD_PIS_CH0_AD16C4T_BRKIN  = 0x0400U,    /** Tim0 break in */

    MD_PIS_CH2_GP16C2T0_ITR0  = 0x0032U,    /** Tim2 internal trigger 0 */
    MD_PIS_CH2_GP16C2T0_ITR1  = 0x0032U,    /** Tim2 internal trigger 1 */
    MD_PIS_CH2_GP16C2T0_ITR2  = 0x0032U,    /** Tim2 internal trigger 2 */
    MD_PIS_CH2_GP16C2T0_ITR3  = 0x0032U,    /** Tim2 internal trigger 3 */
    MD_PIS_CH0_GP16C2T0_CH1  = 0x0800U, /** Tim2 chan1 input catch*/
    MD_PIS_CH1_GP16C2T0_CH2  = 0x0901U, /** Tim2 chan2 input catch*/

    MD_PIS_CH0_GP16C2T1_ITR0  = 0x0030U,    /** Tim3 internal trigger 0 */
    MD_PIS_CH0_GP16C2T1_ITR1  = 0x0030U,    /** Tim3 internal trigger 1 */
    MD_PIS_CH0_GP16C2T1_ITR2  = 0x0030U,    /** Tim3 internal trigger 2 */
    MD_PIS_CH0_GP16C2T1_ITR3  = 0x0030U,    /** Tim3 internal trigger 3 */
    MD_PIS_CH2_GP16C2T1_CH1   = 0x1002U,    /** Tim3 chan1 input catch*/
    MD_PIS_CH3_GP16C2T1_CH2   = 0x1103U,    /** Tim3 chan2 input catch*/

    MD_PIS_CH1_GP16C2T2_ITR0  = 0x0031U,    /** Tim4 internal trigger 0 */
    MD_PIS_CH1_GP16C2T2_ITR1  = 0x0031U,    /** Tim4 internal trigger 1 */
    MD_PIS_CH1_GP16C2T2_ITR2  = 0x0031U,    /** Tim4 internal trigger 2 */
    MD_PIS_CH1_GP16C2T2_ITR3  = 0x0031U,    /** Tim4 internal trigger 3 */
    MD_PIS_CH0_GP16C2T2_CH1   = 0x1800U,    /** Tim4 chan1 input catch*/
    MD_PIS_CH1_GP16C2T2_CH2   = 0x1901U,    /** Tim4 chan2 input catch*/

    MD_PIS_CH4_ADC_NORMAL   = 0x0034U,  /** ADC0 normal transform */
    MD_PIS_CH5_ADC_INSERT   = 0x0035U,  /** ADC0 insert transform */

    MD_PIS_TRIG_RESERVE      = 0xFFFFU, /**< Other Consumer */
} md_pis_trig_t;

/**
  * @brief input source
  */
typedef enum
{
    MD_SRC_NONE    = 0U,    /**< None input source */
    MD_SRC_GPIOA   = 1U,    /**< gpioa source */
    MD_SRC_GPIOB   = 2U,    /**< gpiob source */
    MD_SRC_LVD_CMP = 3U,    /**< lvd or cmp source */
    MD_SRC_USART0  = 4U,    /**< usart0 source */
    MD_SRC_USART1  = 5U,    /**< usart1 source */
    MD_SRC_I2C1    = 6U,    /**< i2c1 source */
    MD_SRC_SPI     = 7U,    /**< SPI source */
    MD_SRC_I2C0    = 8U,    /**< i2c0 source */
    MD_SRC_GP16C2T0 = 9U,   /**< gp16c2t0 source */
    MD_SRC_GP16C2T1 = 10U,  /**< gp16c2t1 source */
    MD_SRC_GP16C2T2 = 11U,  /**< gp16c2t2 source */
    MD_SRC_AD16C4T = 12U,   /**< ad16c4t source */
    MD_SRC_DMA     = 13U,   /**< DMA source */
    MD_SRC_ADC     = 14U,   /**< ADC source */
    MD_SRC_BSTIM0  = 15U,   /**< bstim0 source */
} md_pis_input_src_t;

/**
  * @brief Clock select
  */
typedef enum
{
    MD_PIS_CLK_PCLK1    = 0U,   /**< APB1 peripherals clock */
    MD_PIS_CLK_PCLK2    = 1U,   /**< APB2 peripherals clock */
    MD_PIS_CLK_SYS      = 2U,   /**< AHB peripherals clock */
    MD_PIS_CLK_RESERVE  = 3U,   /**< reserve clock */
} md_pis_clock_t;

/**
  * @brief Level select
  */
typedef enum
{
    MD_PIS_EDGE_NONE    = 0U,   /**< None edge */
    MD_PIS_EDGE_UP      = 1U,   /**< Up edge */
    MD_PIS_EDGE_DOWN    = 2U,   /**< Down edge */
    MD_PIS_EDGE_UP_DOWN = 3U,   /**< Up and down edge */
} md_pis_edge_t;

/**
  * @brief Output style
  */
typedef enum
{
    MD_PIS_OUT_LEVEL = 0U,  /**< Level */
    MD_PIS_OUT_PULSE = 1U,  /**< Pulse */
} md_pis_output_t;
/**
  * @brief Sync select
  */
typedef enum
{
    MD_PIS_SYN_DIRECT         = 0U, /**< Direct */
    MD_PIS_SYN_LEVEL_ASY_APB1 = 1U, /**< Producer level signal and Consumer in APB1 */
    MD_PIS_SYN_LEVEL_ASY_APB2 = 2U, /**< Producer level signal and Consumer in APB2 */
    MD_PIS_SYN_LEVEL_ASY_AHB  = 3U, /**< Producer level signal and Consumer in AHB */
    MD_PIS_SYN_PULSE_ASY_APB1 = 4U, /**< Producer Pulse signal and Consumer in APB1 */
    MD_PIS_SYN_PULSE_ASY_APB2 = 5U, /**< Producer Pulse signal and Consumer in APB2 */
    MD_PIS_SYN_PULSE_ASY_AHB  = 6U, /**< Producer Pulse signal and Consumer in AHB */
} md_pis_syncsel_t;

/**
  * @brief Pis channel
  */
typedef enum
{
    MD_PIS_CH_0 = 0U,   /**< Channel 0 */
    MD_PIS_CH_1 = 1U,   /**< Channel 1 */
    MD_PIS_CH_2 = 2U,   /**< Channel 2 */
    MD_PIS_CH_3 = 3U,   /**< Channel 3 */
    MD_PIS_CH_4 = 4U,   /**< Channel 4 */
    MD_PIS_CH_5 = 5U,   /**< Channel 5 */
} md_pis_ch_t;

/**
  * @brief PIS init structure definition
  */
typedef struct
{
    md_pis_src_t p_src;     /**< Producer entry */
    md_pis_trig_t c_trig;       /**< Consumer entry */
} md_pis_init_t;

/**
  * @brief PIS state structures definition
  */
typedef enum
{
    MD_PIS_STATE_RESET   = 0x00U,   /**< Peripheral is not initialized */
    MD_PIS_STATE_READY   = 0x01U,   /**< Peripheral Initialized and ready for use */
    MD_PIS_STATE_BUSY    = 0x02U,   /**< An internal process is ongoing */
    MD_PIS_STATE_TIMEOUT = 0x03U,   /**< Timeout state */
    MD_PIS_STATE_ERROR   = 0x04U,   /**< Error */
} md_pis_state_t;

/**
  * @brief PIS modulate target
  */
typedef enum
{
    MD_PIS_UART0_TX   = 0U, /**< Modulate uart0 tx */
    MD_PIS_UART1_TX   = 1U, /**< Modulate uart1 tx */
    MD_PIS_UART2_TX   = 2U, /**< Modulate uart2 tx */
    MD_PIS_UART3_TX   = 3U, /**< Modulate uart3 tx */
    MD_PIS_LPUART0_TX = 4U, /**< Modulate lpuart0 tx */
} md_pis_modu_targ_t;

/**
  * @brief PIS modulate level
  */
typedef enum
{
    MD_PIS_LOW_LEVEL  = 0U, /**< Modulate low level */
    MD_PIS_HIGH_LEVEL = 1U, /**< Modulate high level */
} md_pis_modu_level_t;

/**
  * @brief PIS modulate source
  */
typedef enum
{
    MD_PIS_SRC_NONE     = 0U,   /**< Stop modulate */
    MD_PIS_SRC_AD16C4T   = 1U,  /**< Modulate source is AD16C4T */
    MD_PIS_SRC_BUZ      = 2U,   /**< Modulate source is BUZ */
    MD_PIS_SRC_GP16C2T0   = 3U, /**< Modulate source is BS16TN */
    MD_PIS_SRC_GP16C2T1   = 4U, /**< Modulate source is GP16C2T0 */
    MD_PIS_SRC_GP16C2T2   = 5U, /**< Modulate source is GP16C2T1 */
} md_pis_modu_src_t;

/**
  * @brief PIS modulate channel
  */
typedef enum
{
    MD_PIS_TIMER_CH1 = 0U,  /**< Src is TIMERx and choose channel 1 */
    MD_PIS_TIMER_CH2 = 1U,  /**< Src is TIMERx and choose channel 2 */
    MD_PIS_TIMER_CH3 = 2U,  /**< Src is TIMERx and choose channel 3 */
    MD_PIS_TIMER_CH4 = 3U,  /**< Src is TIMERx and choose channel 4 */
} md_pis_modu_channel_t;
/**
  * @}
  */

/** @defgroup MD_PIS_Public_Functions PIS Public Functions
  * @{
  */
/** @defgroup MD_PIS_Public_Functions_Group2 CH_CON
  * @{
  */


/**
  * @brief  Set pis input source.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  src PIS input source.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_input_src(PIS_TypeDef *PISx, md_pis_ch_t channel, md_pis_input_src_t src)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_SRCS_MSK, src << PIS_CH0_CON_SRCS_POSS);
}

/**
  * @brief  Get pis input source.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source @ref md_pis_input_src_t
  */
__STATIC_INLINE uint32_t md_pis_get_input_src(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_SRCS_MSK, PIS_CH0_CON_SRCS_POSS);
}

/**
  * @brief  Set pis input source gpioa.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  pin PIS input source gpioa.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_gpioa(PIS_TypeDef *PISx, md_pis_ch_t channel, uint8_t pina)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, pina << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source gpioa.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source gpioa.
  */
__STATIC_INLINE uint32_t md_pis_get_src_gpioa(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source gpiob.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  pin PIS input source gpiob.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_gpiob(PIS_TypeDef *PISx, md_pis_ch_t channel, uint8_t pinb)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, pinb << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source gpiob.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source gpiob.
  */
__STATIC_INLINE uint32_t md_pis_get_src_gpiob(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source cmp.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  acmp PIS input source cmp.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_cmp(PIS_TypeDef *PISx, md_pis_ch_t channel, uint8_t cmp)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, cmp << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source cmp.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source acmp.
  */
__STATIC_INLINE uint32_t md_pis_get_src_cmp(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source usart0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  uart0 PIS input source usart0.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_usart0(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t usart0)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, usart0 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source usart0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source usart0.
  */
__STATIC_INLINE uint32_t md_pis_get_src_usart0(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source usart1.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  uart1 PIS input source usart1.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_usart1(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t usart1)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, usart1 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source usart1.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source usart1.
  */
__STATIC_INLINE uint32_t md_pis_get_src_usart1(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source spi.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  spi0 PIS input source spi.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_spi(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t spi)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, spi << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source spi.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source spi.
  */
__STATIC_INLINE uint32_t md_pis_get_src_spi(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source i2c0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  i2c0 PIS input source i2c0.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_i2c0(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t i2c0)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, i2c0 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source i2c0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source i2c0.
  */
__STATIC_INLINE uint32_t md_pis_get_src_i2c0(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source tim0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  tim0 PIS input source tim0.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_tim0(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t tim0)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, tim0 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source tim0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source tim0
  */
__STATIC_INLINE uint32_t md_pis_get_src_tim0(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source tim1.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  tim1 PIS input source tim1.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_tim1(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t tim1)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, tim1 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source tim1.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source tim1
  */
__STATIC_INLINE uint32_t md_pis_get_src_tim1(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source tim2.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  tim2 PIS input source tim2.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_tim2(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t tim2)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, tim2 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source tim2.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source tim2
  */
__STATIC_INLINE uint32_t md_pis_get_src_tim2(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source tim3.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  tim3 PIS input source tim3.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_tim3(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t tim3)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, tim3 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source tim3.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source tim3
  */
__STATIC_INLINE uint32_t md_pis_get_src_tim3(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source dma.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  dma PIS input source dma.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_dma(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t dma)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, dma << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source dma.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source dma.
  */
__STATIC_INLINE uint32_t md_pis_get_src_dma(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source adc.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  adc1 PIS input source adc.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_adc(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t adc)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, adc << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source adc.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source adc.
  */
__STATIC_INLINE uint32_t md_pis_get_src_adc(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Set pis input source bstim0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @param  adc1 PIS input source bstim0.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_src_bstim0(PIS_TypeDef *PISx, md_pis_ch_t channel, uint32_t bstim0)
{
    MODIFY_REG(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, bstim0 << PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @brief  Get pis input source bstim0.
  * @param  PISx PIS Instance.
  * @param  channel PIS channel.
  * @retval pis input source bstim0.
  */
__STATIC_INLINE uint32_t md_pis_get_src_bstim0(PIS_TypeDef *PISx, md_pis_ch_t channel)
{
    return READ_BITS(PISx->CH_CON[channel], PIS_CH0_CON_MSIGS_MSK, PIS_CH0_CON_MSIGS_POSS);
}

/**
  * @}
  */
/** @defgroup MD_PIS_Public_Functions_Group CH_OER
  * @{
  */

/**
  * @brief  Enable pis channel 5 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_ch5_output(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->CH_OER, PIS_CH_OER_CH5OE_MSK);
}

/**
  * @brief  Disable pis channel 5 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_disable_ch5_output(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->CH_OER, PIS_CH_OER_CH5OE_MSK);
}

/**
  * @brief  Indicate if pis channel 5 output to port is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_ch5_output(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->CH_OER, PIS_CH_OER_CH5OE_MSK) == (PIS_CH_OER_CH5OE_MSK));
}

/**
  * @brief  Enable pis channel 4 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_ch4_output(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->CH_OER, PIS_CH_OER_CH4OE_MSK);
}

/**
  * @brief  Disable pis channel 4 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_disable_ch4_output(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->CH_OER, PIS_CH_OER_CH4OE_MSK);
}

/**
  * @brief  Indicate if pis channel 4 output to port is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_ch4_output(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->CH_OER, PIS_CH_OER_CH4OE_MSK) == (PIS_CH_OER_CH4OE_MSK));
}

/**
  * @brief  Enable pis channel 3 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_ch3_output(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->CH_OER, PIS_CH_OER_CH3OE_MSK);
}

/**
  * @brief  Disable pis channel 3 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_disable_ch3_output(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->CH_OER, PIS_CH_OER_CH3OE_MSK);
}

/**
  * @brief  Indicate if pis channel 3 output to port is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_ch3_output(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->CH_OER, PIS_CH_OER_CH3OE_MSK) == (PIS_CH_OER_CH3OE_MSK));
}

/**
  * @brief  Enable pis channel 2 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_ch2_output(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->CH_OER, PIS_CH_OER_CH2OE_MSK);
}

/**
  * @brief  Disable pis channel 2 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_disable_ch2_output(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->CH_OER, PIS_CH_OER_CH2OE_MSK);
}

/**
  * @brief  Indicate if pis channel 2 output to port is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_ch2_output(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->CH_OER, PIS_CH_OER_CH2OE_MSK) == (PIS_CH_OER_CH2OE_MSK));
}

/**
  * @brief  Enable pis channel 1 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_ch1_output(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->CH_OER, PIS_CH_OER_CH1OE_MSK);
}

/**
  * @brief  Disable pis channel 1 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_disable_ch1_output(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->CH_OER, PIS_CH_OER_CH1OE_MSK);
}

/**
  * @brief  Indicate if pis channel 1 output to port is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_ch1_output(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->CH_OER, PIS_CH_OER_CH1OE_MSK) == (PIS_CH_OER_CH1OE_MSK));
}

/**
  * @brief  Enable pis channel 0 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_ch0_output(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->CH_OER, PIS_CH_OER_CH0OE_MSK);
}

/**
  * @brief  Disable pis channel 0 output to port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_disable_ch0_output(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->CH_OER, PIS_CH_OER_CH0OE_MSK);
}

/**
  * @brief  Indicate if pis channel 0 output to port is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_ch0_output(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->CH_OER, PIS_CH_OER_CH0OE_MSK) == (PIS_CH_OER_CH0OE_MSK));
}
/**
  * @}
  */
/** @defgroup MD_PIS_Public_Functions_Group4 TAR_CON0
  * @verbatim
      In PIS module, for the convenience of code maintenance,
      TIMERx is used to indicate the sequence of the timer peripheral.
      Different product series TIMERx represent different meanings:
      1. For ES32F36xx series:
      TIMER0 ----> AD16C4T0
      TIMER1 ----> GP16C2T0
      TIMER2 ----> GP16C2T1
      TIMER3 ----> GP16C2T2
    @endverbatim
  * @{
  */

/**
  * @brief  Set pis tim3 input capture ch2 chose ch1.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim3_ch2in_ch1(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T2_CH2IN_SEL_MSK);
}

/**
  * @brief  Set pis tim3 input capture ch2 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim3_ch2in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T2_CH2IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim3 input capture ch2 chose ch1 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim3_ch2in_ch1(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T2_CH2IN_SEL_MSK) == (PIS_TAR_CON0_GP16C2T2_CH2IN_SEL_MSK));
}

/**
  * @brief  Set pis tim3 input capture ch1 chose ch0.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim3_ch1in_ch0(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T2_CH1IN_SEL_MSK);
}

/**
  * @brief  Set pis tim3 input capture ch1 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim3_ch1in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T2_CH1IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim3 input capture ch1 chose ch0 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim3_ch1in_ch0(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T2_CH1IN_SEL_MSK) == (PIS_TAR_CON0_GP16C2T2_CH1IN_SEL_MSK));
}

/**
  * @brief  Set pis tim2 input capture ch2 chose ch3.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim2_ch2in_ch3(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T1_CH2IN_SEL_MSK);
}

/**
  * @brief  Set pis tim2 input capture ch2 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim2_ch2in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T1_CH2IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim2 input capture ch2 chose ch3 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim2_ch2in_ch3(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T1_CH2IN_SEL_MSK) == (PIS_TAR_CON0_GP16C2T1_CH2IN_SEL_MSK));
}

/**
  * @brief  Set pis tim2 input capture ch1 chose ch2.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim2_ch1in_ch2(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T1_CH1IN_SEL_MSK);
}

/**
  * @brief  Set pis tim2 input capture ch1 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim2_ch1in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T1_CH1IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim2 input capture ch1 chose ch2 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim2_ch1in_ch2(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T1_CH1IN_SEL_MSK) == (PIS_TAR_CON0_GP16C2T1_CH1IN_SEL_MSK));
}

/**
  * @brief  Set pis tim1 input capture ch2 chose ch1.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim1_ch2in_ch1(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T0_CH2IN_SEL_MSK);
}

/**
  * @brief  Set pis tim1 input capture ch2 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim1_ch2in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T0_CH2IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim1 input capture ch2 chose ch1 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim1_ch2in_ch1(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T0_CH2IN_SEL_MSK) == (PIS_TAR_CON0_GP16C2T0_CH2IN_SEL_MSK));
}

/**
  * @brief  Set pis tim1 input capture ch1 chose ch0.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim1_ch1in_ch0(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T0_CH1IN_SEL_MSK);
}

/**
  * @brief  Set pis tim1 input capture ch1 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim1_ch1in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T0_CH1IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim1 input capture ch1 chose ch0 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim1_ch1in_ch0(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_GP16C2T0_CH1IN_SEL_MSK) == (PIS_TAR_CON0_GP16C2T0_CH1IN_SEL_MSK));
}
/**
  * @brief  Set pis tim0 input capture brkin chose ch0.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_brkin_ch0(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_BRKIN_SEL_MSK);
}

/**
  * @brief  Set pis tim0 input capture brkin chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_brkin_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_BRKIN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim0 input capture brkin chose ch0 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim0_brkin_ch0(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_BRKIN_SEL_MSK) == (PIS_TAR_CON0_AD16C4T0_BRKIN_SEL_MSK));
}
/**
  * @brief  Set pis tim0 input capture ch4 chose ch3.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch4in_ch3(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_CH4IN_SEL_MSK);
}

/**
  * @brief  Set pis tim0 input capture ch4 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch4in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_CH4IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim0 input capture ch4 chose ch3 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim0_ch4in_ch3(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_CH4IN_SEL_MSK) == (PIS_TAR_CON0_AD16C4T0_CH4IN_SEL_MSK));
}

/**
  * @brief  Set pis tim0 input capture ch3 chose ch2.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch3in_ch2(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_CH3IN_SEL_MSK);
}

/**
  * @brief  Set pis tim0 input capture ch3 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch3in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_CH3IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim0 input capture ch3 chose ch2 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim0_ch3in_ch2(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_CH3IN_SEL_MSK) == (PIS_TAR_CON0_AD16C4T0_CH3IN_SEL_MSK));
}

/**
  * @brief  Set pis tim0 input capture ch2 chose ch1.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch2in_ch1(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_CH2IN_SEL_MSK);
}

/**
  * @brief  Set pis tim0 input capture ch2 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch2in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_CH2IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim0 input capture ch2 chose ch1 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim0_ch2in_ch1(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_CH2IN_SEL_MSK) == (PIS_TAR_CON0_AD16C4T0_CH2IN_SEL_MSK));
}

/**
  * @brief  Set pis tim0 input capture ch1 chose ch0.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch1in_ch0(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_CH1IN_SEL_MSK);
}

/**
  * @brief  Set pis tim0 input capture ch1 chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_tim0_ch1in_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_CH1IN_SEL_MSK);
}

/**
  * @brief  Indicate if pis tim0 input capture ch1 chose ch0 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_tim0_ch1in_ch0(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON0, PIS_TAR_CON0_AD16C4T0_CH1IN_SEL_MSK) == (PIS_TAR_CON0_AD16C4T0_CH1IN_SEL_MSK));
}
/**
  * @}
  */
/** @defgroup MD_PIS_Public_Functions_Group5 TAR_CON1
  * @{
  */
/**
  * @brief  Set pis spi1 clk input chose ch1.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_spi_clk_ch1(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI_CLK_SEL_MSK);
}

/**
  * @brief  Set pis spi1 clk input chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_spi_clk_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI_CLK_SEL_MSK);
}

/**
  * @brief  Indicate if pis spi1 clk input chose ch1 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_spi_clk_ch1(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI_CLK_SEL_MSK) == (PIS_TAR_CON1_SPI_CLK_SEL_MSK));
}

/**
  * @brief  Set pis spi1 rx input chose ch0.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_spi_rx_ch0(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI_RX_SEL_MSK);
}

/**
  * @brief  Set pis spi1 rx input chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_spi_rx_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI_RX_SEL_MSK);
}

/**
  * @brief  Indicate if pis spi1 rx input chose ch7 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_spi_rx_ch0(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON1, PIS_TAR_CON1_SPI_RX_SEL_MSK) == (PIS_TAR_CON1_SPI_RX_SEL_MSK));
}

///**
//  * @brief  Set pis usart2 rx input chose ch11.
//  * @param  PISx PIS Instance.
//  * @retval None
//  */
//__STATIC_INLINE void md_pis_enable_usart2_rx_ch11(PIS_TypeDef *PISx)
//{
//  SET_BIT(PISx->TAR_CON1, PIS_TAR_CON1_USART2_RXD_SEL_MSK);
//}

///**
//  * @brief  Set pis usart2 rx input chose port.
//  * @param  PISx PIS Instance.
//  * @retval None
//  */
//__STATIC_INLINE void md_pis_enable_uart2_rx_port(PIS_TypeDef *PISx)
//{
//  CLEAR_BIT(PISx->TAR_CON1, PIS_TAR_CON1_USART2_RXD_SEL_MSK);
//}

///**
//  * @brief  Indicate if pis usart2 rx input chose ch11 is enabled
//  * @param  PISx PIS Instance.
//  * @retval State of bit (1 or 0).
//  */
//__STATIC_INLINE uint32_t md_pis_is_enabled_uart2_rx_ch11(PIS_TypeDef *PISx)
//{
//  return (uint32_t)(READ_BIT(PISx->TAR_CON1, PIS_TAR_CON1_USART2_RXD_SEL_MSK) == (PIS_TAR_CON1_USART2_RXD_SEL_MSK));
//}

/**
  * @brief  Set pis usart1 rx input chose ch4.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_usart1_rx_ch4(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON1, PIS_TAR_CON1_USART1_RXD_SEL_MSK);
}

/**
  * @brief  Set pis usart1 rx input chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_usart1_rx_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON1, PIS_TAR_CON1_USART1_RXD_SEL_MSK);
}

/**
  * @brief  Indicate if pis usart1 rx input chose ch4 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_usart1_rx_ch4(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON1, PIS_TAR_CON1_USART1_RXD_SEL_MSK) == (PIS_TAR_CON1_USART1_RXD_SEL_MSK));
}

/**
  * @brief  Set pis usart0 rx input chose ch1.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_usart0_rx_ch1(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TAR_CON1, PIS_TAR_CON1_USART0_RXD_SEL_MSK);
}

/**
  * @brief  Set pis usart0 rx input chose port.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_enable_usart0_rx_port(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TAR_CON1, PIS_TAR_CON1_USART0_RXD_SEL_MSK);
}

/**
  * @brief  Indicate if pis usart0 rx input chose ch1 is enabled
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_enabled_usart0_rx_ch1(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TAR_CON1, PIS_TAR_CON1_USART0_RXD_SEL_MSK) == (PIS_TAR_CON1_USART0_RXD_SEL_MSK));
}
/**
  * @}
  */
/** @defgroup MD_PIS_Public_Functions_Group6 USART0_TXMCR
  * @{
  */
/**
  * @brief  Set pis usart0 tx modulation level high.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_usart0_tx_mod_high(PIS_TypeDef *PISx)
{
    SET_BIT(PISx->TXMCR, PIS_TXMCR_TXMLVLS_MSK);
}

/**
  * @brief  Set pis usart0 tx modulation level low.
  * @param  PISx PIS Instance.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_usart0_tx_mod_low(PIS_TypeDef *PISx)
{
    CLEAR_BIT(PISx->TXMCR, PIS_TXMCR_TXMLVLS_MSK);
}

/**
  * @brief  Indicate if pis usart0 tx modulation level high is set
  * @param  PISx PIS Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pis_is_set_usart0_tx_mod_high(PIS_TypeDef *PISx)
{
    return (uint32_t)(READ_BIT(PISx->TXMCR, PIS_TXMCR_TXMLVLS_MSK) == (PIS_TXMCR_TXMLVLS_MSK));
}

/**
  * @brief  Set pis usart0 modulation source.
  * @param  PISx PIS Instance.
  * @param  src PIS usart0 modulation source.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_usart0_mod_src(PIS_TypeDef *PISx, md_pis_modu_src_t src)
{
    MODIFY_REG(PISx->TXMCR, PIS_TXMCR_TXMSS_MSK, src << PIS_TXMCR_TXMSS_POSS);
}

/**
  * @brief  Get pis usart0 modulation source.
  * @param  PISx PIS Instance.
  * @retval usart0 modulation source @ref md_pis_modu_src_t
  */
__STATIC_INLINE uint32_t md_pis_get_usart0_mod_src(PIS_TypeDef *PISx)
{
    return READ_BITS(PISx->TXMCR, PIS_TXMCR_TXMSS_MSK, PIS_TXMCR_TXMSS_POSS);
}

/**
  * @brief  Set pis usart0 modulation timx channel.
  * @param  PISx PIS Instance.
  * @param  channel PIS timx modulation channel.
  * @retval None
  */
__STATIC_INLINE void md_pis_set_usart0_mod_tim_channel(PIS_TypeDef *PISx, md_pis_modu_channel_t channel)
{
    MODIFY_REG(PISx->TXMCR, PIS_TXMCR_TXSIGS_MSK, channel << PIS_TXMCR_TXSIGS_POSS);
}

/**
  * @brief  Get pis usart0 timx modulation channel.
  * @param  PISx PIS Instance.
  * @retval uart0 timx modulation channel @ref md_pis_modu_channel_t
  */
__STATIC_INLINE uint32_t md_pis_get_usart0_mod_tim_channel(PIS_TypeDef *PISx)
{
    return READ_BITS(PISx->TXMCR, PIS_TXMCR_TXSIGS_MSK, PIS_TXMCR_TXSIGS_POSS);
}

/**
  * @}
  */
/** @defgroup MD_PIS_Public_Functions_Group1 Initialization
  * @{
  */
extern void md_dma_reset(void);
extern md_status_t md_pis_init(md_pis_init_t *init);
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
