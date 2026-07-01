#include "ip3561q.h"

volatile ip3561q_data_t      ip3561q_raw;
volatile ip3561q_proc_data_t ip3561q_info;
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
 *  过流保护阈值计算 (根据数据手册公式, 使用工厂校准值)
 *
 *  DOC1 (0x04):  V_DOC1_SEL = V_DOC1_SEL_INIT + (Vdoc1 - 14)     / DOC1_STEP
 *    DOC1_STEP = 2 + DOC1_COMP1/64 (mV),  DOC1_COMP1 为 0x2F[7:3] 5位有符号
 *  DOC2 (0x05):  V_DOC2_SEL = V_DOC2_SEL_INIT + (Vdoc2 - 20)     / DOC2_STEP
 *    DOC2_STEP = 4 + DOC2_COMP1*2/64 (mV), DOC2_COMP1 为 0x3E[7:3] 5位有符号
 *  SC   (0x06):  V_SC_SEL   = V_SC_SEL_INIT   + (Vsc   - 40)     / SC_STEP
 *    SC_STEP   = 8 + SC_COMP1*4/64 (mV),   SC_COMP1   为 0x7E[7:3] 5位有符号
 *  COC  (0x07):  V_COC_SEL  = V_COC_SEL_INIT  + (10     - Vcoc)  / COC_STEP
 *    COC_STEP  = -2 - COC_COMP1/64 (mV),   COC_COMP1  为 0x7F[7:3] 5位有符号
 *
 *  海信20K项目参数 (2.5mΩ采样电阻):
 *    DOC1: 11A  → 27.5mV → 寄存器值 ≈ 0x07
 *    DOC2: 15A  → 37.5mV → 寄存器值 ≈ 0x04
 *    SC:   16A  → 40mV   → 寄存器值 ≈ 0x00 (保持出厂默认)
 *    COC:  5.5A → 13.75mV→ 寄存器值 ≈ 0x02
 * ========================================================================== */

/* 5-bit 有符号解析: bit4 为符号位, 补码表示 */
static int8_t ip3561q_parse_comp_5bit(uint8_t reg_val)
{
    int8_t val = (int8_t)((reg_val & 0xF8U) << 3) >> 3;  /* 算术右移自动带符号扩展 */
    return val;
}

