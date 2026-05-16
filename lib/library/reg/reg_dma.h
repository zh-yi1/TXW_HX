/**********************************************************************************
 *
 * @file    REG_DMA.h
 * @brief   DMA Head File
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

#ifndef __REG_DMA_H__
#define __REG_DMA_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */


/****************** Bit definition for DMA_STATUS register ************************/

#define	DMA_STATUS_STATUS_POSS	4U 
#define	DMA_STATUS_STATUS_POSE	7U 
#define	DMA_STATUS_STATUS_MSK	BITS(DMA_STATUS_STATUS_POSS,DMA_STATUS_STATUS_POSE)

#define	DMA_STATUS_MASTER_ENABLE_POS	0U 
#define	DMA_STATUS_MASTER_ENABLE_MSK	BIT(DMA_STATUS_MASTER_ENABLE_POS)

/****************** Bit definition for DMA_CFG register ************************/

#define	DMA_CFG_CHNL_PROT_CTRL_POSS	5U 
#define	DMA_CFG_CHNL_PROT_CTRL_POSE	7U 
#define	DMA_CFG_CHNL_PROT_CTRL_MSK	BITS(DMA_CFG_CHNL_PROT_CTRL_POSS,DMA_CFG_CHNL_PROT_CTRL_POSE)

#define	DMA_CFG_MASTER_ENABLE_POS	0U 
#define	DMA_CFG_MASTER_ENABLE_MSK	BIT(DMA_CFG_MASTER_ENABLE_POS)

/****************** Bit definition for DMA_CTRLBASE register ************************/

#define	DMA_CTRLBASE_CTRL_BASE_PTR_POSS	9U 
#define	DMA_CTRLBASE_CTRL_BASE_PTR_POSE	31U 
#define	DMA_CTRLBASE_CTRL_BASE_PTR_MSK	BITS(DMA_CTRLBASE_CTRL_BASE_PTR_POSS,DMA_CTRLBASE_CTRL_BASE_PTR_POSE)

/****************** Bit definition for DMA_ALTCTRLBASE register ************************/

#define	DMA_ALTCTRLBASE_ALT_CTRL_BASE_PTR_POSS	0U 
#define	DMA_ALTCTRLBASE_ALT_CTRL_BASE_PTR_POSE	31U 
#define	DMA_ALTCTRLBASE_ALT_CTRL_BASE_PTR_MSK	BITS(DMA_ALTCTRLBASE_ALT_CTRL_BASE_PTR_POSS,DMA_ALTCTRLBASE_ALT_CTRL_BASE_PTR_POSE)

/****************** Bit definition for DMA_CHWAITSTATUS register ************************/

#define	DMA_CHWAITSTATUS_DMA_WAITONREQ_STATUS_POSS	0U 
#define	DMA_CHWAITSTATUS_DMA_WAITONREQ_STATUS_POSE	31U 
#define	DMA_CHWAITSTATUS_DMA_WAITONREQ_STATUS_MSK	BITS(DMA_CHWAITSTATUS_DMA_WAITONREQ_STATUS_POSS,DMA_CHWAITSTATUS_DMA_WAITONREQ_STATUS_POSE)

/****************** Bit definition for DMA_CHSWREQ register ************************/

#define	DMA_CHSWREQ_CHSWREQ_POSS	0U 
#define	DMA_CHSWREQ_CHSWREQ_POSE	31U 
#define	DMA_CHSWREQ_CHSWREQ_MSK	BITS(DMA_CHSWREQ_CHSWREQ_POSS,DMA_CHSWREQ_CHSWREQ_POSE)

/****************** Bit definition for DMA_CHUSEBURSTSET register ************************/

#define	DMA_CHUSEBURSTSET_CHNL_USEBURST_SET_POSS	0U 
#define	DMA_CHUSEBURSTSET_CHNL_USEBURST_SET_POSE	31U 
#define	DMA_CHUSEBURSTSET_CHNL_USEBURST_SET_MSK	BITS(DMA_CHUSEBURSTSET_CHNL_USEBURST_SET_POSS,DMA_CHUSEBURSTSET_CHNL_USEBURST_SET_POSE)

