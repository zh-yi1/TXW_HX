#ifndef __OFF_TIME_PAGE_H__
#define __OFF_TIME_PAGE_H__

#include "global_define.h"

void off_time_page_init(void);    /* 切入本页: 清屏 + 全量绘制, 选中项按当前生效时长 */
void off_time_page_updata(void);  /* 选中项变了才动屏, 每轮主循环调用 */
void off_time_page_next(void);    /* 双击: 选中下一项(轮回), 立即生效 */

#endif
