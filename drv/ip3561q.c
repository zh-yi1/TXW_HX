#include "ip3561q.h"

volatile ip3561q_data_t      ip3561q_raw;
volatile ip3561q_proc_data_t ip3561q_info;
volatile uint8_t             g_bat_high_temp;  /* 电芯高温: rntc_ohm <= 3340Ω (NTC 阻值越低越热, 3.34kΩ≈57℃) */

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

/* 
 * 5-bit 有符号补码解析
 * 寄存器 bit7:3 为补码表示的5位有符号数
 * 正确提取: (reg_val & 0xF8) >> 3，然后进行符号扩展
 */
static int8_t ip3561q_parse_comp_5bit(uint8_t reg_val)
{
    int8_t result;
    
    /* 提取 bit7:3 */
    result = (int8_t)((reg_val & 0xF8) >> 3);
    
    /* 如果最高位(bit4)为1，表示负数，进行符号扩展 */
    if (result & 0x10) {
        result = result - 32;  /* 或者 result |= 0xE0; */
    }
    
    return result;
}

static uint8_t ip3561q_calc_oc_thresholds(uint8_t *doc1_val, uint8_t *doc2_val,
                                          uint8_t *sc_val, uint8_t *coc_val)
{
    uint8_t  buf;
    uint8_t  reg_init;
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
    reg_init = 0;   /* V_DOC1_SEL_INIT 按出厂默认 0, 不读当前寄存器值 (避免污染/越算越大) */
    if (ip3561q_read_reg(IP3561Q_REG_DOC1_COMP, &buf, 1))
        return 1;
    comp1     = ip3561q_parse_comp_5bit(buf);
    /* DOC1_STEP = 2 + comp1/64 (mV) */
    step_64th = (int16_t)(2 * 64 + comp1);                    /* (2 + comp1/64) × 64 */
    if (step_64th <= 0) step_64th = 128;                      /* 安全保护: 最小 2mV */
    delta_64th = (int16_t)((Vdoc1_target - 14) * 64);         /* DOC1_INIT = 14mV */
    result     = (int16_t)reg_init + delta_64th / step_64th;
    if (result < 0)   result = 0;
    if (result > 255) result = 255;
    *doc1_val = (uint8_t)result;
    // LOGI("DOC1: reg_init=%d reg_comp=0x%02X comp1=%d step_64th=%d delta_64th=%d final=%d\r\n",
    //      reg_init, buf, comp1, step_64th, delta_64th, result);

    /* ---- DOC2 (0x05) ---- */
    reg_init = 0;   /* V_DOC2_SEL_INIT 按出厂默认 0, 不读当前寄存器值 (避免污染/越算越大) */
    if (ip3561q_read_reg(IP3561Q_REG_DOC2_COMP, &buf, 1))
        return 1;
    comp1     = ip3561q_parse_comp_5bit(buf);
    /* DOC2_STEP = 4 + comp1*2/64 (mV) */
    step_64th = (int16_t)(4 * 64 + comp1 * 2);                /* (4 + comp1*2/64) × 64 */
    if (step_64th <= 0) step_64th = 256;                      /* 安全保护: 最小 4mV */
    delta_64th = (int16_t)((Vdoc2_target - 20) * 64);         /* DOC2_INIT = 20mV */
    result     = (int16_t)reg_init + delta_64th / step_64th;
    if (result < 0)   result = 0;
    if (result > 255) result = 255;
    *doc2_val = (uint8_t)result;
    // LOGI("DOC2: reg_init=%d reg_comp=0x%02X comp1=%d step_64th=%d delta_64th=%d final=%d\r\n",
    //      reg_init, buf, comp1, step_64th, delta_64th, result);

    /* ---- SC (0x06) ---- */
    reg_init = 0;   /* V_SC_SEL_INIT 按出厂默认 0, 不读当前寄存器值 (避免污染/越算越大) */
    if (ip3561q_read_reg(IP3561Q_REG_SC_COMP, &buf, 1))
        return 1;
    comp1     = ip3561q_parse_comp_5bit(buf);
    /* SC_STEP = 8 + comp1*4/64 (mV) */
    step_64th = (int16_t)(8 * 64 + comp1 * 4);                /* (8 + comp1*4/64) × 64 */
    if (step_64th <= 0) step_64th = 512;                      /* 安全保护: 最小 8mV */
    delta_64th = (int16_t)((Vsc_target - 40) * 64);           /* SC_INIT = 40mV */
    result     = (int16_t)reg_init + delta_64th / step_64th;
    if (result < 0)   result = 0;
    if (result > 255) result = 255;
    *sc_val = (uint8_t)result;
    // LOGI("SC:   reg_init=%d reg_comp=0x%02X comp1=%d step_64th=%d delta_64th=%d final=%d\r\n",
    //      reg_init, buf, comp1, step_64th, delta_64th, result);

    /* ---- COC (0x07) ---- */
    reg_init = 0;   /* V_COC_SEL_INIT 按出厂默认 0, 不读当前寄存器值 (避免污染/越算越大) */
    if (ip3561q_read_reg(IP3561Q_REG_COC_COMP, &buf, 1))
        return 1;
    comp1     = ip3561q_parse_comp_5bit(buf);
    /*
     * COC_STEP = -2 - comp1/64 (mV)
     * 注意: 步长为负数，因为 COC 阈值是负电压
     * Vcoc 为目标绝对值 (如 14mV 表示 -14mV)
     */
    step_64th = (int16_t)(-2 * 64 - comp1);                   /* (-2 - comp1/64) × 64 */
    if (step_64th >= 0) step_64th = -128;                     /* 安全保护: 最大 -2mV */
    delta_64th = (int16_t)((10 - Vcoc_target) * 64);          /* COC_INIT = 10mV */
    result     = (int16_t)reg_init + delta_64th / step_64th;
    if (result < 0)   result = 0;
    if (result > 255) result = 255;
    *coc_val = (uint8_t)result;
    // LOGI("COC:  reg_init=%d reg_comp=0x%02X comp1=%d step_64th=%d delta_64th=%d final=%d\r\n",
    //      reg_init, buf, comp1, step_64th, delta_64th, result);

    return 0;
}

