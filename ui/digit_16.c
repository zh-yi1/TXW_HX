#include "digit_16.h"

/* ================================================================
 * 字符位图显示模块 (12/16 高度)
 *
 * 数据来源: 海信VP785S UI资料/digit/16/ 和 digit/12/ 下 PNG 文件
 *
 * 16 高度: 字符高 16px (顶部对齐)
 * 12 高度: 字符高 10px (顶部对齐)
 *
 *  数字 0-9
 *  大写 A-Z
 *  符号 -
 *  蓝色额外: : ^ /
 *  白色额外: .
 *
 * Flash 索引:
 *   '0'-'9'  → 0-9
 *   '-'      → 10
 *   'A'-'Z'  → 11-36
 *   ':'      → 37 (蓝)
 *   '^'      → 38 (蓝)
 *   '.'      → 37 (白) / 39 (蓝)
 *   '/'      → 40 (蓝)
 * ================================================================ */

#define SCREEN_W 240

/* ---- 顶部对齐: 字模已是全高, 无需偏移 ---- */
#define CHAR_Y_OFF_16  0
#define CHAR_Y_OFF_12  0

/* ================================================================
 * 字符宽度表
 * ================================================================ */

/* 16 高度 — 白/蓝共用 (白色值; 蓝色差异见 get_char_w 内覆盖) */
static const uint8_t digit_16_width[] = {
	['0'] = 14, ['1'] = 8, ['2'] = 14, ['3'] = 14,
	['4'] = 14, ['5'] = 14, ['6'] = 14, ['7'] = 14,
	['8'] = 14, ['9'] = 14,

	['A'] = 16, ['B'] = 14, ['C'] = 18, ['D'] = 16,
	['E'] =  12, ['F'] =  12, ['G'] = 18, ['H'] = 16,
	['I'] =  8, ['J'] =  12, ['K'] = 14, ['L'] =  12,
	['M'] = 18, ['N'] = 14, ['O'] = 18, ['P'] = 14,
	['Q'] = 18, ['R'] = 14, ['S'] = 14, ['T'] = 14,
	['U'] = 16, ['V'] = 16, ['W'] = 22, ['X'] = 14,
	['Y'] = 14, ['Z'] = 14,

	['-'] =  8,
	['.'] =  6,
};

/* 12 高度 — 蓝色 */
static const uint8_t digit_12_width_blue[] = {
	['0'] =  8, ['1'] = 5, ['2'] = 8, ['3'] = 8,
	['4'] =  9, ['5'] = 8, ['6'] = 8, ['7'] = 8,
	['8'] =  8, ['9'] = 8,

	['A'] =  9, ['B'] = 8, ['C'] = 10, ['D'] = 9,
	['E'] =  7, ['F'] = 7, ['G'] = 10, ['H'] = 9,
	['I'] =  5, ['J'] = 7, ['K'] =  8, ['L'] = 7,
	['M'] = 11, ['N'] = 9, ['O'] = 10, ['P'] = 8,
	['Q'] = 10, ['R'] = 8, ['S'] =  8, ['T'] = 8,
	['U'] =  9, ['V'] =10, ['W'] = 13, ['X'] = 9,
	['Y'] =  9, ['Z'] = 9,

	['-'] =  7,

	[':'] =  6,
	['^'] = 13,
	['.'] =  3,
	['/'] =  6,
};

/* ================================================================
 * char_to_idx — 字符 → Flash 索引
 *
 * 根据颜色返回正确的 Flash 索引:
 *   白色 '.' → 37,  蓝色 '.' → 39
 *   ':' '^' '/' 仅蓝色支持, 白色返回 0xFF
 *
 * 返回 0xFF 表示不支持的字符
 * ================================================================ */
static uint8_t char_to_idx(char c, uint8_t color)
{
	if (c >= '0' && c <= '9')
		return (uint8_t)(c - '0');          /* 0-9   */
	if (c == '-')
		return 10;                           /* 10    */
	if (c >= 'A' && c <= 'Z')
		return (uint8_t)(c - 'A' + 11);      /* 11-36 */

	/* '.' 白/蓝共用, 但 Flash 索引不同 */
	if (c == '.')
		return (color == DIGIT_16_COLOR_WHITE) ? 37 : 39;

	/* 以下仅蓝色支持 */
	if (color == DIGIT_16_COLOR_WHITE)
		return 0xFF;

	if (c == ':') return 37;
	if (c == '^') return 38;
	if (c == '/') return 40;

	return 0xFF;
}

