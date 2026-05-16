/**********************************************************************************
 *
 * @file    md_acmp.h
 * @brief   Header file of ACMP module driver.
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

#ifndef __MD_ACMP_H__
#define __MD_ACMP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------ */
#include "md_utils.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup MD_ACMP ACMP
  * @brief ACMP micro driver
  * @{
  */
/** @defgroup MD_ACMP_Public_Types ACMP Public Types
  * @{
  */

/**
  * @brief ACMP interrupt
  */
typedef enum
{
    MD_ACMP_IT_EDGE   = (1U << 0),  /**< Edge interrupt bit */
    MD_ACMP_IT_WARMUP = (1U << 1),  /**< Warm up interrupt bit */
} md_acmp_it_t;

/**
  * @brief ACMP interrupt flag
  */
typedef enum
{
    MD_ACMP_FLAG_EDGE   = (1U << 0),    /**< Edge interrupt flag */
    MD_ACMP_FLAG_WARMUP = (1U << 1),    /**< Warm up interrupt flag */
} md_acmp_flag_t;

/**
  * @brief ACMP status flag
  */
typedef enum
{
    MD_ACMP_STATUS_ACT = (1U << 0), /**< Edge status flag */
    MD_ACMP_STATUS_OUT = (1U << 1), /**< Warm up status flag */
} md_acmp_status_t;

/**
  * @brief ACMP positive input
  */
typedef enum
{
    MD_ACMP_POS_CH0 = 0x0U, /**< Channel 0 as positive input */
    MD_ACMP_POS_CH1 = 0x1U, /**< Channel 1 as positive input */
    MD_ACMP_POS_CH2 = 0x2U, /**< Channel 2 as positive input */
    MD_ACMP_POS_CH3 = 0x3U, /**< Channel 3 as positive input */
//  MD_ACMP_POS_CH4 = 0x4U, /**< Channel 4 as positive input */
//  MD_ACMP_POS_CH5 = 0x5U, /**< Channel 5 as positive input */
//  MD_ACMP_POS_CH6 = 0x6U, /**< Channel 6 as positive input */
//  MD_ACMP_POS_CH7 = 0x7U, /**< Channel 7 as positive input */
} md_acmp_pos_input_t;

/**
  * @brief ACMP negative input
  */
typedef enum
{
    MD_ACMP_NEG_1V   = 0x0U,    /**< 1V as negative input */
//    MD_ACMP_NEG_VDD  = 0x1U,    /**< VDD as negative input */
    MD_ACMP_NEG_CH0  = 0x2U,    /**< Channel 0 as negative input */
    MD_ACMP_NEG_CH1  = 0x3U,    /**< Channel 1 as negative input */
//  MD_ACMP_NEG_CH4  = 0x4U,    /**< Channel 4 as negative input */
//  MD_ACMP_NEG_CH5  = 0x5U,    /**< Channel 5 as negative input */
//  MD_ACMP_NEG_CH6  = 0x6U,    /**< Channel 6 as negative input */
//  MD_ACMP_NEG_CH7  = 0x7U,    /**< Channel 7 as negative input */
//  MD_ACMP_NEG_1V25 = 0x8U,    /**< 1.25v as negative input */
//  MD_ACMP_NEG_2V5  = 0x9U,    /**< 2.5v as negative input */
//  MD_ACMP_NEG_VDD  = 0xAU,    /**< VDD as negative input */
} md_acmp_neg_input_t;

/**
  * @brief ACMP mode
  */
typedef enum
{
    MD_ACMP_ULTRA_LOW_POWER = 0x0U, /**< Ultra low power mode */
    MD_ACMP_LOW_POWER       = 0x1U, /**< Low power mode */
    MD_ACMP_MIDDLE_POWER    = 0x2U, /**< Middle power mode */
    MD_ACMP_HIGH_POWER      = 0x3U, /**< High power mode */
} md_acmp_mode_t;

/**
  * @brief ACMP warm-up time
  */
typedef enum
{
    MD_ACMP_4_PCLK   = 0x0U,    /**< 4 hfperclk cycles */
    MD_ACMP_8_PCLK   = 0x1U,    /**< 8 hfperclk cycles */
    MD_ACMP_16_PCLK  = 0x2U,    /**< 16 hfperclk cycles */
    MD_ACMP_32_PCLK  = 0x3U,    /**< 32 hfperclk cycles */
    MD_ACMP_64_PCLK  = 0x4U,    /**< 64 hfperclk cycles */
    MD_ACMP_128_PCLK = 0x5U,    /**< 128 hfperclk cycles */
    MD_ACMP_256_PCLK = 0x6U,    /**< 256 hfperclk cycles */
    MD_ACMP_512_PCLK = 0x7U,    /**< 512 hfperclk cycles */
} md_acmp_warm_time_t;

/**
  * @brief ACMP hysteresis level
  */
typedef enum
{
    MD_ACMP_HYST_0  = 0x0U, /**< No hysteresis */
    MD_ACMP_HYST_15 = 0x1U, /**< 15mV hysteresis */
    MD_ACMP_HYST_22 = 0x2U, /**< 22mV hysteresis */
    MD_ACMP_HYST_29 = 0x3U, /**< 29mV hysteresis */
    MD_ACMP_HYST_36 = 0x4U, /**< 36mV hysteresis */
    MD_ACMP_HYST_43 = 0x5U, /**< 43mV hysteresis */
    MD_ACMP_HYST_50 = 0x6U, /**< 50mV hysteresis */
    MD_ACMP_HYST_57 = 0x7U, /**< 57mV hysteresis */
} md_acmp_hystsel_t;

/**
  * @brief ACMP inactive state
  */
typedef enum
{
    MD_ACMP_INACTVAL_LOW  = 0x0U,   /**< The inactive value is 0 */
    MD_ACMP_INACTVAL_HIGH = 0x1U,   /**< The inactive value is 1 */
} md_acmp_inactval_t;

/**
  * @brief which edges set up interrupt
  */
typedef enum
{
    MD_ACMP_EDGE_NONE = 0x0U,   /**< Disable EDGE interrupt */
    MD_ACMP_EDGE_FALL = 0x1U,   /**< Falling edges set EDGE interrupt */
    MD_ACMP_EDGE_RISE = 0x2U,   /**< rise edges set EDGE interrupt */
    MD_ACMP_EDGE_ALL  = 0x3U,   /**< Falling edges and rise edges set EDGE interrupt */
} md_acmp_edge_t;

/**
  * @brief ACMP output function
  */
typedef enum
{
    MD_ACMP_OUT_DISABLE = 0x0U, /**< Disable acmp output */
    MD_ACMP_OUT_ENABLE  = 0x1U, /**< Enable acmp output */
} md_acmp_out_func_t;
/**
  * @brief ACMP mode
  */
typedef enum
{
    MD_ACMP_0_FLT_PCLK  = 0x0U, /**< 0 PCLK */
    MD_ACMP_1_FLT_PCLK  = 0x1U, /**< 1 PCLK */
    MD_ACMP_2_FLT_PCLK  = 0x2U, /**< 2 PCLK */
    MD_ACMP_4_FLT_PCLK  = 0x3U, /**< 4 PCLK */
    MD_ACMP_8_FLT_PCLK  = 0x4U, /**< 8 PCLK */
    MD_ACMP_16_FLT_PCLK = 0x5U, /**< 16 PCLK */
    MD_ACMP_32_FLT_PCLK = 0x6U, /**< 32 PCLK */
    MD_ACMP_64_FLT_PCLK = 0x7U, /**< 64 PCLK */
} md_acmp_flt_t;

/**
  * @brief ACMP init structure definition
  */
typedef struct
{
    md_acmp_mode_t mode;            /**< ACMP operation mode */
    md_acmp_warm_time_t warm_time;  /**< ACMP warm up time */
    md_acmp_hystsel_t hystsel;      /**< ACMP hysteresis level */
    md_acmp_pos_input_t p_port;     /**< ACMP positive port select */
    md_acmp_neg_input_t n_port;     /**< ACMP negative port select */
    md_acmp_inactval_t inactval;    /**< ACMP inavtive output value */
    type_func_t out_inv;        /**< ACMP output inverse */
    md_acmp_edge_t edge;            /**< Select edges to set interrupt flag */
//    uint8_t vdd_level;              /**< Select scaling factor for CDD reference level, MAX is 63 */
    md_acmp_flt_t flt;
} md_acmp_init_t;

/**
  * @brief  ACMP Handle Structure definition
  */
//typedef struct md_acmp_handle_s {
//  MD_ACMP_TypeDef *ACMPx; /**< Register base address */
//  md_acmp_init_t init;    /**< ACMP required parameters */
//  lock_state_t lock;  /**< Locking object */

//  void (*md_acmp_warmup_cplt_cbk)(struct md_acmp_handle_s *arg);  /**< ACMP warm-up complete callback */
//  void (*md_acmp_edge_cplt_cbk)(struct md_acmp_handle_s *arg);    /**< ACMP edge trigger callback */
//} md_acmp_handle_t;
/**
  * @}
  */
/** @defgroup MD_ACMP_Public_Functions_Group1 CON
  * @{
  */
/**
  * @brief set flt number
  * @param ACMPx:ACMP instance
  * @param flt number of wave filtering this parameter can be one of the @ref md_acmp_flt_t
  * @retval none
  */
__STATIC_INLINE void md_acmp_set_flt_num(ACMP_TypeDef *ACMPx, md_acmp_flt_t flt)
{
    MODIFY_REG(ACMPx->CON, ACMP_CON_FLTSEL_MSK, flt << ACMP_CON_FLTSEL_POSS);
}

/**
  * @brief get flt number
  * @param ACMPx:ACMP instance
  * @retval wave filtering ,see @ref md_acmp_flt_t
  */
__STATIC_INLINE uint32_t md_acmp_get_flt_num(ACMP_TypeDef *ACMPx)
{
    return READ_BITS(ACMPx->CON, ACMP_CON_FLTSEL_MSK, ACMP_CON_FLTSEL_POSS);
}

/**
  * @brief set fall edge interrupt flag enanble
  * @param ACMPx:ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_enable_fall_edge_trigger(ACMP_TypeDef *ACMPx)
{
    SET_BIT(ACMPx->CON, ACMP_CON_FALLEN_MSK);
}

/**
  * @brief set fall edge interrupt flag disanble
  * @param:ACMPx ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_disable_fall_edge_trigger(ACMP_TypeDef *ACMPx)
{
    CLEAR_BIT(ACMPx->CON, ACMP_CON_FALLEN_MSK);
}

/**
  * @brief check if fall edge interrupt flag is enanbled
  * @param:ACMPx ACMP instance
  * @retval 0x01:enable
  *         0x00:disable
  */
__STATIC_INLINE uint32_t md_acmp_is_enabled_fall_edge_trigger(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->CON, ACMP_CON_FALLEN_MSK) == ACMP_CON_FALLEN_MSK);
}

