#include "i2c_slave.h"

/* ---- 寄存器缓冲区 (协议 V1.1 最大地址 0x8F, 共 0x90=144 字节) ---- */
#define I2C_REG_MAP_SIZE  0x90
volatile uint8_t i2c_reg_map[I2C_REG_MAP_SIZE];

/* ---- 按键事件影子缓冲 (协议 §4.6) ---- */
volatile uint8_t key_event_buf;

/* ---- ISR 内部状态 ---- */
static volatile uint8_t  i2c_reg_addr;
static volatile uint8_t  i2c_first_byte;  /* 1 = 下一个接收字节是寄存器地址 */

/* ---- 方向定义 (与 SDK demo 一致) ---- */
#define I2C_DIR_WRITE  I2C_STAT2_TRF_MSK
#define I2C_DIR_READ   0x00000000U

/* ---- 判断寄存器地址是否可写 (协议 V1.1) ---- */
static uint8_t reg_is_writable(uint8_t addr)
{
    /* 0x00~0x1F: 主机信息 + 电池数据 (W) */
    if (addr <= 0x1F) return 1;
    /* 0x20~0x30: NTC 数据 (W) */
    if (addr <= 0x30) return 1;
    /* 0x31~0x3F: NTC 预留 (W) */
    if (addr <= 0x3F) return 1;
    /* 0x40~0x4F: 端口数据 (W) */
    if (addr <= 0x4F) return 1;
    /* 0x50~0x6F: 电芯/AFE 数据 (R) */
    if (addr <= 0x6F) return 0;
    /* 0x70: KEY_EVENT (R/W) */
    if (addr == 0x70) return 1;
    /* 0x71~0x7F: BMS 备用 (R) */
    if (addr <= 0x7F) return 0;
    /* 0x80~0x8F: 系统信息 (R) */
    if (addr <= 0x8F) return 0;
    /* 其他预留区域: 允许写入 */
    return 1;
}

/* ========================================================================
 * i2c_slave_init — 初始化 I2C1 为从机模式
 * ======================================================================== */
void i2c_slave_init(void)
{
    md_gpio_init_t gpio_init;
    md_i2c_init_t  i2c_init;

    /* --- GPIO: PA5=SCL, PA6=SDA, open-drain, pull-up, FUNC_3 --- */
    md_gpio_init_struct(&gpio_init);

    gpio_init.mode = MD_GPIO_MODE_OUTPUT;
    gpio_init.odos = MD_GPIO_OPEN_DRAIN;
    gpio_init.pupd = MD_GPIO_PUSH_UP;
    gpio_init.odrv = MD_GPIO_OUT_DRIVE_NORMAL;
    gpio_init.flt  = MD_GPIO_FILTER_DISABLE;
    gpio_init.type = MD_GPIO_TYPE_CMOS;
    gpio_init.func = MD_GPIO_FUNC_2;

    md_gpio_init(GPIOA, MD_GPIO_PIN_5, &gpio_init);  /* SCL: PA5 */
    md_gpio_init(GPIOA, MD_GPIO_PIN_6, &gpio_init);  /* SDA: PA6 */

    /* --- I2C1 从机配置 --- */
    md_i2c_struct_init(&i2c_init);

    i2c_init.addr_mode    = MD_I2C_ADDR_7BIT;
    i2c_init.clk_speed    = 100000;            /* 100kHz standard mode */
    i2c_init.dual_addr    = MD_I2C_DUALADDR_DISABLE;
    i2c_init.duty         = MD_I2C_DUTYCYCLE_2;
    i2c_init.general_call = MD_I2C_GENERALCALL_DISABLE;
    i2c_init.stretch      = MD_I2C_STRETCH_ENABLE;
    i2c_init.own_addr1    = I2C_SLAVE_ADDR << 1;

    md_i2c_init(I2C1, &i2c_init);

    /* --- NVIC --- */
    NVIC_SetPriority(I2C1_IRQn, 1);
    NVIC_EnableIRQ(I2C1_IRQn);

    /* --- 使能中断和外设 --- */
    md_i2c_enable_it_evt(I2C1);   /* 事件中断 (ADDR, STOP, BTF) */
    md_i2c_enable_it_err(I2C1);   /* 错误中断 (AF, BERR, ARLO, OVR) */

    MD_I2C_ENABLE(I2C1);
    md_i2c_enable_ack(I2C1);

    for (int i = 0; i < 256; i++)
    {
        i2c_reg_map[i] = i;
    }
    /* --- 初始化寄存器默认值 --- */
    i2c_reg_map[REG_FW_VERSION_L]    = 0x00;  /* V1.00, 由 proc 填充 */
    i2c_reg_map[REG_FW_VERSION_H]    = 0x01;
    i2c_reg_map[REG_TFT_ONLINE_CRC]  = 0x55;  /* 从机就绪标志 */
    i2c_reg_map[REG_UPDATE_CRC]      = 0x00;  /* 默认非升级模式 */
}

