#include "digit_16.h"

/* ================================================================
 * 16px 字符位图表 (Canvas 尺寸, 单位: 像素)
 *
 * 数据来源: 海信VP785S UI资料/digit/16/ 下 PNG 文件的 IHDR
 * 高度统一按 12px 处理
 *
 *  数字 0-9:  10x12
 *  大写 A-Z:  6~17 x 12
 *  符号 -:     9x12
 *
 * Flash 索引 (16_WHITE / 16_BLUE 共用):
 *   '0'-'9'  → 0-9
 *   '-'      → 10
 *   'A'-'Z'  → 11-36
 *
 * 16_BLUE 额外字符:
 *   ':' → 37 (冒号),  '^' → 38 (度数),
 *   '.' → 39 (点),    '_' → 40 (下划线)
 * ================================================================ */

#define SCREEN_W 240
#define CHAR_Y_OFF 0  /* 底部对齐偏移 */

/* ---- 字符宽度表 (按 ASCII 索引, 0 = 不支持的字符) ---- */
/* 白色 */
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

/* 蓝色 (TODO: 填入实际宽度) */
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
	[':'] =  8,   /* 冒号  — FLASH_IDX_16_BLUE_Z_COLON  (TODO) */
	['^'] =  16,   /* 度数  — FLASH_IDX_16_BLUE_Z_DEGREE (TODO) */
	['.'] =  4,   /* 点    — FLASH_IDX_16_BLUE_Z_DOT    (TODO) */
	['/'] =  8,   /* 斜杠 — FLASH_IDX_16_BLUE_Z_LINE   (TODO) */
};

/* ================================================================
 * char_to_idx — 字符 → Flash 索引
 *
 * 蓝色专属字符 (index 37-40): ':' '^' '.' '_'
 * 白色宽度表中未收录这些字符 (w=0), 自动跳过
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
	if (c == ':') return 37;   /* Z_COLON  */
	if (c == '^') return 38;   /* Z_DEGREE */
	if (c == '.') return 39;   /* Z_DOT    */
	if (c == '/') return 40;   /* Z_LINE   */

	return 0xFF;
}

/* ================================================================
 * get_char_w — 获取字符像素宽度
 *
 * 根据颜色选择对应的宽度表
 * 返回 0 表示不支持的字符
 * ================================================================ */
static uint8_t get_char_w(char c, uint8_t color)
{
	const uint8_t *table;

	if ((uint8_t)c >= 128)
		return 0;

	table = (color == DIGIT_16_COLOR_WHITE)
		? digit_16_width
		: digit_16_width_blue;

	return table[(uint8_t)c];
}

/* ================================================================
 * get_char_addr — 计算字符位图在 Flash 中的绝对地址
 *
 * addr = base + idx * stride
 * 两色 stride 相同 (498), 仅 base 不同
 *
 * 返回 0 表示不支持的字符
 * ================================================================ */
static uint32_t get_char_addr(char c, uint8_t color)
{
	uint8_t  idx  = char_to_idx(c);
	uint32_t base;

	if (idx == 0xFF)
		return 0;

	base = (color == DIGIT_16_COLOR_WHITE)
		? FLASH_ADDR_16_WHITE_BASE
		: FLASH_ADDR_16_BLUE_BASE;

	return base + (uint32_t)idx * FLASH_STRIDE_16_WHITE;
}

/* ================================================================
 * string_width_16 — 计算字符串像素宽度
 *
 * 返回 str 所有有效字符宽度之和 (不超过 SCREEN_W)
 * ================================================================ */
uint16_t string_width_16(const char *str, uint8_t color)
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
			w = get_char_w((char)c, color);
			if (w > 0 && get_char_addr((char)c, color) != 0)
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
 * display_string_16 — 在指定位置显示字符串
 *
 * 底部对齐 (行高 16px, 字符高 12px, 顶部偏移 4px)
 * 不支持的字符自动跳过
 * 超出屏幕右边界截断
 * ================================================================ */
void display_string_16(const char *str, uint16_t start_x, uint16_t start_y, uint8_t color)
{
	uint16_t cur_x;
	uint8_t  c, w;
	uint32_t addr;

	if (!str)
		return;

	cur_x = start_x;

	while (*str)
	{
		c = (uint8_t)*str;

		if (c >= 128)
			goto next;

		addr = get_char_addr((char)c, color);
		w    = get_char_w((char)c, color);

		/* 不支持的字符或地址未配置则跳过 */
		if (addr == 0 || w == 0)
			goto next;

		/* 超出屏幕右边界则截断 */
		if (cur_x + w > SCREEN_W)
			break;

		/* 底部对齐 */
		Dispphoto_Dispaly_flash(cur_x, start_y + CHAR_Y_OFF, addr);

		cur_x += w;

	next:
		str++;
	}
}
