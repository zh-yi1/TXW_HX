/**********************************************************************************
 *
 * @file    REG_USART.h
 * @brief   USART Head File
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

#ifndef __REG_USART_H__
#define __REG_USART_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */


/****************** Bit definition for USART_STAT register ************************/

#define	USART_STAT_CTSIF_POS	9U 
#define	USART_STAT_CTSIF_MSK	BIT(USART_STAT_CTSIF_POS)

#define	USART_STAT_TXEMPIF_POS	7U 
#define	USART_STAT_TXEMPIF_MSK	BIT(USART_STAT_TXEMPIF_POS)

#define	USART_STAT_TXCIF_POS	6U 
#define	USART_STAT_TXCIF_MSK	BIT(USART_STAT_TXCIF_POS)

#define	USART_STAT_RXNEIF_POS	5U 
#define	USART_STAT_RXNEIF_MSK	BIT(USART_STAT_RXNEIF_POS)

#define	USART_STAT_IDLEIF_POS	4U 
#define	USART_STAT_IDLEIF_MSK	BIT(USART_STAT_IDLEIF_POS)

#define	USART_STAT_OVRIF_POS	3U 
#define	USART_STAT_OVRIF_MSK	BIT(USART_STAT_OVRIF_POS)

#define	USART_STAT_NDETIF_POS	2U 
#define	USART_STAT_NDETIF_MSK	BIT(USART_STAT_NDETIF_POS)

#define	USART_STAT_FERRIF_POS	1U 
#define	USART_STAT_FERRIF_MSK	BIT(USART_STAT_FERRIF_POS)

#define	USART_STAT_PERRIF_POS	0U 
#define	USART_STAT_PERRIF_MSK	BIT(USART_STAT_PERRIF_POS)

/****************** Bit definition for USART_DATA register ************************/

#define	USART_DATA_VAL_POSS	0U 
#define	USART_DATA_VAL_POSE	8U 
#define	USART_DATA_VAL_MSK	BITS(USART_DATA_VAL_POSS,USART_DATA_VAL_POSE)

/****************** Bit definition for USART_BAUDCON register ************************/

#define	USART_BAUDCON_DIV_M_POSS	4U 
#define	USART_BAUDCON_DIV_M_POSE	15U 
#define	USART_BAUDCON_DIV_M_MSK	BITS(USART_BAUDCON_DIV_M_POSS,USART_BAUDCON_DIV_M_POSE)

#define	USART_BAUDCON_DIV_F_POSS	0U 
#define	USART_BAUDCON_DIV_F_POSE	3U 
#define	USART_BAUDCON_DIV_F_MSK	BITS(USART_BAUDCON_DIV_F_POSS,USART_BAUDCON_DIV_F_POSE)

/****************** Bit definition for USART_CON0 register ************************/

#define	USART_CON0_TXINV_POS	15U 
#define	USART_CON0_TXINV_MSK	BIT(USART_CON0_TXINV_POS)

#define	USART_CON0_RXINV_POS	14U 
#define	USART_CON0_RXINV_MSK	BIT(USART_CON0_RXINV_POS)

#define	USART_CON0_EN_POS	13U 
#define	USART_CON0_EN_MSK	BIT(USART_CON0_EN_POS)

#define	USART_CON0_DLEN_POS	12U 
#define	USART_CON0_DLEN_MSK	BIT(USART_CON0_DLEN_POS)

#define	USART_CON0_WKMOD_POS	11U 
#define	USART_CON0_WKMOD_MSK	BIT(USART_CON0_WKMOD_POS)

#define	USART_CON0_PEN_POS	10U 
#define	USART_CON0_PEN_MSK	BIT(USART_CON0_PEN_POS)

#define	USART_CON0_PSEL_POS	9U 
#define	USART_CON0_PSEL_MSK	BIT(USART_CON0_PSEL_POS)

#define	USART_CON0_PERRIE_POS	8U 
#define	USART_CON0_PERRIE_MSK	BIT(USART_CON0_PERRIE_POS)

#define	USART_CON0_TXEMPIE_POS	7U 
#define	USART_CON0_TXEMPIE_MSK	BIT(USART_CON0_TXEMPIE_POS)

#define	USART_CON0_TXCIE_POS	6U 
#define	USART_CON0_TXCIE_MSK	BIT(USART_CON0_TXCIE_POS)

#define	USART_CON0_RXNEIE_POS	5U 
#define	USART_CON0_RXNEIE_MSK	BIT(USART_CON0_RXNEIE_POS)

