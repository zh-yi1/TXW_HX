#ifndef __DIGIT_16_H__
#define __DIGIT_16_H__

#include "global_define.h"

/* ================================================================
 * 16px 字符位图显示模块
 *
 * 图片位于: 海信VP785S UI资料/digit/16/
 * 字符集: 0-9, A-Z, -
 *
 * Flash 地址通过 flash_image_addr.h 中的
 *   FLASH_ADDR_16_WHITE_BASE / FLASH_ADDR_16_BLUE_BASE
 *   + index * FLASH_STRIDE_16_WHITE (498, 两色相同)
 * 计算得出, 不再使用大数组查表
 * ================================================================ */

/* ---- 字符尺寸 ---- */
#define DIGIT_16_LINE_H     12           /* 行高 / 字符高度 (像素) */

/* ---- 颜色选择 ---- */
#define DIGIT_16_COLOR_WHITE  1
#define DIGIT_16_COLOR_BLUE   0

/* ---- API ---- */

/*
 * 计算字符串像素宽度
 *
 *   str:   以 '\0' 结尾的字符串，支持字符 0-9, A-Z, -
 *   color: DIGIT_16_COLOR_WHITE 或 DIGIT_16_COLOR_BLUE
 *
 *   返回所有有效字符宽度之和 (不超过 240)
 */
uint16_t string_width_16(const char *str, uint8_t color);

/*
 * 在指定位置显示字符串 (比例字体, 底部对齐)
 *
 *   str:     以 '\0' 结尾的字符串，支持字符 0-9, A-Z, -
 *   start_x: 起始 X 坐标 (像素)
 *   start_y: 起始 Y 坐标 (像素, 行高 16px 的顶部)
 *   color:   DIGIT_16_COLOR_WHITE 或 DIGIT_16_COLOR_BLUE
 *
 *   不支持的字符自动跳过 (不占位, 不推进 X)
 *   超出屏幕右边界自动截断
 */
void display_string_16(const char *str, uint16_t start_x, uint16_t start_y, uint8_t color);

#endif /* __DIGIT_16_H__ */
