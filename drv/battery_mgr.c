#include "battery_mgr.h"
#include "abnormal_log.h"
#include "rtc_timer.h"
#include "ui.h"

/* ---- IP3561Q 数据引用 (定义在 ip3561q.c) ---- */
extern volatile ip3561q_proc_data_t ip3561q_info;

/* 禁用原因 (仅内部使用) */
#define DISABLE_REASON_OV  1   /* 过压禁用 */
#define DISABLE_REASON_UV  2   /* 欠压禁用 */

/* 禁用检测开关: 1=启用 0=关闭(测试用) */
#define BAT_DISABLE_DETECT_EN  1
/* 电压测试用: 1=启用 0=关闭 */
#define BAT_ENABLE_TEST_EN  0
/* 禁用原因写Flash: 1=启用(持久化, 复位后仍禁用) 0=关闭(测试用, 仅RAM禁用, 复位后恢复) */
#define BAT_DISABLE_WRITE_FLASH_EN  1

/* 功能开关: 1=启用 0=关闭 */
#define BAT_UV_PROT_EN       0   /* 欠压保护 (V<2.72V 跳警示页, 无 Flash 记录) */
#define BAT_LOW_TEMP_EN      0   /* 低温警告 (ntc_status=0x01 跳低温页, 无 Flash 记录) */

/* 温度源选择: 0=双NTC取高者 1=仅用NTC2 */
#define TEMP_NTC2_ONLY  0

/* ==========================================================================
 *  NTC 阻值-温度查找表 (R25=10KΩ±1%, B25/85=3435K±1%)
 *  温度 -20℃ ~ 80℃, 步进 5℃, 阻值取自 10k-NTC-R-T表.md Rnor 列
 *  阻值随温度升高单调递减
 * ========================================================================== */
static const uint32_t ntc_rnom_table[] = {
    69394UL,  /* -20℃ */
    54398UL,  /* -15℃ */
    43000UL,  /* -10℃ */
    34247UL,  /*  -5℃ */
    27513UL,  /*   0℃ */
    22176UL,  /*   5℃ */
    18016UL,  /*  10℃ */
    14724UL,  /*  15℃ */
    12103UL,  /*  20℃ */
    10000UL,  /*  25℃ */
     8315UL,  /*  30℃ */
     6946UL,  /*  35℃ */
     5831UL,  /*  40℃ */
     4918UL,  /*  45℃ */
     4168UL,  /*  50℃ */
     3546UL,  /*  55℃ */
     3030UL,  /*  60℃ */
     2600UL,  /*  65℃ */
     2239UL,  /*  70℃ */
     1935UL,  /*  75℃ */
     1678UL,  /*  80℃ */
};
#define NTC_TABLE_CNT  (sizeof(ntc_rnom_table) / sizeof(ntc_rnom_table[0]))

/* ---- RAM 状态 ---- */
typedef struct {
    uint32_t last_poll_tick;        /* 上次轮询时刻 */
    uint32_t ov_1h_tick[4];         /* 过压保护 1h 计时起点 (0=未计时) */
#if BAT_UV_PROT_EN
    uint8_t  uv_active[4];          /* 欠压保护激活标志 */
    uint8_t  uv_prot_cnt[4];        /* 每节电芯欠压保护持续次数 (>=20 = 持续 1s) */
    uint8_t  uv_recov_cnt[4];       /* 每节电芯欠压恢复持续次数 (>=100 = 持续 5s) */
#endif
    uint32_t last_commit_hour[4];   /* 每节电芯上次提交记录的小时 (hour_start), 同小时去重 */
    uint32_t temp_1h_tick;          /* 温度异常 1h 计时起点 (0=未计时) */
    uint8_t  ov_prot_cnt[4];        /* 每节电芯过压保护持续次数 (>=20 = 持续 1s) */
    uint8_t  uv_seconds[4];         /* 每节电芯欠压禁用持续次数 */
    uint8_t  ov_seconds[4];         /* 每节电芯过压禁用持续次数 */
    uint8_t  ov_recov_cnt[4];       /* 每节电芯过压恢复持续次数 (>=100 = 持续 5s) */
    uint8_t  disabled;              /* 禁用标志 */
    uint8_t  disable_reason;        /* 禁用原因 (DISABLE_REASON_OV / DISABLE_REASON_UV) */
    uint8_t  chg_state;             /* 充放电状态 */
    uint8_t  warning_chg_state;     /* 警告触发时的充放电状态 */
    int16_t  temperature_01c;       /* 电池温度 0.1℃ (TEMP_NTC2_ONLY=1: 仅用 bat_ntc2) */
} battery_mgr_ctx_t;

