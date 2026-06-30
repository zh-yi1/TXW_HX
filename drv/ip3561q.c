#include "ip3561q.h"

volatile ip3561q_data_t      ip3561q_raw;
volatile ip3561q_proc_data_t ip3561q_info;
volatile uint8_t             ip3561q_comm_ok = 1;
volatile uint8_t             g_bat_high_temp;  /* 电芯高温: rntc_ohm <= 26000Ω (NTC 阻值越低越热, 26kΩ≈57℃) */

static uint8_t ip3561q_cfg_done = 0;

uint8_t ip3561q_is_ready(void)
{
    return ip3561q_cfg_done;
}

/* ==========================================================================
 *  I2C 读写 (无 CRC, 标准 I2C 协议)
 * ========================================================================== */
uint8_t ip3561q_write_reg(uint8_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    uint8_t sla_w = (uint8_t)(IP3561Q_SLAVE_ADDR << 1);

    if (len == 0 || buf == 0)
        return 1;

    sw_i2c_start();
    if (sw_i2c_write_byte(sla_w))
    {
        sw_i2c_stop();
        return 1;
    }
    if (sw_i2c_write_byte(reg))
    {
        sw_i2c_stop();
        return 1;
    }

    for (i = 0; i < len; i++)
    {
        if (sw_i2c_write_byte(buf[i]))
        {
            sw_i2c_stop();
            return 1;
        }
    }

    sw_i2c_stop();
    md_delay_1us(100);
    return 0;
}

uint8_t ip3561q_read_reg(uint8_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    uint8_t sla_w = (uint8_t)(IP3561Q_SLAVE_ADDR << 1);
    uint8_t sla_r = sla_w | 1U;

    if (len == 0 || buf == 0)
        return 1;

    sw_i2c_start();
    if (sw_i2c_write_byte(sla_w))
    {
        sw_i2c_stop();
        return 1;
    }
    if (sw_i2c_write_byte(reg))
    {
        sw_i2c_stop();
        return 1;
    }

    /* Repeated start */
    sw_i2c_restart();
    if (sw_i2c_write_byte(sla_r))
    {
        sw_i2c_stop();
        return 1;
    }

    for (i = 0; i < len; i++)
    {
        buf[i] = sw_i2c_read_byte((i == (len - 1)) ? 0 : 1);
    }

    sw_i2c_stop();
    md_delay_1us(100);
    return 0;
}

/* ==========================================================================
 *  配置寄存器写入 (按海信20K项目表格)
 * ========================================================================== */
static const uint8_t ip3561q_cfg_table[][2] = {
    { IP3561Q_REG_CTL1,         0x04 },   /* OC_MODE_SEL=1 */
    { IP3561Q_REG_CTL2,         0x04 },   /* CELL_BALANCE_MODE=1 */
    { IP3561Q_REG_CTL3,         0x0C },   /* IDLE_ADC_MODE=11 */
    { IP3561Q_REG_DOC1,         0x07 },   /* DOC1: 11A→27.5mV */
    { IP3561Q_REG_DOC2,         0x04 },   /* DOC2: 15A→37.5mV */
    { IP3561Q_REG_COC,          0x02 },   /* COC: 5.5A→-13.75mV */
    { IP3561Q_REG_IDLE_CK,      0x80 },   /* IDLE_CK=131kHz */
    { IP3561Q_REG_SLEEP_IDLE,   0x40 },   /* IDLE均衡使能 */
    { IP3561Q_REG_NTC_WDOG,     0x38 },   /* NTC_EN+UTC+UTD */
    { IP3561Q_REG_CELL_PD,      0x40 },   /* 4串 */
    { IP3561Q_REG_OV_H,         0x03 },   /* OV=4.5V, TH_OV高8位 */
    { IP3561Q_REG_OVL_OVRH,     0x2E },   /* OV低2位 + OVR高6位 */
    { IP3561Q_REG_OVRL_OVDLY,   0x60 },   /* OVR低4位 + OV延时 */
    { IP3561Q_REG_UV_H,         0x1D },   /* UV=2.72V, TH_UV高8位 */
    { IP3561Q_REG_UVL_UVRH,     0x20 },   /* UV低2位 + UVR高6位 */
    { IP3561Q_REG_BAL_H,        0xB9 },   /* 均衡=4.35V, 高8位 */
    { IP3561Q_REG_BAL_L_DLY,    0x8B },   /* 均衡低2位 + 延时 */
    { IP3561Q_REG_MCU_CTL2,     0x40 },   /* IDLE_EN=1 */
};

