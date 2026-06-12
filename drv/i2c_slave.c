#include "i2c_slave.h"

/* ---- 寄存器缓冲区 (协议 V1.1 最大地址 0x8F, 共 0x90=144 字节) ---- */
#define I2C_REG_MAP_SIZE  0x90
volatile uint8_t i2c_reg_map[I2C_REG_MAP_SIZE];

/* ---- 按键事件影子缓冲 (协议 §4.6) ---- */
volatile uint8_t key_event_buf;

/* ---- ISR 内部状态 ---- */
static volatile uint8_t  i2c_reg_addr;
static volatile uint8_t  i2c_first_byte;  /* 1 = 下一个接收字节是寄存器地址 */

static volatile uint8_t  icr_expect_len;  /* 期望的数据长度 (来自 LEN 字节) */
static volatile uint8_t  icr_byte_cnt;    /* 当前已发/已收的字节计数 */
static volatile uint8_t  icr_data_sum;    /* 数据字节累加和 (CRC 中间值) */

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

/* ---- 寄存器读写封装 (减少 Flash 占用) ---- */

static uint16_t reg_read_u16(uint8_t addr_l)
{
    return (uint16_t)i2c_reg_map[addr_l]
         | ((uint16_t)i2c_reg_map[addr_l + 1] << 8);
}

static int16_t reg_read_s16(uint8_t addr_l)
{
    return (int16_t)reg_read_u16(addr_l);
}

static uint32_t reg_read_u32(uint8_t addr_0)
{
    return (uint32_t)i2c_reg_map[addr_0]
         | ((uint32_t)i2c_reg_map[addr_0 + 1] << 8)
         | ((uint32_t)i2c_reg_map[addr_0 + 2] << 16)
         | ((uint32_t)i2c_reg_map[addr_0 + 3] << 24);
}

static void reg_write_u16(uint8_t addr_l, uint16_t val)
{
    i2c_reg_map[addr_l]     = (uint8_t)(val & 0xFF);
    i2c_reg_map[addr_l + 1] = (uint8_t)(val >> 8);
}

static void reg_write_u32(uint8_t addr_0, uint32_t val)
{
    i2c_reg_map[addr_0]     = (uint8_t)(val & 0xFF);
    i2c_reg_map[addr_0 + 1] = (uint8_t)((val >> 8) & 0xFF);
    i2c_reg_map[addr_0 + 2] = (uint8_t)((val >> 16) & 0xFF);
    i2c_reg_map[addr_0 + 3] = (uint8_t)((val >> 24) & 0xFF);
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
    i2c_init.clk_speed    = 400000;            /* 100kHz standard mode */
    i2c_init.dual_addr    = MD_I2C_DUALADDR_DISABLE;
    i2c_init.duty         = MD_I2C_DUTYCYCLE_16_9;
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

    /* --- 初始化寄存器默认值 --- */
    i2c_reg_map[REG_FW_VERSION_L]    = 0x00;  /* V1.00, 由 proc 填充 */
    i2c_reg_map[REG_FW_VERSION_H]    = 0x01;
    i2c_reg_map[REG_TFT_ONLINE_CRC]  = 0x55;  /* 从机就绪标志 */
    i2c_reg_map[REG_UPDATE_CRC]      = 0x00;  /* 默认非升级模式 */
}

/* ========================================================================
 * tft_calc_crc — CRC 校验 (累加和取反)
 *
 * 对 DATA[0..LEN-1] 的累加和取低字节按位取反
 * ISR 中通过 icr_data_sum 增量累加, 本函数仅做最终取反
 * ======================================================================== */
static uint8_t tft_calc_crc_final(uint8_t sum)
{
    return ~sum;
}

/* ========================================================================
 * I2C1_Handler — I2C1 中断服务函数
 *
 * 状态流转:
 *   ADDR 匹配 → 根据方向设置 first_byte / 复位字节计数
 *   WRITE: REG_ADDR → LEN → DATA[0..LEN-1] → CRC 校验
 *   READ:  写阶段收 REG_ADDR+LEN, 读阶段发 DATA[0..LEN-1]+CRC
 *   STOP/AF → 重置全部状态
 * ======================================================================== */
