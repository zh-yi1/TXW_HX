#include "digit_16.h"

/* ================================================================
 * 字符位图显示模块 (12/16 号)
 *
 * 字模只有白色一套, 不再区分蓝白。
 *
 * Flash 索引全部取自 flash_image_addr.h 生成的 FLASH_IDX_NUM_12_* /
 * FLASH_IDX_NUM_16_* (名字以 '_' 结尾的那个是 '-'), 不在这里写死数字 ——
 * 切图增删重排后重新生成头文件即可, 本文件不用跟着改。
 *
 * 字符集: '0'-'9'  '-'  'A'-'Z'  ':'  '^'(度)  '.'  —— 两档当前排列一致。
 * 字母区是否覆盖到 'Z' 由切图决定: 字母索引一旦顶到后面符号的槽位就判为
 * 不支持, 所以某个字母没出图时会被自动跳过。
 * 两档都没有 '/'。
 * ================================================================ */

#define SCREEN_W 240

/* ---- 顶部对齐: 字模已是全高, 无需偏移 ---- */
#define CHAR_Y_OFF_16  0
#define CHAR_Y_OFF_12  0

/* ================================================================
 * 字符宽度表 —— 必须等于 flash 里位图的真实像素宽
 *
 * 表值大于位图宽 = 字符之间留下一条从没写过的列, 串长变化时旧字的笔画
 * 会残留在缝里 (总电压 "XX.XXV" 里冒出竖条/斜杠就是这么来的)。
 *
 * 数值由 flash_image_addr.h 的 FLASH_SIZE_NUM_xx_* 反推:
 *   宽 = (size - 66 字节 BMP 头) / 字符高 / 2 字节每像素
 * 切图重出后按同样方法重算。表按 ASCII 下标索引, 未列出 = 0 = 不支持。
 * ================================================================ */

/* 12 号 (字符高 10, 最宽 14) */
static const uint8_t digit_12_width[] = {
	['0'] =  8, ['1'] = 5, ['2'] = 8, ['3'] = 8,
	['4'] = 10, ['5'] = 8, ['6'] = 8, ['7'] = 8,
	['8'] =  8, ['9'] = 8,

	['A'] = 10, ['B'] = 8, ['C'] = 10, ['D'] = 9,
	['E'] =  7, ['F'] = 7, ['G'] = 10, ['H'] = 9,
	['I'] =  5, ['J'] = 8, ['K'] =  8, ['L'] = 7,
	['M'] = 11, ['N'] =9, ['O'] = 10, ['P'] = 8,
	['Q'] = 10, ['R'] = 8, ['S'] =  8, ['T'] = 8,
	['U'] = 9, ['V'] =10, ['W'] = 13, ['X'] =9,
	['Y'] = 9, ['Z'] =9,

	['-'] =  7,
	[':'] =  6,
	['^'] = 13,
	['.'] =  3,
};

/* 16 号 (字符高 16, 最宽 22) */
static const uint8_t digit_16_width[] = {
	['0'] = 11, ['1'] = 7, ['2'] = 11, ['3'] = 11,
	['4'] = 11, ['5'] = 11, ['6'] = 11, ['7'] = 11,
	['8'] = 11, ['9'] = 11,

	['A'] = 14, ['B'] = 11, ['C'] = 14, ['D'] = 13,
	['E'] = 9, ['F'] = 9, ['G'] = 14, ['H'] = 12,
	['I'] =  6, ['J'] = 10, ['K'] = 12, ['L'] = 9,
	['M'] = 15, ['N'] = 12, ['O'] = 14, ['P'] = 10,
	['Q'] = 14, ['R'] = 11, ['S'] = 10, ['T'] = 11,
	['U'] = 12, ['V'] = 14, ['W'] = 19, ['X'] = 13,
	['Y'] = 12, ['Z'] = 11,

	['-'] =  8,
	[':'] =  6,
	['^'] = 22,
	['.'] =  6,
};

/* ================================================================
 * char_to_idx — 字符 → Flash 索引
 *
 * 返回 0xFF 表示该字号不支持这个字符
 * ================================================================ */
