/**********************************************************************************
 *
 * @file    REG_CMU.h
 * @brief   CMU Head File
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

#ifndef __REG_CMU_H__
#define __REG_CMU_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */


/****************** Bit definition for CMU_CSR register ************************/

#define	CMU_CSR_CFT_RDYN_POS	25U 
#define	CMU_CSR_CFT_RDYN_MSK	BIT(CMU_CSR_CFT_RDYN_POS)

#define	CMU_CSR_CFT_STU_POS	24U 
#define	CMU_CSR_CFT_STU_MSK	BIT(CMU_CSR_CFT_STU_POS)

#define	CMU_CSR_CFT_CMD_POSS	16U 
#define	CMU_CSR_CFT_CMD_POSE	23U 
#define	CMU_CSR_CFT_CMD_MSK	BITS(CMU_CSR_CFT_CMD_POSS,CMU_CSR_CFT_CMD_POSE)

#define	CMU_CSR_SYS_RDYN_POS	12U 
#define	CMU_CSR_SYS_RDYN_MSK	BIT(CMU_CSR_SYS_RDYN_POS)

#define	CMU_CSR_SYS_STU_POSS	8U 
#define	CMU_CSR_SYS_STU_POSE	9U 
#define	CMU_CSR_SYS_STU_MSK	BITS(CMU_CSR_SYS_STU_POSS,CMU_CSR_SYS_STU_POSE)

#define	CMU_CSR_SYS_CMD_POSS	0U 
#define	CMU_CSR_SYS_CMD_POSE	1U 
#define	CMU_CSR_SYS_CMD_MSK	BITS(CMU_CSR_SYS_CMD_POSS,CMU_CSR_SYS_CMD_POSE)

/****************** Bit definition for CMU_CFGR register ************************/

#define	CMU_CFGR_HRCFSW_POSS	24U 
#define	CMU_CFGR_HRCFSW_POSE	25U 
#define	CMU_CFGR_HRCFSW_MSK	BITS(CMU_CFGR_HRCFSW_POSS,CMU_CFGR_HRCFSW_POSE)

#define	CMU_CFGR_PCLKDIV_POSS	16U 
#define	CMU_CFGR_PCLKDIV_POSE	19U 
#define	CMU_CFGR_PCLKDIV_MSK	BITS(CMU_CFGR_PCLKDIV_POSS,CMU_CFGR_PCLKDIV_POSE)

#define	CMU_CFGR_SYSDIV_POSS	12U 
#define	CMU_CFGR_SYSDIV_POSE	15U 
#define	CMU_CFGR_SYSDIV_MSK	BITS(CMU_CFGR_SYSDIV_POSS,CMU_CFGR_SYSDIV_POSE)

/****************** Bit definition for CMU_CLKENR register ************************/

#define	CMU_CLKENR_HOSCFLYBPS_POS	10U 
#define	CMU_CLKENR_HOSCFLYBPS_MSK	BIT(CMU_CLKENR_HOSCFLYBPS_POS)

#define	CMU_CLKENR_HOSCBPS_POS	9U 
#define	CMU_CLKENR_HOSCBPS_MSK	BIT(CMU_CLKENR_HOSCBPS_POS)

#define	CMU_CLKENR_HOSC1M_POS	8U 
#define	CMU_CLKENR_HOSC1M_MSK	BIT(CMU_CLKENR_HOSC1M_POS)

#define	CMU_CLKENR_HRCEN_POS	2U 
#define	CMU_CLKENR_HRCEN_MSK	BIT(CMU_CLKENR_HRCEN_POS)

#define	CMU_CLKENR_HOSCEN_POS	0U 
#define	CMU_CLKENR_HOSCEN_MSK	BIT(CMU_CLKENR_HOSCEN_POS)

/****************** Bit definition for CMU_CLKSR register ************************/

#define	CMU_CLKSR_LRCRDY_POS	19U 
#define	CMU_CLKSR_LRCRDY_MSK	BIT(CMU_CLKSR_LRCRDY_POS)

#define	CMU_CLKSR_HRCRDY_POS	18U 
#define	CMU_CLKSR_HRCRDY_MSK	BIT(CMU_CLKSR_HRCRDY_POS)

#define	CMU_CLKSR_HOSCRDY_POS	16U 
#define	CMU_CLKSR_HOSCRDY_MSK	BIT(CMU_CLKSR_HOSCRDY_POS)

#define	CMU_CLKSR_HRCACT_POS	2U 
#define	CMU_CLKSR_HRCACT_MSK	BIT(CMU_CLKSR_HRCACT_POS)

