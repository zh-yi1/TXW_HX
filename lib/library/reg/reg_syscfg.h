/**********************************************************************************
 *
 * @file    REG_SYSCFG.h
 * @brief   SYSCFG Head File
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

#ifndef __REG_SYSCFG_H__
#define __REG_SYSCFG_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */


/****************** Bit definition for SYSCFG_PROT register ************************/

#define	SYSCFG_PROT_KEY_POSS	1U 
#define	SYSCFG_PROT_KEY_POSE	31U 
#define	SYSCFG_PROT_KEY_MSK	BITS(SYSCFG_PROT_KEY_POSS,SYSCFG_PROT_KEY_POSE)

#define	SYSCFG_PROT_PROT_POS	0U 
#define	SYSCFG_PROT_PROT_MSK	BIT(SYSCFG_PROT_PROT_POS)

/****************** Bit definition for SYSCFG_MEMRMP register ************************/

#define	SYSCFG_MEMRMP_VTOEN_POS	16U 
#define	SYSCFG_MEMRMP_VTOEN_MSK	BIT(SYSCFG_MEMRMP_VTOEN_POS)

#define	SYSCFG_MEMRMP_BFRMPEN_POS	8U 
#define	SYSCFG_MEMRMP_BFRMPEN_MSK	BIT(SYSCFG_MEMRMP_BFRMPEN_POS)

/****************** Bit definition for SYSCFG_VTOR register ************************/

#define	SYSCFG_VTOR_VTO_POSS	0U 
#define	SYSCFG_VTOR_VTO_POSE	29U 
#define	SYSCFG_VTOR_VTO_MSK	BITS(SYSCFG_VTOR_VTO_POSS,SYSCFG_VTOR_VTO_POSE)

/****************** Bit definition for SYSCFG_TBKCFG register ************************/

#define	SYSCFG_TBKCFG_CLUBKE_POS	2U 
#define	SYSCFG_TBKCFG_CLUBKE_MSK	BIT(SYSCFG_TBKCFG_CLUBKE_POS)

#define	SYSCFG_TBKCFG_LVDBKE_POS	1U 
#define	SYSCFG_TBKCFG_LVDBKE_MSK	BIT(SYSCFG_TBKCFG_LVDBKE_POS)

#define	SYSCFG_TBKCFG_CCSBKE_POS	0U 
#define	SYSCFG_TBKCFG_CCSBKE_MSK	BIT(SYSCFG_TBKCFG_CCSBKE_POS)

typedef struct
{
	__IO uint32_t PROT;
	__IO uint32_t MEMRMP;
	__IO uint32_t VTOR;
	__IO uint32_t TBKCFG;
} SYSCFG_TypeDef;





#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
