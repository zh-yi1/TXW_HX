#ifndef __IP3561Q_H
#define __IP3561Q_H

#include "global_define.h"

/* IP3561Q I2C 7-bit slave address */
#define IP3561Q_SLAVE_ADDR       0x74U

/* ==========================================================================
 *  寄存器地址
 * ========================================================================== */

/* ---- 配置寄存器 (R/W) ---- */
#define IP3561Q_REG_CTL0         0x00U   /* CRC/TJ protect */
#define IP3561Q_REG_CTL1         0x01U   /* OW/均衡/OC模式 */
#define IP3561Q_REG_CTL2         0x02U   /* NTC1-4使能/均衡模式 */
#define IP3561Q_REG_CTL3         0x03U   /* VADC/CADC模式/IDLE ADC/电流检测阈值 */
#define IP3561Q_REG_DOC1         0x04U   /* 放电过流1阈值 */
#define IP3561Q_REG_DOC2         0x05U   /* 放电过流2阈值 */
#define IP3561Q_REG_SC           0x06U   /* 短路阈值 */
#define IP3561Q_REG_COC          0x07U   /* 充电过流阈值 */
#define IP3561Q_REG_IDLE_CK      0x0AU   /* IDLE时钟分频 */
#define IP3561Q_REG_SLEEP_IDLE   0x0BU   /* SLEEP/IDLE均衡 */
#define IP3561Q_REG_NTC_WDOG     0x0CU   /* NTC总使能/低温使能/0V禁充/看门狗 */
#define IP3561Q_REG_CELL_PD      0x0DU   /* 节数/PD/延时 */
#define IP3561Q_REG_OV_H         0x0EU   /* OV阈值高8位 */
#define IP3561Q_REG_OVL_OVRH     0x0FU   /* OV低2位 + OVR高6位 */
#define IP3561Q_REG_OVRL_OVDLY   0x10U   /* OVR低4位 + OV延时 */
#define IP3561Q_REG_UV_H         0x11U   /* UV阈值高8位 */
#define IP3561Q_REG_UVL_UVRH     0x12U   /* UV低2位 + UVR高6位 */
#define IP3561Q_REG_UVRL_UVDLY   0x13U   /* UVR低4位 + UV延时 */
#define IP3561Q_REG_DOC_DLY      0x14U   /* DOC1/2延时 */
#define IP3561Q_REG_SCCOC_DLY    0x15U   /* SC/COC延时 */
#define IP3561Q_REG_BAL_H        0x16U   /* 均衡阈值高8位 */
#define IP3561Q_REG_BAL_L_DLY    0x17U   /* 均衡阈值低2位 + 均衡延时 */
#define IP3561Q_REG_ZERO_VOL     0x1AU   /* 0V禁充阈值 */
#define IP3561Q_REG_OTC          0x1BU   /* 充电过温 */
#define IP3561Q_REG_OTCR         0x1CU   /* 充电过温释放 */
#define IP3561Q_REG_OTD          0x1DU   /* 放电过温 */
#define IP3561Q_REG_OTDR         0x1EU   /* 放电过温释放 */
#define IP3561Q_REG_UTC          0x1FU   /* 充电低温 */
#define IP3561Q_REG_UTCR         0x20U   /* 充电低温释放 */
#define IP3561Q_REG_UTD          0x21U   /* 放电低温 */
#define IP3561Q_REG_UTDR         0x22U   /* 放电低温释放 */
#define IP3561Q_REG_DOC1_COMP    0x2FU   /* DOC1精度补偿 */
#define IP3561Q_REG_DOC2_COMP    0x3EU   /* DOC2精度补偿 */
#define IP3561Q_REG_MCU_CTL      0x40U   /* MCU CO/DO/均衡控制 */
#define IP3561Q_REG_MCU_CTL2     0x42U   /* IDLE/PD/看门狗 */
#define IP3561Q_REG_PD_PWD       0x43U   /* PD口令 */
#define IP3561Q_REG_SC_COMP      0x7EU   /* SC补偿 */
#define IP3561Q_REG_COC_COMP     0x7FU   /* COC补偿 */