/* ==========================================================================
 *  OC 阈值 Flash 备份 (CRC-8 校验)
 * ========================================================================== */
#define IP3561Q_OC_MAGIC    0xA5U
#define IP3561Q_CRC8_POLY   0x07U
#define IP3561Q_OC_MAX_VAL  0x0AU   /* 阈值合理上限: 正常值 ≤8 (DOC1≈7), 130/255 为读失败垃圾 */

static uint8_t ip3561q_crc8(const uint8_t *data, uint8_t len)
{
    uint8_t crc = 0;
    uint8_t i, j;

    for (i = 0; i < len; i++)
    {
        crc ^= data[i];
        for (j = 0; j < 8; j++)
        {
            if (crc & 0x80)
                crc = (uint8_t)((crc << 1) ^ IP3561Q_CRC8_POLY);
            else
                crc <<= 1;
        }
    }
    return crc;
}

/* 阈值合理性校验: DOC1/DOC2/SC/COC 正常值 ≤8 (目标 ≈0x07/0x04/0x00/0x02),
   超过上限说明是读失败/算错的垃圾值 (如 130), 拒绝采用以免固化到 Flash */
static uint8_t ip3561q_oc_val_range_ok(const ip3561q_oc_cfg_t *cfg)
{
    return (cfg->doc1 <= IP3561Q_OC_MAX_VAL &&
            cfg->doc2 <= IP3561Q_OC_MAX_VAL &&
            cfg->sc   <= IP3561Q_OC_MAX_VAL &&
            cfg->coc  <= IP3561Q_OC_MAX_VAL);
}

uint8_t ip3561q_oc_cfg_read(ip3561q_oc_cfg_t *cfg)
{
    uint8_t expected_crc;

    if (cfg == NULL)
        return 0;

    if (flash_read(FLASH_DATA_BASE + FLASH_OFFS_IP3561Q_OC_CFG,
                   (uint8_t *)cfg, sizeof(ip3561q_oc_cfg_t)) != MD_OK)
        return 0;

    if (cfg->magic != IP3561Q_OC_MAGIC)
        return 0;

    /* CRC8 覆盖 magic ~ coc (前 5 字节) */
    expected_crc = ip3561q_crc8((const uint8_t *)cfg, sizeof(ip3561q_oc_cfg_t) - 1);
    if (cfg->crc8 != expected_crc)
        return 0;

    /* 数值合理性: 已固化垃圾值 (如 130) 即使 magic/CRC 正确也判无效, 触发重算自愈 */
    if (!ip3561q_oc_val_range_ok(cfg))
        return 0;

    return 1;
}