static battery_mgr_ctx_t g_bat;

#if BAT_ENABLE_TEST_EN
    uint16_t vcell_mv[4]={4200,4200,4300,4300};
#endif
/* ---- 内部函数 ---- */

/* ==========================================================================
 * ntc_resistance_to_temp — NTC 阻值 → 温度 (0.1℃)
 *
 * 使用线性插值查找表, 覆盖 -20℃ ~ 80℃.
 * NTC 物理上为单颗, 接在 IP3561Q (TFT 侧); TFT 经 0x5C 上报主机,
 * 主机再通过 bat_ntc2 回传 (TEMP_NTC2_ONLY=1 时仅用 bat_ntc2).
 * 阻值 = 0 表示尚未收到数据, 保持上次温度.
 * ========================================================================== */
static int16_t ntc_resistance_to_temp(uint32_t r_ohm)
{
    uint8_t i;

    /* 无数据: 保持上次温度 */
    if (r_ohm == 0) {
        return g_bat.temperature_01c;
    }

    /* 超出上限: 阻值太小 → 温度过高, 钳位到 80℃ */
    if (r_ohm <= ntc_rnom_table[NTC_TABLE_CNT - 1]) {
        return (int16_t)(NTC_TEMP_MAX_C * 10);
    }

    /* 超出下限: 阻值太大 → 温度过低, 钳位到 -20℃ */
    if (r_ohm >= ntc_rnom_table[0]) {
        return (int16_t)(NTC_TEMP_MIN_C * 10);
    }

    /* 线性插值: 温度 = T_base + 5℃ * (R_high - R) / (R_high - R_low) */
    for (i = 0; i < (uint8_t)(NTC_TABLE_CNT - 1); i++) {
        if (r_ohm <= ntc_rnom_table[i] && r_ohm > ntc_rnom_table[i + 1]) {
            uint32_t r_high  = ntc_rnom_table[i];
            uint32_t r_low   = ntc_rnom_table[i + 1];
            uint32_t delta_r = r_high - r_low;
            uint32_t r_diff  = r_high - r_ohm;

            /* T_01c = (-20 + i*5)*10 + 50 * r_diff / delta_r */
            int32_t t_01c = (int32_t)(NTC_TEMP_MIN_C * 10)
                          + (int32_t)i * (int32_t)(NTC_TABLE_STEP_C * 10)
                          + (int32_t)((NTC_TABLE_STEP_C * 10) * r_diff / delta_r);
            return (int16_t)t_01c;
        }
    }

    /* 不应到达此处, 安全回退 */
    return g_bat.temperature_01c;
}

/* 判断充放电状态 (基于 USB 端口状态) */
static uint8_t detect_chg_state(void)
{
    /* 任一端口充电 → 充电中 */
    if (ui_data.usb_c1_status == 0x01 ||
        ui_data.usb_c2_status == 0x01 ||
        ui_data.usb_a_status  == 0x01)
        return CHG_STATE_CHARGING;

    /* 任一端口放电 → 放电中 */
    if (ui_data.usb_c1_status == 0x02 ||
        ui_data.usb_c2_status == 0x02 ||
        ui_data.usb_a_status  == 0x02)
        return CHG_STATE_DISCHARGING;

    return CHG_STATE_IDLE;
}