static void ip3561q_calc_oc_thresholds(uint8_t *doc1_val, uint8_t *doc2_val,
                                        uint8_t *sc_val, uint8_t *coc_val)
{
    uint8_t  buf;
    int8_t   comp1;
    int16_t  step_64th;     /* 步长 × 64 (定点, 避免浮点) */
    int16_t  delta_64th;    /* 差值 × 64 */
    int16_t  result;

    /* ---- 目标电压 (mV) ---- */
    const int16_t Vdoc1_target = 28;   /* 11A × 2.5mΩ = 27.5mV, 取整28mV ≈ 11.2A */
    const int16_t Vdoc2_target = 36;   /* 15A × 2.5mΩ = 37.5mV, 取整36mV ≈ 14.4A */
    const int16_t Vsc_target   = 40;   /* 保持出厂默认 40mV */
    const int16_t Vcoc_target  = 14;   /* 5.5A × 2.5mΩ = 13.75mV, 取整14mV ≈ 5.6A */

    /* ---- DOC1 (0x04) ---- */
    ip3561q_read_reg(IP3561Q_REG_DOC1, doc1_val, 1);          /* V_DOC1_SEL_INIT */
    ip3561q_read_reg(IP3561Q_REG_DOC1_COMP, &buf, 1);
    comp1     = ip3561q_parse_comp_5bit(buf);
    step_64th = (int16_t)(2 * 64 + comp1);                    /* (2 + comp1/64) × 64 */
    if (step_64th <= 0) step_64th = 128;                      /* 安全保护: 最小 2mV */
    delta_64th = (int16_t)((Vdoc1_target - 14) * 64);
    result     = (int16_t)(*doc1_val) + delta_64th / step_64th;
    if (result < 0)   result = 0;
    if (result > 255) result = 255;
    *doc1_val = (uint8_t)result;

    /* ---- DOC2 (0x05) ---- */
    ip3561q_read_reg(IP3561Q_REG_DOC2, doc2_val, 1);          /* V_DOC2_SEL_INIT */
    ip3561q_read_reg(IP3561Q_REG_DOC2_COMP, &buf, 1);
    comp1     = ip3561q_parse_comp_5bit(buf);
    step_64th = (int16_t)(4 * 64 + comp1 * 2);                /* (4 + comp1*2/64) × 64 */
    if (step_64th <= 0) step_64th = 256;
    delta_64th = (int16_t)((Vdoc2_target - 20) * 64);
    result     = (int16_t)(*doc2_val) + delta_64th / step_64th;
    if (result < 0)   result = 0;
    if (result > 255) result = 255;
    *doc2_val = (uint8_t)result;

    /* ---- SC (0x06) ---- */
    ip3561q_read_reg(IP3561Q_REG_SC, sc_val, 1);              /* V_SC_SEL_INIT */
    ip3561q_read_reg(IP3561Q_REG_SC_COMP, &buf, 1);
    comp1     = ip3561q_parse_comp_5bit(buf);
    step_64th = (int16_t)(8 * 64 + comp1 * 4);                /* (8 + comp1*4/64) × 64 */
    if (step_64th <= 0) step_64th = 512;
    delta_64th = (int16_t)((Vsc_target - 40) * 64);
    result     = (int16_t)(*sc_val) + delta_64th / step_64th;
    if (result < 0)   result = 0;
    if (result > 255) result = 255;
    *sc_val = (uint8_t)result;

    /* ---- COC (0x07) ---- */
    ip3561q_read_reg(IP3561Q_REG_COC, coc_val, 1);            /* V_COC_SEL_INIT */
    ip3561q_read_reg(IP3561Q_REG_COC_COMP, &buf, 1);
    comp1     = ip3561q_parse_comp_5bit(buf);
    step_64th = (int16_t)(-2 * 64 - comp1);                   /* (-2 - comp1/64) × 64, 负步长! */
    if (step_64th >= 0) step_64th = -128;                     /* 安全保护: 最大 -2mV */
    delta_64th = (int16_t)((10 - Vcoc_target) * 64);          /* COC_INIT=10, Vcoc=目标绝对值 */
    result     = (int16_t)(*coc_val) + delta_64th / step_64th;
    if (result < 0)   result = 0;
    if (result > 255) result = 255;
    *coc_val = (uint8_t)result;
}

/* ==========================================================================
 *  配置寄存器写入 (按海信20K项目寄存器操作手册)
 *
 *  注意: 0x04-0x07 由 ip3561q_calc_oc_thresholds() 动态计算,
 *        补偿寄存器 (0x2F/0x3E/0x7E/0x7F) 为工厂校准值, 不写入
 * ========================================================================== */