/****************** Bit definition for DMA_CHUSEBURSTCLR register ************************/

#define	DMA_CHUSEBURSTCLR_CHNL_USEBURST_CLR_POSS	0U 
#define	DMA_CHUSEBURSTCLR_CHNL_USEBURST_CLR_POSE	31U 
#define	DMA_CHUSEBURSTCLR_CHNL_USEBURST_CLR_MSK	BITS(DMA_CHUSEBURSTCLR_CHNL_USEBURST_CLR_POSS,DMA_CHUSEBURSTCLR_CHNL_USEBURST_CLR_POSE)

/****************** Bit definition for DMA_CHREQMASKSET register ************************/

#define	DMA_CHREQMASKSET_CHNL_REQ_MASK_SET_POSS	0U 
#define	DMA_CHREQMASKSET_CHNL_REQ_MASK_SET_POSE	31U 
#define	DMA_CHREQMASKSET_CHNL_REQ_MASK_SET_MSK	BITS(DMA_CHREQMASKSET_CHNL_REQ_MASK_SET_POSS,DMA_CHREQMASKSET_CHNL_REQ_MASK_SET_POSE)

/****************** Bit definition for DMA_CHREQMASKCLR register ************************/

#define	DMA_CHREQMASKCLR_CHNL_REQ_MASK_CLR_POSS	0U 
#define	DMA_CHREQMASKCLR_CHNL_REQ_MASK_CLR_POSE	31U 
#define	DMA_CHREQMASKCLR_CHNL_REQ_MASK_CLR_MSK	BITS(DMA_CHREQMASKCLR_CHNL_REQ_MASK_CLR_POSS,DMA_CHREQMASKCLR_CHNL_REQ_MASK_CLR_POSE)

/****************** Bit definition for DMA_CHENSET register ************************/

#define	DMA_CHENSET_CHNL_ENABLE_SET_POSS	0U 
#define	DMA_CHENSET_CHNL_ENABLE_SET_POSE	31U 
#define	DMA_CHENSET_CHNL_ENABLE_SET_MSK	BITS(DMA_CHENSET_CHNL_ENABLE_SET_POSS,DMA_CHENSET_CHNL_ENABLE_SET_POSE)

/****************** Bit definition for DMA_CHENCLR register ************************/

#define	DMA_CHENCLR_CHNL_ENABLE_CLR_POSS	0U 
#define	DMA_CHENCLR_CHNL_ENABLE_CLR_POSE	31U 
#define	DMA_CHENCLR_CHNL_ENABLE_CLR_MSK	BITS(DMA_CHENCLR_CHNL_ENABLE_CLR_POSS,DMA_CHENCLR_CHNL_ENABLE_CLR_POSE)

/****************** Bit definition for DMA_CHPRIALTSET register ************************/

#define	DMA_CHPRIALTSET_CHNL_PRI_ALT_SET_POSS	0U 
#define	DMA_CHPRIALTSET_CHNL_PRI_ALT_SET_POSE	31U 
#define	DMA_CHPRIALTSET_CHNL_PRI_ALT_SET_MSK	BITS(DMA_CHPRIALTSET_CHNL_PRI_ALT_SET_POSS,DMA_CHPRIALTSET_CHNL_PRI_ALT_SET_POSE)

/****************** Bit definition for DMA_CHPRIALTCLR register ************************/

#define	DMA_CHPRIALTCLR_CHNL_PRI_ALT_CLR_POSS	0U 
#define	DMA_CHPRIALTCLR_CHNL_PRI_ALT_CLR_POSE	31U 
#define	DMA_CHPRIALTCLR_CHNL_PRI_ALT_CLR_MSK	BITS(DMA_CHPRIALTCLR_CHNL_PRI_ALT_CLR_POSS,DMA_CHPRIALTCLR_CHNL_PRI_ALT_CLR_POSE)

/****************** Bit definition for DMA_CHPRSET register ************************/

#define	DMA_CHPRSET_CHNL_PRIORITY_SET_POSS	0U 
#define	DMA_CHPRSET_CHNL_PRIORITY_SET_POSE	31U 
#define	DMA_CHPRSET_CHNL_PRIORITY_SET_MSK	BITS(DMA_CHPRSET_CHNL_PRIORITY_SET_POSS,DMA_CHPRSET_CHNL_PRIORITY_SET_POSE)