/**
  * @brief set rise edge interrupt flag enanble
  * @param ACMPx:ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_enable_rise_edge_trigger(ACMP_TypeDef *ACMPx)
{
    SET_BIT(ACMPx->CON, ACMP_CON_RISEEN_MSK);
}

/**
  * @brief set rise edge interrupt flag disanble
  * @param ACMPx:ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_disable_rise_edge_trigger(ACMP_TypeDef *ACMPx)
{
    CLEAR_BIT(ACMPx->CON, ACMP_CON_RISEEN_MSK);
}

/**
  * @brief check if rise edge interrupt flag enanbled
  * @param ACMPx:ACMP instance
  * @retval 0x01:enable
  *         0x00:disable
  */
__STATIC_INLINE uint32_t md_acmp_is_enabled_rise_edge_trigger(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->CON, ACMP_CON_RISEEN_MSK) == ACMP_CON_RISEEN_MSK);
}

/**
  * @brief choose acmp mode
  * @param ACMPx :ACMP instance
  * @param mode : work mode.This parameter can be one of the  @ref md_acmp_mode_t
  * @retval none
  */
__STATIC_INLINE void md_acmp_set_acmp_mode(ACMP_TypeDef *ACMPx, md_acmp_mode_t mode)
{
    MODIFY_REG(ACMPx->CON, ACMP_CON_MODSEL_MSK, mode << ACMP_CON_MODSEL_POSS);
}

