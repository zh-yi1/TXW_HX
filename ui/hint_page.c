#include "hint_page.h"

typedef enum
{
	HINT_OVER_TEMP,    /* 过温保护 */
	HINT_LOW_TEMP,     /* 低温保护 */
	HINT_SHORT_CIRCUIT,/* 短路保护 */

	HINT_IMG_MAX,
} hint_img_e;

pos_and_addr_t hint_img_pos[] = {
	{80, 4, FLASH_ADDR_TEMP_BLUE},
	{80, 4, FLASH_ADDR_TEMP_ORANGE},
	{80, 4, FLASH_ADDR_CIRCUIT_PROTECTION},
};

pos_and_addr_t hint_text_img_pos[] = {
	{0, 87, FLASH_ADDR_LOW_TMP_TEXT},
	{0, 87, FLASH_ADDR_HIGH_TMP_TEXT},
	{0, 87, FLASH_ADDR_CIRCUIT_PROTECTION_TEXT},
};

void over_temp_hint_page(void)
{
	DispBlock(0, 0, ROW - 1, COL - 1);
	Dispphoto_Dispaly_flash(hint_img_pos[HINT_OVER_TEMP].x, hint_img_pos[HINT_OVER_TEMP].y, hint_img_pos[HINT_OVER_TEMP].img_addr);
	Dispphoto_Dispaly_flash(hint_text_img_pos[HINT_OVER_TEMP].x, hint_text_img_pos[HINT_OVER_TEMP].y, hint_text_img_pos[HINT_OVER_TEMP].img_addr);
}

void low_temp_hint_page(void)
{
	DispBlock(0, 0, ROW - 1, COL - 1);
	Dispphoto_Dispaly_flash(hint_img_pos[HINT_LOW_TEMP].x, hint_img_pos[HINT_LOW_TEMP].y, hint_img_pos[HINT_LOW_TEMP].img_addr);
	Dispphoto_Dispaly_flash(hint_text_img_pos[HINT_LOW_TEMP].x, hint_text_img_pos[HINT_LOW_TEMP].y, hint_text_img_pos[HINT_LOW_TEMP].img_addr);
}

void short_circuit_hint_page(void)
{
	DispBlock(0, 0, ROW - 1, COL - 1);
	Dispphoto_Dispaly_flash(hint_img_pos[HINT_SHORT_CIRCUIT].x, hint_img_pos[HINT_SHORT_CIRCUIT].y, hint_img_pos[HINT_SHORT_CIRCUIT].img_addr);
	Dispphoto_Dispaly_flash(hint_text_img_pos[HINT_SHORT_CIRCUIT].x, hint_text_img_pos[HINT_SHORT_CIRCUIT].y, hint_text_img_pos[HINT_SHORT_CIRCUIT].img_addr);
}
