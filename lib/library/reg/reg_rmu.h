/**********************************************************************************
 *
 * @file    REG_RMU.h
 * @brief   RMU Head File
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

#ifndef __REG_RMU_H__
#define __REG_RMU_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */


/****************** Bit definition for RMU_CR register ************************/

#define	RMU_CR_BORVS_POSS	4U 
#define	RMU_CR_BORVS_POSE	5U 
#define	RMU_CR_BORVS_MSK	BITS(RMU_CR_BORVS_POSS,RMU_CR_BORVS_POSE)

#define	RMU_CR_BORFLT_POSS	1U 
#define	RMU_CR_BORFLT_POSE	3U 
#define	RMU_CR_BORFLT_MSK	BITS(RMU_CR_BORFLT_POSS,RMU_CR_BORFLT_POSE)

#define	RMU_CR_BOREN_POS	0U 
#define	RMU_CR_BOREN_MSK	BIT(RMU_CR_BOREN_POS)

/****************** Bit definition for RMU_RSTSR register ************************/

#define	RMU_RSTSR_CFGERR_POS	16U 
#define	RMU_RSTSR_CFGERR_MSK	BIT(RMU_RSTSR_CFGERR_POS)

#define	RMU_RSTSR_CFG_POS	10U 
#define	RMU_RSTSR_CFG_MSK	BIT(RMU_RSTSR_CFG_POS)

#define	RMU_RSTSR_CPU_POS	9U 
#define	RMU_RSTSR_CPU_MSK	BIT(RMU_RSTSR_CPU_POS)

#define	RMU_RSTSR_MCU_POS	8U 
#define	RMU_RSTSR_MCU_MSK	BIT(RMU_RSTSR_MCU_POS)

#define	RMU_RSTSR_CHIP_POS	7U 
#define	RMU_RSTSR_CHIP_MSK	BIT(RMU_RSTSR_CHIP_POS)

#define	RMU_RSTSR_LOCKUP_POS	6U 
#define	RMU_RSTSR_LOCKUP_MSK	BIT(RMU_RSTSR_LOCKUP_POS)

#define	RMU_RSTSR_WWDT_POS	5U 
#define	RMU_RSTSR_WWDT_MSK	BIT(RMU_RSTSR_WWDT_POS)

#define	RMU_RSTSR_IWDT_POS	4U 
#define	RMU_RSTSR_IWDT_MSK	BIT(RMU_RSTSR_IWDT_POS)

#define	RMU_RSTSR_NMRST_POS	3U 
#define	RMU_RSTSR_NMRST_MSK	BIT(RMU_RSTSR_NMRST_POS)

#define	RMU_RSTSR_BOR_POS	2U 
#define	RMU_RSTSR_BOR_MSK	BIT(RMU_RSTSR_BOR_POS)

#define	RMU_RSTSR_POR_POS	0U 
#define	RMU_RSTSR_POR_MSK	BIT(RMU_RSTSR_POR_POS)

/****************** Bit definition for RMU_CRSTSR register ************************/

#define	RMU_CRSTSR_CFG_POS	10U 
#define	RMU_CRSTSR_CFG_MSK	BIT(RMU_CRSTSR_CFG_POS)

#define	RMU_CRSTSR_CPU_POS	9U 
#define	RMU_CRSTSR_CPU_MSK	BIT(RMU_CRSTSR_CPU_POS)

#define	RMU_CRSTSR_MCU_POS	8U 
#define	RMU_CRSTSR_MCU_MSK	BIT(RMU_CRSTSR_MCU_POS)

#define	RMU_CRSTSR_CHIP_POS	7U 
#define	RMU_CRSTSR_CHIP_MSK	BIT(RMU_CRSTSR_CHIP_POS)

#define	RMU_CRSTSR_LOCKUP_POS	6U 
#define	RMU_CRSTSR_LOCKUP_MSK	BIT(RMU_CRSTSR_LOCKUP_POS)

#define	RMU_CRSTSR_WWDT_POS	5U 
#define	RMU_CRSTSR_WWDT_MSK	BIT(RMU_CRSTSR_WWDT_POS)

#define	RMU_CRSTSR_IWDT_POS	4U 
#define	RMU_CRSTSR_IWDT_MSK	BIT(RMU_CRSTSR_IWDT_POS)

#define	RMU_CRSTSR_NMRST_POS	3U 
#define	RMU_CRSTSR_NMRST_MSK	BIT(RMU_CRSTSR_NMRST_POS)

#define	RMU_CRSTSR_BOR_POS	2U 
#define	RMU_CRSTSR_BOR_MSK	BIT(RMU_CRSTSR_BOR_POS)

#define	RMU_CRSTSR_POR_POS	0U 
#define	RMU_CRSTSR_POR_MSK	BIT(RMU_CRSTSR_POR_POS)

/****************** Bit definition for RMU_AHB1RSTR register ************************/