/* ========================================================================
 * I2C1_Handler — I2C1 中断服务函数
 *
 * 状态流转:
 *   ADDR 匹配 → 根据方向设置 first_byte 标志
 *   WRITE: first_byte=1 → 收到 reg_addr, first_byte=0 → 后续字节写入 reg_map
 *   READ:  从 reg_map[reg_addr++] 发送数据
 *   STOP/AF → 重置状态
 * ======================================================================== */
void I2C1_Handler(void)
{
    uint8_t tmp;

    /* --- TXBE: 发送缓冲区空 (主机读方向, 从机发送) --- */
    if (md_i2c_is_active_flag_txbe(I2C1) && md_i2c_is_enable_it_buf(I2C1)
        && md_i2c_is_enable_it_evt(I2C1))
    {
        if (i2c_reg_addr < I2C_REG_MAP_SIZE)
            md_i2c_transmit_data8(I2C1, i2c_reg_map[i2c_reg_addr]);
        else
            md_i2c_transmit_data8(I2C1, 0x00);  /* 越界返回 0 */
        i2c_reg_addr++;
    }

    /* --- RXNE: 接收缓冲区非空 (主机写方向, 从机接收) --- */
    if (md_i2c_is_active_flag_rxne(I2C1) && md_i2c_is_enable_it_buf(I2C1)
        && md_i2c_is_enable_it_evt(I2C1))
    {
        tmp = md_i2c_receive_data8(I2C1);

        if (i2c_first_byte)
        {
            /* 第一个字节 = 寄存器地址 */
            i2c_reg_addr   = tmp;
            i2c_first_byte = 0;
        }
        else
        {
            /* 后续字节 = 数据，只写入可写寄存器 (且不越界) */
            if (i2c_reg_addr < I2C_REG_MAP_SIZE && reg_is_writable(i2c_reg_addr))
            {
                i2c_reg_map[i2c_reg_addr] = tmp;
            }
            i2c_reg_addr++;
        }
    }

    /* --- ADDR: 地址匹配 --- */
    if (md_i2c_is_active_flag_addr(I2C1) && md_i2c_is_enable_it_evt(I2C1))
    {
        i2c_clear_flag_addr(I2C1);
        md_i2c_enable_it_buf(I2C1);

        if (md_i2c_get_transfer_direction(I2C1) == I2C_DIR_READ)
        {
            /* TRF=0: 从机接收 → 主机写, 下一个字节是寄存器地址 */
            i2c_first_byte = 1;
        }
        else
        {
            /* TRF=1: 从机发送 → 主机读, 从当前 reg_addr 开始发送 */
            i2c_first_byte = 0;
        }
    }

    /* --- AF: ACK 失败 (主机读结束, 发了 NACK) --- */
    if (md_i2c_is_active_flag_af(I2C1) && md_i2c_is_enable_it_err(I2C1))
    {
        md_i2c_clear_flag_af(I2C1);
        md_i2c_disable_it_buf(I2C1);
        i2c_first_byte = 0;
    }

    /* --- STOP: 停止条件 --- */
    if (md_i2c_is_active_flag_stop(I2C1) && md_i2c_is_enable_it_evt(I2C1))
    {
        i2c_clear_flag_stop(I2C1);
        md_i2c_disable_it_buf(I2C1);

        /* 排空 RXNE */
        while (md_i2c_is_active_flag_rxne(I2C1))
        {
            md_i2c_receive_data8(I2C1);
        }

        i2c_first_byte = 0;
        i2c_reg_addr   = 0;
    }

    /* --- BERR: 总线错误, 需要复位 I2C 模块恢复 --- */
    if (md_i2c_is_active_flag_berr(I2C1) && md_i2c_is_enable_it_err(I2C1))
    {
        md_i2c_clear_flag_berr(I2C1);
        md_i2c_disable_it_buf(I2C1);
        i2c_first_byte = 0;
        i2c_reg_addr   = 0;

        /* 软复位 I2C 外设 */
        MD_I2C_DISABLE(I2C1);
        md_i2c_enable_ack(I2C1);
        MD_I2C_ENABLE(I2C1);
    }

    /* --- ARLO: 仲裁丢失 (从机模式下罕见, 清标志即可) --- */
    if (md_i2c_is_active_flag_arlo(I2C1) && md_i2c_is_enable_it_err(I2C1))
    {
        md_i2c_clear_flag_arlo(I2C1);
    }

    /* --- OVR: 溢出 (数据丢失, 清标志, 通信流会错位, 等待下次 START 恢复) --- */
    if (md_i2c_is_active_flag_ovr(I2C1) && md_i2c_is_enable_it_err(I2C1))
    {
        md_i2c_clear_flag_ovr(I2C1);
    }
}