/* 检查 1h 计时是否到期, 到期则提交当前小时异常最差值 */
static void check_hour_commit(void)
{
    uint32_t now = md_get_tick();
    uint32_t hour_ms = 3600000UL;
    uint32_t ts;
    uint8_t i;

    /* 电压: 每节电芯独立 1h 计时 (仅过压保护有 Flash 提交) */
    for (i = 0; i < 4; i++) {
        if (g_bat.ov_1h_tick[i] != 0 && now - g_bat.ov_1h_tick[i] >= hour_ms) {
            ts = rtc_get_timestamp();
            if (ts > 0)
                abnormal_log_voltage_commit(ts);
            g_bat.ov_1h_tick[i] = now;
        }
    }

    if (g_bat.temp_1h_tick != 0 && now - g_bat.temp_1h_tick >= hour_ms) {
        ts = rtc_get_timestamp();
        if (ts > 0)
            abnormal_log_temperature_commit(ts);
        g_bat.temp_1h_tick = now;
    }
}

/* ==========================================================================
 * battery_mgr_jump_to_alert_page — 跳转到告警页面
 *
 * 仅当当前页面为首页或信息页时才跳转, 否则保持当前页.
 * 保存跳转前的页面到 last_page 以便退出告警时恢复.
 * ========================================================================== */
static void battery_mgr_jump_to_alert_page(page_t target_page)
{
    if (ui_data.cur_page == PAGE_DEFAULT ||
        ui_data.cur_page == PAGE_INFO_1 ||
        ui_data.cur_page == PAGE_INFO_2 ||
        ui_data.cur_page == PAGE_INFO_3) {
        ui_data.last_page = ui_data.cur_page;
        ui_data.cur_page  = target_page;
    }
}

/* ==========================================================================
 * battery_mgr_set_disabled — 标记电池永久禁用
 *
 * 由过压/欠压禁用检测触发, 设置 RAM 标志,
 * 可选写 Flash 持久化, 并跳转到全红禁用页.
 * ========================================================================== */
static void battery_mgr_set_disabled(uint8_t reason)
{
    g_bat.disabled       = 1;
    g_bat.disable_reason = reason;

#if BAT_DISABLE_WRITE_FLASH_EN
    factory_cfg_t cfg;
    factory_cfg_read(&cfg);
    cfg.disable_reason = reason;
    factory_cfg_write(&cfg);
#endif

    ui_data.last_page = ui_data.cur_page;
    ui_data.cur_page  = PAGE_DISABLED;
}

/* ==========================================================================
 * battery_mgr_update_temperature — 主机 NTC 阻值 → 本地温度换算
 *
 * TEMP_NTC2_ONLY=0: 双 NTC 模式, bat_ntc1 + bat_ntc2
 *   - 两路都 >0℃ 取最高温, 任一 ≤0℃ 取最低温
 * TEMP_NTC2_ONLY=1: 单 NTC 模式, 仅用 bat_ntc2
 * ========================================================================== */
static void battery_mgr_update_temperature(void)
{
#if !TEMP_NTC2_ONLY
    int16_t  t1, t2;
    uint8_t  v1, v2;

    t1 = 0; t2 = 0;
    v1 = (ui_data.bat_ntc1 != 0);
    v2 = (ui_data.bat_ntc2 != 0);

    if (v1) t1 = ntc_resistance_to_temp(ui_data.bat_ntc1);
    if (v2) t2 = ntc_resistance_to_temp(ui_data.bat_ntc2);

    if (v1 && v2) {
        /* 双路都 >0℃ 取最高温, 任一 ≤0℃ 取最低温 */
        if (t1 > 0 && t2 > 0)
            g_bat.temperature_01c = (t1 > t2) ? t1 : t2;
        else
            g_bat.temperature_01c = (t1 < t2) ? t1 : t2;
    } else if (v1) {
        g_bat.temperature_01c = t1;
    } else if (v2) {
        g_bat.temperature_01c = t2;
    }
    /* else: 双 NTC 均无数据, 保持上次温度 */
#else
    if (ui_data.bat_ntc2 != 0)
        g_bat.temperature_01c = ntc_resistance_to_temp(ui_data.bat_ntc2);
#endif
}

