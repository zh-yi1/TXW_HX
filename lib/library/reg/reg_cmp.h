/**********************************************************************************
 *
 * @file    REG_ACMP.h
 * @brief   ACMP Head File
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

#ifndef __REG_ACMP_H__
#define __REG_ACMP_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */


/****************** Bit definition for ACMP_CON register ************************/

#define	ACMP_CON_FLTSEL_POSS	20U 
#define	ACMP_CON_FLTSEL_POSE	22U 
#define	ACMP_CON_FLTSEL_MSK	BITS(ACMP_CON_FLTSEL_POSS,ACMP_CON_FLTSEL_POSE)

#define	ACMP_CON_FALLEN_POS	17U 
#define	ACMP_CON_FALLEN_MSK	BIT(ACMP_CON_FALLEN_POS)

#define	ACMP_CON_RISEEN_POS	16U 
#define	ACMP_CON_RISEEN_MSK	BIT(ACMP_CON_RISEEN_POS)

#define	ACMP_CON_MODSEL_POSS	14U 
#define	ACMP_CON_MODSEL_POSE	15U 
#define	ACMP_CON_MODSEL_MSK	BITS(ACMP_CON_MODSEL_POSS,ACMP_CON_MODSEL_POSE)

#define	ACMP_CON_WARMUPT_POSS	8U 
#define	ACMP_CON_WARMUPT_POSE	10U 
#define	ACMP_CON_WARMUPT_MSK	BITS(ACMP_CON_WARMUPT_POSS,ACMP_CON_WARMUPT_POSE)

#define	ACMP_CON_HYSTSEL_POSS	4U 
#define	ACMP_CON_HYSTSEL_POSE	6U 
#define	ACMP_CON_HYSTSEL_MSK	BITS(ACMP_CON_HYSTSEL_POSS,ACMP_CON_HYSTSEL_POSE)

#define	ACMP_CON_OUTINV_POS	3U 
#define	ACMP_CON_OUTINV_MSK	BIT(ACMP_CON_OUTINV_POS)

#define	ACMP_CON_INACTV_POS	2U 
#define	ACMP_CON_INACTV_MSK	BIT(ACMP_CON_INACTV_POS)

#define	ACMP_CON_EN_POS	0U 
#define	ACMP_CON_EN_MSK	BIT(ACMP_CON_EN_POS)

/****************** Bit definition for ACMP_INPUTSEL register ************************/

//#define	ACMP_INPUTSEL_VDDLVL_POSS	8U 
//#define	ACMP_INPUTSEL_VDDLVL_POSE	13U 
//#define	ACMP_INPUTSEL_VDDLVL_MSK	BITS(ACMP_INPUTSEL_VDDLVL_POSS,ACMP_INPUTSEL_VDDLVL_POSE)

#define	ACMP_INPUTSEL_NSEL_POSS	4U 
#define	ACMP_INPUTSEL_NSEL_POSE	7U 
#define	ACMP_INPUTSEL_NSEL_MSK	BITS(ACMP_INPUTSEL_NSEL_POSS,ACMP_INPUTSEL_NSEL_POSE)

#define	ACMP_INPUTSEL_PSEL_POSS	0U 
#define	ACMP_INPUTSEL_PSEL_POSE	2U 
#define	ACMP_INPUTSEL_PSEL_MSK	BITS(ACMP_INPUTSEL_PSEL_POSS,ACMP_INPUTSEL_PSEL_POSE)

/****************** Bit definition for ACMP_STAT register ************************/

#define	ACMP_STAT_OUT_POS	1U 
#define	ACMP_STAT_OUT_MSK	BIT(ACMP_STAT_OUT_POS)

#define	ACMP_STAT_ACT_POS	0U 
#define	ACMP_STAT_ACT_MSK	BIT(ACMP_STAT_ACT_POS)

/****************** Bit definition for ACMP_IES register ************************/

#define	ACMP_IES_WARMUP_POS	1U 
#define	ACMP_IES_WARMUP_MSK	BIT(ACMP_IES_WARMUP_POS)

#define	ACMP_IES_EDGE_POS	0U 
#define	ACMP_IES_EDGE_MSK	BIT(ACMP_IES_EDGE_POS)

/****************** Bit definition for ACMP_IEC register ************************/

#define	ACMP_IEC_WARMUP_POS	1U 
#define	ACMP_IEC_WARMUP_MSK	BIT(ACMP_IEC_WARMUP_POS)

#define	ACMP_IEC_EDGE_POS	0U 
#define	ACMP_IEC_EDGE_MSK	BIT(ACMP_IEC_EDGE_POS)

/****************** Bit definition for ACMP_IEV register ************************/

#define	ACMP_IEV_WARMUP_POS	1U 
#define	ACMP_IEV_WARMUP_MSK	BIT(ACMP_IEV_WARMUP_POS)

#define	ACMP_IEV_EDGE_POS	0U 
#define	ACMP_IEV_EDGE_MSK	BIT(ACMP_IEV_EDGE_POS)

/****************** Bit definition for ACMP_RIF register ************************/

#define	ACMP_RIF_WARMUP_POS	1U 
#define	ACMP_RIF_WARMUP_MSK	BIT(ACMP_RIF_WARMUP_POS)

#define	ACMP_RIF_EDGE_POS	0U 
#define	ACMP_RIF_EDGE_MSK	BIT(ACMP_RIF_EDGE_POS)

/****************** Bit definition for ACMP_IFM register ************************/

#define	ACMP_IFM_WARMUP_POS	1U 
#define	ACMP_IFM_WARMUP_MSK	BIT(ACMP_IFM_WARMUP_POS)

#define	ACMP_IFM_EDGE_POS	0U 
#define	ACMP_IFM_EDGE_MSK	BIT(ACMP_IFM_EDGE_POS)

/****************** Bit definition for ACMP_IFC register ************************/

#define	ACMP_IFC_WARMUP_POS	1U 
#define	ACMP_IFC_WARMUP_MSK	BIT(ACMP_IFC_WARMUP_POS)

#define	ACMP_IFC_EDGE_POS	0U 
#define	ACMP_IFC_EDGE_MSK	BIT(ACMP_IFC_EDGE_POS)

/****************** Bit definition for ACMP_PORT register ************************/

#define	ACMP_PORT_PEN_POS	0U 
#define	ACMP_PORT_PEN_MSK	BIT(ACMP_PORT_PEN_POS)

typedef struct
{
	__IO uint32_t CON;
	__IO uint32_t INPUTSEL;
	__I uint32_t STAT;
	__O uint32_t IES;
	__O uint32_t IEC;
	__I uint32_t IEV;
	__I uint32_t RIF;
	__I uint32_t IFM;
	__O uint32_t IFC;
	__IO uint32_t PORT;
} ACMP_TypeDef;





#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