/* ================================================================
 * get_char_w — 获取字符像素宽度
 *
 * 根据颜色和高度选择对应的宽度表
 * 返回 0 表示不支持的字符
 * ================================================================ */
static uint8_t get_char_w(char c, uint8_t color, uint8_t height)
{
	uint8_t w;

	/* 不支持的字符 → 0, 同时防止数组越界 (删 [128] 后数组仅到最高有效索引) */
	if (char_to_idx(c, color) == 0xFF)
		return 0;

	if (height == DIGIT_HEIGHT_12)
		return digit_12_width_blue[(uint8_t)c];

	/* 16 高度: 白/蓝共用主表 (白色值) */
	w = digit_16_width[(uint8_t)c];

	/* 蓝色宽度覆盖: 'M','R' 与白色不同; ':','^','.','/' 蓝色专属 */
	if (color == DIGIT_16_COLOR_BLUE) {
		if (c == ':') return  6;
		else if (c == '^') return 22;
		else if (c == '.') return  6;
		else if (c == '/') return  12;
	}

	return w;
}

/* ================================================================
 * get_char_addr — 计算字符位图在 Flash 中的绝对地址
 *
 * addr = base + idx * stride
 *
 * 12 高度仅支持蓝色
 * 返回 0 表示不支持的字符
 * ================================================================ */
static uint32_t get_char_addr(char c, uint8_t color, uint8_t height)
{
	uint8_t  idx  = char_to_idx(c, color);
	uint32_t base;
	uint32_t stride;

	if (idx == 0xFF)
		return 0xFFFFFFFF;

	if (height == DIGIT_HEIGHT_12)
	{
		/* 仅蓝色 */
		if (color != DIGIT_16_COLOR_BLUE)
			return 0xFFFFFFFF;
		base   = FLASH_ADDR_12_BLUE_BASE;
		stride = FLASH_STRIDE_12_BLUE;
	}
	else
	{
		base   = (color == DIGIT_16_COLOR_WHITE)
			? FLASH_ADDR_16_WHITE_BASE
			: FLASH_ADDR_16_BLUE_BASE;
		stride = FLASH_STRIDE_16_WHITE;
	}

	return base + (uint32_t)idx * stride;
}

/* ================================================================
 * digit_string_width — 计算字符串像素宽度
 *
 * 返回 str 所有有效字符宽度之和 (不超过 SCREEN_W)
 * ================================================================ */
uint16_t digit_string_width(const char *str, uint8_t color, uint8_t height)
{
	uint16_t total_w = 0;
	uint8_t  c, w;

	if (!str)
		return 0;

	while (*str)
	{
		c = (uint8_t)*str;
		if (c < 128)
		{
			w = get_char_w((char)c, color, height);
			if (w > 0 && get_char_addr((char)c, color, height) != 0xFFFFFFFF)
			{
				if (total_w + w > SCREEN_W)
					break;
				total_w += w;
			}
		}
		str++;
	}
	return total_w;
}

/* ================================================================
 * digit_display_string — 在指定位置显示字符串
 *
 * 底部对齐
 * 不支持的字符自动跳过
 * 超出屏幕右边界截断
 * ================================================================ */
void digit_display_string(const char *str, uint16_t start_x, uint16_t start_y, uint8_t color, uint8_t height)
{
	uint16_t cur_x;
	uint8_t  c, w;
	uint32_t addr;
	uint8_t  y_off;

	if (!str)
		return;

	y_off = (height == DIGIT_HEIGHT_12) ? CHAR_Y_OFF_12 : CHAR_Y_OFF_16;

	cur_x = start_x;

	while (*str)
	{
		c = (uint8_t)*str;

		if (c >= 128)
			goto next;

		addr = get_char_addr((char)c, color, height);
		w    = get_char_w((char)c, color, height);

		/* 不支持的字符或地址未配置则跳过 */
		if (addr == 0xFFFFFFFF || w == 0)
			goto next;

		/* 超出屏幕右边界则截断 */
		if (cur_x + w > SCREEN_W)
			break;

		/* 底部对齐 */
		Dispphoto_Dispaly_flash(cur_x, start_y + y_off, addr);

		cur_x += w;

	next:
		str++;
	}
}