/****************** Bit definition for DMA_CHPRCLR register ************************/

#define	DMA_CHPRCLR_CHNL_PRIORITY_CLR_POSS	0U 
#define	DMA_CHPRCLR_CHNL_PRIORITY_CLR_POSE	31U 
#define	DMA_CHPRCLR_CHNL_PRIORITY_CLR_MSK	BITS(DMA_CHPRCLR_CHNL_PRIORITY_CLR_POSS,DMA_CHPRCLR_CHNL_PRIORITY_CLR_POSE)

/****************** Bit definition for DMA_ERRCLR register ************************/

#define	DMA_ERRCLR_ERR_CLR_POS	0U 
#define	DMA_ERRCLR_ERR_CLR_MSK	BIT(DMA_ERRCLR_ERR_CLR_POS)

/****************** Bit definition for DMA_IFLAG register ************************/

#define	DMA_IFLAG_DMAERRIF_POS	31U 
#define	DMA_IFLAG_DMAERRIF_MSK	BIT(DMA_IFLAG_DMAERRIF_POS)

#define	DMA_IFLAG_CH3DONEIF_POS	3U 
#define	DMA_IFLAG_CH3DONEIF_MSK	BIT(DMA_IFLAG_CH3DONEIF_POS)

#define	DMA_IFLAG_CH2DONEIF_POS	2U 
#define	DMA_IFLAG_CH2DONEIF_MSK	BIT(DMA_IFLAG_CH2DONEIF_POS)

#define	DMA_IFLAG_CH1DONEIF_POS	1U 
#define	DMA_IFLAG_CH1DONEIF_MSK	BIT(DMA_IFLAG_CH1DONEIF_POS)

#define	DMA_IFLAG_CH0DONEIF_POS	0U 
#define	DMA_IFLAG_CH0DONEIF_MSK	BIT(DMA_IFLAG_CH0DONEIF_POS)

/****************** Bit definition for DMA_ICFR register ************************/

#define	DMA_ICFR_DMAERRC_POS	31U 
#define	DMA_ICFR_DMAERRC_MSK	BIT(DMA_ICFR_DMAERRC_POS)

#define	DMA_ICFR_CH3DONEC_POS	3U 
#define	DMA_ICFR_CH3DONEC_MSK	BIT(DMA_ICFR_CH3DONEC_POS)

#define	DMA_ICFR_CH2DONEC_POS	2U 
#define	DMA_ICFR_CH2DONEC_MSK	BIT(DMA_ICFR_CH2DONEC_POS)

#define	DMA_ICFR_CH1DONEC_POS	1U 
#define	DMA_ICFR_CH1DONEC_MSK	BIT(DMA_ICFR_CH1DONEC_POS)

#define	DMA_ICFR_CH0DONEC_POS	0U 
#define	DMA_ICFR_CH0DONEC_MSK	BIT(DMA_ICFR_CH0DONEC_POS)

/****************** Bit definition for DMA_IER register ************************/

#define	DMA_IER_DMAERRIE_POS	31U 
#define	DMA_IER_DMAERRIE_MSK	BIT(DMA_IER_DMAERRIE_POS)

#define	DMA_IER_CH3DONEIE_POS	3U 
#define	DMA_IER_CH3DONEIE_MSK	BIT(DMA_IER_CH3DONEIE_POS)

#define	DMA_IER_CH2DONEIE_POS	2U 
#define	DMA_IER_CH2DONEIE_MSK	BIT(DMA_IER_CH2DONEIE_POS)

#define	DMA_IER_CH1DONEIE_POS	1U 
#define	DMA_IER_CH1DONEIE_MSK	BIT(DMA_IER_CH1DONEIE_POS)

#define	DMA_IER_CH0DONEIE_POS	0U 
#define	DMA_IER_CH0DONEIE_MSK	BIT(DMA_IER_CH0DONEIE_POS)

/****************** Bit definition for DMA_CH0_SELCON register ************************/