/* ========================================================================
 * pull_sensor_data — 采集 CW1573 电池数据, 填入 reg_map (R 区域 §4.5) + ui_data
 *
 * V1~V4 (0x50-0x57), VPACK (0x58-0x59), BAT_CURRENT (0x5A-0x5B),
 * NTC1 (0x5C-0x5F), OVP_PERMANENT (0x60), AFE_PROTECT1-3 (0x61-0x63)
 * ======================================================================== */
static void pull_sensor_data(void)
{
    uint32_t mv;
    uint16_t tmp16;

    /* CW1573 未就绪: 不覆盖 ui_data 已有值 (可能来自主机或初始值) */
    if (!cw1573_is_ready())
        return;

    cw1573_calc_data((cw1573_data_t *)&cw1573_raw, (cw1573_proc_data_t *)&cw1573_info);

    /* V1~V4: 电芯电压 (mV), 协议 §4.5 */
    for (int i = 0; i < 4; i++) {
        mv = (uint32_t)cw1573_raw.vcell[i] * 78125UL / 1000000UL;
        tmp16 = (uint16_t)mv;
        i2c_reg_map[REG_V1_L + i * 2] = (uint8_t)(tmp16 & 0xFF);
        i2c_reg_map[REG_V1_H + i * 2] = (uint8_t)(tmp16 >> 8);
    }

    /* VPACK: 电池组总电压 (mV), 协议 §4.5 */
    mv = 0;
    for (int i = 0; i < 4; i++)
        mv += (uint32_t)cw1573_raw.vcell[i] * 78125UL / 1000000UL;
    tmp16 = (uint16_t)mv;
    i2c_reg_map[REG_VPACK_L] = (uint8_t)(tmp16 & 0xFF);
    i2c_reg_map[REG_VPACK_H] = (uint8_t)(tmp16 >> 8);
    ui_data.bat_voltage = tmp16;

    /* BAT_CURRENT: 电池电流 (mA, 正=充电), 协议 §4.5 */
    int16_t cur = (int16_t)cw1573_info.current_ma;
    i2c_reg_map[REG_BAT_CURRENT_L] = (uint8_t)(cur & 0xFF);
    i2c_reg_map[REG_BAT_CURRENT_H] = (uint8_t)((cur >> 8) & 0xFF);
    ui_data.bat_current = cw1573_info.current_ma;

    /* 充放电状态: 来自 CW1573 state_flag2 bit4 (CHG_STATE) */
    ui_data.is_charge = (cw1573_raw.state_flag2 & CW1573_CHG_STATE) ? true : false;

    /* 充电时自动关闭小电流模式 */
    if (ui_data.is_charge)
        ui_data.low_current_flag = false;

    /* NTC1: 温度电阻值 (Ω), 协议 §4.2 */
    uint16_t ts = cw1573_raw.ts_adc & 0x7FFF;
    uint32_t vntc = (uint32_t)ts * 78125UL / 1000000UL;
    uint32_t rntc = 0;
    if (vntc > 0 && vntc < 2545)
        rntc = 10000UL * vntc / (2545 - vntc);
    i2c_reg_map[REG_NTC1_0] = (uint8_t)(rntc & 0xFF);
    i2c_reg_map[REG_NTC1_1] = (uint8_t)((rntc >> 8) & 0xFF);
    i2c_reg_map[REG_NTC1_2] = (uint8_t)((rntc >> 16) & 0xFF);
    i2c_reg_map[REG_NTC1_3] = (uint8_t)((rntc >> 24) & 0xFF);
    ui_data.bat_temperature = cw1573_info.temp_01c;
    ui_data.bat_cc = cw1573_info.cc_mah;

    /* AFE_PROTECT1-3: 映射 CW1573 原始状态寄存器, 协议 §4.5 */
    i2c_reg_map[REG_AFE_PROTECT1] = cw1573_raw.state_flag0;
    i2c_reg_map[REG_AFE_PROTECT2] = cw1573_raw.state_flag1;
    i2c_reg_map[REG_AFE_PROTECT3] = cw1573_raw.state_flag2;

}