static uint8_t char_to_idx(char c, uint8_t height)
{
	if (height == DIGIT_HEIGHT_12)
	{
		if (c >= '0' && c <= '9')
			return (uint8_t)(FLASH_IDX_NUM_12_0 + (c - '0'));
		if (c == '-') return FLASH_IDX_NUM_12__;
		if (c >= 'A' && c <= 'Z')
		{
			uint8_t idx = (uint8_t)(FLASH_IDX_NUM_12_A + (c - 'A'));
			/* 字母区顶到后面符号的槽位 = 这个字母没出图 */
			return (idx < FLASH_IDX_NUM_12_Z_COLON) ? idx : 0xFF;
		}
		if (c == ':') return FLASH_IDX_NUM_12_Z_COLON;
		if (c == '^') return FLASH_IDX_NUM_12_Z_DEGREE;   /* 度符号 */
		if (c == '.') return FLASH_IDX_NUM_12_Z_DOT;
		return 0xFF;
	}

	if (c >= '0' && c <= '9')
		return (uint8_t)(FLASH_IDX_NUM_16_0 + (c - '0'));
	if (c == '-') return FLASH_IDX_NUM_16__;
	if (c >= 'A' && c <= 'Z')
	{
		uint8_t idx = (uint8_t)(FLASH_IDX_NUM_16_A + (c - 'A'));
		return (idx < FLASH_IDX_NUM_16_Z_COLON) ? idx : 0xFF;
	}
	if (c == ':') return FLASH_IDX_NUM_16_Z_COLON;
	if (c == '^') return FLASH_IDX_NUM_16_Z_DEGREE;   /* 度符号 */
	if (c == '.') return FLASH_IDX_NUM_16_Z_DOT;

	return 0xFF;
}

/* ================================================================
 * get_char_w — 获取字符像素宽度, 0 = 不支持
 * ================================================================ */
static uint8_t get_char_w(char c, uint8_t height)
{
	if (char_to_idx(c, height) == 0xFF)
		return 0;   /* 顺带防止下面按 ASCII 下标越界 */

	if (height == DIGIT_HEIGHT_12)
	{
		if ((uint8_t)c >= sizeof(digit_12_width)) return 0;
		return digit_12_width[(uint8_t)c];
	}

	if ((uint8_t)c >= sizeof(digit_16_width)) return 0;
	return digit_16_width[(uint8_t)c];
}

/* ================================================================
 * get_char_addr — 字符位图在 Flash 中的绝对地址
 *
 * addr = base + idx * stride, 返回 0xFFFFFFFF 表示不支持
 * ================================================================ */
static uint32_t get_char_addr(char c, uint8_t height)
{
	uint8_t  idx = char_to_idx(c, height);
	uint32_t base, stride;

	if (idx == 0xFF)
		return 0xFFFFFFFF;

	if (height == DIGIT_HEIGHT_12)
	{
		base   = FLASH_ADDR_NUM_12_BASE;
		stride = FLASH_STRIDE_NUM_12;
	}
	else
	{
		base   = FLASH_ADDR_NUM_16_BASE;
		stride = FLASH_STRIDE_NUM_16;
	}

	return base + (uint32_t)idx * stride;
}

/* ================================================================
 * digit_string_width — 计算字符串像素宽度
 *
 * 返回 str 所有有效字符宽度之和 (不超过 SCREEN_W)
 * ================================================================ */
uint16_t digit_string_width(const char *str, uint8_t height)
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
			w = get_char_w((char)c, height);
			if (w > 0)
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
 * 顶部对齐, 不支持的字符自动跳过, 超出屏幕右边界截断
 * ================================================================ */
void digit_display_string(const char *str, uint16_t start_x, uint16_t start_y, uint8_t height)
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

		addr = get_char_addr((char)c, height);
		w    = get_char_w((char)c, height);

		/* 不支持的字符或宽度未配置则跳过 */
		if (addr == 0xFFFFFFFF || w == 0)
			goto next;

		/* 超出屏幕右边界则截断 */
		if (cur_x + w > SCREEN_W)
			break;

		Dispphoto_Dispaly_flash(cur_x, start_y + y_off, addr);

		cur_x += w;

	next:
		str++;
	}
}
