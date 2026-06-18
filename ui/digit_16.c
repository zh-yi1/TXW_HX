#include "digit_16.h"

/* ================================================================
 * 字符位图显示模块 (12/16 高度)
 *
 * 数据来源: 海信VP785S UI资料/digit/16/ 和 digit/12/ 下 PNG 文件
 *
 * 16 高度: 字符高 12px, 行高 16px
 * 12 高度: 字符高 10px, 行高 12px
 *
 *  数字 0-9
 *  大写 A-Z
 *  符号 -
 *  蓝色额外: : ^ . /
 *
 * Flash 索引 (共用):
 *   '0'-'9'  → 0-9
 *   '-'      → 10
 *   'A'-'Z'  → 11-36
 *   ':'      → 37
 *   '^'      → 38
 *   '.'      → 39
 *   '/'      → 40
 * ================================================================ */

#define SCREEN_W 240

/* ---- 底部对齐偏移: 行高 - 字符高 ---- */
#define CHAR_Y_OFF_16  4  /* 16 - 12 */
#define CHAR_Y_OFF_12  2  /* 12 - 10 */

/* ================================================================
 * 字符宽度表
 * ================================================================ */

/* 16 高度 — 白色 */
static const uint8_t digit_16_width[128] = {
	['0'] = 10, ['1'] = 6, ['2'] = 10, ['3'] = 10,
	['4'] = 10, ['5'] = 10, ['6'] = 10, ['7'] = 10,
	['8'] = 10, ['9'] = 10,

	['A'] = 12, ['B'] = 11, ['C'] = 13, ['D'] = 11,
	['E'] =  9, ['F'] =  9, ['G'] = 13, ['H'] = 12,
	['I'] =  6, ['J'] =  9, ['K'] = 11, ['L'] =  9,
	['M'] = 14, ['N'] = 12, ['O'] = 13, ['P'] = 11,
	['Q'] = 13, ['R'] = 10, ['S'] = 11, ['T'] = 11,
	['U'] = 12, ['V'] = 12, ['W'] = 17, ['X'] = 11,
	['Y'] = 11, ['Z'] = 11,

	['-'] =  9,
};

/* 16 高度 — 蓝色 */
static const uint8_t digit_16_width_blue[128] = {
	['0'] = 10, ['1'] = 6, ['2'] = 10, ['3'] = 10,
	['4'] = 10, ['5'] = 10, ['6'] = 10, ['7'] = 10,
	['8'] = 10, ['9'] = 10,

	['A'] = 12, ['B'] = 11, ['C'] = 13, ['D'] = 11,
	['E'] =  9, ['F'] =  9, ['G'] = 13, ['H'] = 12,
	['I'] =  6, ['J'] =  9, ['K'] = 11, ['L'] =  9,
	['M'] = 13, ['N'] = 12, ['O'] = 13, ['P'] = 11,
	['Q'] = 13, ['R'] = 11, ['S'] = 11, ['T'] = 11,
	['U'] = 12, ['V'] = 12, ['W'] = 17, ['X'] = 11,
	['Y'] = 11, ['Z'] = 11,

	['-'] =  9,

	/* 蓝色专属特殊字符 (Flash index 37-40) */
	[':'] =  8,
	['^'] = 16,
	['.'] =  4,
	['/'] =  8,
};

/* 12 高度 — 蓝色 (TODO: 填入实际宽度) */
static const uint8_t digit_12_width_blue[128] = {
	['0'] =  8, ['1'] = 5, ['2'] = 8, ['3'] = 8,
	['4'] =  9, ['5'] = 8, ['6'] = 8, ['7'] = 8,
	['8'] =  8, ['9'] = 8,

	['A'] =  9, ['B'] = 8, ['C'] = 10, ['D'] = 9,
	['E'] =  7, ['F'] = 7, ['G'] = 10, ['H'] = 9,
	['I'] =  5, ['J'] = 7, ['K'] =  8, ['L'] = 7,
	['M'] = 11, ['N'] = 8, ['O'] = 10, ['P'] = 8,
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
 * 12/16 高度共用同一套索引映射
 *
 * 返回 0xFF 表示不支持的字符
 * ================================================================ */
static uint8_t char_to_idx(char c)
{
	if (c >= '0' && c <= '9')
		return (uint8_t)(c - '0');          /* 0-9   */
	if (c == '-')
		return 10;                           /* 10    */
	if (c >= 'A' && c <= 'Z')
		return (uint8_t)(c - 'A' + 11);      /* 11-36 */

	/* 蓝色专属特殊字符 */
	if (c == ':') return 37;
	if (c == '^') return 38;
	if (c == '.') return 39;
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
	const uint8_t *table;

	if ((uint8_t)c >= 128)
		return 0;

	if (height == DIGIT_HEIGHT_12)
	{
		table = digit_12_width_blue;
	}
	else
	{
		table = (color == DIGIT_16_COLOR_WHITE)
			? digit_16_width
			: digit_16_width_blue;
	}

	return table[(uint8_t)c];
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
	uint8_t  idx  = char_to_idx(c);
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
