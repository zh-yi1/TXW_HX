#ifndef __DIGIT_16_H__
#define __DIGIT_16_H__

#include "global_define.h"

/* ================================================================
 * 16px 字符位图显示模块
 *
 * 图片位于: 海信VP785S UI资料/digit/16/
 * 字符集: 0-9, A-Z, -
 *
 * Flash 地址定义在 flash_image_addr.h (FLASH_ADDR_0 ~ FLASH_ADDR_9,
 * FLASH_ADDR_A ~ FLASH_ADDR_Z, FLASH_ADDR_ 为 '-' 减号)
 * ================================================================ */

/* ---- 字符尺寸 ---- */
#define DIGIT_16_LINE_H     12           /* 行高 / 字符高度 (像素) */

/* ---- API ---- */

/*
 * 在指定位置显示字符串 (比例字体, 底部对齐)
 *
 *   str:     以 '\0' 结尾的字符串，支持字符 0-9, A-Z, -
 *   start_x: 起始 X 坐标 (像素)
 *   start_y: 起始 Y 坐标 (像素, 行高 16px 的顶部)
 *
 *   不支持的字符自动跳过 (不占位, 不推进 X)
 *   超出屏幕右边界自动截断
 */
void display_string_16(const char *str, uint16_t start_x, uint16_t start_y);
uint16_t string_width_16(const char *str);

#endif /* __DIGIT_16_H__ */
