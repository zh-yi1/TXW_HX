/**********************************************************************************
 *
 * @file    md_syscfg.h
 * @brief   SYSCFG module driver.
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

#ifndef __MD_SYSCFG_H__
#define __MD_SYSCFG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------ */
#include "md_utils.h"


/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_SYSCFG SYSCFG
  * @brief SYSCFG module driver
  * @{
  */

/** @defgroup MD_SYSCFG_Public_Macros SYSCFG Public Macros
  * @{
  */
#define SYSCFG_LOCK()       WRITE_REG(SYSCFG->PROT, 0x0U)
#define SYSCFG_UNLOCK()     WRITE_REG(SYSCFG->PROT, 0x55AA6996U)
#define GET_SYSCFG_LOCK()   READ_BIT(SYSCFG->PROT, SYSCFG_PROT_PROT_MSK)

#define MD_BOOT_FROM_BOOT_ROM()                 \
    do {                                \
        SYSCFG_UNLOCK();                    \
        CLEAR_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_BFRMPEN_MSK);   \
        SYSCFG_LOCK();                      \
    } while (0)

#define MD_BOOT_FROM_BOOT_FLASH()                   \
    do {                                \
        SYSCFG_UNLOCK();                    \
        SET_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_BFRMPEN_MSK); \
        SYSCFG_LOCK();                      \
    } while (0)

#define MD_BOOT_FROM_FLASH()                    \
    do {                                \
        SYSCFG_UNLOCK();                    \
        CLEAR_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_BFRMPEN_MSK);   \
        SYSCFG_LOCK();                      \
    } while (0)
/**
  * @}
  */


/** @defgroup MD_SYSCFG_Public_Functions SYSCFG Public Functions
  * @{
  */
/** @defgroup MD_SYSCFG_Public_Functions_Group1 VTOR
  * @{
  */
__INLINE void md_vtor_config(uint32_t offset, type_func_t status)
{
    SYSCFG_UNLOCK();

    if (status)
    {
        MODIFY_REG(SYSCFG->VTOR, SYSCFG_VTOR_VTO_MSK, (offset & ~0x3FU));
        SET_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_VTOEN_MSK);
    }
    else
    {
        CLEAR_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_VTOEN_MSK);
    }

    SYSCFG_LOCK();
    return;
}
/**
  * @}
  */
/** @defgroup MD_SYSCFG_Public_Functions_Group3 TBKCFG
  * @{
  */
/**
  * @brief  Enable clock safety event as the timer brake source
  * @retval None
  */
__STATIC_INLINE void md_syscfg_usb_enable_cssbke(void)
{
    SET_BIT(SYSCFG->TBKCFG, SYSCFG_TBKCFG_CCSBKE_MSK);
}

/**
  * @brief  Disable clock safety event as the timer brake source
  * @retval None
  */
__STATIC_INLINE void md_syscfg_usb_disable_cssbke(void)
{
    CLEAR_BIT(SYSCFG->TBKCFG, SYSCFG_TBKCFG_CCSBKE_MSK);
}

/**
  * @brief  Whether clock safety event is the timer brake source
  * @retval 1-enable, 0-disable
  */
__STATIC_INLINE uint32_t md_syscfg_usb_is_enable_cssbke(void)
{
    return READ_BITS(SYSCFG->TBKCFG, SYSCFG_TBKCFG_CCSBKE_MSK, SYSCFG_TBKCFG_CCSBKE_POS);
}

/**
  * @brief  Enable LVD event as the timer brake source
  * @retval None
  */
__STATIC_INLINE void md_syscfg_usb_enable_lvdbke(void)
{
    SET_BIT(SYSCFG->TBKCFG, SYSCFG_TBKCFG_LVDBKE_MSK);
}

/**
  * @brief  Disable LVD event as the timer brake source
  * @retval None
  */
__STATIC_INLINE void md_syscfg_usb_disable_lvdbke(void)
{
    CLEAR_BIT(SYSCFG->TBKCFG, SYSCFG_TBKCFG_LVDBKE_MSK);
}

/**
  * @brief  Whether LVD event is the timer brake source
  * @retval 1-enable, 0-disable
  */
__STATIC_INLINE uint32_t md_syscfg_usb_is_enable_lvdbke(void)
{
    return READ_BITS(SYSCFG->TBKCFG, SYSCFG_TBKCFG_LVDBKE_MSK, SYSCFG_TBKCFG_LVDBKE_POS);
}

/**
  * @brief  Enable CPU lock event as the timer brake source
  * @retval None
  */
__STATIC_INLINE void md_syscfg_usb_enable_clubke(void)
{
    SET_BIT(SYSCFG->TBKCFG, SYSCFG_TBKCFG_CLUBKE_MSK);
}

/**
  * @brief  Disable CPU lock as the timer brake source
  * @retval None
  */
__STATIC_INLINE void md_syscfg_usb_disable_clubke(void)
{
    CLEAR_BIT(SYSCFG->TBKCFG, SYSCFG_TBKCFG_CLUBKE_MSK);
}

/**
  * @brief  Whether CPU lock is the timer brake source
  * @retval 1-enable, 0-disable
  */
__STATIC_INLINE uint32_t md_syscfg_usb_is_enable_clubke(void)
{
    return READ_BITS(SYSCFG->TBKCFG, SYSCFG_TBKCFG_CLUBKE_MSK, SYSCFG_TBKCFG_CLUBKE_POS);
}
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
