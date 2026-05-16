/**********************************************************************************
 *
 * @file    md_pmu.h
 * @brief   Header file of PMU module driver.
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

#ifndef __MD_PMU_H__
#define __MD_PMU_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------ */
#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_PMU PMU
  * @brief PMU micro driver
  * @{
  */

/** @defgroup MD_PMU_Public_Types PMU Public Types
  * @{
  */

/**
  * @brief Low power mode
  */
typedef enum
{
    MD_PMU_LP_SLEEP = 0x0U,         /**< sleep */
    MD_PMU_LP_STOP = 0x1U           /**< stop */
} md_pmu_lp_mode_t;

/**
  * @brief LVD voltage select
  */
typedef enum
{
    MD_PMU_LVD_VOL_SEL_2_2 = 0x0U,  /**< 2.2V ~ 2.25V */
    MD_PMU_LVD_VOL_SEL_2_4 = 0x1U,  /**< 2.4V ~ 2.45V */
    MD_PMU_LVD_VOL_SEL_2_6 = 0x2U,  /**< 2.6V ~ 2.65V */
    MD_PMU_LVD_VOL_SEL_2_8 = 0x3U,  /**< 2.8V ~ 2.85V */
    MD_PMU_LVD_VOL_SEL_3_0 = 0x4U,  /**< 3.0V ~ 3.05V */
    MD_PMU_LVD_VOL_SEL_3_6 = 0x5U,  /**< 3.6V ~ 3.65V */
    MD_PMU_LVD_VOL_SEL_4_0 = 0x6U,  /**< 4.0V ~ 4.05V */
    MD_PMU_LVD_VOL_SEL_4_6 = 0x7U,  /**< 4.6V ~ 4.65V */
} md_pmu_lvd_voltage_sel_t;

/**
  * @brief LVD trigger mode
  */
typedef enum
{
    MD_PMU_LVD_TRIGGER_RISING_EDGE    = 0x0U,   /**< Rising edge */
    MD_PMU_LVD_TRIGGER_FALLING_EDGE   = 0x1U,   /**< Falling edge */
    MD_PMU_LVD_TRIGGER_HIGH_LEVEL     = 0x2U,   /**< High level */
    MD_PMU_LVD_TRIGGER_LOW_LEVEL      = 0x3U,   /**< Low level */
    MD_PMU_LVD_TRIGGER_RISING_FALLING = 0x4U,   /**< Rising and falling edge */
} md_pmu_lvd_trigger_mode_t;

/**
  * @}
  */

/** @defgroup MD_PMU_Public_Functions PMU Public Functions
  * @{
  */
/** @defgroup MD_PMU_Public_Functions_Group2 CR
  * @{
  */

/**
  * @brief  Clear wuf flag.
  * @retval None
  */
__STATIC_INLINE void md_pmu_clear_flag_cwuf(void)
{
    SET_BIT(PMU->CR, PMU_CR_CWUF_MSK);
}

/**
  * @brief  Set VR clock enable.
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_vr_clk_enable_vroscen(void)
{
    SET_BIT(PMU->CR, PMU_CR_VROSCEN_MSK);
}
/**
  * @brief  Set VR clock disable.
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_vr_clk_disable_vroscen(void)
{
    CLEAR_BIT(PMU->CR, PMU_CR_VROSCEN_MSK);
}
/**
  * @brief  check if VR clock enable.
  * @retval Status:
  *         - 0: DISABLE
  *         - 1: ENABLE
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_vr_clk(void)
{
    return (READ_BIT(PMU->CR, PMU_CR_VROSCEN_MSK) == PMU_CR_VROSCEN_MSK);
}
/**
  * @brief  Set the ldo voltage in lowpower mode.
  * @param  voltage:
  *           0x0 - 1.3V
  *           0x1 - 1.4V
  *           0x2 - 1.5V
  *           0x3 - 1.6V
  * @retval None
  */
__STATIC_INLINE void md_pmu_set_ldo_mode(uint32_t voltage)
{
    MODIFY_REG(PMU->CR, PMU_CR_LPVS_MSK, (voltage << PMU_CR_LPVS_POSS));
}
/**
  * @brief  Get ldo voltage in lowpower mode.
  * @retval ldo voltage in lowpower mode.
  */
__STATIC_INLINE uint32_t md_pmu_get_ldo(void)
{
    return (READ_BITS(PMU->CR, PMU_CR_LPVS_MSK, PMU_CR_LPVS_POSS));
}


/**
  * @}
  */

/** @defgroup MD_PMU_Public_Functions_Group3 SR
  * @{
  */

/**
  * @brief  Get Wakeup flag .
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_active_flag_wakeup(void)
{
    return (READ_BIT(PMU->SR, PMU_SR_WUF_MSK) == PMU_SR_WUF_MSK);
}
/**
  * @}
  */
/** @defgroup MD_PMU_Public_Functions_Group4 LVDCR
  * @{
  */
/**
  * @brief  Get LVD Status flag .
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_active_flag_lvdo(void)
{
    return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDO_MSK) == PMU_LVDCR_LVDO_MSK);
}

/**
  * @brief  Enable the LVD filter .
  * @retval None
  */
__STATIC_INLINE void md_pmu_enable_lvd_filter(void)
{
    SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK);
}

