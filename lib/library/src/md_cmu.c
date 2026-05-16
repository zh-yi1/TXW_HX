/**********************************************************************************
 *
 * @file    md_cmu.c
 * @brief   CMU module driver.
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
#include "md_cmu.h"
#include "md_msc.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @addtogroup MD_CMU
  * @{
  */
/**
  * @defgroup MD_CMU_Private_Variables CMU Private Variables
  * @{
  */
uint32_t md_system_clock = 32000000U;
/**
  * @}
  */
/** @defgroup MD_CMU_Private_Functions CMU Private Functions
  * @{
  */

/**
  * @brief  Update the current system clock. This function
  *         will be invoked, when system clock has changed.
  * @param  clock: The new clock.
  * @retval None
  */

static void md_cmu_clock_update(uint32_t clock)
{
    md_system_clock = clock;
}
/**
  * @}
  */
/** @addtogroup MD_CMU_Public_Functions
  * @{
  */
/** @addtogroup MD_CMU_Public_Functions_Group1
  * @{
  */
/**
  * @brief  Configure system clock using default.
  *         Select MD_CMU_CLOCK_HRC(32MHz) as system clock and
  *         enable MD_CMU_CLOCK_LRC(32768Hz).
  * @retval The status of HAL.
  */
md_status_t md_cmu_clock_config_default(void)
{
    uint32_t cnt = 4000, tmp;

    md_msc_set_flash_read_wait_cycle(3);

    SYSCFG_UNLOCK();

    /* Select HRC */
    MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_HRC << CMU_CSR_SYS_CMD_POSS);

    while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

    if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_HRC)
    {
        SYSCFG_LOCK();
        return MD_ERROR;
    }

    WRITE_REG(CMU->CFGR, 0x0);
    MODIFY_REG(CMU->CFGR, CMU_CFGR_HRCFSW_MSK, 2 << CMU_CFGR_HRCFSW_POSS);  /* Select 32Mhz */

    tmp = READ_REG(CMU->CLKENR);
    /* Enable HRC */
    SET_BIT(tmp, CMU_CLKENR_HRCEN_MSK);
    WRITE_REG(CMU->CLKENR, tmp);
    SYSCFG_LOCK();

    /* Flash wait time */
    md_msc_set_flash_read_wait_cycle(1);

    return MD_OK;
}

/**
  * @brief  Configure system clock using specified parameters
  * @param  clk: The parameter can be one of the following:
  *           @arg @ref MD_CMU_CLOCK_HRC  2MHz or 24MHz
  *           @arg @ref MD_CMU_CLOCK_LRC  32768Hz
  *           @arg @ref MD_CMU_CLOCK_LOSC 32768Hz
  *           @arg @ref MD_CMU_CLOCK_PLL1 36MHz, 48MHz/52MHz
  *           @arg @ref MD_CMU_CLOCK_HOSC 1MHz -- 24MHz
  * @param  clock: The clock which will be set. the value depends
  *         on the parameter of clk.
  * @retval The status of HAL.
  */
