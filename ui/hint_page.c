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

/* ================================================================
 * 电压 / 温度异常信息页
 *
 * type=0 电压:  标签 (88,12)(21,52)(21,74)(21,92)
 *               (53,99) 显示 "X.XXV", (53,117) 显示电池编号
 * type=1 温度:  标签 TODO, (53,99) 显示 "XX.X", 无电池编号
 * ================================================================ */
void abnormal_hint_page(uint8_t  type,        /* 0=电压 1=温度                */
                                uint8_t  index,       /* 第几条 (1-based)            */
                                uint8_t  total,       /* 总条数                      */
                                uint32_t timestamp,   /* Unix 时间戳                 */
                                uint16_t value,       /* 电压 mV / 温度 ℃ (整度)     */
                                const char *bat_num)  /* 电池编号 (type=1 时忽略)     */
{
	uint16_t year;
	uint8_t  month, day, hour, min, sec;
	char     buf[20];
	uint8_t  p;

	/* 清屏 */
	DispBlock(0, 0, ROW - 1, COL - 1);

	
	Dispphoto_Dispaly_flash(88, 12, FLASH_ADDR_ABNORMAL_INF);   /* 异常信息 */

	if (type == 0) {	
		Dispphoto_Dispaly_flash(21, 52, FLASH_ADDR_VOLTAGE_PROTECTION);   /* 电压保护 */
		Dispphoto_Dispaly_flash(21, 74, FLASH_ADDR_ABNORMAL_TIME);   /* 时间 */
		Dispphoto_Dispaly_flash(21, 96, FLASH_ADDR_ABNORMAL_V);   /* 电压 */
	} else {
		Dispphoto_Dispaly_flash(21, 52, FLASH_ADDR_TMP_PROTECT);   /* 温度保护 */
		Dispphoto_Dispaly_flash(21, 74, FLASH_ADDR_ABNORMAL_TIME);   /* 时间 */
	}

	/* ---- (94,55) 第几条/总条数 "1/5" ---- */
	p = 0;
	if (index >= 100) { buf[p++] = '0' + index/100; index %= 100; }
	if (index >= 10)  { buf[p++] = '0' + index/10;  index %= 10;  }
	buf[p++] = '0' + index;
	buf[p++] = '/';
	if (total >= 100) { buf[p++] = '0' + total/100; total %= 100; }
	if (total >= 10)  { buf[p++] = '0' + total/10;  total %= 10;  }
	buf[p++] = '0' + total;
	buf[p] = '\0';
	display_string_16(buf, 94, 55, DIGIT_16_COLOR_BLUE);

	/* ---- (53,77) 日期 + 5px + 时间 ---- */
	rtc_unix_to_datetime(timestamp, &year, &month, &day, &hour, &min, &sec);

	buf[0] = '0' + year/1000; year %= 1000;
	buf[1] = '0' + year/100;  year %= 100;
	buf[2] = '0' + year/10;
	buf[3] = '0' + year%10;
	buf[4] = '-';
	buf[5] = '0' + month/10;
	buf[6] = '0' + month%10;
	buf[7] = '-';
	buf[8] = '0' + day/10;
	buf[9] = '0' + day%10;
	buf[10] = '\0';
	display_string_16(buf, 53, 77, DIGIT_16_COLOR_BLUE);
	p = 53 + string_width_16(buf, DIGIT_16_COLOR_BLUE) + 5;

	buf[0] = '0' + hour/10;
	buf[1] = '0' + hour%10;
	buf[2] = ':';
	buf[3] = '0' + min/10;
	buf[4] = '0' + min%10;
	buf[5] = '\0';
	display_string_16(buf, p, 77, DIGIT_16_COLOR_BLUE);

	/* ---- (53,99) 电压 "5.13V" / 温度 "35" ---- */
	if (type == 0) {
		uint16_t v  = value / 100;
		uint8_t  vp = 0;

		if (v >= 100) { buf[vp++] = '0' + v/100; v %= 100; }
		if (v >= 10)  { buf[vp++] = '0' + v/10;  v %= 10;  }
		buf[vp++] = '0' + v;
		buf[vp++] = '.';
		buf[vp++] = '0' + (value / 10) % 10;
		buf[vp++] = '0' + value % 10;
		buf[vp++] = 'V';
		buf[vp]   = '\0';
		display_string_16(buf, 53, 99, DIGIT_16_COLOR_BLUE);
	} else {
		/* 温度: 整度, '^' 作为度符号 */
		uint16_t t  = value;
		uint8_t  tp = 0;

		if (t >= 100) { buf[tp++] = '0' + t/100; t %= 100; }
		if (t >= 10)  { buf[tp++] = '0' + t/10;  t %= 10;  }
		buf[tp++] = '0' + t;
		buf[tp++] = '^';   /* 蓝色 Z_DEGREE 位图 */
		buf[tp]   = '\0';
		display_string_16(buf, 98, 99, DIGIT_16_COLOR_BLUE);
	}

	/* ---- (53,117) 电池编号 (仅电压) ---- */
	if (type == 0 && bat_num)
		display_string_16(bat_num, 53, 117, DIGIT_16_COLOR_BLUE);
}