/**
  * @brief  Disable the LVD filter .
  * @retval None
  */
__STATIC_INLINE void md_pmu_disable_lvd_filter(void)
{
    CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK);
}

/**
  * @brief  Check if the LVD filter is enable or disable.
  * @retval State for bit (1 or 0)
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_lvd_filter(void)
{
    return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK) == PMU_LVDCR_LVDFLT_MSK);
}

/**
  * @brief  Set LVD Interrupt mode.
  * @param  mode: lvd interrupt mode @see md_pmu_lvd_trigger_mode_t.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_set_lvd_it_mode(md_pmu_lvd_trigger_mode_t mode)
{
    MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVDIFS_MSK, mode << PMU_LVDCR_LVDIFS_POSS);
}

/**
  * @brief  Get LVD Interrupt mode.
  * @retval value for lvd it mode.
  */
__STATIC_INLINE uint32_t md_pmu_get_lvd_it_mode(void)
{
    return READ_BITS(PMU->LVDCR, PMU_LVDCR_LVDIFS_MSK, PMU_LVDCR_LVDIFS_POSS);
}

/**
  * @brief  Set LVD voltage threshold value.
  * @param  value: threshold value @see md_pmu_lvd_voltage_sel_t.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_set_lvd_vol_threshold(md_pmu_lvd_voltage_sel_t value)
{
    MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVDS_MSK, value << PMU_LVDCR_LVDS_POSS);
}

/**
  * @brief  Get LVD voltage threshold value.
  * @retval value for lvd voltage threshold @see pmu_lvd_voltage_sel_t.
  */
__STATIC_INLINE uint32_t md_pmu_get_lvd_vol_threshold(void)
{
    return (READ_BITS(PMU->LVDCR, PMU_LVDCR_LVDS_MSK, PMU_LVDCR_LVDS_POSS));
}

/**
  * @brief  Set LVD interrupt flag clear bit.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_set_lvd_it_flag(void)
{
    SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
}

/**
  * @brief  Get LVD interrupt flag.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_active_flag_lvd_it(void)
{
    return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDIF_MSK) == PMU_LVDCR_LVDIF_MSK);
}

/**
  * @brief  Enable LVD interrupt.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_enable_lvd_it(void)
{
    SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
}

/**
  * @brief  Disable LVD interrupt.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_disable_lvd_it(void)
{
    CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
}

/**
  * @brief  Check if LVD interrupt is enable or disable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_is_enable_lvd_it(void)
{
    return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK) == PMU_LVDCR_LVDIE_MSK);
}

/**
  * @brief  Enable LVD.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_enable_lvd(void)
{
    SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
}

/**
  * @brief  Disable LVD interrupt.
  * @retval None.
  */
__STATIC_INLINE void md_pmu_disable_lvd(void)
{
    CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
}

/**
  * @brief  Check if LVD is enable or disable.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_pmu_lvd_is_enable(void)
{
    return (READ_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK) == PMU_LVDCR_LVDEN_MSK);
}
/**
  * @}
  */

/** @defgroup MD_PMU_Public_Functions_Group1 Initialization
  * @{
  */
__STATIC_INLINE__ void md_pmu_sleep_enter()
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    __WFI();
}

extern void md_pmu_reset(void);
extern void md_pmu_sleep_enter(void);
extern void md_pmu_stop_enter(void);
extern void md_pmu_lvd_config(md_pmu_lvd_voltage_sel_t sel, md_pmu_lvd_trigger_mode_t mode, type_func_t state);
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