md_status_t md_cmu_clock_config(md_cmu_clock_t clk, uint32_t clock)
{
    uint32_t cnt = 8000;

    md_msc_set_flash_read_wait_cycle(3);

    SYSCFG_UNLOCK();
    MODIFY_REG(CMU->CFGR, 0xFFFFFFU, 0);

    switch (clk)
    {
        case MD_CMU_CLOCK_HRC:

#if  ((defined ES32F0100) || (defined ES32F0131))
            assert_param(clock == 2000000 || clock == 16000000 || clock == 32000000 || clock == 48000000);
#elif (defined ES32F0101)
            assert_param(clock == 2000000 || clock == 16000000 || clock == 32000000 || clock == 52000000);
#else
            assert_param(clock == 2000000 || clock == 16000000 || clock == 32000000);
#endif
            MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_HRC << CMU_CSR_SYS_CMD_POSS);

            while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

            if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_HRC)
            {
                SYSCFG_LOCK();
                return MD_ERROR;
            }

            cnt = 8000;

            switch (clock)
            {
                case  2000000:
                    MODIFY_REG(CMU->CFGR, CMU_CFGR_HRCFSW_MSK, 0 << CMU_CFGR_HRCFSW_POSS);
                    break;

                case 16000000:
                    MODIFY_REG(CMU->CFGR, CMU_CFGR_HRCFSW_MSK, 1 << CMU_CFGR_HRCFSW_POSS);
                    break;

                case 32000000:
                    MODIFY_REG(CMU->CFGR, CMU_CFGR_HRCFSW_MSK, 2 << CMU_CFGR_HRCFSW_POSS);
                    break;

#if  ((defined ES32F0100) || (defined ES32F0131))

                case 48000000:
                    MODIFY_REG(CMU->CFGR, CMU_CFGR_HRCFSW_MSK, 3 << CMU_CFGR_HRCFSW_POSS);
                    MODIFY_REG(CMU->CSR, CMU_CSR_CFT_STU_MSK, 1 << CMU_CSR_CFT_STU_POS);

                    while (READ_BIT(CMU->CSR, CMU_CSR_CFT_RDYN_MSK) && (--cnt));

                    break;
#elif (defined ES32F0101)

                case 52000000:
                    MODIFY_REG(CMU->CFGR, CMU_CFGR_HRCFSW_MSK, 3 << CMU_CFGR_HRCFSW_POSS);
                    MODIFY_REG(CMU->CSR, CMU_CSR_CFT_STU_MSK, 1 << CMU_CSR_CFT_STU_POS);

                    while (READ_BIT(CMU->CSR, CMU_CSR_CFT_RDYN_MSK) && (--cnt));

                    break;
#endif

                default:
                    while (1);
            }

            SET_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);

            for (cnt = 4000; cnt; --cnt);

            cnt = 4000;

            while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRCACT_MSK))) && (--cnt));

            cnt = 4000;

            while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRCRDY_MSK))) && (--cnt));

            md_cmu_clock_update(clock);

            switch (clock)
            {
                case  2000000:
                    md_msc_set_flash_read_wait_cycle(0);
                    break;

                case 16000000:
                    md_msc_set_flash_read_wait_cycle(0);
                    break;

                case 32000000:
                    md_msc_set_flash_read_wait_cycle(1);
                    break;

                case 48000000:
                    md_msc_set_flash_read_wait_cycle(1);
                    break;

                case 52000000:
                    md_msc_set_flash_read_wait_cycle(1);
                    break;

                default:
                    break;
            }

            break;

        case MD_CMU_CLOCK_LRC:
            md_msc_set_flash_read_wait_cycle(0);
            /* Close SysTick interrupt in lower clock */
            SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

            MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_LRC << CMU_CSR_SYS_CMD_POSS);

            while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

            if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_LRC)
            {
                SYSCFG_LOCK();
                return MD_ERROR;
            }

            cnt = 4000;

            while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_LRCRDY_MSK))) && (--cnt));

            md_cmu_clock_update(32768);
            break;

        case MD_CMU_CLOCK_HOSC:
            assert_param(clock <= 24000000);

            MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, MD_CMU_CLOCK_HOSC << CMU_CSR_SYS_CMD_POSS);

            while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

            if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != MD_CMU_CLOCK_HOSC)
            {
                SYSCFG_LOCK();
                return MD_ERROR;
            }

            SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
            MODIFY_REG(CMU->HOSCCFG, CMU_HOSCCFG_FREQ_MSK, clock / 1000000 - 1);

            for (cnt = 8000; cnt; --cnt);

            cnt = 4000;

            while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCACT_MSK))) && (--cnt));

            cnt = 4000;

            while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCRDY_MSK))) && (--cnt));

            md_cmu_clock_update(clock);
            md_msc_set_flash_read_wait_cycle(0);
            break;

        default:
            break;
    }

    SYSCFG_LOCK();
    return MD_OK;
}

/**
  * @brief  Configure the bus division.
  * @param  bus: The type of bus:
  *          @arg CMU_SYS
  *          @arg CMU_PCLK
  * @param  div: The value of divider.
  * @retval None
  */
void md_cmu_div_config(md_cmu_bus_t bus, md_cmu_div_t div)
{
    SYSCFG_UNLOCK();

    switch (bus)
    {

        case MD_CMU_SYS:
            MODIFY_REG(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, div << CMU_CFGR_SYSDIV_POSS);
            break;

        case MD_CMU_PCLK:
            MODIFY_REG(CMU->CFGR, CMU_CFGR_PCLKDIV_MSK, div << CMU_CFGR_PCLKDIV_POSS);
            break;

        default:
            break;
    }

    SYSCFG_LOCK();
    return;
}

/**
  * @brief  Get AHB clock.
  * @retval The value of AHB clock.
  */
uint32_t md_cmu_get_hclk_clock(void)
{
    uint32_t sys_div = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);

    return md_system_clock >> sys_div;
}

/**
  * @brief  Get SYS clock
  * @retval The value of SYS clock
  */
uint32_t md_cmu_get_sys_clock(void)
{
    uint32_t sys_div = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);

    return md_system_clock >> sys_div;
}

/**
  * @brief  Get APB clock.
  * @retval The value of APB clock.
  */
uint32_t md_cmu_get_pclk_clock(void)
{
    uint32_t sys_div  = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);
    uint32_t apb_div = READ_BITS(CMU->CFGR, CMU_CFGR_PCLKDIV_MSK, CMU_CFGR_PCLKDIV_POSS);

    return (md_system_clock >> sys_div) >> apb_div;
}

/**
  * @brief  Gets current system clock.
  * @retval The value of system clock.
  */
uint32_t md_cmu_get_clock(void)
{
    return md_system_clock;
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

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
