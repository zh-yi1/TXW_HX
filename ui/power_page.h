#ifndef __POWER_PAGE_H__
#define __POWER_PAGE_H__

#include "global_define.h"

void power_page_init(void);    /* 切入本页: 清屏 + 三行全量绘制 */
void power_page_updata(void);  /* 周期刷新(500ms): 只重绘变化的部分 */
void power_page_sample(void);  /* 功率采样, 每轮主循环调用, 内部按 100ms 节流 */

#endif