/* ==========================================================================
 * battery_mgr_check_cell_prot — 单节电芯电压保护检测
 *
 * 对单节电芯执行 4 种检测:
 *   4.1 欠压禁用 (V<1.5V 持续5s)  → 永久禁用
 *   4.2 过压禁用 (V>4.6V 持续1s)  → 永久禁用
 *   4.3 过压保护 (V>4.47V 持续1s进入, V<4.40V 持续5s退出) → 跳警示页 + 写Flash异常日志
 *   4.4 欠压保护 (V<2.72V 持续1s进入, V>3.00V 持续5s退出) → 跳警示页 (非充电态, 无日志)
 * ========================================================================== */
static void battery_mgr_check_cell_prot(uint8_t i, uint16_t v, uint32_t ts, uint32_t now)
{
#if BAT_DISABLE_DETECT_EN
    /* ---- 4.1 欠压禁用检测 (V < 1.5V 持续 5s) ---- */
    if (v < BAT_UV_DISABLE_MV && v > 0) {
        g_bat.uv_seconds[i]++;
        if (g_bat.uv_seconds[i] >= BAT_MGR_POLL_CNT(BAT_UV_DISABLE_S)) {
            battery_mgr_set_disabled(DISABLE_REASON_UV);
        }
    } else {
        g_bat.uv_seconds[i] = 0;
    }

    /* ---- 4.2 过压禁用检测 (V > 4.6V 持续 1s) ---- */
    if (v > BAT_OV_DISABLE_MV) {
        g_bat.ov_seconds[i]++;
        if (g_bat.ov_seconds[i] >= BAT_MGR_POLL_CNT(BAT_OV_DISABLE_S)) {
            battery_mgr_set_disabled(DISABLE_REASON_OV);
        }
    } else {
        g_bat.ov_seconds[i] = 0;
    }
#endif /* BAT_DISABLE_DETECT_EN */

    /* ---- 4.3 过压保护 (V > 4.47V 持续 1s 进入, V < 4.40V 持续 5s 退出) ---- */
    if (v > BAT_OV_PROT_MV) {
        g_bat.ov_prot_cnt[i]++;
        g_bat.ov_recov_cnt[i] = 0;
        if (g_bat.ov_prot_cnt[i] >= BAT_MGR_POLL_CNT(BAT_OV_PROT_ENTER_S)) {
            if (ts > 0) {
                /* 首次进入: 强制更新 + 立即写 Flash, 启动 1h 计时 */
                if (g_bat.ov_1h_tick[i] == 0) {
                    abnormal_log_voltage_update_force(ts - (ts % 3600), v, i, g_bat.chg_state);
                    abnormal_log_voltage_commit(ts);
                    g_bat.ov_1h_tick[i] = now;
                } else {
                    /* 持续中: 仅更新 RAM, 保留本小时最差值 */
                    abnormal_log_voltage_update(ts - (ts % 3600), v, i, g_bat.chg_state);
                }
            }
            battery_mgr_jump_to_alert_page(PAGE_SHORT_CIRCUIT);
        }
    } else if (v < BAT_OV_RECOVER_MV) {
        g_bat.ov_prot_cnt[i] = 0;
        if (g_bat.ov_1h_tick[i] != 0) {
            g_bat.ov_recov_cnt[i]++;
            if (g_bat.ov_recov_cnt[i] >= BAT_MGR_POLL_CNT(BAT_OV_RECOVER_S)) {
                g_bat.ov_1h_tick[i] = 0;
                g_bat.ov_recov_cnt[i] = 0;
            }
        }
    } else {
        /* 滞回区间 [4.40V, 4.47V]: 保持当前状态 */
        g_bat.ov_prot_cnt[i] = 0;
    }

#if BAT_UV_PROT_EN
    /* ---- 4.4 欠压保护 (V < 2.72V 持续 1s 进入, V > 3.00V 持续 5s 退出, 仅非充电态, 无日志) ---- */
    if (g_bat.chg_state != CHG_STATE_CHARGING && v < BAT_UV_PROT_MV && v > 0) {
        g_bat.uv_prot_cnt[i]++;
        g_bat.uv_recov_cnt[i] = 0;
        if (g_bat.uv_prot_cnt[i] >= BAT_MGR_POLL_CNT(BAT_UV_PROT_ENTER_S)) {
            g_bat.uv_active[i] = 1;
            battery_mgr_jump_to_alert_page(PAGE_SHORT_CIRCUIT);
        }
    } else if (v > BAT_UV_RECOVER_MV || g_bat.chg_state == CHG_STATE_CHARGING) {
        g_bat.uv_prot_cnt[i] = 0;
        if (g_bat.uv_active[i]) {
            g_bat.uv_recov_cnt[i]++;
            if (g_bat.uv_recov_cnt[i] >= BAT_MGR_POLL_CNT(BAT_UV_RECOVER_S)) {
                g_bat.uv_active[i] = 0;
                g_bat.uv_recov_cnt[i] = 0;
            }
        }
    } else {
        /* 滞回区间 [2.72V, 3.00V]: 保持当前状态 */
        g_bat.uv_prot_cnt[i] = 0;
    }
#endif /* BAT_UV_PROT_EN */
}

