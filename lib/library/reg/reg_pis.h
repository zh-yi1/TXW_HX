/**********************************************************************************
 *
 * @file    REG_PIS.h
 * @brief   PIS Head File
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

#ifndef __REG_PIS_H__
#define __REG_PIS_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */


/****************** Bit definition for PIS_CH0_CON register ************************/

#define	PIS_CH0_CON_SRCS_POSS	8U 
#define	PIS_CH0_CON_SRCS_POSE	11U 
#define	PIS_CH0_CON_SRCS_MSK	BITS(PIS_CH0_CON_SRCS_POSS,PIS_CH0_CON_SRCS_POSE)

#define	PIS_CH0_CON_MSIGS_POSS	0U 
#define	PIS_CH0_CON_MSIGS_POSE	3U 
#define	PIS_CH0_CON_MSIGS_MSK	BITS(PIS_CH0_CON_MSIGS_POSS,PIS_CH0_CON_MSIGS_POSE)

/****************** Bit definition for PIS_CH1_CON register ************************/

#define	PIS_CH1_CON_SRCS_POSS	8U 
#define	PIS_CH1_CON_SRCS_POSE	11U 
#define	PIS_CH1_CON_SRCS_MSK	BITS(PIS_CH1_CON_SRCS_POSS,PIS_CH1_CON_SRCS_POSE)

#define	PIS_CH1_CON_MSIGS_POSS	0U 
#define	PIS_CH1_CON_MSIGS_POSE	3U 
#define	PIS_CH1_CON_MSIGS_MSK	BITS(PIS_CH1_CON_MSIGS_POSS,PIS_CH1_CON_MSIGS_POSE)

/****************** Bit definition for PIS_CH2_CON register ************************/

#define	PIS_CH2_CON_SRCS_POSS	8U 
#define	PIS_CH2_CON_SRCS_POSE	11U 
#define	PIS_CH2_CON_SRCS_MSK	BITS(PIS_CH2_CON_SRCS_POSS,PIS_CH2_CON_SRCS_POSE)

#define	PIS_CH2_CON_MSIGS_POSS	0U 
#define	PIS_CH2_CON_MSIGS_POSE	3U 
#define	PIS_CH2_CON_MSIGS_MSK	BITS(PIS_CH2_CON_MSIGS_POSS,PIS_CH2_CON_MSIGS_POSE)

/****************** Bit definition for PIS_CH3_CON register ************************/

#define	PIS_CH3_CON_SRCS_POSS	8U 
#define	PIS_CH3_CON_SRCS_POSE	11U 
#define	PIS_CH3_CON_SRCS_MSK	BITS(PIS_CH3_CON_SRCS_POSS,PIS_CH3_CON_SRCS_POSE)

#define	PIS_CH3_CON_MSIGS_POSS	0U 
#define	PIS_CH3_CON_MSIGS_POSE	3U 
#define	PIS_CH3_CON_MSIGS_MSK	BITS(PIS_CH3_CON_MSIGS_POSS,PIS_CH3_CON_MSIGS_POSE)

/****************** Bit definition for PIS_CH4_CON register ************************/

#define	PIS_CH4_CON_SRCS_POSS	8U 
#define	PIS_CH4_CON_SRCS_POSE	11U 
#define	PIS_CH4_CON_SRCS_MSK	BITS(PIS_CH4_CON_SRCS_POSS,PIS_CH4_CON_SRCS_POSE)

#define	PIS_CH4_CON_MSIGS_POSS	0U 
#define	PIS_CH4_CON_MSIGS_POSE	3U 
#define	PIS_CH4_CON_MSIGS_MSK	BITS(PIS_CH4_CON_MSIGS_POSS,PIS_CH4_CON_MSIGS_POSE)

/****************** Bit definition for PIS_CH5_CON register ************************/

#define	PIS_CH5_CON_SRCS_POSS	8U 
#define	PIS_CH5_CON_SRCS_POSE	11U 
#define	PIS_CH5_CON_SRCS_MSK	BITS(PIS_CH5_CON_SRCS_POSS,PIS_CH5_CON_SRCS_POSE)

#define	PIS_CH5_CON_MSIGS_POSS	0U 
#define	PIS_CH5_CON_MSIGS_POSE	3U 
#define	PIS_CH5_CON_MSIGS_MSK	BITS(PIS_CH5_CON_MSIGS_POSS,PIS_CH5_CON_MSIGS_POSE)

/****************** Bit definition for PIS_CH_OER register ************************/

#define	PIS_CH_OER_CH5OE_POS	5U 
#define	PIS_CH_OER_CH5OE_MSK	BIT(PIS_CH_OER_CH5OE_POS)

#define	PIS_CH_OER_CH4OE_POS	4U 
#define	PIS_CH_OER_CH4OE_MSK	BIT(PIS_CH_OER_CH4OE_POS)

#define	PIS_CH_OER_CH3OE_POS	3U 
#define	PIS_CH_OER_CH3OE_MSK	BIT(PIS_CH_OER_CH3OE_POS)

#define	PIS_CH_OER_CH2OE_POS	2U 
#define	PIS_CH_OER_CH2OE_MSK	BIT(PIS_CH_OER_CH2OE_POS)

#define	PIS_CH_OER_CH1OE_POS	1U 
#define	PIS_CH_OER_CH1OE_MSK	BIT(PIS_CH_OER_CH1OE_POS)

#define	PIS_CH_OER_CH0OE_POS	0U 
#define	PIS_CH_OER_CH0OE_MSK	BIT(PIS_CH_OER_CH0OE_POS)

