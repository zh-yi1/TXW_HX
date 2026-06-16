#ifndef __HINT_PAGE_H__
#define __HINT_PAGE_H__

#include "global_define.h"

void over_temp_hint_page(void);
void low_temp_hint_page(void);
void short_circuit_hint_page(void);

/*
 * 电压 / 温度异常信息页
 *
 *   type:      0=电压 1=温度
 *   index:     第几条 (1-based)
 *   total:     总条数
 *   timestamp: Unix 时间戳
 *   value:     电压 mV / 温度 ℃ (整度)
 *   bat_num:   电池编号 (type=1 时忽略)
 */
void abnormal_hint_page(uint8_t  type,
                                uint8_t  index,
                                uint8_t  total,
                                uint32_t timestamp,
                                uint16_t value,
                                const char *bat_num);

#endif