static const uint8_t ip3561q_cfg_static[][2] = {
    { IP3561Q_REG_CTL1,         0x04 },   /* OC_MODE_SEL=1: 放电过流只关DO, 充电过流只关CO */
    { IP3561Q_REG_CTL2,         0x34 },   /* NTC1/2使能, NTC3/4不使能, 均衡始终开启 */
    { IP3561Q_REG_CTL3,         0x0C },   /* IDLE下CADC+VADC分时采样, 功耗最小 */
    { IP3561Q_REG_IDLE_CK,      0x80 },   /* IDLE时钟131kHz, 电压保护延时×2 */
    { IP3561Q_REG_SLEEP_IDLE,   0x40 },   /* IDLE下均衡不使能, 节省功耗 */
    { IP3561Q_REG_NTC_WDOG,     0x38 },   /* NTC总使能 + 充电低温 + 放电低温 */
    { IP3561Q_REG_CELL_PD,      0x40 },   /* 4串电池 */
    { IP3561Q_REG_OV_H,         0xC0 },   /* OV=4.5V, TH_OV=0x300, 高8位=0xC0 */
    { IP3561Q_REG_OVL_OVRH,     0x2E },   /* OV低2位=0 + OVR高6位=0x2E (4.35V) */
    { IP3561Q_REG_OVRL_OVDLY,   0x60 },   /* OVR低4位=0x6, 组合0x2E6 (4.35V); OV延时65ms */
    { IP3561Q_REG_UV_H,         0x74 },   /* UV=2.72V, TH_UV=0x1D0, 高8位=0x74 */
    { IP3561Q_REG_UVL_UVRH,     0x20 },   /* UV低2位=0 + UVR高6位=0x20 (3.00V) */
    { IP3561Q_REG_UVRL_UVDLY,   0x00 },   /* UVR低4位=0; UV延时65ms */
    { IP3561Q_REG_BAL_H,        0xB9 },   /* 均衡=4.35V, TH_BAL=0x2E6, 高8位=0xB9 */
    { IP3561Q_REG_BAL_L_DLY,    0x8B },   /* 均衡低2位=0x2 (组合0x2E6); 延时65ms */
    { IP3561Q_REG_MCU_CTL2,     0x40 },   /* IDLE使能, 功耗约80μA */
};

#define IP3561Q_CFG_STATIC_COUNT \
    (sizeof(ip3561q_cfg_static) / sizeof(ip3561q_cfg_static[0]))

static uint8_t ip3561q_config_regs(void)
{
    uint8_t i;
    uint8_t rbuf;
    uint8_t res = 1;
    uint8_t doc1_val, doc2_val, sc_val, coc_val;

    /* Step 1: 读取工厂校准值, 计算 0x04-0x07 过流保护阈值 */
    ip3561q_calc_oc_thresholds(&doc1_val, &doc2_val, &sc_val, &coc_val);

    /* Step 2: 写入固定配置寄存器 (0x00-0x03, 0x0A-0x17, 0x42 等) */
    for (i = 0; i < IP3561Q_CFG_STATIC_COUNT; i++)
    {
        uint8_t reg  = ip3561q_cfg_static[i][0];
        uint8_t val  = ip3561q_cfg_static[i][1];

        ip3561q_write_reg(reg, &val, 1);
        if (ip3561q_read_reg(reg, &rbuf, 1) || rbuf != val)
            res = 0;
    }

    /* Step 3: 写入计算后的过流保护阈值 (0x04-0x07) */
    ip3561q_write_reg(IP3561Q_REG_DOC1, &doc1_val, 1);
    if (ip3561q_read_reg(IP3561Q_REG_DOC1, &rbuf, 1) || rbuf != doc1_val)
        res = 0;

    ip3561q_write_reg(IP3561Q_REG_DOC2, &doc2_val, 1);
    if (ip3561q_read_reg(IP3561Q_REG_DOC2, &rbuf, 1) || rbuf != doc2_val)
        res = 0;

    ip3561q_write_reg(IP3561Q_REG_SC, &sc_val, 1);
    if (ip3561q_read_reg(IP3561Q_REG_SC, &rbuf, 1) || rbuf != sc_val)
        res = 0;

    ip3561q_write_reg(IP3561Q_REG_COC, &coc_val, 1);
    if (ip3561q_read_reg(IP3561Q_REG_COC, &rbuf, 1) || rbuf != coc_val)
        res = 0;

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

    /* NTC1 阻值: 手册直接公式 Rntc(Ω) = NTC_ADC * 10000 / (32768 - NTC_ADC)
     * 手册注明 NTC bit15 恒为 0, 直接 unsigned 计算 */
    {
        uint16_t ntc = raw->ntc_adc[0];  /* NTC1 */
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

    ip3561q_read_all((ip3561q_data_t *)&ip3561q_raw);
}