/**
  * @brief get acmp mode
  * @param ACMPx :ACMP instance
  * @retval mode :the acmp work mode,see @ref md_acmp_mode_t
  */
__STATIC_INLINE uint32_t md_acmp_get_acmp_mode(ACMP_TypeDef *ACMPx)
{
    return READ_BITS(ACMPx->CON, ACMP_CON_MODSEL_MSK, ACMP_CON_MODSEL_POSS);
}

/**
  * @brief set warm up time
  * @param ACMPx :ACMP instance
  * @param val : warm up time. This parameter can be one of the @ref md_acmp_warm_time_t
  * @retval none
  */
__STATIC_INLINE void md_acmp_set_warmup_time(ACMP_TypeDef *ACMPx, md_acmp_warm_time_t val)
{
    MODIFY_REG(ACMPx->CON, ACMP_CON_WARMUPT_MSK, val << ACMP_CON_WARMUPT_POSS);
}

/**
  * @brief set warm up time
  * @param ACMPx :ACMP instance
  * @retval warm up time, see @ref md_acmp_warm_time_t
  */
__STATIC_INLINE uint32_t md_acmp_get_warmup_time(ACMP_TypeDef *ACMPx)
{
    return READ_BITS(ACMPx->CON, ACMP_CON_WARMUPT_MSK, ACMP_CON_WARMUPT_POSS);
}

