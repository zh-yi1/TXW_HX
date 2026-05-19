#include "hint_page.h"
typedef enum
{
	HINT_OVER_TEMP,		/* 过温保护 */
	HINT_LOW_TEMP,		/* 低温保护 */
	HINT_OVER_VOLT,		/* 过压保护 */
	HINT_LOW_VOLT,		/* 低压保护 */
	HINT_SHORT_CIRCUIT,	/* 短路保护 */
	HINT_OVER_CURRENT,	/* 过流保护 */

	HINT_IMG_MAX,
} hint_img_e;

pos_and_addr_t hint_img_pos[] = {
    {80, 4, FLASH_ADDR_TEMP_BLUE},
    {80, 4, FLASH_ADDR_TEMP_ORANGE},
    {80, 4, FLASH_ADDR_VOLTAGE_BLUE},
    {80, 4, FLASH_ADDR_VOLTAGE_ORANGE},
    {80, 4, FLASH_ADDR_SHORT_CIRCUIT},
    {80, 4, FLASH_ADDR_OVER_CURRENT},
};

//TODO :后续添加文字提示

void over_temp_hint_page(void)
{
    // 清除屏幕
	DispBlock(0, 0, ROW - 1, COL - 1);

    Dispphoto_Dispaly_flash(hint_img_pos[HINT_OVER_TEMP].x, hint_img_pos[HINT_OVER_TEMP].y, hint_img_pos[HINT_OVER_TEMP].img_addr);
}

void low_temp_hint_page(void)
{
    // 清除屏幕
	DispBlock(0, 0, ROW - 1, COL - 1);

    Dispphoto_Dispaly_flash(hint_img_pos[HINT_LOW_TEMP].x, hint_img_pos[HINT_LOW_TEMP].y, hint_img_pos[HINT_LOW_TEMP].img_addr);
}

void over_volt_hint_page(void)
{
    // 清除屏幕
	DispBlock(0, 0, ROW - 1, COL - 1);

    Dispphoto_Dispaly_flash(hint_img_pos[HINT_OVER_VOLT].x, hint_img_pos[HINT_OVER_VOLT].y, hint_img_pos[HINT_OVER_VOLT].img_addr);
}

void low_volt_hint_page(void)
{
    // 清除屏幕
	DispBlock(0, 0, ROW - 1, COL - 1);

    Dispphoto_Dispaly_flash(hint_img_pos[HINT_LOW_VOLT].x, hint_img_pos[HINT_LOW_VOLT].y, hint_img_pos[HINT_LOW_VOLT].img_addr);
}

void short_circuit_hint_page(void)
{
    // 清除屏幕
	DispBlock(0, 0, ROW - 1, COL - 1);

    Dispphoto_Dispaly_flash(hint_img_pos[HINT_SHORT_CIRCUIT].x, hint_img_pos[HINT_SHORT_CIRCUIT].y, hint_img_pos[HINT_SHORT_CIRCUIT].img_addr);
}

void over_current_hint_page(void)
{
    // 清除屏幕
	DispBlock(0, 0, ROW - 1, COL - 1);

    Dispphoto_Dispaly_flash(hint_img_pos[HINT_OVER_CURRENT].x, hint_img_pos[HINT_OVER_CURRENT].y, hint_img_pos[HINT_OVER_CURRENT].img_addr);
}