#define	USART_CON0_IDLEIE_POS	4U 
#define	USART_CON0_IDLEIE_MSK	BIT(USART_CON0_IDLEIE_POS)

#define	USART_CON0_TXEN_POS	3U 
#define	USART_CON0_TXEN_MSK	BIT(USART_CON0_TXEN_POS)

#define	USART_CON0_RXEN_POS	2U 
#define	USART_CON0_RXEN_MSK	BIT(USART_CON0_RXEN_POS)

#define	USART_CON0_RXWK_POS	1U 
#define	USART_CON0_RXWK_MSK	BIT(USART_CON0_RXWK_POS)

/****************** Bit definition for USART_CON1 register ************************/

#define	USART_CON1_STPLEN_POSS	12U 
#define	USART_CON1_STPLEN_POSE	13U 
#define	USART_CON1_STPLEN_MSK	BITS(USART_CON1_STPLEN_POSS,USART_CON1_STPLEN_POSE)

#define	USART_CON1_SCKEN_POS	11U 
#define	USART_CON1_SCKEN_MSK	BIT(USART_CON1_SCKEN_POS)

#define	USART_CON1_SCKPOL_POS	10U 
#define	USART_CON1_SCKPOL_MSK	BIT(USART_CON1_SCKPOL_POS)

#define	USART_CON1_SCKPHA_POS	9U 
#define	USART_CON1_SCKPHA_MSK	BIT(USART_CON1_SCKPHA_POS)

#define	USART_CON1_LBCP_POS	8U 
#define	USART_CON1_LBCP_MSK	BIT(USART_CON1_LBCP_POS)

#define	USART_CON1_ADDR_POSS	0U 
#define	USART_CON1_ADDR_POSE	3U 
#define	USART_CON1_ADDR_MSK	BITS(USART_CON1_ADDR_POSS,USART_CON1_ADDR_POSE)

/****************** Bit definition for USART_CON2 register ************************/

#define	USART_CON2_CTSIE_POS	10U 
#define	USART_CON2_CTSIE_MSK	BIT(USART_CON2_CTSIE_POS)

#define	USART_CON2_CTSEN_POS	9U 
#define	USART_CON2_CTSEN_MSK	BIT(USART_CON2_CTSEN_POS)

#define	USART_CON2_RTSEN_POS	8U 
#define	USART_CON2_RTSEN_MSK	BIT(USART_CON2_RTSEN_POS)

#define	USART_CON2_TXDMAEN_POS	7U 
#define	USART_CON2_TXDMAEN_MSK	BIT(USART_CON2_TXDMAEN_POS)

#define	USART_CON2_RXDMAEN_POS	6U 
#define	USART_CON2_RXDMAEN_MSK	BIT(USART_CON2_RXDMAEN_POS)

#define	USART_CON2_SMARTEN_POS	5U 
#define	USART_CON2_SMARTEN_MSK	BIT(USART_CON2_SMARTEN_POS)

#define	USART_CON2_NACK_POS	4U 
#define	USART_CON2_NACK_MSK	BIT(USART_CON2_NACK_POS)

#define	USART_CON2_HDPSEL_POS	3U 
#define	USART_CON2_HDPSEL_MSK	BIT(USART_CON2_HDPSEL_POS)

#define	USART_CON2_IREN_POS	1U 
#define	USART_CON2_IREN_MSK	BIT(USART_CON2_IREN_POS)

#define	USART_CON2_ERRIE_POS	0U 
#define	USART_CON2_ERRIE_MSK	BIT(USART_CON2_ERRIE_POS)

/****************** Bit definition for USART_GP register ************************/

#define	USART_GP_GTVAL_POSS	8U 
#define	USART_GP_GTVAL_POSE	15U 
#define	USART_GP_GTVAL_MSK	BITS(USART_GP_GTVAL_POSS,USART_GP_GTVAL_POSE)

#define	USART_GP_PSC_POSS	0U 
#define	USART_GP_PSC_POSE	7U 
#define	USART_GP_PSC_MSK	BITS(USART_GP_PSC_POSS,USART_GP_PSC_POSE)

typedef struct
{
	__IO uint32_t STAT;
	__IO uint32_t DATA;
	__IO uint32_t BAUDCON;
	__IO uint32_t CON0;
	__IO uint32_t CON1;
	__IO uint32_t CON2;
	__IO uint32_t GP;
} USART_TypeDef;





#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