/**
  * @brief set Hysteresis level
  * @param ACMPx :ACMP instance
  * @param val :Hysteresis level.This parameter can be one of the @ref md_acmp_hystsel_t
  * @retval none
  */
__STATIC_INLINE void md_acmp_set_hysteresis_level(ACMP_TypeDef *ACMPx, md_acmp_hystsel_t val)
{
    MODIFY_REG(ACMPx->CON, ACMP_CON_HYSTSEL_MSK, val << ACMP_CON_HYSTSEL_POSS);
}

/**
  * @brief get Hysteresis level
  * @param ACMPx :ACMP instance
  * @retval Hysteresis level,see @ref md_acmp_hystsel_t
  */
__STATIC_INLINE uint32_t md_acmp_get_hysteresis_level(ACMP_TypeDef *ACMPx)
{
    return READ_BITS(ACMPx->CON, ACMP_CON_HYSTSEL_MSK, ACMP_CON_HYSTSEL_POSS);
}

/**
  * @brief set acmp output inverse enable
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_enable_output_inverse(ACMP_TypeDef *ACMPx)
{
    SET_BIT(ACMPx->CON, ACMP_CON_OUTINV_MSK);
}

/**
  * @brief set acmp output inverse disable
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_disable_output_inverse(ACMP_TypeDef *ACMPx)
{
    CLEAR_BIT(ACMPx->CON, ACMP_CON_OUTINV_MSK);
}

/**
  * @brief check if acmp output inverse is enabled
  * @param ACMPx :ACMP instance
  * @retval 0x01:enable
  *         0x00:disable
  */
__STATIC_INLINE uint32_t md_acmp_is_enabled_output_inverse(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->CON, ACMP_CON_OUTINV_MSK) == ACMP_CON_OUTINV_MSK);
}

/**
  * @brief set acmp invalid state as 1
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_set_invalid_1(ACMP_TypeDef *ACMPx)
{
    SET_BIT(ACMPx->CON, ACMP_CON_INACTV_MSK);
}

/**
  * @brief set acmp invalid state as 0
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_set_invalid_0(ACMP_TypeDef *ACMPx)
{
    CLEAR_BIT(ACMPx->CON, ACMP_CON_INACTV_MSK);
}

/**
  * @brief get acmp invalid state
  * @param ACMPx :ACMP instance
  * @retval 0x01:invalid state is 1
  *         0x00:invalid state is 0
  */
