/**********************************************************************************
 *
 * @file    REG_I2C.h
 * @brief   I2C Head File
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

#ifndef __REG_I2C_H__
#define __REG_I2C_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */


/****************** Bit definition for I2C_CON1 register ************************/

#define	I2C_CON1_SRST_POS	15U 
#define	I2C_CON1_SRST_MSK	BIT(I2C_CON1_SRST_POS)

#define	I2C_CON1_ALARM_POS	13U 
#define	I2C_CON1_ALARM_MSK	BIT(I2C_CON1_ALARM_POS)

#define	I2C_CON1_TRPEC_POS	12U 
#define	I2C_CON1_TRPEC_MSK	BIT(I2C_CON1_TRPEC_POS)

#define	I2C_CON1_POSAP_POS	11U 
#define	I2C_CON1_POSAP_MSK	BIT(I2C_CON1_POSAP_POS)

#define	I2C_CON1_ACKEN_POS	10U 
#define	I2C_CON1_ACKEN_MSK	BIT(I2C_CON1_ACKEN_POS)

#define	I2C_CON1_STOP_POS	9U 
#define	I2C_CON1_STOP_MSK	BIT(I2C_CON1_STOP_POS)

#define	I2C_CON1_START_POS	8U 
#define	I2C_CON1_START_MSK	BIT(I2C_CON1_START_POS)

#define	I2C_CON1_DISCS_POS	7U 
#define	I2C_CON1_DISCS_MSK	BIT(I2C_CON1_DISCS_POS)

#define	I2C_CON1_GCEN_POS	6U 
#define	I2C_CON1_GCEN_MSK	BIT(I2C_CON1_GCEN_POS)

#define	I2C_CON1_PECEN_POS	5U 
#define	I2C_CON1_PECEN_MSK	BIT(I2C_CON1_PECEN_POS)

#define	I2C_CON1_ARPEN_POS	4U 
#define	I2C_CON1_ARPEN_MSK	BIT(I2C_CON1_ARPEN_POS)

#define	I2C_CON1_SMBMOD_POS	3U 
#define	I2C_CON1_SMBMOD_MSK	BIT(I2C_CON1_SMBMOD_POS)

#define	I2C_CON1_PMOD_POS	1U 
#define	I2C_CON1_PMOD_MSK	BIT(I2C_CON1_PMOD_POS)

#define	I2C_CON1_PEN_POS	0U 
#define	I2C_CON1_PEN_MSK	BIT(I2C_CON1_PEN_POS)

/****************** Bit definition for I2C_CON2 register ************************/

#define	I2C_CON2_LDMA_POS	12U 
#define	I2C_CON2_LDMA_MSK	BIT(I2C_CON2_LDMA_POS)

#define	I2C_CON2_DMAEN_POS	11U 
#define	I2C_CON2_DMAEN_MSK	BIT(I2C_CON2_DMAEN_POS)

#define	I2C_CON2_BUFIE_POS	10U 
#define	I2C_CON2_BUFIE_MSK	BIT(I2C_CON2_BUFIE_POS)

#define	I2C_CON2_EVTIE_POS	9U 
#define	I2C_CON2_EVTIE_MSK	BIT(I2C_CON2_EVTIE_POS)

#define	I2C_CON2_ERRIE_POS	8U 
#define	I2C_CON2_ERRIE_MSK	BIT(I2C_CON2_ERRIE_POS)

#define	I2C_CON2_CLKF_POSS	0U 
#define	I2C_CON2_CLKF_POSE	5U 
#define	I2C_CON2_CLKF_MSK	BITS(I2C_CON2_CLKF_POSS,I2C_CON2_CLKF_POSE)

/****************** Bit definition for I2C_ADDR1 register ************************/

#define	I2C_ADDR1_ADDTYPE_POS	15U 
#define	I2C_ADDR1_ADDTYPE_MSK	BIT(I2C_ADDR1_ADDTYPE_POS)

#define	I2C_ADDR1_ADDH_POSS	8U 
#define	I2C_ADDR1_ADDH_POSE	9U 
#define	I2C_ADDR1_ADDH_MSK	BITS(I2C_ADDR1_ADDH_POSS,I2C_ADDR1_ADDH_POSE)

#define	I2C_ADDR1_ADD_POSS	1U 
#define	I2C_ADDR1_ADD_POSE	7U 
#define	I2C_ADDR1_ADD_MSK	BITS(I2C_ADDR1_ADD_POSS,I2C_ADDR1_ADD_POSE)

#define	I2C_ADDR1_ADDLSB_POS	0U 
#define	I2C_ADDR1_ADDLSB_MSK	BIT(I2C_ADDR1_ADDLSB_POS)

/****************** Bit definition for I2C_ADDR2 register ************************/

#define	I2C_ADDR2_ADD_POSS	1U 
#define	I2C_ADDR2_ADD_POSE	7U 
#define	I2C_ADDR2_ADD_MSK	BITS(I2C_ADDR2_ADD_POSS,I2C_ADDR2_ADD_POSE)

#define	I2C_ADDR2_DUALEN_POS	0U 
#define	I2C_ADDR2_DUALEN_MSK	BIT(I2C_ADDR2_DUALEN_POS)

/****************** Bit definition for I2C_DATA register ************************/

#define	I2C_DATA_TRBUF_POSS	0U 
#define	I2C_DATA_TRBUF_POSE	7U 
#define	I2C_DATA_TRBUF_MSK	BITS(I2C_DATA_TRBUF_POSS,I2C_DATA_TRBUF_POSE)