void ip3561q_oc_cfg_save(const ip3561q_oc_cfg_t *cfg)
{
    ip3561q_oc_cfg_t local;

    if (cfg == NULL)
        return;

    local = *cfg;
    local.magic = IP3561Q_OC_MAGIC;
    /* CRC8 覆盖 magic ~ coc (前 5 字节) */
    local.crc8 = ip3561q_crc8((const uint8_t *)&local, sizeof(ip3561q_oc_cfg_t) - 1);

    flash_page_erase(FLASH_DATA_BASE + FLASH_OFFS_IP3561Q_OC_CFG);
    flash_write(FLASH_DATA_BASE + FLASH_OFFS_IP3561Q_OC_CFG,
                (uint8_t *)&local, sizeof(ip3561q_oc_cfg_t));
}

/* ==========================================================================
 *  配置寄存器写入 (按海信20K项目寄存器操作手册)
 *
 *  注意: 0x04-0x07 优先从 Flash 备份加载, 备份无效时动态计算并保存;
 *        补偿寄存器 (0x2F/0x3E/0x7E/0x7F) 为工厂校准值, 不写入
 * ========================================================================== */
static const uint8_t ip3561q_cfg_static[][2] = {
    { IP3561Q_REG_CTL1,         0x04 },   /* OC_MODE_SEL=1: 放电过流只关DO, 充电过流只关CO */
    { IP3561Q_REG_CTL2,         0x34 },   /* NTC1/2使能, NTC3/4不使能, 均衡始终开启 */
    { IP3561Q_REG_CTL3,         0x0C },   /* IDLE下CADC+VADC分时采样, 功耗最小 */
    // { IP3561Q_REG_IDLE_CK,      0x80 },   /* IDLE时钟131kHz, 电压保护延时×2 */
    { IP3561Q_REG_SLEEP_IDLE,   0x40 },   /* IDLE下均衡不使能, 节省功耗 */
    { IP3561Q_REG_NTC_WDOG,     0x38 },   /* NTC总使能 + 充电低温 + 放电低温 */
    // { IP3561Q_REG_CELL_PD,      0x40 },   /* 4串电池 */
    { IP3561Q_REG_OV_H,         0xC0 },   /* OV=4.5V, TH_OV=0x300, 高8位=0xC0 */
    { IP3561Q_REG_OVL_OVRH,     0x2E },   /* OV低2位=0 + OVR高6位=0x2E (4.35V) */
    { IP3561Q_REG_OVRL_OVDLY,   0x60 },   /* OVR低4位=0x6, 组合0x2E6 (4.35V); OV延时65ms */
    { IP3561Q_REG_UV_H,         0x74 },   /* UV=2.72V, TH_UV=0x1D0, 高8位=0x74 */
    { IP3561Q_REG_UVL_UVRH,     0x20 },   /* UV低2位=0 + UVR高6位=0x20 (3.00V) */
    { IP3561Q_REG_UVRL_UVDLY,   0x00 },   /* UVR低4位=0; UV延时65ms */
    { IP3561Q_REG_BAL_H,        0xBB },   /* 均衡=4.4V, TH_BAL=0x2EF, 高8位=0xBB */
    { IP3561Q_REG_BAL_L_DLY,    0xCB },   /* 均衡低2位=0x3 (组合0x2EF); 延时65ms */
    { IP3561Q_REG_MCU_CTL2,     0x00 },   /* IDLE使能, 功耗约80μA */
};

#define IP3561Q_CFG_STATIC_COUNT \
    (sizeof(ip3561q_cfg_static) / sizeof(ip3561q_cfg_static[0]))