__STATIC_INLINE uint32_t md_acmp_get_invalid_state(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->CON, ACMP_CON_INACTV_MSK) == ACMP_CON_INACTV_MSK);
}

/**
  * @brief set acmp enable
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_enable(ACMP_TypeDef *ACMPx)
{
    SET_BIT(ACMPx->CON, ACMP_CON_EN_MSK);
}

/**
  * @brief set acmp disable
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_disable(ACMP_TypeDef *ACMPx)
{
    CLEAR_BIT(ACMPx->CON, ACMP_CON_EN_MSK);
}

/**
  * @brief check if acmp is enable
  * @param ACMPx :ACMP instance
  * @retval 0x01:enable
  *         0x00:disable
  */
__STATIC_INLINE uint32_t md_acmp_is_enabled(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->CON, ACMP_CON_EN_MSK) == ACMP_CON_EN_MSK);
}
/**
  * @}
  */
/** @defgroup MD_ACMP_Public_Functions_Group2 INPUTSEL
  * @{
  */
/**
  * @brief set vdd reference voltage division
  * @param ACMPx :ACMP instance
  * @param val :should be less than 63
  * @retval
  */
//__STATIC_INLINE void md_acmp_set_vdd_ref_divise(ACMP_TypeDef *ACMPx, uint32_t val)
//{
//    MODIFY_REG(ACMPx->INPUTSEL, ACMP_INPUTSEL_VDDLVL_MSK, val << ACMP_INPUTSEL_VDDLVL_POSS);
//}

/**
  * @brief get vdd reference voltage division
  * @param ACMPx :ACMP instance
  * @retval voltage division
  */
//__STATIC_INLINE uint32_t md_acmp_get_vdd_ref_divise(ACMP_TypeDef *ACMPx)
//{
//    return READ_BITS(ACMPx->INPUTSEL, ACMP_INPUTSEL_VDDLVL_MSK, ACMP_INPUTSEL_VDDLVL_POSS);
//}

/**
  * @brief choose negative input
  * @param ACMPx :ACMP instance
  * @param val:negetive choice .this parameter can be one of the @ref md_acmp_neg_input_t
  * @retval none
  */
__STATIC_INLINE void md_acmp_set_ninput(ACMP_TypeDef *ACMPx, md_acmp_neg_input_t val)
{
    MODIFY_REG(ACMPx->INPUTSEL, ACMP_INPUTSEL_NSEL_MSK, val << ACMP_INPUTSEL_NSEL_POSS);
}

/**
  * @brief get negative input
  * @param ACMPx :ACMP instance
  * @retval negative input :negetive choice .see @ref md_acmp_neg_input_t
  */
__STATIC_INLINE uint32_t md_acmp_get_ninput(ACMP_TypeDef *ACMPx)
{
    return READ_BITS(ACMPx->INPUTSEL, ACMP_INPUTSEL_NSEL_MSK, ACMP_INPUTSEL_NSEL_POSS);
}

/**
  * @brief choose positive input
  * @param ACMPx :ACMP instance
  * @param val:positive choice .this parameter can be one of the @ref md_acmp_pos_input_t
  * @retval none
  */
__STATIC_INLINE void md_acmp_set_pinput(ACMP_TypeDef *ACMPx, md_acmp_pos_input_t val)
{
    MODIFY_REG(ACMPx->INPUTSEL, ACMP_INPUTSEL_PSEL_MSK, val << ACMP_INPUTSEL_PSEL_POSS);
}

/**
  * @brief get positive input
  * @param ACMPx :ACMP instance
  * @retval positive input :negetive choice .see @ref md_acmp_pos_input_t
  */
__STATIC_INLINE uint32_t md_acmp_get_pinput(ACMP_TypeDef *ACMPx)
{
    return READ_BITS(ACMPx->INPUTSEL, ACMP_INPUTSEL_PSEL_MSK, ACMP_INPUTSEL_PSEL_POSS);
}
/**
  * @}
  */
