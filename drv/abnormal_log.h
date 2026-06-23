#ifndef __ABNORMAL_LOG_H
#define __ABNORMAL_LOG_H

#include "global_define.h"
#include "rtc_timer.h"   /* Flash 地址宏定义 */

/* ---- 异常类型枚举 ---- */
typedef enum {
    ABNORMAL_EVT_NONE            = 0,   /* 无异常 */
    ABNORMAL_EVT_OV_PROT         = 1,   /* 电芯过压保护 (V > Uup) */
    ABNORMAL_EVT_OT_PROT_CHG     = 2,   /* 充电 NTC 高温保护 */
    ABNORMAL_EVT_OT_PROT_DSG     = 3,   /* 放电 NTC 高温保护 */
    ABNORMAL_EVT_OT_PROT_IDLE    = 4,   /* 静置 NTC 高温保护 */
    ABNORMAL_EVT_UT_PROT_CHG     = 5,   /* 充电 NTC 低温保护 */
    ABNORMAL_EVT_UT_PROT_DSG     = 6,   /* 放电 NTC 低温保护 */
    ABNORMAL_EVT_UT_PROT_IDLE    = 7,   /* 静置 NTC 低温保护 */
} abnormal_event_type_t;

/* ---- 充放电状态枚举 ---- */
typedef enum {
    CHG_STATE_IDLE        = 0,   /* 静置 */
    CHG_STATE_CHARGING    = 1,   /* 充电 */
    CHG_STATE_DISCHARGING = 2,   /* 放电 */
} chg_state_t;

/* ---- 固定区异常记录 (16B) ---- */
/* #pragma pack(1): timestamp 在偏移 1、value 在偏移 5, 均非对齐.
   必须整体按字节访问 (经 buf[16] + memcpy 进出 Flash); 切勿对成员取址做强转
   (如 *(uint32_t*)&rec.timestamp) —— Cortex-M0 无非对齐访问支持会触发 HardFault.
   abnormal_log.c 已统一用 buf[RECORD_SIZE] + memcpy 处理. */
#pragma pack(1)
typedef struct {
    uint8_t  magic;         /* 0x5A 表示有效记录 */
    uint32_t timestamp;     /* 发生时间 Unix 时间戳 */
    uint16_t value;         /* 异常值 (mV 或 0.1℃) */
    uint8_t  type;          /* abnormal_event_type_t */
    uint8_t  cell;          /* 电芯编号 (0~3), 过温=0xFF */
    uint8_t  chg_state;     /* chg_state_t */
    uint8_t  reserved[6];   /* 对齐到 16B */
} abnormal_record_t;
#pragma pack()

/* ---- 外部接口 ---- */
void abnormal_log_init(void);
#if FACTORY_RESET_EN
void abnormal_log_reset(void);  /* V1.3: 恢复出厂设置 — 擦除全部异常记录 Flash 区并复位 RAM */
#endif

/* 电压异常: 更新当前提交窗口最差值(约1h, 自上次 commit 起) (仅 RAM) */
void abnormal_log_voltage_update(uint32_t hour_start, uint16_t value_mv, uint8_t cell, uint8_t chg_state);

/* 电压异常: 提交到 Flash, 满 100 条返回 0 */
uint8_t abnormal_log_voltage_commit(uint32_t timestamp);

/* 电压异常: 读第 index 条 (0=最新), 越界返回 1 */
uint8_t abnormal_log_voltage_read(uint8_t index, abnormal_record_t *out);

/* 电压异常: 总条数 */
uint8_t abnormal_log_voltage_count(void);

/* 温度异常: 更新当前提交窗口最差值(约1h, 自上次 commit 起) (仅 RAM) */
void abnormal_log_temperature_update(uint32_t hour_start, uint16_t value_01c, uint8_t type, uint8_t chg_state);

/* 温度异常: 强制更新当前提交窗口最差值(约1h, 自上次 commit 起) (仅 RAM) */
void abnormal_log_temperature_update_force(uint32_t hour_start, uint16_t value_01c, uint8_t type, uint8_t chg_state);

/* 温度异常: 提交到 Flash, 满 100 条返回 0 */
uint8_t abnormal_log_temperature_commit(uint32_t timestamp);

/* 温度异常: 读第 index 条 (0=最新), 越界返回 1 */
uint8_t abnormal_log_temperature_read(uint8_t index, abnormal_record_t *out);

/* 温度异常: 总条数 */
uint8_t abnormal_log_temperature_count(void);

#endif /* __ABNORMAL_LOG_H__ */
