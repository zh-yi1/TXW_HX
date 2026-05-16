/**********************************************************************************
 *
 * @file    REG_SPI.h
 * @brief   SPI Head File
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

#ifndef __REG_SPI_H__
#define __REG_SPI_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */


/****************** Bit definition for SPI_CON1 register ************************/

#define	SPI_CON1_BIDEN_POS	15U 
#define	SPI_CON1_BIDEN_MSK	BIT(SPI_CON1_BIDEN_POS)

#define	SPI_CON1_BIDOEN_POS	14U 
#define	SPI_CON1_BIDOEN_MSK	BIT(SPI_CON1_BIDOEN_POS)

#define	SPI_CON1_CRCEN_POS	13U 
#define	SPI_CON1_CRCEN_MSK	BIT(SPI_CON1_CRCEN_POS)

#define	SPI_CON1_NXTCRC_POS	12U 
#define	SPI_CON1_NXTCRC_MSK	BIT(SPI_CON1_NXTCRC_POS)

#define	SPI_CON1_FLEN_POS	11U 
#define	SPI_CON1_FLEN_MSK	BIT(SPI_CON1_FLEN_POS)

#define	SPI_CON1_RXO_POS	10U 
#define	SPI_CON1_RXO_MSK	BIT(SPI_CON1_RXO_POS)

#define	SPI_CON1_SSEN_POS	9U 
#define	SPI_CON1_SSEN_MSK	BIT(SPI_CON1_SSEN_POS)

#define	SPI_CON1_SSOUT_POS	8U 
#define	SPI_CON1_SSOUT_MSK	BIT(SPI_CON1_SSOUT_POS)

#define	SPI_CON1_LSBFST_POS	7U 
#define	SPI_CON1_LSBFST_MSK	BIT(SPI_CON1_LSBFST_POS)

#define	SPI_CON1_SPIEN_POS	6U 
#define	SPI_CON1_SPIEN_MSK	BIT(SPI_CON1_SPIEN_POS)

#define	SPI_CON1_BAUD_POSS	3U 
#define	SPI_CON1_BAUD_POSE	5U 
#define	SPI_CON1_BAUD_MSK	BITS(SPI_CON1_BAUD_POSS,SPI_CON1_BAUD_POSE)

#define	SPI_CON1_MSTREN_POS	2U 
#define	SPI_CON1_MSTREN_MSK	BIT(SPI_CON1_MSTREN_POS)

#define	SPI_CON1_CPOL_POS	1U 
#define	SPI_CON1_CPOL_MSK	BIT(SPI_CON1_CPOL_POS)

#define	SPI_CON1_CPHA_POS	0U 
#define	SPI_CON1_CPHA_MSK	BIT(SPI_CON1_CPHA_POS)

/****************** Bit definition for SPI_CON2 register ************************/

#define	SPI_CON2_TXBEIE_POS	7U 
#define	SPI_CON2_TXBEIE_MSK	BIT(SPI_CON2_TXBEIE_POS)

#define	SPI_CON2_RXBNEIE_POS	6U 
#define	SPI_CON2_RXBNEIE_MSK	BIT(SPI_CON2_RXBNEIE_POS)

#define	SPI_CON2_ERRIE_POS	5U 
#define	SPI_CON2_ERRIE_MSK	BIT(SPI_CON2_ERRIE_POS)

#define	SPI_CON2_NSSOE_POS	2U 
#define	SPI_CON2_NSSOE_MSK	BIT(SPI_CON2_NSSOE_POS)

#define	SPI_CON2_TXDMA_POS	1U 
#define	SPI_CON2_TXDMA_MSK	BIT(SPI_CON2_TXDMA_POS)

#define	SPI_CON2_RXDMA_POS	0U 
#define	SPI_CON2_RXDMA_MSK	BIT(SPI_CON2_RXDMA_POS)

/****************** Bit definition for SPI_STAT register ************************/

#define	SPI_STAT_BUSY_POS	7U 
#define	SPI_STAT_BUSY_MSK	BIT(SPI_STAT_BUSY_POS)

#define	SPI_STAT_OVERR_POS	6U 
#define	SPI_STAT_OVERR_MSK	BIT(SPI_STAT_OVERR_POS)

#define	SPI_STAT_MODERR_POS	5U 
#define	SPI_STAT_MODERR_MSK	BIT(SPI_STAT_MODERR_POS)

#define	SPI_STAT_CRCERR_POS	4U 
#define	SPI_STAT_CRCERR_MSK	BIT(SPI_STAT_CRCERR_POS)

#define	SPI_STAT_TXBE_POS	1U 
#define	SPI_STAT_TXBE_MSK	BIT(SPI_STAT_TXBE_POS)

#define	SPI_STAT_RXBNE_POS	0U 
#define	SPI_STAT_RXBNE_MSK	BIT(SPI_STAT_RXBNE_POS)

/****************** Bit definition for SPI_DATA register ************************/

#define	SPI_DATA_VALUE_POSS	0U 
#define	SPI_DATA_VALUE_POSE	15U 
#define	SPI_DATA_VALUE_MSK	BITS(SPI_DATA_VALUE_POSS,SPI_DATA_VALUE_POSE)

/****************** Bit definition for SPI_CRCPOLY register ************************/

#define	SPI_CRCPOLY_VALUE_POSS	0U 
#define	SPI_CRCPOLY_VALUE_POSE	15U 
#define	SPI_CRCPOLY_VALUE_MSK	BITS(SPI_CRCPOLY_VALUE_POSS,SPI_CRCPOLY_VALUE_POSE)

/****************** Bit definition for SPI_RXCRC register ************************/

#define	SPI_RXCRC_CRCVAL_POSS	0U 
#define	SPI_RXCRC_CRCVAL_POSE	15U 
#define	SPI_RXCRC_CRCVAL_MSK	BITS(SPI_RXCRC_CRCVAL_POSS,SPI_RXCRC_CRCVAL_POSE)

/****************** Bit definition for SPI_TXCRC register ************************/

#define	SPI_TXCRC_CRCVAL_POSS	0U 
#define	SPI_TXCRC_CRCVAL_POSE	15U 
#define	SPI_TXCRC_CRCVAL_MSK	BITS(SPI_TXCRC_CRCVAL_POSS,SPI_TXCRC_CRCVAL_POSE)

typedef struct
{
	__IO uint32_t CON1;
	__IO uint32_t CON2;
	__IO uint32_t STAT;
	__IO uint32_t DATA;
	__IO uint32_t CRCPOLY;
	__I uint32_t RXCRC;
	__I uint32_t TXCRC;
} SPI_TypeDef;





#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