/** @defgroup MD_ACMP_Public_Functions_Group3 STAT
  * @{
  */
/**
  * @brief get acmp output
  * @param ACMPx :ACMP instance
  * @retval acmp output value
  */
__STATIC_INLINE uint32_t md_acmp_get_output(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->STAT, ACMP_STAT_OUT_MSK) == ACMP_STAT_OUT_MSK);
}

/**
  * @brief check if acmp is valid
  * @param ACMPx :ACMP instance
  * @retval 0x01: valid
  *         0x00: invalid
  */
__STATIC_INLINE uint32_t md_acmp_get_valid_state(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->STAT, ACMP_STAT_ACT_MSK) == ACMP_STAT_ACT_MSK);
}
/**
  * @}
  */
/** @defgroup MD_ACMP_Public_Functions_Group4 IES
  * @{
  */
/**
  * @brief set warm up interrupt enable
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_enable_warmup_interrupt(ACMP_TypeDef *ACMPx)
{
    SET_BIT(ACMPx->IES, ACMP_IES_WARMUP_MSK);
}
/**
  * @brief set edge interrupt enable
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_enable_edge_interrupt(ACMP_TypeDef *ACMPx)
{
    SET_BIT(ACMPx->IES, ACMP_IES_EDGE_MSK);
}
/**
  * @}
  */
/** @defgroup MD_ACMP_Public_Functions_Group5 IEC
  * @{
  */
/**
  * @brief set warm up interrupt disable
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_disable_warmup_interrupt(ACMP_TypeDef *ACMPx)
{
    SET_BIT(ACMPx->IEC, ACMP_IEC_WARMUP_MSK);
}

/**
  * @brief set edge interrupt disable
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_disable_edge_interrupt(ACMP_TypeDef *ACMPx)
{
    SET_BIT(ACMPx->IEC, ACMP_IEC_EDGE_MSK);
}
/**
  * @}
  */
/** @defgroup MD_ACMP_Public_Functions_Group6 IEV
  * @{
  */
/**
  * @brief check if warm up interrupt is enable
  * @param ACMPx :ACMP instance
  * @retval 0x01:enable
  *         0x00:disable
  */
__STATIC_INLINE uint32_t md_acmp_is_enabled_warmup_interrupt(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->IEV, ACMP_IEV_WARMUP_MSK) == ACMP_IEV_WARMUP_MSK);
}
/**
  * @brief check if edge interrupt is enable
  * @param ACMPx :ACMP instance
  * @retval 0x01:enable
  *         0x00:disable
  */
__STATIC_INLINE uint32_t md_acmp_is_enabled_edge_interrupt(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->IEV, ACMP_IEV_EDGE_MSK) == ACMP_IEV_EDGE_MSK);
}
/**
  * @}
  */
/** @defgroup MD_ACMP_Public_Functions_Group7 RIF
  * @{
  */
/**
  * @brief get warm up interrupt flag
  * @param ACMPx :ACMP instance
  * @retval 0x01:set up
  *         0x00:did not set up
  */
__STATIC_INLINE uint32_t md_acmp_get_warmup_flag(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->RIF, ACMP_RIF_WARMUP_MSK) == ACMP_RIF_WARMUP_MSK);
}

/**
  * @brief get edge interrupt flag
  * @param ACMPx :ACMP instance
  * @retval 0x01:set up
  *         0x00:did not set up
  */
__STATIC_INLINE uint32_t md_acmp_get_edge_flag(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->RIF, ACMP_RIF_EDGE_MSK) == ACMP_RIF_EDGE_MSK);
}
/**
  * @}
  */
/** @defgroup MD_ACMP_Public_Functions_Group8 IFM
  * @{
  */

/**
  * @brief check if warm up interrupt is enabled and flag set up
  * @param ACMPx :ACMP instance
  * @retval state
  */
