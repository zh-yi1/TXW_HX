#ifndef __DIGIT_16_H__
#define __DIGIT_16_H__

#include "global_define.h"

/* ================================================================
 * 字符位图显示模块 (12/16 号)
 *
 * 字模只有白色一套 (NUM_12 / NUM_16), 不再区分蓝白, 故 API 无颜色参数。
 *
 * Flash 地址通过 flash_image_addr.h 中的
 *   FLASH_ADDR_NUM_xx_BASE + index * FLASH_STRIDE_NUM_xx
 * 计算得出
 * ================================================================ */

/* ---- 字号选择 (字模已是全高, 顶部对齐, start_y 即字符顶部) ---- */
#define DIGIT_HEIGHT_12      12           /* 12 号: 字符高 10px */
#define DIGIT_HEIGHT_16      16           /* 16 号: 字符高 16px */

/* ---- 字符高度 (用于局部刷新擦除) ---- */
#define DIGIT_12_LINE_H      10           /* 12 号字符高 */
#define DIGIT_16_LINE_H      16           /* 16 号字符高 */

/* ---- API ---- */

/*
 * 计算字符串像素宽度
 *
 *   str:    以 '\0' 结尾的字符串
 *   height: DIGIT_HEIGHT_12 或 DIGIT_HEIGHT_16
 *
 *   返回所有有效字符宽度之和 (不超过 240)
 */
uint16_t digit_string_width(const char *str, uint8_t height);

/*
 * 在指定位置显示字符串 (比例字体, 顶部对齐)
 *
 *   str:     以 '\0' 结尾的字符串
 *   start_x: 起始 X 坐标 (像素)
 *   start_y: 起始 Y 坐标 (像素, 字符顶部)
 *   height:  DIGIT_HEIGHT_12 或 DIGIT_HEIGHT_16
 *
 *   不支持的字符自动跳过 (不占位, 不推进 X)
 *   超出屏幕右边界自动截断
 */
void digit_display_string(const char *str, uint16_t start_x, uint16_t start_y, uint8_t height);

/* ---- 简写 (默认 16 号) ---- */
#define string_width_16(str)          digit_string_width(str, DIGIT_HEIGHT_16)
#define display_string_16(str, x, y)  digit_display_string(str, x, y, DIGIT_HEIGHT_16)

#endif /* __DIGIT_16_H__ */