/* ---- 状态/数据寄存器 (R) ---- */
#define IP3561Q_REG_STATUS1      0x44U   /* OV/UV/DOC1/DOC2/SC/COC/0V */
#define IP3561Q_REG_STATUS2      0x45U   /* OTC/OTD/UTC/UTD/CO/DO */
#define IP3561Q_REG_STATUS3      0x46U   /* CHG/DSG/OW/BALANCE */
#define IP3561Q_REG_VC1_H        0x47U
#define IP3561Q_REG_VC1_L        0x48U
#define IP3561Q_REG_VC2_H        0x49U
#define IP3561Q_REG_VC2_L        0x4AU
#define IP3561Q_REG_VC3_H        0x4BU
#define IP3561Q_REG_VC3_L        0x4CU
#define IP3561Q_REG_VC4_H        0x4DU
#define IP3561Q_REG_VC4_L        0x4EU
#define IP3561Q_REG_VBAT_H       0x51U
#define IP3561Q_REG_VBAT_L       0x52U
#define IP3561Q_REG_PACK_H       0x53U
#define IP3561Q_REG_PACK_L       0x54U
#define IP3561Q_REG_NTC1_H       0x55U
#define IP3561Q_REG_NTC1_L       0x56U
#define IP3561Q_REG_NTC2_H       0x57U
#define IP3561Q_REG_NTC2_L       0x58U
#define IP3561Q_REG_NTC3_H       0x59U
#define IP3561Q_REG_NTC3_L       0x5AU
#define IP3561Q_REG_NTC4_H       0x5BU
#define IP3561Q_REG_NTC4_L       0x5CU
#define IP3561Q_REG_TJ_H         0x5FU
#define IP3561Q_REG_TJ_L         0x60U
#define IP3561Q_REG_CURRENT_H    0x61U
#define IP3561Q_REG_CURRENT_L    0x62U
#define IP3561Q_REG_TIMER0       0x63U
#define IP3561Q_REG_TIMER1       0x64U
#define IP3561Q_REG_FLAG1        0x65U   /* OV/UV/DOC/SC/COC/WDOG (读清零) */
#define IP3561Q_REG_FLAG2        0x66U   /* OTC/OTD/UTC/UTD/WK/ADC (读清零) */
#define IP3561Q_REG_TIMER2       0x7CU
#define IP3561Q_REG_TIMER3       0x7DU

/* ==========================================================================
 *  数据结构
 * ========================================================================== */
#pragma pack(1)
typedef struct
{
    uint8_t  status1;       /* 0x44: OV/UV/DOC1/DOC2/SC/COC/0V */
    uint8_t  status2;       /* 0x45: OTC/OTD/UTC/UTD/CO/DO */
    uint8_t  status3;       /* 0x46: CHG/DSG/OW/BALANCE */
    uint16_t vcell[4];      /* VC1~VC4 ADC raw */
    uint16_t vbat_adc;      /* VBAT ADC raw */
    uint16_t pack_adc;      /* PACK ADC raw */
    uint16_t ntc_adc[4];    /* NTC1~NTC4 ADC raw */
    uint16_t tj_adc;        /* 结温(芯片内部温度) ADC raw */
    int16_t  current_adc;   /* 电流 ADC raw (有符号) */
    uint32_t timer;         /* TIMER 32-bit */
} ip3561q_data_t;
#pragma pack()

/* 处理后数据 */
typedef struct
{
    uint16_t vcell_mv[4];   /* 电芯电压 mV (VC1~VC4) */
    uint16_t vbat_mv;       /* 电池包总电压 mV (VBAT ADC) */
    uint32_t rntc_ohm;      /* NTC阻值 Ω (来自NTC2) */
    int32_t  current_ma;    /* 电流 mA (正=充电) */
} ip3561q_proc_data_t;

#define IP3561Q_CELL_CNT    4U   /* 4 串电芯 */

/* ==========================================================================
 *  API
 * ========================================================================== */
void     ip3561q_init(void);
uint8_t  ip3561q_is_ready(void);
uint8_t  ip3561q_read_reg(uint8_t reg, uint8_t *buf, uint8_t len);
uint8_t  ip3561q_write_reg(uint8_t reg, uint8_t *buf, uint8_t len);
uint8_t  ip3561q_read_all(ip3561q_data_t *data);
void     ip3561q_calc_data(ip3561q_data_t *raw, ip3561q_proc_data_t *p);
void     ip3561q_proc(void);

#define IP3561Q_POLL_MS        500U
#define IP3561Q_CFG_RETRY_MS  200U

extern volatile uint8_t           g_bat_high_temp;
extern volatile ip3561q_data_t      ip3561q_raw;
extern volatile ip3561q_proc_data_t ip3561q_info;

#endif /* __IP3561Q_H */