__STATIC_INLINE uint32_t md_acmp_get_warmup_interrupt_valid_flag(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->IFM, ACMP_IFM_WARMUP_MSK) == ACMP_IFM_WARMUP_MSK);
}
/**
  * @brief check if edge interrupt is enabled and flag set up
  * @param ACMPx :ACMP instance
  * @retval state
  */
__STATIC_INLINE uint32_t md_acmp_get_edge_interrupt_valid_flag(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->IFM, ACMP_IFM_EDGE_MSK) == ACMP_IFM_EDGE_MSK);
}
/**
  * @}
  */
/** @defgroup MD_ACMP_Public_Functions_Group9 IFC
  * @{
  */
/**
  * @brief clear warm up flag
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_clear_warmup_flag(ACMP_TypeDef *ACMPx)
{
    SET_BIT(ACMPx->IFC, ACMP_IFC_WARMUP_MSK);
}

/**
  * @brief clear edge flag
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_clear_edge_flag(ACMP_TypeDef *ACMPx)
{
    SET_BIT(ACMPx->IFC, ACMP_IFC_EDGE_MSK);
}

/**
  * @}
  */
/** @defgroup MD_ACMP_Public_Functions_Group10 PORT
  * @{
  */
/**
  * @brief set acmp output gpio enable
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_enable_output_port(ACMP_TypeDef *ACMPx)
{
    SET_BIT(ACMPx->PORT, ACMP_PORT_PEN_MSK);
}

/**
  * @brief set acmp output gpio disable
  * @param ACMPx :ACMP instance
  * @retval none
  */
__STATIC_INLINE void md_acmp_disable_output_port(ACMP_TypeDef *ACMPx)
{
    CLEAR_BIT(ACMPx->PORT, ACMP_PORT_PEN_MSK);
}

/**
  * @brief check if  acmp output gpio is enable
  * @param ACMPx :ACMP instance
  * @retval 0x01:enable
  *         0x00:disable
  */
__STATIC_INLINE uint32_t md_acmp_is_enabled_output_port(ACMP_TypeDef *ACMPx)
{
    return (READ_BIT(ACMPx->PORT, ACMP_PORT_PEN_MSK) == ACMP_PORT_PEN_MSK);
}

/**
  * @}
  */

/** @defgroup MD_ACMP_Public_Macros ACMP Public Macros
  * @{
  */
#define MD_ACMP_ENABLE(ACMPx)   (SET_BIT(ACMPx->CON, ACMP_CON_EN_MSK))
#define MD_ACMP_DISABLE(ACMPx)  (CLEAR_BIT(ACMPx->CON, ACMP_CON_EN_MSK))
/**
  * @}
  */

/** @defgroup ACMP_Private_Macros   ACMP Private Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup ACMP_Public_Functions
  * @{
  */

/** @addtogroup ACMP_Public_Functions_Group1
  * @{
  */
void md_acmp_init(ACMP_TypeDef *ACMPx, md_acmp_init_t *init);
/**
  * @}
  */
/** @addtogroup ACMP_Public_Functions_Group2
  * @{
  */
void md_acmp_interrupt_config(ACMP_TypeDef *ACMPx, md_acmp_it_t it, type_func_t state);
it_status_t md_acmp_get_it_status(ACMP_TypeDef *ACMPx, md_acmp_it_t it);
flag_status_t md_acmp_get_flag_status(ACMP_TypeDef *ACMPx, md_acmp_flag_t flag);
flag_status_t md_acmp_get_mask_flag_status(ACMP_TypeDef *ACMPx, md_acmp_flag_t flag);
void md_acmp_clear_flag_status(ACMP_TypeDef *ACMPx, md_acmp_flag_t flag);
/**
  * @}
  */
/** @addtogroup ACMP_Public_Functions_Group3
  * @{
  */
void md_acmp_out_config(ACMP_TypeDef *ACMPx, type_func_t state);
uint8_t md_acmp_out_result(ACMP_TypeDef *ACMPx);
flag_status_t md_acmp_get_status(ACMP_TypeDef *ACMPx, md_acmp_status_t status);
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
extern "C"
}
#endif
#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