/****************** Bit definition for PIS_TAR_CON0 register ************************/

#define	PIS_TAR_CON0_GP16C2T2_CH2IN_SEL_POS	25U 
#define	PIS_TAR_CON0_GP16C2T2_CH2IN_SEL_MSK	BIT(PIS_TAR_CON0_GP16C2T2_CH2IN_SEL_POS)

#define	PIS_TAR_CON0_GP16C2T2_CH1IN_SEL_POS	24U 
#define	PIS_TAR_CON0_GP16C2T2_CH1IN_SEL_MSK	BIT(PIS_TAR_CON0_GP16C2T2_CH1IN_SEL_POS)

#define	PIS_TAR_CON0_GP16C2T1_CH2IN_SEL_POS	17U 
#define	PIS_TAR_CON0_GP16C2T1_CH2IN_SEL_MSK	BIT(PIS_TAR_CON0_GP16C2T1_CH2IN_SEL_POS)

#define	PIS_TAR_CON0_GP16C2T1_CH1IN_SEL_POS	16U 
#define	PIS_TAR_CON0_GP16C2T1_CH1IN_SEL_MSK	BIT(PIS_TAR_CON0_GP16C2T1_CH1IN_SEL_POS)

#define	PIS_TAR_CON0_GP16C2T0_CH2IN_SEL_POS	9U 
#define	PIS_TAR_CON0_GP16C2T0_CH2IN_SEL_MSK	BIT(PIS_TAR_CON0_GP16C2T0_CH2IN_SEL_POS)

#define	PIS_TAR_CON0_GP16C2T0_CH1IN_SEL_POS	8U 
#define	PIS_TAR_CON0_GP16C2T0_CH1IN_SEL_MSK	BIT(PIS_TAR_CON0_GP16C2T0_CH1IN_SEL_POS)

#define	PIS_TAR_CON0_AD16C4T0_BRKIN_SEL_POS	4U 
#define	PIS_TAR_CON0_AD16C4T0_BRKIN_SEL_MSK	BIT(PIS_TAR_CON0_AD16C4T0_BRKIN_SEL_POS)

#define	PIS_TAR_CON0_AD16C4T0_CH4IN_SEL_POS	3U 
#define	PIS_TAR_CON0_AD16C4T0_CH4IN_SEL_MSK	BIT(PIS_TAR_CON0_AD16C4T0_CH4IN_SEL_POS)

#define	PIS_TAR_CON0_AD16C4T0_CH3IN_SEL_POS	2U 
#define	PIS_TAR_CON0_AD16C4T0_CH3IN_SEL_MSK	BIT(PIS_TAR_CON0_AD16C4T0_CH3IN_SEL_POS)

#define	PIS_TAR_CON0_AD16C4T0_CH2IN_SEL_POS	1U 
#define	PIS_TAR_CON0_AD16C4T0_CH2IN_SEL_MSK	BIT(PIS_TAR_CON0_AD16C4T0_CH2IN_SEL_POS)

#define	PIS_TAR_CON0_AD16C4T0_CH1IN_SEL_POS	0U 
#define	PIS_TAR_CON0_AD16C4T0_CH1IN_SEL_MSK	BIT(PIS_TAR_CON0_AD16C4T0_CH1IN_SEL_POS)

/****************** Bit definition for PIS_TAR_CON1 register ************************/

#define	PIS_TAR_CON1_SPI_CLK_SEL_POS	9U 
#define	PIS_TAR_CON1_SPI_CLK_SEL_MSK	BIT(PIS_TAR_CON1_SPI_CLK_SEL_POS)

#define	PIS_TAR_CON1_SPI_RX_SEL_POS	8U 
#define	PIS_TAR_CON1_SPI_RX_SEL_MSK	BIT(PIS_TAR_CON1_SPI_RX_SEL_POS)

#define	PIS_TAR_CON1_USART1_RXD_SEL_POS	1U 
#define	PIS_TAR_CON1_USART1_RXD_SEL_MSK	BIT(PIS_TAR_CON1_USART1_RXD_SEL_POS)

#define	PIS_TAR_CON1_USART0_RXD_SEL_POS	0U 
#define	PIS_TAR_CON1_USART0_RXD_SEL_MSK	BIT(PIS_TAR_CON1_USART0_RXD_SEL_POS)

/****************** Bit definition for PIS_TXMCR register ************************/

#define	PIS_TXMCR_TXMLVLS_POS	8U 
#define	PIS_TXMCR_TXMLVLS_MSK	BIT(PIS_TXMCR_TXMLVLS_POS)

#define	PIS_TXMCR_TXMSS_POSS	4U 
#define	PIS_TXMCR_TXMSS_POSE	7U 
#define	PIS_TXMCR_TXMSS_MSK	BITS(PIS_TXMCR_TXMSS_POSS,PIS_TXMCR_TXMSS_POSE)

#define	PIS_TXMCR_TXSIGS_POSS	0U 
#define	PIS_TXMCR_TXSIGS_POSE	3U 
#define	PIS_TXMCR_TXSIGS_MSK	BITS(PIS_TXMCR_TXSIGS_POSS,PIS_TXMCR_TXSIGS_POSE)

typedef struct
{
	__IO uint32_t CH_CON[6];
	uint32_t RESERVED0[10] ;
	__IO uint32_t CH_OER;
	__IO uint32_t TAR_CON0;
	__IO uint32_t TAR_CON1;
	uint32_t RESERVED1[5] ;
	__IO uint32_t TXMCR;
} PIS_TypeDef;





#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