#define IP3561Q_CFG_COUNT  (sizeof(ip3561q_cfg_table) / sizeof(ip3561q_cfg_table[0]))

static uint8_t ip3561q_config_regs(void)
{
    uint8_t i;
    uint8_t rbuf;
    uint8_t res = 1;

    for (i = 0; i < IP3561Q_CFG_COUNT; i++)
    {
        uint8_t reg  = ip3561q_cfg_table[i][0];
        uint8_t val  = ip3561q_cfg_table[i][1];

        ip3561q_write_reg(reg, &val, 1);
        if (ip3561q_read_reg(reg, &rbuf, 1) || rbuf != val)
            res = 0;
    }

    return res;
}

/* ==========================================================================
 *  初始化
 * ========================================================================== */
void ip3561q_init(void)
{
    sw_i2c_init();

    if (ip3561q_config_regs() != 0)
        ip3561q_cfg_done = 1;
}

/* ==========================================================================
 *  读取全部数据
 * ========================================================================== */
uint8_t ip3561q_read_all(ip3561q_data_t *data)
{
    uint8_t err = 0;
    uint8_t buf[2];

    if (data == NULL)
        return 1;

    /* 状态寄存器: 0x44-0x46 */
    err |= ip3561q_read_reg(IP3561Q_REG_STATUS1, &data->status1, 1);
    err |= ip3561q_read_reg(IP3561Q_REG_STATUS2, &data->status2, 1);
    err |= ip3561q_read_reg(IP3561Q_REG_STATUS3, &data->status3, 1);

    /* VC1~VC4 电芯电压: 每路2字节 */
    err |= ip3561q_read_reg(IP3561Q_REG_VC1_H, buf, 2);
    data->vcell[0] = ((uint16_t)buf[0] << 8) | buf[1];
    err |= ip3561q_read_reg(IP3561Q_REG_VC2_H, buf, 2);
    data->vcell[1] = ((uint16_t)buf[0] << 8) | buf[1];
    err |= ip3561q_read_reg(IP3561Q_REG_VC3_H, buf, 2);
    data->vcell[2] = ((uint16_t)buf[0] << 8) | buf[1];
    err |= ip3561q_read_reg(IP3561Q_REG_VC4_H, buf, 2);
    data->vcell[3] = ((uint16_t)buf[0] << 8) | buf[1];

    /* VBAT: 0x51-0x52 */
    err |= ip3561q_read_reg(IP3561Q_REG_VBAT_H, buf, 2);
    data->vbat_adc = ((uint16_t)buf[0] << 8) | buf[1];

    /* PACK: 0x53-0x54 */
    err |= ip3561q_read_reg(IP3561Q_REG_PACK_H, buf, 2);
    data->pack_adc = ((uint16_t)buf[0] << 8) | buf[1];

    /* NTC1~NTC4: 每路2字节 */
    err |= ip3561q_read_reg(IP3561Q_REG_NTC1_H, buf, 2);
    data->ntc_adc[0] = ((uint16_t)buf[0] << 8) | buf[1];
    err |= ip3561q_read_reg(IP3561Q_REG_NTC2_H, buf, 2);
    data->ntc_adc[1] = ((uint16_t)buf[0] << 8) | buf[1];
    err |= ip3561q_read_reg(IP3561Q_REG_NTC3_H, buf, 2);
    data->ntc_adc[2] = ((uint16_t)buf[0] << 8) | buf[1];
    err |= ip3561q_read_reg(IP3561Q_REG_NTC4_H, buf, 2);
    data->ntc_adc[3] = ((uint16_t)buf[0] << 8) | buf[1];

    /* 结温: 0x5F-0x60 */
    err |= ip3561q_read_reg(IP3561Q_REG_TJ_H, buf, 2);
    data->tj_adc = ((uint16_t)buf[0] << 8) | buf[1];

    /* 电流: 0x61-0x62 (有符号) */
    {
        uint8_t ca[2];
        err |= ip3561q_read_reg(IP3561Q_REG_CURRENT_H, ca, 2);
        data->current_adc = (int16_t)(((uint16_t)ca[0] << 8) | ca[1]);
    }

    /* TIMER: 0x63, 0x64, 0x7C, 0x7D */
    {
        uint8_t tm[4];
        err |= ip3561q_read_reg(IP3561Q_REG_TIMER0, tm, 4);
        data->timer  = ((uint32_t)tm[0]);
        data->timer |= ((uint32_t)tm[1] << 8);

        err |= ip3561q_read_reg(IP3561Q_REG_TIMER2, tm, 2);
        data->timer |= ((uint32_t)tm[0] << 16);
        data->timer |= ((uint32_t)tm[1] << 24);
    }

    return err;
}