/* ==========================================================================
 * battery_mgr_check_temp_warning — 温度保护警告处理
 *
 * 解析主机下发的 ntc_status 寄存器:
 *   BIT[1:0]=NTC1, BIT[3:2]=NTC2, 00=正常 01=低温 02=高温
 *
 * 过温: 跳过温页 + 写Flash异常日志 + 1h 计时
 *   - 首次进入: 立即写 Flash
 *   - 持续中: 每 1h 提交当前小时最差值到 Flash
 *   - 退出: 清 1h 计时, 下次再进入又是首次
 * 低温: 跳低温页 (无日志)
 * ========================================================================== */
static void battery_mgr_check_temp_warning(uint32_t ts, uint32_t now)
{
    uint8_t ntc       = ui_data.ntc_status;
    uint8_t over_temp = 0;
#if BAT_LOW_TEMP_EN
    uint8_t low_temp  = 0;
#endif
    uint8_t i;

    /* 解析 NTC1/2 状态 */
    for (i = 0; i < 2; i++) {
        uint8_t st = (ntc >> (i * 2)) & 0x03;
        if (st == 0x02) over_temp = 1;
#if BAT_LOW_TEMP_EN
        if (st == 0x01) low_temp  = 1;
#endif
    }
    // LOGI("ntc_status = %d bat_ntc1 = %d bat_ntc2 = %d\r\n",
    //      ntc, ui_data.bat_ntc1, ui_data.bat_ntc2);

    if (over_temp) {
        g_bat.warning_chg_state = g_bat.chg_state;
        battery_mgr_jump_to_alert_page(PAGE_OVER_TEMP);

        /* 根据充放电状态确定事件类型 */
        {
            uint8_t evt_type;

            if (g_bat.warning_chg_state == CHG_STATE_CHARGING)
                evt_type = ABNORMAL_EVT_OT_PROT_CHG;
            else if (g_bat.warning_chg_state == CHG_STATE_DISCHARGING)
                evt_type = ABNORMAL_EVT_OT_PROT_DSG;
            else
                evt_type = ABNORMAL_EVT_OT_PROT_IDLE;

            if (ts > 0) {
                /* 更新当前小时最差值 */
                abnormal_log_temperature_update(ts - (ts % 3600),
                                    (uint16_t)g_bat.temperature_01c,
                                    evt_type, g_bat.warning_chg_state);
                /* 首次进入: 立即写 Flash, 启动 1h 计时 */
                if (g_bat.temp_1h_tick == 0) {
                    abnormal_log_temperature_update_force(ts - (ts % 3600),
                                    (uint16_t)g_bat.temperature_01c,
                                    evt_type, g_bat.warning_chg_state);
                    abnormal_log_temperature_commit(ts);
                    g_bat.temp_1h_tick = now;
                }
            }
        }
    }
#if BAT_LOW_TEMP_EN
    else if (low_temp) {
        battery_mgr_jump_to_alert_page(PAGE_LOW_TEMP);
    }
#endif

    /* 退出过温: 清零 1h 计时, 下次再进入又是首次 */
    if (!over_temp && g_bat.temp_1h_tick != 0)
        g_bat.temp_1h_tick = 0;
}

/* ---- 对外函数 ---- */