static uint8_t ip3561q_config_regs(void)
{
    uint8_t i;
    uint8_t rbuf;
    uint8_t res = 1;
    uint8_t doc1_val, doc2_val, sc_val, coc_val;
    uint8_t cell_pd_val = 0x40;

    ip3561q_write_reg(IP3561Q_REG_CELL_PD, &cell_pd_val, 1);
    if (ip3561q_read_reg(IP3561Q_REG_CELL_PD, &rbuf, 1) || rbuf != cell_pd_val)
        res = 0;

    /* Step 1: 获取 0x04-0x07 过流保护阈值 (优先 Flash 备份, 无效则计算并保存) */  
    ip3561q_oc_cfg_t oc_cfg;
    
    if (ip3561q_oc_cfg_read(&oc_cfg))
    {
        /* Flash 备份有效, 直接使用 */
        doc1_val = oc_cfg.doc1;
        doc2_val = oc_cfg.doc2;
        sc_val   = oc_cfg.sc;
        coc_val  = oc_cfg.coc;
    }
    else
    {
        /* 首次上电或备份无效: 芯片未就绪则本轮不配置, 交给 ip3561q_proc 重试 */
        if (sw_i2c_ping((uint8_t)(IP3561Q_SLAVE_ADDR << 1)))
            return 0;

        /* 读取工厂校准值计算; 任一 I2C 读失败则不保存, 交给重试 */
        if (ip3561q_calc_oc_thresholds(&doc1_val, &doc2_val, &sc_val, &coc_val) != 0)
            return 0;

        oc_cfg.doc1 = doc1_val;
        oc_cfg.doc2 = doc2_val;
        oc_cfg.sc   = sc_val;
        oc_cfg.coc  = coc_val;
        ip3561q_oc_cfg_save(&oc_cfg);
    }

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

/* 休眠唤醒初始化 — 仅恢复 I2C 硬件, 不重新配置 AFE 寄存器 (芯片保持断电前配置) */
void ip3561q_wakeup_init(void)
{
    sw_i2c_init();
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

    /* TIMER: 0x63, 0x64, 0x7C, 0x7D
       注意: data 是 pack(1) 结构体, timer 成员地址非 4 字节对齐,
       不能把 &data->timer 直接传给 uint32_t* (M0 非对齐访问 HardFault),
       必须经对齐的局部变量中转, 由编译器按 packed 成员拆字节写入 */
    {
        uint32_t tmr;
        if (ip3561q_read_timer(&tmr) == 0)
            data->timer = tmr;
        else
            err |= 1;
    }

    return err;
}

/* ==========================================================================
 *  读取 32 位实时计时器 (手册 §10.13)
 *
 *  LSB=1s, 上电即计数且 IDLE 下不停, 掉电清零.
 *  低 16 位在 0x63/0x64, 高 16 位在 0x7C/0x7D, 两笔传输之间低 16 位可能
 *  进位, 用 "高-低-高" 一致性读法: 两次高 16 位一致才接受, 否则重读.
 *  注意起始地址必须用 0x63 而非连读 4 字节: 0x65/0x66 是读清零的标志位
 *  寄存器, 连读会把它们误清除.
 * ========================================================================== */
uint8_t ip3561q_read_timer(uint32_t *sec)
{
    uint8_t retry;

    if (sec == NULL)
        return 1;

    for (retry = 0; retry < 3; retry++)
    {
        uint8_t hi1[2], lo[2], hi2[2];

        if (ip3561q_read_reg(IP3561Q_REG_TIMER2, hi1, 2))
            continue;
        if (ip3561q_read_reg(IP3561Q_REG_TIMER0, lo, 2))
            continue;
        if (ip3561q_read_reg(IP3561Q_REG_TIMER2, hi2, 2))
            continue;
        if (hi1[0] != hi2[0] || hi1[1] != hi2[1])
            continue;

        *sec = ((uint32_t)hi1[1] << 24) | ((uint32_t)hi1[0] << 16) |
               ((uint32_t)lo[1]  << 8)  | ((uint32_t)lo[0]);
        return 0;
    }
    return 1;
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
            p->rntc1_ohm = (uint32_t)ntc * 10000UL / (32768UL - ntc);
        }
        else
        {
            p->rntc1_ohm = 0;
        }
    }

    /* NTC2 阻值: 同上公式 */
    {
        uint16_t ntc = raw->ntc_adc[1];  /* NTC2 */
        if (ntc > 0 && ntc < 32768)
        {
            p->rntc2_ohm = (uint32_t)ntc * 10000UL / (32768UL - ntc);
        }
        else
        {
            p->rntc2_ohm = 0;
        }
    }

    /* 高温标志: 任意 NTC 阻值 ≤ 3.34kΩ (≈57℃, 用于 key_wake_host 唤醒主机) */
    g_bat_high_temp = ((p->rntc1_ohm  > 0 && p->rntc1_ohm  <= 3340UL) ||
                       (p->rntc2_ohm > 0 && p->rntc2_ohm <= 3340UL)) ? 1 : 0;

    /* 电流: I(mA) = ADC_signed * 375 / 256
     * IP3561Q 手册: 正=放电, 负=充电
     * 协议规范:   正=充电, 负=放电
     * 取反以统一为协议方向 */
    {
        int32_t cadc = (int32_t)raw->current_adc;  /* 已是 int16_t, 符号正确 */
        p->current_ma = -(cadc * 375L) / 256L;
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
