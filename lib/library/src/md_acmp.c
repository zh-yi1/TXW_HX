/**********************************************************************************
 *
 * @file    md_acmp.c
 * @brief   ACMP module driver.
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

/* Includes ------------------------------------------------------------------ */
#include "md_acmp.h"

/** @addtogroup Micro_Driver
  * @{
  */
//#ifdef MD_ACMP

/** @addtogroup MD_ACMP
  * @{
  */

/** @addtogroup MD_ACMP_Public_Functions
  * @{
  */
/** @addtogroup MD_ACMP_Public_Functions_Group1
  * @{
  */

/**
  * @brief  Initializes the ACMP mode according to the specified parameters in
  *         the acmp_init_t and create the associated handle.
  * @param  ACMPx: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @retval Status, see @ref md_status_t.
  */
void md_acmp_init(ACMP_TypeDef *ACMPx, md_acmp_init_t *init)
{
    uint32_t tmp = 0;

    tmp = ((init->mode << ACMP_CON_MODSEL_POSS) | (init->warm_time << ACMP_CON_WARMUPT_POSS) |
           (init->inactval << ACMP_CON_INACTV_POS) | (init->hystsel << ACMP_CON_HYSTSEL_POSS) | (init->flt << ACMP_CON_FLTSEL_POSS));

    ACMPx->CON = tmp;

    tmp = 0;
    tmp |= ((init->p_port << ACMP_INPUTSEL_PSEL_POSS) | (init->n_port << ACMP_INPUTSEL_NSEL_POSS));
    ACMPx->INPUTSEL = tmp;

    if (init->out_inv)
        SET_BIT(ACMPx->CON, ACMP_CON_OUTINV_MSK);
    else
        CLEAR_BIT(ACMPx->CON, ACMP_CON_OUTINV_MSK);

    switch (init->edge)
    {
        case MD_ACMP_EDGE_NONE:
            CLEAR_BIT(ACMPx->CON, ACMP_CON_FALLEN_MSK);
            CLEAR_BIT(ACMPx->CON, ACMP_CON_RISEEN_MSK);
            break;

        case MD_ACMP_EDGE_FALL:
            SET_BIT(ACMPx->CON, ACMP_CON_FALLEN_MSK);
            CLEAR_BIT(ACMPx->CON, ACMP_CON_RISEEN_MSK);
            break;

        case MD_ACMP_EDGE_RISE:
            CLEAR_BIT(ACMPx->CON, ACMP_CON_FALLEN_MSK);
            SET_BIT(ACMPx->CON, ACMP_CON_RISEEN_MSK);
            break;

        case MD_ACMP_EDGE_ALL:
            SET_BIT(ACMPx->CON, ACMP_CON_FALLEN_MSK);
            SET_BIT(ACMPx->CON, ACMP_CON_RISEEN_MSK);
            break;

        default:
            break;
    }

    SET_BIT(ACMPx->CON, ACMP_CON_EN_MSK);

    tmp = 0;

}
/**
  * @}
  */

/** @defgroup ACMP_Public_Functions_Group2 Interrupt operation functions
  * @brief ACMP Interrupt operation functions
  * @{
  */

/**
  * @brief  Enables or disables the specified ACMP interrupts.
  * @param  ACMPx: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  it: Specifies the ACMP interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref acmp_it_t.
  * @param  state: New status
  *           - ENABLE
  *           - DISABLE
  * @retval None
  */
void md_acmp_interrupt_config(ACMP_TypeDef *ACMPx, md_acmp_it_t it, type_func_t state)
{

    if (state)
        ACMPx->IES = it;
    else
        ACMPx->IEC = it;

    return;
}

/**
  * @brief  Checks whether the specified ACMP interrupt has set or not.
  * @param  ACMPx: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  it: Specifies the ACMP interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref acmp_it_t.
  * @retval it_status_t
  *           - SET
  *           - RESET
  */
it_status_t md_acmp_get_it_status(ACMP_TypeDef *ACMPx, md_acmp_it_t it)
{

    if (ACMPx->IEV & it)
        return SET;

    return RESET;
}

/**
  * @brief  Checks whether the specified ACMP interrupt has occurred or not.
  * @param  ACMPx: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  flag: Specifies the ACMP interrupt source to check.
  *         This parameter can be one of the @ref acmp_flag_t.
  * @retval flag_status_t
  *           - SET
  *           - RESET
  */
flag_status_t md_acmp_get_flag_status(ACMP_TypeDef *ACMPx, md_acmp_flag_t flag)
{

    if (ACMPx->RIF & flag)
        return SET;

    return RESET;
}

/**
  * @brief  Get the status of interrupt flag and interupt source.
  * @param  ACMPx: Pointer to a acmp_handle_t structure that contains
  *               the configuration information for the specified ACMP.
  * @param  flag: Specifies the ACMP interrupt flag.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t md_acmp_get_mask_flag_status(ACMP_TypeDef *ACMPx, md_acmp_flag_t flag)
{

    if (ACMPx->IFM & flag)
        return SET;

    return RESET;
}

/** @brief  Clear the specified ACMP it flags.
  * @param  ACMPx: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  flag: specifies the it flag.
  *         This parameter can be one of the @ref acmp_flag_t.
  * @retval None
  */
void md_acmp_clear_flag_status(ACMP_TypeDef *ACMPx, md_acmp_flag_t flag)
{

    ACMPx->IFC = flag;
    return;
}
/**
  * @}
  */
/** @defgroup ACMP_Public_Functions_Group3 Output value functions
  * @brief ACMP Output value functions
  * @{
  */

/**
  * @brief  This function config acmp output.
  * @param  ACMPx: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  state: ENABLE/DISABLE.
  * @retval None
  */
void md_acmp_out_config(ACMP_TypeDef *ACMPx, type_func_t state)
{

    if (state)
        SET_BIT(ACMPx->PORT, ACMP_PORT_PEN_MSK);
    else
        CLEAR_BIT(ACMPx->PORT, ACMP_PORT_PEN_MSK);

    return;
}

/**
  * @brief  This function output acmp result.
  * @param  ACMPx: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @retval output value.
  */
uint8_t md_acmp_out_result(ACMP_TypeDef *ACMPx)
{

    return (READ_BIT(ACMPx->STAT, ACMP_STAT_OUT_MSK) >> ACMP_STAT_OUT_POS);
}

/** @brief  Check whether the specified ACMP flag is set or not.
  * @param  ACMPx: Pointer to a acmp_handle_t structure that contains
  *         the configuration information for the specified ACMP module.
  * @param  status: specifies the status to check.
  *         This parameter can be one of the @ref acmp_status_t.
  * @retval flag_status_t
  *           - SET
  *           - RESET
  */
flag_status_t md_acmp_get_status(ACMP_TypeDef *ACMPx, md_acmp_status_t status)
{

    if (ACMPx->STAT & status)
        return SET;

    return RESET;
}
/**
  * @}
  */
/**
  * @}
  */
//#endif /* MD_ACMP */
/**
  * @}
  */
/**
  * @}
  */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
