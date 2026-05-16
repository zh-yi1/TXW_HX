/**********************************************************************************
 *
 * @file    md_rmu.h
 * @brief   Header file of RMU module driver.
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


#ifndef __MD_RMU_H__
#define __MD_RMU_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------ */
#include "md_utils.h"
//#include "type.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_RMU RMU
  * @brief RMU micro driver
  * @{
  */

/** @defgroup MD_RMU_Public_Types RMU Public Types
  * @{
  */

/**
  * @brief Standby wakeup port select
  */
typedef enum
{
    MD_RMU_BORFLT_1 = 0x1U, /**< 1 cycle  */
    MD_RMU_BORFLT_2 = 0x2U, /**< 2 cycles */
    MD_RMU_BORFLT_3 = 0x3U, /**< 3 cycles */
    MD_RMU_BORFLT_4 = 0x4U, /**< 4 cycles */
    MD_RMU_BORFLT_5 = 0x5U, /**< 5 cycles */
    MD_RMU_BORFLT_6 = 0x6U, /**< 6 cycles */
    MD_RMU_BORFLT_7 = 0x7U, /**< 7 cycles */
} md_rmu_bor_filter_t;

/**
  * @brief RMU BOR voltage
  */
typedef enum
{
    MD_RMU_VOL_1_9  = 0x0U, /**< 1.9V */
    MD_RMU_VOL_2_1  = 0x1U, /**< 2.1V */
    MD_RMU_VOL_2_5  = 0x2U, /**< 2.5V */
    MD_RMU_VOL_3_1  = 0x3U, /**< 3.1V */
} md_rmu_bor_vol_t;

/**
  * @brief RMU reset status
  */
typedef enum
{
    MD_RMU_RST_POR    = (1U << 0),  /**< POR */
    MD_RMU_RST_WAKEUP = (1U << 1),  /**< WAKEUP */
    MD_RMU_RST_BOR    = (1U << 2),  /**< BOR */
    MD_RMU_RST_NMRST  = (1U << 3),  /**< NMRST */
    MD_RMU_RST_IWDT   = (1U << 4),  /**< IWDT */
    MD_RMU_RST_WWDT   = (1U << 5),  /**< WWDT */
    MD_RMU_RST_LOCKUP = (1U << 6),  /**< LOCKUP */
    MD_RMU_RST_CHIP   = (1U << 7),  /**< CHIP */
    MD_RMU_RST_MCU    = (1U << 8),  /**< MCU */
    MD_RMU_RST_CPU    = (1U << 9),  /**< CPU */
    MD_RMU_RST_CFG    = (1U << 10), /**< CFG */
    MD_RMU_RST_CFGERR = (1U << 16), /**< CFG Error */
    MD_RMU_RST_ALL    = (0xFFFFFU), /**< ALL */
} md_rmu_state_t;

/**
  * @brief RMU periperal select bit
  * @verbatim
      In this module, for the convenience of code maintenance,
      TIMERx is used to indicate the sequence of the timer peripheral.
      Different product series TIMERx represent different meanings:
      1. For ES32F36xx series:
      TIMER0 ----> AD16C4T0
      TIMER1 ----> AD16C4T1
      TIMER2 ----> GP32C4T0
      TIMER3 ----> GP32C4T1
      TIMER4 ----> BS16T0
      TIMER5 ----> BS16T1
      TIMER6 ----> GP16C4T0
      TIMER7 ----> GP16C4T1

      2. For ES32F393x/ES32F336x/ES32F392x series:
      TIMER0 ----> GP16C4T0
      TIMER1 ----> GP16C4T1
      TIMER2 ----> GP32C4T0
      TIMER3 ----> GP32C4T1
      TIMER4 ----> BS16T0
      TIMER5 ----> BS16T1
      TIMER6 ----> GP16C4T2
      TIMER7 ----> GP16C4T3
    @endverbatim
  */
typedef enum
{
    MD_RMU_PERH_GPIO    = (1U << 0),        /**< AHB1: GPIO */
    MD_RMU_PERH_CRC     = (1U << 1),        /**< AHB1: CRC */
    MD_RMU_PERH_PIS     = (1U << 5),        /**< AHB1: PIS */
    MD_RMU_PERH_CHIP    = (1U << 0)  | (1U << 27),  /**< AHB2: CHIP */
    MD_RMU_PERH_CPU     = (1U << 1)  | (1U << 27),  /**< AHB2: CPU */
    MD_RMU_PERH_AD16C4T  = (1U << 0)  | (1U << 28), /**< APB: AD16C4T */
    MD_RMU_PERH_BS16T    = (1U << 1)  | (1U << 28), /**< APB: BS16T */
    MD_RMU_PERH_GP16C2T0 = (1U << 2)  | (1U << 28), /**< APB: GP16C2T0 */
    MD_RMU_PERH_GP16C2T1 = (1U << 3)  | (1U << 28), /**< APB: GP16C2T1 */
    MD_RMU_PERH_GP16C2T2 = (1U << 4)  | (1U << 28), /**< APB: GP16C2T2 */

    MD_RMU_PERH_USART0   = (1U << 12) | (1U << 28), /**< APB: USART0 */
    MD_RMU_PERH_USART1   = (1U << 13) | (1U << 28), /**< APB: USART1 */
    MD_RMU_PERH_SPI      = (1U << 16) | (1U << 28), /**< APB: SPI */

    MD_RMU_PERH_I2C0    = (1U << 20) | (1U << 28),  /**< APB: I2C0 */
    MD_RMU_PERH_I2C1    = (1U << 21) | (1U << 28),  /**< APB: I2C1 */
    MD_RMU_PERH_WWDT    = (1U << 22) | (1U << 28),  /**< APB: WWDT */
    MD_RMU_PERH_IWDT    = (1U << 23) | (1U << 28),  /**< APB: IWDT */
    MD_RMU_PERH_DBGCON  = (1U << 24) | (1U << 28),  /**< APB: DBGCON */
    MD_RMU_PERH_ADC     = (1U << 25) | (1U << 28),  /**< APB: ADC */
    MD_RMU_PERH_ACMP0   = (1U << 26) | (1U << 28),  /**< APB: ACMP0 */
    MD_RMU_PERH_ACMP1   = (1U << 27) | (1U << 28),  /**< APB: ACMP1 */

} md_rmu_peripheral_t;
/**
  * @}
  */

/** @defgroup MD_RMU_Public_Functions RMU Public Functions
  * @{
  */
/** @defgroup MD_RMU_Public_Functions_Group2 CR
  * @{
  */
/**
  * @brief  Set BOR threshold voltage.
  * @param  vol for BOR threshold.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_set_bor_voltage(md_rmu_bor_vol_t vol)
{
    MODIFY_REG(RMU->CR, RMU_CR_BORVS_MSK, vol << RMU_CR_BORVS_POSS);
}

/**
  * @brief  Get BOR threshold voltage.
  * @retval Voltage for BOR threshold.
  */
__STATIC_INLINE uint32_t md_rmu_get_bor_voltage(void)
{
    return READ_BITS(RMU->CR, RMU_CR_BORVS_MSK, RMU_CR_BORVS_POSS);
}

/**
  * @brief  Set period for BOR filter.
  * @param  period for BOR filter.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_set_bor_filter_period(md_rmu_bor_filter_t period)
{
    MODIFY_REG(RMU->CR, RMU_CR_BORFLT_MSK, period << RMU_CR_BORFLT_POSS);
}

/**
  * @brief  Enable rmu BOR.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_bor(void)
{
    SET_BIT(RMU->CR, RMU_CR_BOREN_MSK);
}


/**
  * @brief  Disable rmu BOR.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_disable_bor(void)
{
    CLEAR_BIT(RMU->CR, RMU_CR_BOREN_MSK);
}

/**
  * @brief  Check if rmu is enable bor.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_enable_bor(void)
{
    return (READ_BIT(RMU->CR, RMU_CR_BOREN_MSK) == (RMU_CR_BOREN_MSK));
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group3 RSTSR
  * @{
  */
/**
  * @brief  Get rmu configuration byte flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_cfgerr(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_CFGERR_MSK) == (RMU_RSTSR_CFGERR_MSK));
}

/**
  * @brief  Get rmu configuration byte reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_cfg(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_CFG_MSK) == (RMU_RSTSR_CFG_MSK));
}

/**
  * @brief  Get rmu cpu reset by soft flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_cpu(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_CPU_MSK) == (RMU_RSTSR_CPU_MSK));
}

/**
  * @brief  Get rmu mcu reset by soft flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_mcu(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_MCU_MSK) == (RMU_RSTSR_MCU_MSK));
}

/**
  * @brief  Get rmu chip reset by soft flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_rmu(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_CHIP_MSK) == (RMU_RSTSR_CHIP_MSK));
}

/**
  * @brief  Get rmu lockup reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_lockup(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_LOCKUP_MSK) == (RMU_RSTSR_LOCKUP_MSK));
}

/**
  * @brief  Get rmu wwdt reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_wwdt(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_WWDT_MSK) == (RMU_RSTSR_WWDT_MSK));
}

/**
  * @brief  Get rmu iwdt reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_iwdt(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_IWDT_MSK) == (RMU_RSTSR_IWDT_MSK));
}

/**
  * @brief  Get rmu nmrst reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_nmrst(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_NMRST_MSK) == (RMU_RSTSR_NMRST_MSK));
}

/**
  * @brief  Get rmu bor reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_bor(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_BOR_MSK) == (RMU_RSTSR_BOR_MSK));
}

///**
//  * @brief  Get rmu wake up reset flag.
//  * @retval State of bit (1 or 0).
//  */
//__STATIC_INLINE uint32_t md_rmu_is_active_flag_wakeup(void)
//{
//  return (READ_BIT(RMU->RSTSR, RMU_RSTSR_WAKEUP_MSK) == (RMU_RSTSR_WAKEUP_MSK));
//}

/**
  * @brief  Get rmu por reset flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_rmu_is_active_flag_por(void)
{
    return (READ_BIT(RMU->RSTSR, RMU_RSTSR_POR_MSK) == (RMU_RSTSR_POR_MSK));
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group4 CRSTSR
  * @{
  */
/**
  * @brief  Clear rmu configuration byte reset flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_cfg(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_CFG_MSK);
}

/**
  * @brief  Clear rmu cpu reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_cpu(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_CPU_MSK);
}

/**
  * @brief  Clear rmu mcu reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_mcu(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_MCU_MSK);
}

/**
  * @brief  Clear rmu chip reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_chip(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_CHIP_MSK);
}

/**
  * @brief  Clear rmu lockup reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_lockup(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_LOCKUP_MSK);
}

/**
  * @brief  Clear rmu wwdt reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_wwdt(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_WWDT_MSK);
}

/**
  * @brief  Clear rmu iwdt reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_iwdt(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_IWDT_MSK);
}

/**
  * @brief  Clear rmu nmrst reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_nmrst(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_NMRST_MSK);
}

/**
  * @brief  Clear rmu bor reset by soft flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_bor(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_BOR_MSK);
}

///**
//  * @brief  Clear rmu wakeup reset flag.
//  * @retval None.
//  */
//__STATIC_INLINE void md_rmu_clear_flag_wakeup(void)
//{
//  SET_BIT(RMU->CRSTSR, RMU_CRSTSR_WAKEUP_MSK);
//}

/**
  * @brief  Clear rmu por reset flag.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_clear_flag_por(void)
{
    SET_BIT(RMU->CRSTSR, RMU_CRSTSR_POR_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group5 AHB1RSTR
  * @{
  */
/**
  * @brief  Reset pis periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_pis_reset(void)
{
    SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_PISRST_MSK);
}

/**
  * @brief  Reset crc periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_crc_reset(void)
{
    SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_CRCRST_MSK);
}

/**
  * @brief  Reset gpio periperal which depend on AHB1 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_gpio_reset(void)
{
    SET_BIT(RMU->AHB1RSTR, RMU_AHB1RSTR_GPIORST_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group6 AHB2RSTR
  * @{
  */
/**
  * @brief  Reset kernel processor which depend on AHB2 bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_cpu_reset(void)
{
    SET_BIT(RMU->AHB2RSTR, RMU_AHB2RSTR_CPURST_MSK);
}

/**
  * @brief  Reset full chip .
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_chip_reset(void)
{
    SET_BIT(RMU->AHB2RSTR, RMU_AHB2RSTR_CHIPRST_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group7 APBRSTR
  * @{
  */
/**
  * @brief  Reset acmp1 periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_acmp1_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_ACMP1RST_MSK);
}
/**
  * @brief  Reset acmp0 periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_acmp0_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_ACMP0RST_MSK);
}
/**
  * @brief  Reset adc periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_adc_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_ADCRST_MSK);
}

/**
  * @brief  Reset dbgcon periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_dbgcon_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_DBGCONRST_MSK);
}

/**
  * @brief  Reset iwdt periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_iwdt_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_IWDTRST_MSK);
}

/**
  * @brief  Reset wwdt periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_wwdt_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_WWDTRST_MSK);
}

/**
  * @brief  Reset i2c1 periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_i2c1_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_I2C1RST_MSK);
}

/**
  * @brief  Reset i2c0 periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_i2c0_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_I2C0RST_MSK);
}

/**
  * @brief  Reset spi periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_spi_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_SPI0RST_MSK);
}


/**
  * @brief  Reset usart2 periperal which depend on APB bus.
  * @retval None.
  */
//__STATIC_INLINE void md_rmu_enable_usart2_reset(void)
//{
//  SET_BIT(RMU->APBRSTR, RMU_APBRSTR_USART2RST_MSK);
//}

/**
  * @brief  Reset usart1 periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_usart1_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_USART1RST_MSK);
}

/**
  * @brief  Reset usart0 periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_usart0_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_USART0RST_MSK);
}

/**
  * @brief  Reset gp16c2t2 periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_gp16c2t2_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_GP16C2T2RST_MSK);
}

/**
  * @brief  Reset gp16c2t1 periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_gp16c2t1_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_GP16C2T1RST_MSK);
}

/**
  * @brief  Reset gp16c2t0 periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_gp16c2t0_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_GP16C2T0RST_MSK);
}

/**
  * @brief  Reset bs16t periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_bs16t_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_BS16T0RST_MSK);
}

/**
  * @brief  Reset ad16c4t periperal which depend on APB bus.
  * @retval None.
  */
__STATIC_INLINE void md_rmu_enable_ad16c4t_reset(void)
{
    SET_BIT(RMU->APBRSTR, RMU_APBRSTR_AD16C4T0RST_MSK);
}
/**
  * @}
  */
/** @defgroup MD_RMU_Public_Functions_Group1 Initialization
  * @{
  */
extern void md_rmu_reset(void);
extern void md_rmu_bor_config(md_rmu_bor_filter_t flt, md_rmu_bor_vol_t vol, type_func_t state);
extern uint32_t md_rmu_get_reset_status(md_rmu_state_t state);
extern void md_rmu_clear_reset_status(md_rmu_state_t state);
extern void md_rmu_reset_periperal(md_rmu_peripheral_t perh);
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