/* ==========================================================================
 *  数据换算
 *
 *  手册 §10.10.1 (VADC, 16-bit 有符号):
 *    bit15=0: V = ADC * Vref / 32768
 *    bit15=1: V = (ADC - 65536) * Vref / 32768
 *    VCx: Vref=6V   → mV = ADC_signed * 6000 / 32768
 *    VBAT: Vref=30V → mV = ADC_signed * 30000 / 32768
 *    PACK: Vref=30V → mV = ADC_signed * 30000 / 32768
 *    NTC: Vref=VLDO=3.3V → Rntc = ADC * Rup / (32768-ADC) (手册注明bit15恒为0)
 *
 *  手册 §10.10.2 (CADC, 16-bit 有符号):
 *    Vcadc = ADC_signed * 120 / 32768 (mV)
 *    I(mA) = Vcadc(mV) * 1000 / 2.5 = ADC_signed * 375 / 256
 * ========================================================================== */

void ip3561q_calc_data(ip3561q_data_t *raw, ip3561q_proc_data_t *p)
{
    uint8_t i;

    if (raw == NULL || p == NULL) return;

    /* 电芯电压: Vcell(mV) = ADC * 6000 / 32768
     * 6000/32768 = 375/2048, +1024 四舍五入 */
    for (i = 0; i < IP3561Q_CELL_CNT; i++)
    {
        uint16_t adc = raw->vcell[i];
        if (adc & 0x8000U) {
            p->vcell_mv[i] = 0;
        } else {
            p->vcell_mv[i] = (uint16_t)(((uint32_t)adc * 375UL + 1024UL) / 2048UL);
        }
    }

    /* VBAT: 电池包总电压, Vbat(mV) = ADC * 30000 / 32768
     * 30000/32768 = 1875/2048 */
    {
        uint16_t adc = raw->vbat_adc;
        if (adc & 0x8000U) {
            p->vbat_mv = 0;
        } else {
            p->vbat_mv = (uint16_t)(((uint32_t)adc * 1875UL + 1024UL) / 2048UL);
        }
    }

    /* NTC2 阻值: 手册直接公式 Rntc(Ω) = NTC_ADC * 10000 / (32768 - NTC_ADC)
     * 手册注明 NTC bit15 恒为 0, 直接 unsigned 计算 */
    {
        uint16_t ntc = raw->ntc_adc[1];  /* NTC2 */
        if (ntc > 0 && ntc < 32768)
        {
            p->rntc_ohm = (uint32_t)ntc * 10000UL / (32768UL - ntc);
        }
        else
        {
            p->rntc_ohm = 0;
        }
    }

    /* 高温标志: NTC 阻值 ≤ 26kΩ (≈57℃, 用于 key_wake_host 唤醒主机) */
    g_bat_high_temp = (p->rntc_ohm > 0 && p->rntc_ohm <= 26000UL) ? 1 : 0;

    /* 电流: I(mA) = ADC_signed * 375 / 256 */
    {
        int32_t cadc = (int32_t)raw->current_adc;  /* 已是 int16_t, 符号正确 */
        p->current_ma = (cadc * 375L) / 256L;
    }
}

/* ==========================================================================
 *  主轮询
 * ========================================================================== */
void ip3561q_proc(void)
{
    static uint32_t last_tick;
    static uint32_t last_cfg_tick;
    uint32_t now = md_get_tick();

    /* 配置重试 */
    if (!ip3561q_cfg_done)
    {
        if (now - last_cfg_tick >= IP3561Q_CFG_RETRY_MS)
        {
            last_cfg_tick = now;
            if (ip3561q_config_regs() != 0)
                ip3561q_cfg_done = 1;
            else
                return;
        }
        else
            return;
    }

    /* 定时轮询 */
    if (now - last_tick < IP3561Q_POLL_MS)
        return;
    last_tick = now;

    ip3561q_comm_ok = (ip3561q_read_all((ip3561q_data_t *)&ip3561q_raw) == 0) ? 1 : 0;
}