/****************** Bit definition for I2C_STAT1 register ************************/

#define	I2C_STAT1_SMBALARM_POS	15U 
#define	I2C_STAT1_SMBALARM_MSK	BIT(I2C_STAT1_SMBALARM_POS)

#define	I2C_STAT1_SMBTO_POS	14U 
#define	I2C_STAT1_SMBTO_MSK	BIT(I2C_STAT1_SMBTO_POS)

#define	I2C_STAT1_PECERR_POS	12U 
#define	I2C_STAT1_PECERR_MSK	BIT(I2C_STAT1_PECERR_POS)

#define	I2C_STAT1_ROUERR_POS	11U 
#define	I2C_STAT1_ROUERR_MSK	BIT(I2C_STAT1_ROUERR_POS)

#define	I2C_STAT1_ACKERR_POS	10U 
#define	I2C_STAT1_ACKERR_MSK	BIT(I2C_STAT1_ACKERR_POS)

#define	I2C_STAT1_LARB_POS	9U 
#define	I2C_STAT1_LARB_MSK	BIT(I2C_STAT1_LARB_POS)

#define	I2C_STAT1_BUSERR_POS	8U 
#define	I2C_STAT1_BUSERR_MSK	BIT(I2C_STAT1_BUSERR_POS)

#define	I2C_STAT1_TXBE_POS	7U 
#define	I2C_STAT1_TXBE_MSK	BIT(I2C_STAT1_TXBE_POS)

#define	I2C_STAT1_RXBNE_POS	6U 
#define	I2C_STAT1_RXBNE_MSK	BIT(I2C_STAT1_RXBNE_POS)

#define	I2C_STAT1_DETSTP_POS	4U 
#define	I2C_STAT1_DETSTP_MSK	BIT(I2C_STAT1_DETSTP_POS)

#define	I2C_STAT1_SENDADD10_POS	3U 
#define	I2C_STAT1_SENDADD10_MSK	BIT(I2C_STAT1_SENDADD10_POS)

#define	I2C_STAT1_BTC_POS	2U 
#define	I2C_STAT1_BTC_MSK	BIT(I2C_STAT1_BTC_POS)

#define	I2C_STAT1_ADDR_POS	1U 
#define	I2C_STAT1_ADDR_MSK	BIT(I2C_STAT1_ADDR_POS)

#define	I2C_STAT1_SENDSTR_POS	0U 
#define	I2C_STAT1_SENDSTR_MSK	BIT(I2C_STAT1_SENDSTR_POS)

/****************** Bit definition for I2C_STAT2 register ************************/

#define	I2C_STAT2_PECV_POSS	8U 
#define	I2C_STAT2_PECV_POSE	15U 
#define	I2C_STAT2_PECV_MSK	BITS(I2C_STAT2_PECV_POSS,I2C_STAT2_PECV_POSE)

#define	I2C_STAT2_DMF_POS	7U 
#define	I2C_STAT2_DMF_MSK	BIT(I2C_STAT2_DMF_POS)

#define	I2C_STAT2_SMBHH_POS	6U 
#define	I2C_STAT2_SMBHH_MSK	BIT(I2C_STAT2_SMBHH_POS)

#define	I2C_STAT2_SMBDEF_POS	5U 
#define	I2C_STAT2_SMBDEF_MSK	BIT(I2C_STAT2_SMBDEF_POS)

#define	I2C_STAT2_RXGCF_POS	4U 
#define	I2C_STAT2_RXGCF_MSK	BIT(I2C_STAT2_RXGCF_POS)

#define	I2C_STAT2_TRF_POS	2U 
#define	I2C_STAT2_TRF_MSK	BIT(I2C_STAT2_TRF_POS)

#define	I2C_STAT2_BSYF_POS	1U 
#define	I2C_STAT2_BSYF_MSK	BIT(I2C_STAT2_BSYF_POS)

#define	I2C_STAT2_MASTER_POS	0U 
#define	I2C_STAT2_MASTER_MSK	BIT(I2C_STAT2_MASTER_POS)

/****************** Bit definition for I2C_CKCFG register ************************/

#define	I2C_CKCFG_CLKMOD_POS	15U 
#define	I2C_CKCFG_CLKMOD_MSK	BIT(I2C_CKCFG_CLKMOD_POS)

#define	I2C_CKCFG_DUTY_POS	14U 
#define	I2C_CKCFG_DUTY_MSK	BIT(I2C_CKCFG_DUTY_POS)

#define	I2C_CKCFG_CLKSET_POSS	0U 
#define	I2C_CKCFG_CLKSET_POSE	11U 
#define	I2C_CKCFG_CLKSET_MSK	BITS(I2C_CKCFG_CLKSET_POSS,I2C_CKCFG_CLKSET_POSE)

/****************** Bit definition for I2C_RT register ************************/

#define	I2C_RT_RISET_POSS	0U 
#define	I2C_RT_RISET_POSE	5U 
#define	I2C_RT_RISET_MSK	BITS(I2C_RT_RISET_POSS,I2C_RT_RISET_POSE)

typedef struct
{
	__IO uint32_t CON1;
	__IO uint32_t CON2;
	__IO uint32_t ADDR1;
	__IO uint32_t ADDR2;
	__IO uint32_t DATA;
	__IO uint32_t STAT1;
	__I uint32_t STAT2;
	__IO uint32_t CKCFG;
	__IO uint32_t RT;
} I2C_TypeDef;





#endif

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
