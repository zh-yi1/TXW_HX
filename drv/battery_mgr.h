#ifndef __BATTERY_MGR_H
#define __BATTERY_MGR_H

#include "global_define.h"

/* ==========================================================================
 *  NTC 热敏电阻参数 (R25=10KΩ±1%, B25/85=3435K±1%)
 *  使用本地阻值
 * ========================================================================== */
#define NTC_TEMP_MIN_C      (-20)   /* 温度下限 ℃ */
#define NTC_TEMP_MAX_C       80     /* 温度上限 ℃ */
#define NTC_TABLE_STEP_C     5      /* 查找表步进 ℃ */

/* ---- 过压/欠压检测阈值 (TFT 本地判断, 基于 IP3561Q 电芯电压) ---- */
#define BAT_OV_PROT_MV      4540U   /* 过压保护记录阈值 mV */
#define BAT_OV_RECOVER_MV   4200U   /* 过压保护恢复阈值 mV (滞回) */
#define BAT_OV_DISABLE_MV   4600U   /* 过压禁用阈值 mV */
#define BAT_UV_DISABLE_MV   1500U   /* 欠压禁用阈值 mV */
#define BAT_OV_PROT_ENTER_S 1U      /* 过压保护进入持续秒数 */
#define BAT_OV_RECOVER_S    5U      /* 过压保护恢复持续秒数 */
#define BAT_OV_DISABLE_S    1U      /* 过压禁用持续秒数 */
#define BAT_UV_DISABLE_S    5U      /* 欠压禁用持续秒数 */

/* 欠压保护 (非充电状态) */
#define BAT_UV_PROT_MV      2720U   /* 欠压保护记录阈值 mV */
#define BAT_UV_RECOVER_MV   3000U   /* 欠压保护恢复阈值 mV (滞回) */
#define BAT_UV_PROT_ENTER_S 1U      /* 欠压保护进入持续秒数 */
#define BAT_UV_RECOVER_S    5U      /* 欠压保护恢复持续秒数 */

/* ---- 检测轮询周期 ---- */
#define BAT_MGR_POLL_MS     50U     /* 50ms 轮询一次 */

/* 秒数 → 轮询次数 */
#define BAT_MGR_POLL_CNT(s)  ((uint16_t)((s) * 1000U / BAT_MGR_POLL_MS))

/* ---- 对外接口 ---- */
void battery_mgr_init(void);
void battery_mgr_proc(void);
void static_cfg_erasure(void);
void abnormal_log_erasure(void);
void static_cfg_save_test(void);
void battery_mgr_clear_disable(void);     /* 场测解锁后清除禁用状态 */

/* 查询函数 (无回调, 被动读取) */
uint16_t battery_mgr_cell_voltage_mv(uint8_t cell_idx);   /* 电芯电压 mV */
uint16_t battery_mgr_pack_voltage_mv(void);               /* 总电压 mV */
int16_t  battery_mgr_current_ma(void);                    /* 电流 mA */
int16_t  battery_mgr_temperature_01c(void);               /* 温度 0.1℃ (由主机 NTC 阻值换算) */

uint8_t  battery_mgr_is_disabled(void);                   /* 是否已禁用 (OV/UV) */
uint8_t  battery_mgr_get_disable_reason(void);            /* 禁用原因 1=OV 2=UV */
uint8_t  battery_mgr_get_chg_state(void);                 /* 当前充放电状态 */
uint8_t  battery_mgr_get_warning_chg_state(void);         /* 警告触发时的充放电状态 */
uint8_t  battery_mgr_is_any_protection(void);             /* 任意保护标志: OV禁用/UV禁用/OV保护 */

void battery_mgr_sync_to_ui(void);                         /* 同步 battery_mgr → ui_data */
void static_cfg_load_to_ui(void);                          /* 上电读静态配置区 → ui_data */

/* V1.3: 剩余充满时间估算 (分钟), 未准备好返回 -1 (不显示)。
   内部按 1s 采样电流, 需被主循环持续调用以维持环形缓冲 */
int16_t  calc_charge_remain_min(void);

#endif /* __BATTERY_MGR_H */
