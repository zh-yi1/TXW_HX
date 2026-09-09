#ifndef __HOME_PAGE_H__
#define __HOME_PAGE_H__

#include "global_define.h"

void home_page_init(void);       /* 切入本页: 清屏 + 全量绘制 */
void home_page_updata(void);     /* 周期刷新(500ms): 只重绘变化的部分 */
void home_page_sample(void);     /* 电量采样, 每轮主循环调用, 内部按 100ms 节流 */
void home_page_anim_proc(void);  /* 主页充电/待机动画驱动，每轮主循环调用，12帧/2秒循环 */

#endif