void I2C1_Handler(void)
{
    volatile uint8_t tmp;

    /* --- TXBE: 发送缓冲区空 (主机读方向, 从机发送) --- */
    if (md_i2c_is_active_flag_txbe(I2C1) == 1 && md_i2c_is_enable_it_buf(I2C1)
        && md_i2c_is_enable_it_evt(I2C1))
    {
        if (icr_byte_cnt < icr_expect_len)
        {
            /* 发送数据字节 */
            uint8_t data_byte;
            if (i2c_reg_addr < I2C_REG_MAP_SIZE)
                data_byte = i2c_reg_map[i2c_reg_addr];
            else
                data_byte = 0x00;  /* 越界返回 0 */

            md_i2c_transmit_data8(I2C1, data_byte);
            icr_data_sum += data_byte;  /* 累加 CRC */

            i2c_reg_addr++;
            if (i2c_reg_addr >= I2C_REG_MAP_SIZE)
                i2c_reg_addr = 0;

            icr_byte_cnt++;
        }
        else
        {
            /* 发送 CRC 字节 */
            uint8_t crc_value = tft_calc_crc_final(icr_data_sum);
            md_i2c_transmit_data8(I2C1, crc_value);

            icr_byte_cnt = 0;
        }
    }

    /* --- RXNE: 接收缓冲区非空 (主机写方向, 从机接收) --- */
    if (md_i2c_is_active_flag_rxne(I2C1) == 1 && md_i2c_is_enable_it_buf(I2C1)
        && md_i2c_is_enable_it_evt(I2C1))
    {
        tmp = md_i2c_receive_data8(I2C1);

        if (i2c_first_byte)
        {
            /* 第 1 字节 = 寄存器地址 */
            i2c_reg_addr   = tmp;
            i2c_first_byte = 0;
            icr_byte_cnt   = 0;
            icr_data_sum   = 0;
        }
        else if (icr_byte_cnt == 0)
        {
            /* 第 2 字节 = 数据长度 LEN */
            icr_expect_len = tmp;
            icr_byte_cnt   = 1;
        }
        else if (icr_byte_cnt <= icr_expect_len)
        {
            /* 第 3..N 字节 = DATA[0..LEN-1] */
            if (i2c_reg_addr < I2C_REG_MAP_SIZE && reg_is_writable(i2c_reg_addr))
            {
                i2c_reg_map[i2c_reg_addr] = tmp;
            }
            icr_data_sum += tmp;  /* 累加 CRC (无论是否写入均参与校验) */

            i2c_reg_addr++;
            if (i2c_reg_addr >= I2C_REG_MAP_SIZE)
                i2c_reg_addr = 0;

            icr_byte_cnt++;
        }
        else
        {
            /* 最后一字节 = CRC: 校验失败则丢弃整包 */
            uint8_t calc = tft_calc_crc_final(icr_data_sum);
            if (calc != tmp)
            {
                /* CRC 失败, 重置状态丢弃该包, 等待下一帧 */
                i2c_first_byte = 0;
            }
        }
    }

    /* --- ADDR: 地址匹配 --- */
    if (md_i2c_is_active_flag_addr(I2C1) && md_i2c_is_enable_it_evt(I2C1))
    {
        i2c_clear_flag_addr(I2C1);
        md_i2c_enable_it_buf(I2C1);

        if (md_i2c_get_transfer_direction(I2C1) == I2C_DIR_READ)
        {
            /* TRF=0: 从机接收 → 主机写, 下一字节是寄存器地址 */
            i2c_first_byte = 1;
        }
        else
        {
            /* TRF=1: 从机发送 → 主机读 */
            i2c_first_byte = 0;
            icr_byte_cnt   = 0;
            icr_data_sum   = 0;
        }
    }

    /* --- AF: ACK 失败 (主机读结束, 发了 NACK) --- */
    if (md_i2c_is_active_flag_af(I2C1) && md_i2c_is_enable_it_err(I2C1))
    {
        md_i2c_clear_flag_af(I2C1);
        md_i2c_disable_it_buf(I2C1);
        i2c_first_byte  = 0;
        i2c_reg_addr    = 0;
        icr_expect_len  = 0;
        icr_byte_cnt    = 0;
        icr_data_sum    = 0;
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

        i2c_first_byte  = 0;
        i2c_reg_addr    = 0;
        icr_expect_len  = 0;
        icr_byte_cnt    = 0;
        icr_data_sum    = 0;
    }

    /* --- BERR: 总线错误, 需要复位 I2C 模块恢复 --- */
    if (md_i2c_is_active_flag_berr(I2C1) && md_i2c_is_enable_it_err(I2C1))
    {
        md_i2c_clear_flag_berr(I2C1);

    }

    /* --- ARLO: 仲裁丢失 (从机模式下罕见, 清标志即可) --- */
    if (md_i2c_is_active_flag_arlo(I2C1) && md_i2c_is_enable_it_err(I2C1))
    {
        md_i2c_clear_flag_arlo(I2C1);
    }

    /* --- OVR: 溢出 (数据丢失, 清标志) --- */
    if (md_i2c_is_active_flag_ovr(I2C1) && md_i2c_is_enable_it_err(I2C1))
    {
        md_i2c_clear_flag_ovr(I2C1);
    }

    /* --- SMBALERT: SMBus 报警 --- */
    if (md_i2c_is_active_smbus_flag_alert(I2C1) && md_i2c_is_enable_it_err(I2C1))
    {
        i2c_clear_smbus_flag_alert(I2C1);
    }

    /* --- SMBTO: SMBus 超时 --- */
    if (md_i2c_is_active_smbus_flag_timeout(I2C1) && md_i2c_is_enable_it_err(I2C1))
    {
        md_i2c_clear_smbus_flag_timeout(I2C1);
    }

    /* --- PECERR: PEC 校验错 --- */
    if (md_i2c_is_active_smbus_flag_pecerr(I2C1) && md_i2c_is_enable_it_err(I2C1))
    {
        md_i2c_clear_smbus_flag_pecerr(I2C1);
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
    /* CW1573 未就绪: 不覆盖 ui_data 已有值 (可能来自主机或初始值) */
    if (!cw1573_is_ready())
        return;

    cw1573_calc_data((cw1573_data_t *)&cw1573_raw, (cw1573_proc_data_t *)&cw1573_info);

    /* V1~V4: 电芯电压 (mV), 协议 §4.5 */
    for (int i = 0; i < cw1573_cell_cnt; i++) {
        uint16_t v = cw1573_info.vcell_mv[i];
        reg_write_u16(REG_V1_L + i * 2, v);
    }

    /* VPACK: 电池组总电压 (mV), 协议 §4.5 (4 串)
       直接使用 cw1573_calc_data 已计算的 pack_mv，无需重复累加 */
    {
        uint16_t vp = cw1573_info.pack_mv;
        reg_write_u16(REG_VPACK_L, vp);
        ui_data.bat_voltage = vp;
    }

    /* BAT_CURRENT: 电池电流 (mA, 正=充电), 协议 §4.5 */
    int16_t cur = (int16_t)cw1573_info.current_ma;
    reg_write_u16(REG_BAT_CURRENT_L, (uint16_t)cur);
    ui_data.bat_current = cw1573_info.current_ma;

    /* NTC1: 温度电阻值 (Ω), 协议 §4.2
       直接使用 cw1573_calc_data 已计算的 rntc_ohm，无需重复计算 */
    {
        uint32_t rntc = cw1573_info.rntc_ohm;
        reg_write_u32(REG_NTC1_0, rntc);
    }
    //TODO :温度如何计算
    ui_data.bat_temperature = 0; /* 温度由主机通过 NTC 阻值自行计算 */
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
    ui_data.bat_cycle_cnt = reg_read_u16(REG_CYCLE_L);
    ui_data.charge_remain_time    = reg_read_u32(REG_CHARGE_REMAIN_0);
    ui_data.discharge_remain_time = reg_read_u32(REG_DISCHARGE_REMAIN_0);
    ui_data.res_vbat       = reg_read_u16(REG_RES_VBAT_L);

    /* ---- NTC 数据 (协议 §4.3) ---- */
    ui_data.ntc_status = i2c_reg_map[REG_NTC_STATUS];
    ui_data.bat_ntc1   = reg_read_u32(REG_BAT_NTC1_0);
    ui_data.bat_ntc2   = reg_read_u32(REG_BAT_NTC2_0);
    ui_data.pcb_ntc1   = reg_read_u32(REG_PCB_NTC1_0);
    ui_data.pcb_ntc2   = reg_read_u32(REG_PCB_NTC2_0);

    /* NTC 温度保护警告 (协议 §4.3 0x20)
     * 仅判断 BAT_NTC1/2: BIT[1:0]=BAT_NTC1, BIT[3:2]=BAT_NTC2
     * 值: 00=正常 01=低温保护 02=高温保护 */
    uint8_t ntc = ui_data.ntc_status;
    uint8_t over_temp = 0, low_temp = 0;
    for (int i = 0; i < 2; i++) {
        uint8_t st = (ntc >> (i * 2)) & 0x03;
        if (st == 0x02) over_temp = 1;
        if (st == 0x01) low_temp  = 1;
    }
    //TODO ：这样写是否有问题
    if (over_temp)
        ui_data.warning = WARNING_OVER_TEMP;
    else if (low_temp)
        ui_data.warning = WARNING_LOW_TEMP;
    else
        ui_data.warning = WARNING_NONE;

    /* ---- 端口数据 (协议 §4.4) ---- */

    /* USB-C1 (协议 §4.4: 0=未连接 1=充电 2=放电) */
    ui_data.usb_c1_status = i2c_reg_map[REG_C1_STATUS];
    if (ui_data.usb_c1_status) {
        uint16_t v = reg_read_u16(REG_C1_VOLTAGE_L);
        int16_t  a = reg_read_s16(REG_C1_CURRENT_L);
        uint32_t mw = (uint32_t)v * (uint32_t)(a > 0 ? a : -a) / 1000UL;
        uint8_t  w  = (uint8_t)(mw / 1000UL);
        ui_data.usb_c1_power = (w > 99) ? 99 : w;
    } else {
        ui_data.usb_c1_power = 0;
    }

    /* USB-C2 (协议 §4.4: 0=未连接 1=充电 2=放电) */
    ui_data.usb_c2_status = i2c_reg_map[REG_C2_STATUS];
    if (ui_data.usb_c2_status) {
        uint16_t v = reg_read_u16(REG_C2_VOLTAGE_L);
        int16_t  a = reg_read_s16(REG_C2_CURRENT_L);
        uint32_t mw = (uint32_t)v * (uint32_t)(a > 0 ? a : -a) / 1000UL;
        uint8_t  w  = (uint8_t)(mw / 1000UL);
        ui_data.usb_c2_power = (w > 99) ? 99 : w;
    } else {
        ui_data.usb_c2_power = 0;
    }

    /* USB-A (协议 §4.4: 0=未连接 1=充电 2=放电) */
    ui_data.usb_a_status = i2c_reg_map[REG_USBA_STATUS];
    if (ui_data.usb_a_status) {
        uint16_t v = reg_read_u16(REG_USBA_VOLTAGE_L);
        int16_t  a = reg_read_s16(REG_USBA_CURRENT_L);
        uint32_t mw = (uint32_t)v * (uint32_t)(a > 0 ? a : -a) / 1000UL;
        uint8_t  w  = (uint8_t)(mw / 1000UL);
        ui_data.usb_a_power = (w > 99) ? 99 : w;
    } else {
        ui_data.usb_a_power = 0;
    }

    /* 小电流模式 (协议 §4.4 0x4F) */
    ui_data.low_current_flag = i2c_reg_map[REG_SMALL_CURRENT_MODE] ? true : false;

    /* 充放电状态: 根据主机下发的端口状态判断 (§4.4)
       任一端口为 0x01(充电中) 即认为电池在充电 */
    ui_data.is_charge = (ui_data.usb_c1_status == 0x01)
                     || (ui_data.usb_c2_status == 0x01)
                     || (ui_data.usb_a_status  == 0x01);

    /* 充电时自动关闭小电流模式 */
    if (ui_data.is_charge)
        ui_data.low_current_flag = false;
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