#define	DMA_CH0_SELCON_MSEL_POSS	8U 
#define	DMA_CH0_SELCON_MSEL_POSE	11U 
#define	DMA_CH0_SELCON_MSEL_MSK	BITS(DMA_CH0_SELCON_MSEL_POSS,DMA_CH0_SELCON_MSEL_POSE)

#define	DMA_CH0_SELCON_MSIGSEL_POSS	0U 
#define	DMA_CH0_SELCON_MSIGSEL_POSE	3U 
#define	DMA_CH0_SELCON_MSIGSEL_MSK	BITS(DMA_CH0_SELCON_MSIGSEL_POSS,DMA_CH0_SELCON_MSIGSEL_POSE)

/****************** Bit definition for DMA_CH1_SELCON register ************************/

#define	DMA_CH1_SELCON_MSEL_POSS	8U 
#define	DMA_CH1_SELCON_MSEL_POSE	11U 
#define	DMA_CH1_SELCON_MSEL_MSK	BITS(DMA_CH1_SELCON_MSEL_POSS,DMA_CH1_SELCON_MSEL_POSE)

#define	DMA_CH1_SELCON_MSIGSEL_POSS	0U 
#define	DMA_CH1_SELCON_MSIGSEL_POSE	3U 
#define	DMA_CH1_SELCON_MSIGSEL_MSK	BITS(DMA_CH1_SELCON_MSIGSEL_POSS,DMA_CH1_SELCON_MSIGSEL_POSE)

/****************** Bit definition for DMA_CH2_SELCON register ************************/

#define	DMA_CH2_SELCON_MSEL_POSS	8U 
#define	DMA_CH2_SELCON_MSEL_POSE	11U 
#define	DMA_CH2_SELCON_MSEL_MSK	BITS(DMA_CH2_SELCON_MSEL_POSS,DMA_CH2_SELCON_MSEL_POSE)

#define	DMA_CH2_SELCON_MSIGSEL_POSS	0U 
#define	DMA_CH2_SELCON_MSIGSEL_POSE	3U 
#define	DMA_CH2_SELCON_MSIGSEL_MSK	BITS(DMA_CH2_SELCON_MSIGSEL_POSS,DMA_CH2_SELCON_MSIGSEL_POSE)

/****************** Bit definition for DMA_CH3_SELCON register ************************/

#define	DMA_CH3_SELCON_MSEL_POSS	8U 
#define	DMA_CH3_SELCON_MSEL_POSE	11U 
#define	DMA_CH3_SELCON_MSEL_MSK	BITS(DMA_CH3_SELCON_MSEL_POSS,DMA_CH3_SELCON_MSEL_POSE)

#define	DMA_CH3_SELCON_MSIGSEL_POSS	0U 
#define	DMA_CH3_SELCON_MSIGSEL_POSE	3U 
#define	DMA_CH3_SELCON_MSIGSEL_MSK	BITS(DMA_CH3_SELCON_MSIGSEL_POSS,DMA_CH3_SELCON_MSIGSEL_POSE)

typedef struct
{
	__I uint32_t STATUS;
	__IO uint32_t CFG;
	__IO uint32_t CTRLBASE;
	__I uint32_t ALTCTRLBASE;
	__I uint32_t CHWAITSTATUS;
	__IO uint32_t CHSWREQ;
	__IO uint32_t CHUSEBURSTSET;
	__O uint32_t CHUSEBURSTCLR;
	__IO uint32_t CHREQMASKSET;
	__O uint32_t CHREQMASKCLR;
	__IO uint32_t CHENSET;
	__O uint32_t CHENCLR;
	__IO uint32_t CHPRIALTSET;
	__O uint32_t CHPRIALTCLR;
	__IO uint32_t CHPRSET;
	__O uint32_t CHPRCLR;
	uint32_t RESERVED0[3] ;
	__IO uint32_t ERRCLR;
	uint32_t RESERVED1[1004] ;
	__I uint32_t IFLAG;
	uint32_t RESERVED2 ;
	__O uint32_t ICFR;
	__IO uint32_t IER;
	uint32_t RESERVED3[60] ;
	__IO uint32_t CH_SELCON[4];
} DMA_TypeDef;





#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
