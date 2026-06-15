#ifndef __BATTERY_MGR_H
#define __BATTERY_MGR_H

#include "global_define.h"

/* ==========================================================================
 *  NTC 热敏电阻参数 (MF52-104F3950FA, R25=100KΩ, B25/50=3950K)
 *  阻值由主机 (020) 通过 I2C 下发, TFT 侧本地换算温度
 * ========================================================================== */
#define NTC_TEMP_MIN_C      (-20)   /* 温度下限 ℃ */
#define NTC_TEMP_MAX_C       80     /* 温度上限 ℃ */
#define NTC_TABLE_STEP_C     5      /* 查找表步进 ℃ */

/* ---- 过压/欠压检测阈值 (TFT 本地判断, 基于 CW1573 电芯电压) ---- */
#define BAT_OV_PROT_MV      4500U   /* 过压保护记录阈值 mV */
#define BAT_OV_DISABLE_MV   4600U   /* 过压禁用阈值 mV */
#define BAT_UV_DISABLE_MV   1500U   /* 欠压禁用阈值 mV */
#define BAT_OV_DISABLE_S    1U      /* 过压禁用持续秒数 */
#define BAT_UV_DISABLE_S    5U      /* 欠压禁用持续秒数 */

/* ---- 检测轮询周期 ---- */
#define BAT_MGR_POLL_MS     500U    /* 500ms 轮询一次 */

/* ---- 对外接口 ---- */
void battery_mgr_init(void);
void battery_mgr_proc(void);

/* 查询函数 (无回调, 被动读取) */
uint16_t battery_mgr_cell_voltage_mv(uint8_t cell_idx);   /* 电芯电压 mV */
uint16_t battery_mgr_pack_voltage_mv(void);               /* 总电压 mV */
int16_t  battery_mgr_current_ma(void);                    /* 电流 mA */
int16_t  battery_mgr_temperature_01c(void);               /* 温度 0.1℃ (由主机 NTC 阻值换算) */

uint8_t  battery_mgr_is_disabled(void);                   /* 是否已禁用 (OV/UV) */
uint8_t  battery_mgr_get_disable_reason(void);            /* 禁用原因 1=OV 2=UV */
uint8_t  battery_mgr_get_warning(void);                   /* 当前警告类型 (主机 ntc_status) */
uint8_t  battery_mgr_get_chg_state(void);                 /* 当前充放电状态 */

void battery_mgr_sync_to_ui(void);                         /* 同步 battery_mgr → ui_data */
void static_cfg_load_to_ui(void);                          /* 上电读静态配置区 → ui_data */

#endif /* __BATTERY_MGR_H */