#define	CMU_CLKSR_HOSCACT_POS	0U 
#define	CMU_CLKSR_HOSCACT_MSK	BIT(CMU_CLKSR_HOSCACT_POS)

/****************** Bit definition for CMU_HOSCCFG register ************************/

#define	CMU_HOSCCFG_FREQ_POSS	0U 
#define	CMU_HOSCCFG_FREQ_POSE	4U 
#define	CMU_HOSCCFG_FREQ_MSK	BITS(CMU_HOSCCFG_FREQ_POSS,CMU_HOSCCFG_FREQ_POSE)

/****************** Bit definition for CMU_HOSMCR register ************************/

#define	CMU_HOSMCR_NMIE_POS	20U 
#define	CMU_HOSMCR_NMIE_MSK	BIT(CMU_HOSMCR_NMIE_POS)

#define	CMU_HOSMCR_STPIF_POS	19U 
#define	CMU_HOSMCR_STPIF_MSK	BIT(CMU_HOSMCR_STPIF_POS)

#define	CMU_HOSMCR_STRIF_POS	18U 
#define	CMU_HOSMCR_STRIF_MSK	BIT(CMU_HOSMCR_STRIF_POS)

#define	CMU_HOSMCR_STPIE_POS	17U 
#define	CMU_HOSMCR_STPIE_MSK	BIT(CMU_HOSMCR_STPIE_POS)

#define	CMU_HOSMCR_STRIE_POS	16U 
#define	CMU_HOSMCR_STRIE_MSK	BIT(CMU_HOSMCR_STRIE_POS)

#define	CMU_HOSMCR_FRQS_POSS	8U 
#define	CMU_HOSMCR_FRQS_POSE	10U 
#define	CMU_HOSMCR_FRQS_MSK	BITS(CMU_HOSMCR_FRQS_POSS,CMU_HOSMCR_FRQS_POSE)

#define	CMU_HOSMCR_FLAG_POS	1U 
#define	CMU_HOSMCR_FLAG_MSK	BIT(CMU_HOSMCR_FLAG_POS)

#define	CMU_HOSMCR_EN_POS	0U 
#define	CMU_HOSMCR_EN_MSK	BIT(CMU_HOSMCR_EN_POS)

/****************** Bit definition for CMU_CLKOCR register ************************/

#define	CMU_CLKOCR_LSCOS_POSS	24U 
#define	CMU_CLKOCR_LSCOS_POSE	26U 
#define	CMU_CLKOCR_LSCOS_MSK	BITS(CMU_CLKOCR_LSCOS_POSS,CMU_CLKOCR_LSCOS_POSE)

#define	CMU_CLKOCR_LSCOEN_POS	16U 
#define	CMU_CLKOCR_LSCOEN_MSK	BIT(CMU_CLKOCR_LSCOEN_POS)

#define	CMU_CLKOCR_HSCODIV_POSS	12U 
#define	CMU_CLKOCR_HSCODIV_POSE	14U 
#define	CMU_CLKOCR_HSCODIV_MSK	BITS(CMU_CLKOCR_HSCODIV_POSS,CMU_CLKOCR_HSCODIV_POSE)

#define	CMU_CLKOCR_HSCOS_POSS	8U 
#define	CMU_CLKOCR_HSCOS_POSE	10U 
#define	CMU_CLKOCR_HSCOS_MSK	BITS(CMU_CLKOCR_HSCOS_POSS,CMU_CLKOCR_HSCOS_POSE)

#define	CMU_CLKOCR_HSCOEN_POS	0U 
#define	CMU_CLKOCR_HSCOEN_MSK	BIT(CMU_CLKOCR_HSCOEN_POS)

/****************** Bit definition for CMU_BUZZCR register ************************/

#define	CMU_BUZZCR_DAT_POSS	16U 
#define	CMU_BUZZCR_DAT_POSE	31U 
#define	CMU_BUZZCR_DAT_MSK	BITS(CMU_BUZZCR_DAT_POSS,CMU_BUZZCR_DAT_POSE)

#define	CMU_BUZZCR_DIV_POSS	8U 
#define	CMU_BUZZCR_DIV_POSE	10U 
#define	CMU_BUZZCR_DIV_MSK	BITS(CMU_BUZZCR_DIV_POSS,CMU_BUZZCR_DIV_POSE)

#define	CMU_BUZZCR_EN_POS	0U 
#define	CMU_BUZZCR_EN_MSK	BIT(CMU_BUZZCR_EN_POS)

/****************** Bit definition for CMU_AHBENR register ************************/

#define	CMU_AHBENR_PISEN_POS	5U 
#define	CMU_AHBENR_PISEN_MSK	BIT(CMU_AHBENR_PISEN_POS)