/* ==========================================================================
 * static_cfg_load_to_ui — 上电时从 Flash 静态配置区读取数据到 ui_data
 *
 * 读取内容:
 *   1. factory_cfg_t → bat_model[4], cell_count, device_sn
 *   2. OV 永久标志 → battery_mgr 内部状态 + I2C 寄存器
 * ========================================================================== */
void static_cfg_load_to_ui(void)
{
    factory_cfg_t cfg;

    factory_cfg_read(&cfg);

    /* magic 正确才复制数据 (上位机已写入) */
    if (cfg.magic != 0x55) 
        return;
    
    memcpy(ui_data.bat_model_1, cfg.bat_model[0], sizeof(ui_data.bat_model_1));
    memcpy(ui_data.bat_model_2, cfg.bat_model[1], sizeof(ui_data.bat_model_2));
    memcpy(ui_data.bat_model_3, cfg.bat_model[2], sizeof(ui_data.bat_model_3));
    memcpy(ui_data.bat_model_4, cfg.bat_model[3], sizeof(ui_data.bat_model_4));
    
    /* 恢复禁用原因 (0=正常 1=OV 2=UV) */
    if (cfg.disable_reason != 0) {
        g_bat.disabled       = 1;
        g_bat.disable_reason = cfg.disable_reason;
        ui_data.cur_page     = PAGE_DISABLED;  /* 开机即全红 */
    }
}

void static_cfg_erasure(void)
{
    flash_page_erase(FLASH_DATA_BASE + FLASH_OFFS_FACTORY_CFG);
    flash_wait_unbusy();

    /* 同时擦除时间戳块, 避免 rtc_timer_init 恢复出旧累计秒数导致时间错乱 */
    flash_page_erase(FLASH_DATA_BASE + FLASH_OFFS_TIMESTAMP_BLOCK0);
    flash_wait_unbusy();
    flash_page_erase(FLASH_DATA_BASE + FLASH_OFFS_TIMESTAMP_BLOCK1);
    flash_wait_unbusy();
    flash_page_erase(FLASH_DATA_BASE + FLASH_OFFS_TIMESTAMP_BLOCK2);
    flash_wait_unbusy();
}

/* 擦除全部异常记录区 (电压 + 温度, 各 7 块 × 256B) */
void abnormal_log_erasure(void)
{
    uint8_t i;

    for (i = 0; i < 7; i++) {
        flash_page_erase(FLASH_DATA_BASE + FLASH_OFFS_ABNORMAL_VOLTAGE
                           + (uint32_t)i * 256);
        flash_wait_unbusy();
    }

    for (i = 0; i < 7; i++) {
        flash_page_erase(FLASH_DATA_BASE + FLASH_OFFS_ABNORMAL_TEMPERATURE
                           + (uint32_t)i * 256);
        flash_wait_unbusy();
    }
}

/*
 * battery_mgr_clear_disable — 场测解锁后清除禁用状态
 */
void battery_mgr_clear_disable(void)
{
    g_bat.disabled       = 0;
    g_bat.disable_reason = 0;
}

void static_cfg_save_test(void)
{
    factory_cfg_t cfg;
    cfg.magic = 0x55;
    cfg.start_timestamp = 1783507680;
    strcpy(cfg.bat_model[0], "DFLKSKLDGSJ");
    strcpy(cfg.bat_model[1], "218399MMGKF");
    strcpy(cfg.bat_model[2], "90494UTJGNG");
    strcpy(cfg.bat_model[3], "PYL905K9MIJ");
    cfg.cell_count = 4;     
    memset(cfg.device_sn, 0, sizeof(cfg.device_sn));
    cfg.disable_reason = 0;
    factory_cfg_write(&cfg);
}

void battery_mgr_init(void)
{
    memset(&g_bat, 0, sizeof(g_bat));

    /* 非零默认值 */
    g_bat.temperature_01c = 0;            /* 0℃ */

    /* 加载静态配置 (factory_cfg + OV 标志) */
    static_cfg_load_to_ui();
}

