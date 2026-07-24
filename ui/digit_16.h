#ifndef __DIGIT_16_H__
#define __DIGIT_16_H__

#include "global_define.h"

/* ================================================================
 * 字符位图显示模块 (12/16 高度)
 *
 * 图片位于: 海信VP785S UI资料/digit/12/ 和 digit/16/
 * 字符集: 0-9, A-Z, -
 * 蓝色额外: : ^ /
 * 白色额外: .
 *
 * Flash 地址通过 flash_image_addr.h 中的
 *   FLASH_ADDR_XX_BASE + index * FLASH_STRIDE_XX
 * 计算得出
 * ================================================================ */

/* ---- 字号选择 (字模已是全高, 顶部对齐, start_y 即字符顶部) ---- */
#define DIGIT_HEIGHT_12      12           /* 12 号: 字符高 10px */
#define DIGIT_HEIGHT_16      16           /* 16 号: 字符高 16px */

/* ---- 字符高度 (用于局部刷新擦除) ---- */
#define DIGIT_12_LINE_H      10           /* 12 号字符高 */
#define DIGIT_16_LINE_H      16           /* 16 号字符高 */

/* ---- 颜色选择 ---- */
#define DIGIT_16_COLOR_WHITE  1
#define DIGIT_16_COLOR_BLUE   0

/* ---- API (带高度参数) ---- */

/*
 * 计算字符串像素宽度
 *
 *   str:    以 '\0' 结尾的字符串
 *   color:  DIGIT_16_COLOR_WHITE 或 DIGIT_16_COLOR_BLUE
 *   height: DIGIT_HEIGHT_12 或 DIGIT_HEIGHT_16
 *
 *   返回所有有效字符宽度之和 (不超过 240)
 */
uint16_t digit_string_width(const char *str, uint8_t color, uint8_t height);

/*
 * 在指定位置显示字符串 (比例字体, 顶部对齐)
 *
 *   str:     以 '\0' 结尾的字符串
 *   start_x: 起始 X 坐标 (像素)
 *   start_y: 起始 Y 坐标 (像素, 字符顶部)
 *   color:   DIGIT_16_COLOR_WHITE 或 DIGIT_16_COLOR_BLUE
 *   height:  DIGIT_HEIGHT_12 或 DIGIT_HEIGHT_16
 *
 *   不支持的字符自动跳过 (不占位, 不推进 X)
 *   超出屏幕右边界自动截断
 */
void digit_display_string(const char *str, uint16_t start_x, uint16_t start_y, uint8_t color, uint8_t height);

/* ---- 兼容旧 API (默认 16 高度) ---- */
#define string_width_16(str, color)        digit_string_width(str, color, DIGIT_HEIGHT_16)
#define display_string_16(str, x, y, color) digit_display_string(str, x, y, color, DIGIT_HEIGHT_16)

#endif /* __DIGIT_16_H__ */