#define	CMU_AHBENR_CRCEN_POS	1U 
#define	CMU_AHBENR_CRCEN_MSK	BIT(CMU_AHBENR_CRCEN_POS)

#define	CMU_AHBENR_GPIOEN_POS	0U 
#define	CMU_AHBENR_GPIOEN_MSK	BIT(CMU_AHBENR_GPIOEN_POS)

/****************** Bit definition for CMU_APBENR register ************************/

#define	CMU_APBENR_ACMP1EN_POS	27U 
#define	CMU_APBENR_ACMP1EN_MSK	BIT(CMU_APBENR_ACMP1EN_POS)

#define	CMU_APBENR_ACMP0EN_POS	26U 
#define	CMU_APBENR_ACMP0EN_MSK	BIT(CMU_APBENR_ACMP0EN_POS)

#define	CMU_APBENR_ADCEN_POS	25U 
#define	CMU_APBENR_ADCEN_MSK	BIT(CMU_APBENR_ADCEN_POS)

#define	CMU_APBENR_DBGCEN_POS	24U 
#define	CMU_APBENR_DBGCEN_MSK	BIT(CMU_APBENR_DBGCEN_POS)

#define	CMU_APBENR_IWDTEN_POS	23U 
#define	CMU_APBENR_IWDTEN_MSK	BIT(CMU_APBENR_IWDTEN_POS)

#define	CMU_APBENR_WWDTEN_POS	22U 
#define	CMU_APBENR_WWDTEN_MSK	BIT(CMU_APBENR_WWDTEN_POS)

#define	CMU_APBENR_I2C1EN_POS	21U 
#define	CMU_APBENR_I2C1EN_MSK	BIT(CMU_APBENR_I2C1EN_POS)

#define	CMU_APBENR_I2C0EN_POS	20U 
#define	CMU_APBENR_I2C0EN_MSK	BIT(CMU_APBENR_I2C0EN_POS)

#define	CMU_APBENR_SPI0EN_POS	16U 
#define	CMU_APBENR_SPI0EN_MSK	BIT(CMU_APBENR_SPI0EN_POS)

#define	CMU_APBENR_USART1EN_POS	13U 
#define	CMU_APBENR_USART1EN_MSK	BIT(CMU_APBENR_USART1EN_POS)

#define	CMU_APBENR_USART0EN_POS	12U 
#define	CMU_APBENR_USART0EN_MSK	BIT(CMU_APBENR_USART0EN_POS)

#define	CMU_APBENR_GP16C2T2EN_POS	4U 
#define	CMU_APBENR_GP16C2T2EN_MSK	BIT(CMU_APBENR_GP16C2T2EN_POS)

#define	CMU_APBENR_GP16C2T1EN_POS	3U 
#define	CMU_APBENR_GP16C2T1EN_MSK	BIT(CMU_APBENR_GP16C2T1EN_POS)

#define	CMU_APBENR_GP16C2T0EN_POS	2U 
#define	CMU_APBENR_GP16C2T0EN_MSK	BIT(CMU_APBENR_GP16C2T0EN_POS)

#define	CMU_APBENR_BS16T0EN_POS	1U 
#define	CMU_APBENR_BS16T0EN_MSK	BIT(CMU_APBENR_BS16T0EN_POS)

#define	CMU_APBENR_AD16C4T0EN_POS	0U 
#define	CMU_APBENR_AD16C4T0EN_MSK	BIT(CMU_APBENR_AD16C4T0EN_POS)

/****************** Bit definition for CMU_LPENR register ************************/

#define	CMU_LPENR_HOSCEN_POS	3U 
#define	CMU_LPENR_HOSCEN_MSK	BIT(CMU_LPENR_HOSCEN_POS)

#define	CMU_LPENR_HRCEN_POS	2U 
#define	CMU_LPENR_HRCEN_MSK	BIT(CMU_LPENR_HRCEN_POS)

typedef struct
{
	__O uint32_t CSR;
	__IO uint32_t CFGR;
	uint32_t RESERVED0[2] ;
	__IO uint32_t CLKENR;
	__I uint32_t CLKSR;
	uint32_t RESERVED1 ;
	__IO uint32_t HOSCCFG;
	__IO uint32_t HOSMCR;
	uint32_t RESERVED2[3] ;
	__IO uint32_t CLKOCR;
	__IO uint32_t BUZZCR;
	uint32_t RESERVED3[2] ;
	__IO uint32_t AHBENR;
	uint32_t RESERVED4[3] ;
	__IO uint32_t APBENR;
	uint32_t RESERVED5[3] ;
	__IO uint32_t LPENR;
} CMU_TypeDef;





#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
