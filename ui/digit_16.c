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
 * ================================================================ */

#define SCREEN_W 240
#define CHAR_Y_OFF 0  /* 底部对齐偏移 */

/* ---- 字符宽度表 (按 ASCII 索引, 0 = 不支持的字符) ---- */
static const uint8_t digit_16_width[128] = {
	['0'] = 10, ['1'] = 10, ['2'] = 10, ['3'] = 10,
	['4'] = 10, ['5'] = 10, ['6'] = 10, ['7'] = 10,
	['8'] = 10, ['9'] = 10,

	['A'] = 12, ['B'] = 11, ['C'] = 13, ['D'] = 12,
	['E'] =  9, ['F'] =  9, ['G'] = 13, ['H'] = 12,
	['I'] =  6, ['J'] =  9, ['K'] = 11, ['L'] =  9,
	['M'] = 14, ['N'] = 12, ['O'] = 13, ['P'] = 11,
	['Q'] = 13, ['R'] = 11, ['S'] = 11, ['T'] = 11,
	['U'] = 12, ['V'] = 12, ['W'] = 17, ['X'] = 11,
	['Y'] = 11, ['Z'] = 11,

	['-'] =  9,
};

/* ---- Flash 地址表 (按 ASCII 索引, 0 = 不支持的字符) ---- */
/* 地址定义在 flash_image_addr.h */
static const uint32_t digit_16_addr[128] = {
	['0'] = FLASH_ADDR_0, ['1'] = FLASH_ADDR_1,
	['2'] = FLASH_ADDR_2, ['3'] = FLASH_ADDR_3,
	['4'] = FLASH_ADDR_4, ['5'] = FLASH_ADDR_5,
	['6'] = FLASH_ADDR_6, ['7'] = FLASH_ADDR_7,
	['8'] = FLASH_ADDR_8, ['9'] = FLASH_ADDR_9,

	['A'] = FLASH_ADDR_A, ['B'] = FLASH_ADDR_B,
	['C'] = FLASH_ADDR_C, ['D'] = FLASH_ADDR_D,
	['E'] = FLASH_ADDR_E, ['F'] = FLASH_ADDR_F,
	['G'] = FLASH_ADDR_G, ['H'] = FLASH_ADDR_H,
	['I'] = FLASH_ADDR_I, ['J'] = FLASH_ADDR_J,
	['K'] = FLASH_ADDR_K, ['L'] = FLASH_ADDR_L,
	['M'] = FLASH_ADDR_M, ['N'] = FLASH_ADDR_N,
	['O'] = FLASH_ADDR_O, ['P'] = FLASH_ADDR_P,
	['Q'] = FLASH_ADDR_Q, ['R'] = FLASH_ADDR_R,
	['S'] = FLASH_ADDR_S, ['T'] = FLASH_ADDR_T,
	['U'] = FLASH_ADDR_U, ['V'] = FLASH_ADDR_V,
	['W'] = FLASH_ADDR_W, ['X'] = FLASH_ADDR_X,
	['Y'] = FLASH_ADDR_Y, ['Z'] = FLASH_ADDR_Z,

	['-'] = FLASH_ADDR_,
};

/* ================================================================
 * string_width_16 — 计算字符串像素宽度
 *
 * 返回 str 所有有效字符宽度之和 (不超过 SCREEN_W)
 * ================================================================ */
uint16_t string_width_16(const char *str)
{
	uint16_t total_w = 0;
	uint8_t c, w;

	if (!str)
		return 0;

	while (*str)
	{
		c = (uint8_t)*str;
		if (c < 128)
		{
			w = digit_16_width[c];
			if (w > 0 && digit_16_addr[c] != 0)
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
void display_string_16(const char *str, uint16_t start_x, uint16_t start_y)
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

		addr = digit_16_addr[c];
		w    = digit_16_width[c];

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