/* ==========================================================================
 * battery_mgr_proc — 主轮询调度, 50ms 周期 (BAT_MGR_POLL_MS)
 *
 * 将实际处理逻辑分发到各阶段函数:
 *   1. battery_mgr_update_temperature()  — NTC 温度换算
 *   2. detect_chg_state()                — 充放电检测
 *   3. check_hour_commit()               — 小时边界 Flash 提交
 *   4. battery_mgr_check_cell_prot()     — 逐电芯电压保护
 *   5. battery_mgr_check_temp_warning()  — 温度保护警告
 * ========================================================================== */
void battery_mgr_proc(void)
{
    uint32_t now, ts;
    uint8_t  i;

    /* 前置守卫 */
    if (md_get_tick() < 2000)
        return;

    if (!ip3561q_is_ready())
        return;

    now = md_get_tick();
    if (now - g_bat.last_poll_tick < BAT_MGR_POLL_MS)
        return;
    g_bat.last_poll_tick = now;

#if BAT_DISABLE_DETECT_EN
    if (g_bat.disabled)
        return;
#endif

    /* 1. 温度计算 */
    battery_mgr_update_temperature();
    // LOGI("g_bat.temperature_01c = %d\r\n", g_bat.temperature_01c);

    /* 2. 充放电状态 */
    g_bat.chg_state = detect_chg_state();

    /* 3. 小时边界 Flash 提交 */
    check_hour_commit();

    ts = rtc_get_timestamp();

    /* 4. 逐电芯电压保护检测 */
    for (i = 0; i < IP3561Q_CELL_CNT; i++) {
#if BAT_ENABLE_TEST_EN
        uint16_t v = vcell_mv[i];
#else
        uint16_t v = ip3561q_info.vcell_mv[i];
#endif
        battery_mgr_check_cell_prot(i, v, ts, now);
    }

    /* 5. 温度保护警告 */
    battery_mgr_check_temp_warning(ts, now);

}

/* ---- Getter 函数 ---- */

uint16_t battery_mgr_cell_voltage_mv(uint8_t cell_idx)
{
    if (cell_idx >= 4 || !ip3561q_is_ready())
        return 0;
    return ip3561q_info.vcell_mv[cell_idx];
}

uint16_t battery_mgr_pack_voltage_mv(void)
{
    if (!ip3561q_is_ready())
        return 0;
    return ip3561q_info.vbat_mv;
}

int16_t battery_mgr_current_ma(void)
{
    if (!ip3561q_is_ready())
        return 0;
    return ip3561q_info.current_ma;
}

int16_t battery_mgr_temperature_01c(void)
{
    return g_bat.temperature_01c;
}

uint8_t battery_mgr_is_disabled(void)
{
    return g_bat.disabled;
}

uint8_t battery_mgr_get_disable_reason(void)
{
    return g_bat.disable_reason;
}

uint8_t battery_mgr_get_chg_state(void)
{
    return g_bat.chg_state;
}

uint8_t battery_mgr_get_warning_chg_state(void)
{
    return g_bat.warning_chg_state;
}

/* 任意保护标志: OV禁用 / UV禁用 / OV保护 (任一有效返回 1) */
uint8_t battery_mgr_is_any_protection(void)
{
    uint8_t i;

    if (g_bat.disabled)
        return 1;

    for (i = 0; i < 4; i++) {
        if (g_bat.ov_1h_tick[i] != 0
#if BAT_UV_PROT_EN
            || g_bat.uv_active[i]
#endif
            )
            return 1;
    }
    return 0;
}

/* ==========================================================================
 * battery_mgr_sync_to_ui — 将 battery_mgr 状态同步到 ui_data
 * ========================================================================== */
void battery_mgr_sync_to_ui(void)
{
    uint8_t i;
    for (i = 0; i < 4; i++) {
        ui_data.cell_voltage_mv[i] = battery_mgr_cell_voltage_mv(i);
    }
    ui_data.bat_temperature = battery_mgr_temperature_01c();
    ui_data.disable_flag        = battery_mgr_is_disabled();
    ui_data.abnormal_volt_count = abnormal_log_voltage_count();
    ui_data.abnormal_temp_count = abnormal_log_temperature_count();
}