#define	RMU_AHB1RSTR_PISRST_POS	5U 
#define	RMU_AHB1RSTR_PISRST_MSK	BIT(RMU_AHB1RSTR_PISRST_POS)

#define	RMU_AHB1RSTR_CRCRST_POS	1U 
#define	RMU_AHB1RSTR_CRCRST_MSK	BIT(RMU_AHB1RSTR_CRCRST_POS)

#define	RMU_AHB1RSTR_GPIORST_POS	0U 
#define	RMU_AHB1RSTR_GPIORST_MSK	BIT(RMU_AHB1RSTR_GPIORST_POS)

/****************** Bit definition for RMU_AHB2RSTR register ************************/

#define	RMU_AHB2RSTR_CPURST_POS	1U 
#define	RMU_AHB2RSTR_CPURST_MSK	BIT(RMU_AHB2RSTR_CPURST_POS)

#define	RMU_AHB2RSTR_CHIPRST_POS	0U 
#define	RMU_AHB2RSTR_CHIPRST_MSK	BIT(RMU_AHB2RSTR_CHIPRST_POS)

/****************** Bit definition for RMU_APBRSTR register ************************/

#define	RMU_APBRSTR_ACMP1RST_POS	27U 
#define	RMU_APBRSTR_ACMP1RST_MSK	BIT(RMU_APBRSTR_ACMP1RST_POS)

#define	RMU_APBRSTR_ACMP0RST_POS	26U 
#define	RMU_APBRSTR_ACMP0RST_MSK	BIT(RMU_APBRSTR_ACMP0RST_POS)

#define	RMU_APBRSTR_ADCRST_POS	25U 
#define	RMU_APBRSTR_ADCRST_MSK	BIT(RMU_APBRSTR_ADCRST_POS)

#define	RMU_APBRSTR_DBGCONRST_POS	24U 
#define	RMU_APBRSTR_DBGCONRST_MSK	BIT(RMU_APBRSTR_DBGCONRST_POS)

#define	RMU_APBRSTR_IWDTRST_POS	23U 
#define	RMU_APBRSTR_IWDTRST_MSK	BIT(RMU_APBRSTR_IWDTRST_POS)

#define	RMU_APBRSTR_WWDTRST_POS	22U 
#define	RMU_APBRSTR_WWDTRST_MSK	BIT(RMU_APBRSTR_WWDTRST_POS)

#define	RMU_APBRSTR_I2C1RST_POS	21U 
#define	RMU_APBRSTR_I2C1RST_MSK	BIT(RMU_APBRSTR_I2C1RST_POS)

#define	RMU_APBRSTR_I2C0RST_POS	20U 
#define	RMU_APBRSTR_I2C0RST_MSK	BIT(RMU_APBRSTR_I2C0RST_POS)

#define	RMU_APBRSTR_SPI0RST_POS	16U 
#define	RMU_APBRSTR_SPI0RST_MSK	BIT(RMU_APBRSTR_SPI0RST_POS)

#define	RMU_APBRSTR_USART1RST_POS	13U 
#define	RMU_APBRSTR_USART1RST_MSK	BIT(RMU_APBRSTR_USART1RST_POS)

#define	RMU_APBRSTR_USART0RST_POS	12U 
#define	RMU_APBRSTR_USART0RST_MSK	BIT(RMU_APBRSTR_USART0RST_POS)

#define	RMU_APBRSTR_GP16C2T2RST_POS	4U 
#define	RMU_APBRSTR_GP16C2T2RST_MSK	BIT(RMU_APBRSTR_GP16C2T2RST_POS)

#define	RMU_APBRSTR_GP16C2T1RST_POS	3U 
#define	RMU_APBRSTR_GP16C2T1RST_MSK	BIT(RMU_APBRSTR_GP16C2T1RST_POS)

#define	RMU_APBRSTR_GP16C2T0RST_POS	2U 
#define	RMU_APBRSTR_GP16C2T0RST_MSK	BIT(RMU_APBRSTR_GP16C2T0RST_POS)

#define	RMU_APBRSTR_BS16T0RST_POS	1U 
#define	RMU_APBRSTR_BS16T0RST_MSK	BIT(RMU_APBRSTR_BS16T0RST_POS)

#define	RMU_APBRSTR_AD16C4T0RST_POS	0U 
#define	RMU_APBRSTR_AD16C4T0RST_MSK	BIT(RMU_APBRSTR_AD16C4T0RST_POS)

typedef struct
{
	__IO uint32_t CR;
	uint32_t RESERVED0[3] ;
	__I uint32_t RSTSR;
	__O uint32_t CRSTSR;
	uint32_t RESERVED1[2] ;
	__IO uint32_t AHB1RSTR;
	__IO uint32_t AHB2RSTR;
	uint32_t RESERVED2[2] ;
	__IO uint32_t APBRSTR;
} RMU_TypeDef;





#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
