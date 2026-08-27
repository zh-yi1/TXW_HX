#ifndef __RTC_TIMER_H
#define __RTC_TIMER_H

#include "global_define.h"

/*
 * ============================================================================
 *  外部 SPI Flash (P25Q64SH, 4MB) 数据区布局规划
 * ============================================================================
 *
 *  ┌─────────────────────────────────┐ 0x000000
 *  │  图片资源 (~2.4MB)               │
 *  │  Sector 0 ~ 589                 │
 *  ├─────────────────────────────────┤ ~0x24DFFF
 *  │  预留 (图片扩展)                  │
 *  │                                │
 *  │       ... 中部空闲 ~1.4MB ...     │
 *  │                                │
 *  ├═════════════════════════════════┤ 0x3E0000  ← FLASH_DATA_BASE (末段 128K)
 *  │                                │
 *  │  ■ 静态配置区 (256B)             │ +0x0000
 *  │    factory_cfg_t                │
 *  │    magic 1B (0x55=已写入)        │
 *  │    起始时间戳 4B                 │
 *  │    运行起始时间 4B               │
 *  │    电芯型号 4×19B               │
 *  │    电芯数量 1B                  │
 *  │    设备序列号 32B                │
 *  │    禁用原因 1B                   │
 *  │    SOH 1B                       │
 *  │    循环次数 2B                   │
 *  │    SOC 1B                       │
 *  │    CRC8 1B                      │
 *  │    生产时串口写入, 永不擦除       │
 *  │                                │
 *  ├─────────────────────────────────┤ +0x0100
 *  │  ■ 时间戳块0 (256B)             │
 *  │    条目 7B, 最多 36 条           │
 *  │    顺序追加, 写满擦除换块         │
 *  ├─────────────────────────────────┤ +0x0200
 *  │  ■ 时间戳块1 (256B)             │
 *  ├─────────────────────────────────┤ +0x0300
 *  │  ■ 时间戳块2 (256B)             │
 *  ├─────────────────────────────────┤ +0x0400  ← FLASH_OFFS_IP3561Q_OC_CFG
 *  │  ■ IP3561Q OC 阈值备份 (256B)    │
 *  │    DOC1/DOC2/SC/COC + CRC8      │
 *  │                                │
 *  │  ... 预留 ...                   │
 *  │                                │
 *  ├─────────────────────────────────┤ +0x3000  ← FLASH_OFFS_ABNORMAL_VOLTAGE
 *  │  ■ 电压异常固定区 (7 × 256B)     │
 *  │    每条 16B, 每块 16 条          │
 *  │    共 112 条, 限存 100 条        │
 *  │    存满即停, 不覆盖               │
 *  ├─────────────────────────────────┤ +0x3700  ← FLASH_OFFS_ABNORMAL_TEMPERATURE
 *  │  ■ 温度异常固定区 (7 × 256B)     │
 *  │    每条 16B, 每块 16 条          │
 *  │    共 112 条, 限存 100 条        │
 *  │    存满即停, 不覆盖               │
 *  │                                │
 *  │  ... 释放的 ~112KB (可后续扩展)    │
 *  │                                │
 *  └─────────────────────────────────┘ 0x400000  (Flash 末尾)
 *
 *  数据区容量: 128 KB (0x3E0000 ~ 0x400000)
 *
 *  擦除粒度: 256B (Flash 页/子扇区)
 *  写入策略: 全部追加写, 不读-改-写
 *  磨损均衡: 时间戳区 3 块轮转
 *
 * ============================================================================
 */

/* ---- Flash 数据区基地址（偏移宏，可后续调整）---- */
#define FLASH_DATA_BASE              0x3E0000UL    /* 4MB Flash 末段 128K 起点 */

/* ---- 静态配置区 (256B) ---- */
#define FLASH_OFFS_FACTORY_CFG       (0x0000)      /* 相对基地址偏移 0, factory_cfg_t 占用 124B */

/* ---- 时间戳存储区 (256B × N) ---- */
#define FLASH_OFFS_TIMESTAMP_BLOCK0  (0x0100)      /* 时间戳块 0 */
#define FLASH_OFFS_TIMESTAMP_BLOCK1  (0x0200)      /* 时间戳块 1 */
#define FLASH_OFFS_TIMESTAMP_BLOCK2  (0x0300)      /* 时间戳块 2 */