/* ========================================================================
 * apply_host_data — 解析 G020 写入的 W 寄存器 → ui_data
 * ======================================================================== */
static void apply_host_data(void)
{
    /* 电池数据 (协议 §4.2 W 区域) */
    ui_data.bat_power     = i2c_reg_map[REG_SOC];
    ui_data.bat_max_cap   = i2c_reg_map[REG_SOH];
    ui_data.bat_cycle_cnt = (uint16_t)i2c_reg_map[REG_CYCLE_L]
                          | ((uint16_t)i2c_reg_map[REG_CYCLE_H] << 8);

    /* ---- 端口数据 (协议 §4.4) ---- */

    /* USB-C1 (协议 §4.4: 0=未连接 1=充电 2=放电) */
    ui_data.usb_c1_status = i2c_reg_map[REG_C1_STATUS];
    if (ui_data.usb_c1_status) {
        uint16_t v = (uint16_t)i2c_reg_map[REG_C1_VOLTAGE_L]
                   | ((uint16_t)i2c_reg_map[REG_C1_VOLTAGE_H] << 8);
        int16_t  a = (int16_t)((uint16_t)i2c_reg_map[REG_C1_CURRENT_L]
                             | ((uint16_t)i2c_reg_map[REG_C1_CURRENT_H] << 8));
        uint32_t mw = (uint32_t)v * (uint32_t)(a > 0 ? a : -a) / 1000UL;
        uint8_t  w  = (uint8_t)(mw / 1000UL);
        ui_data.usb_c1_power = (w > 99) ? 99 : w;
    } else {
        ui_data.usb_c1_power = 0;
    }

    /* USB-C2 (协议 §4.4: 0=未连接 1=充电 2=放电) */
    ui_data.usb_c2_status = i2c_reg_map[REG_C2_STATUS];
    if (ui_data.usb_c2_status) {
        uint16_t v = (uint16_t)i2c_reg_map[REG_C2_VOLTAGE_L]
                   | ((uint16_t)i2c_reg_map[REG_C2_VOLTAGE_H] << 8);
        int16_t  a = (int16_t)((uint16_t)i2c_reg_map[REG_C2_CURRENT_L]
                             | ((uint16_t)i2c_reg_map[REG_C2_CURRENT_H] << 8));
        uint32_t mw = (uint32_t)v * (uint32_t)(a > 0 ? a : -a) / 1000UL;
        uint8_t  w  = (uint8_t)(mw / 1000UL);
        ui_data.usb_c2_power = (w > 99) ? 99 : w;
    } else {
        ui_data.usb_c2_power = 0;
    }

    /* USB-A (协议 §4.4: 0=未连接 1=充电 2=放电) */
    ui_data.usb_a_status = i2c_reg_map[REG_USBA_STATUS];
    if (ui_data.usb_a_status) {
        uint16_t v = (uint16_t)i2c_reg_map[REG_USBA_VOLTAGE_L]
                   | ((uint16_t)i2c_reg_map[REG_USBA_VOLTAGE_H] << 8);
        int16_t  a = (int16_t)((uint16_t)i2c_reg_map[REG_USBA_CURRENT_L]
                             | ((uint16_t)i2c_reg_map[REG_USBA_CURRENT_H] << 8));
        uint32_t mw = (uint32_t)v * (uint32_t)(a > 0 ? a : -a) / 1000UL;
        uint8_t  w  = (uint8_t)(mw / 1000UL);
        ui_data.usb_a_power = (w > 99) ? 99 : w;
    } else {
        ui_data.usb_a_power = 0;
    }

    /* 小电流模式 (协议 §4.4 0x4F) */
    ui_data.low_current_flag = i2c_reg_map[REG_SMALL_CURRENT_MODE] ? true : false;

    /* NTC 温度保护状态 (协议 §4.3 0x20)
     * BIT[1:0]=BAT_NTC1, BIT[3:2]=BAT_NTC2, BIT[5:4]=PCB_NTC1, BIT[7:6]=PCB_NTC2
     * 值: 00=正常 01=低温保护 02=高温保护 */
    uint8_t ntc = i2c_reg_map[REG_NTC_STATUS];
    uint8_t over_temp = 0, low_temp = 0;
    for (int i = 0; i < 4; i++) {
        uint8_t st = (ntc >> (i * 2)) & 0x03;
        if (st == 0x02) over_temp = 1;
        if (st == 0x01) low_temp  = 1;
    }
    if (over_temp)
        ui_data.warning = WARNING_OVER_TEMP;
    else if (low_temp)
        ui_data.warning = WARNING_LOW_TEMP;
    else
        ui_data.warning = WARNING_NONE;
}

/* ========================================================================
 * i2c_slave_proc — 主循环调用
 * ======================================================================== */
void i2c_slave_proc(void)
{
    /* 固件版本和在线标志 (协议 §4.8: 0x80-0x83) */
    i2c_reg_map[REG_FW_VERSION_L]   = 0x00;  /* V1.00 */
    i2c_reg_map[REG_FW_VERSION_H]   = 0x01;
    i2c_reg_map[REG_TFT_ONLINE_CRC] = 0x55;

    /* OVP_PERMANENT: 协议 §4.5 密匙 0x5A, CW1573 离线时也可信 */
    i2c_reg_map[REG_OVP_PERMANENT] = 0x5A;

    /* 按键事件原子交换: 影子缓冲 → reg_map, 防止主机清零竞争 (§4.6) */
    i2c_reg_map[REG_KEY_EVENT] = key_event_buf;
    key_event_buf = 0;

    /* CW1573 采集 → reg_map (R) + ui_data */
    pull_sensor_data();

    /* G020 下发数据 (W) → ui_data */
    apply_host_data();
}