/* ---- BMS OC (过流保护) 初始值 ---- */
#define FLASH_OFFS_IP3561Q_OC_CFG      (0x0400)      /* IP3561Q 过流保护阈值备份 (256B) */

/* ---- 异常记录区 ---- */
#define FLASH_OFFS_ABNORMAL_VOLTAGE     (0x3000)      /* 电压异常固定区 */
#define FLASH_OFFS_ABNORMAL_TEMPERATURE (0x3700)      /* 温度异常固定区 */

/* ---- 时间戳块内条目格式 (7B) ---- */
#pragma pack(1)
typedef struct {
    uint8_t  magic_h;           /* 0xAA */
    uint8_t  magic_l;           /* 0x55 */
    uint32_t running_seconds;   /* 从起始时间累计运行秒数 */
    uint8_t  crc8;              /* 前 6B 的 CRC-8 */
} timestamp_entry_t;
#pragma pack()

/* ---- 生产静态配置 (存于 Flash, 生产时串口写入) ---- */
#pragma pack(1)
typedef struct {
    uint8_t  magic;                 /* 0x55 = 上位机已写入, 首字节便于快速判读 */
    uint32_t start_timestamp;       /* 起始 Unix 时间戳 (RTC 绝对时间纪元) */
    uint32_t dis_start_ts;   /* 显示的运行时间起始点 (首次使用=start_timestamp, 充电完成/场测同步时更新) */
    char     bat_model[4][19];      /* 4 节电芯型号 ASCII (18 位 + \0) */
    uint8_t  cell_count;            /* 电芯数量 */
    char     device_sn[34];          /* 设备序列号 (33位 ASCII + null) */
    uint8_t  disable_reason;        /* 禁用原因: 0=正常 1=过压 2=欠压 (持久化) */
    uint8_t  soh;                   /* 电池健康度 SOH (%) */
    uint16_t cycle_count;           /* 真实循环次数 CYCLE_A (掉电保存) */
    uint8_t  soc;                   /* 电池电量 SOC (%, 掉电保存, 进休眠前写) */
    uint8_t  crc8;                  /* 覆盖 magic ~ soc 的 CRC-8 */
} factory_cfg_t;                    /* 共 126B */
#pragma pack()

/* ---- 外部接口 ---- */
void rtc_timer_init(void);
void rtc_timer_reinit(void);               /* 生产配置写入后重新初始化 */
void rtc_timer_proc(void);
uint32_t rtc_get_timestamp(void);          /* 返回当前 Unix 时间戳，未同步返回 0 */
void rtc_save_checkpoint(void);            /* 强制保存时间戳存盘点 */
uint8_t rtc_timer_afe_update(void);        /* 用 AFE 实时计时器推进时间, 0=成功 */
void rtc_timer_compensate_stop(uint32_t seconds); /* STOP唤醒后按名义时长补偿 (AFE 读失败时的回退) */
uint8_t rtc_is_synced(void);               /* 是否已时间同步 */
void rtc_reset_running_time_on_event(void);/* 充电完成/场测同步时复位运行时间起始点 */
uint32_t rtc_get_dis_seconds(void);       /* 获取运行时间 (秒) */

/* ---- 生产配置读写 ---- */
void     factory_cfg_read(factory_cfg_t *cfg);
void     factory_cfg_write(const factory_cfg_t *cfg);
uint8_t  factory_cfg_is_valid(const factory_cfg_t *cfg);  /* magic==0x55 && CRC8 正确 */
void     factory_cfg_write_bat(uint8_t soc, uint8_t soh, uint16_t cycle); /* 读-改-写 SOC+SOH+循环 */
void     factory_cfg_write_soc(uint8_t soc);              /* 读-改-写 SOC (进休眠前, 不同才写) */

/* ---- 时间转换 ---- */
uint32_t rtc_bcd6_to_unix(const uint8_t bcd[6]);           /* BCD(YYMMDDHHMMSS) → Unix */
void rtc_unix_to_datetime(uint32_t ts, uint16_t *year, uint8_t *month,
                          uint8_t *day, uint8_t *hour, uint8_t *min, uint8_t *sec);

#endif /* __RTC_TIMER_H */
