#include "hint_page.h"

typedef enum
{
	HINT_OVER_TEMP_IDLE = 0,  /* 静置过温保护 (对齐 CHG_STATE_IDLE) */
	HINT_OVER_TEMP_CHG  = 1,  /* 充电过温保护 (对齐 CHG_STATE_CHARGING) */
	HINT_OVER_TEMP_DSG  = 2,  /* 放电过温保护 (对齐 CHG_STATE_DISCHARGING) */
	HINT_LOW_TEMP,            /* 低温保护 */
	HINT_SHORT_CIRCUIT,       /* 短路保护 */
	HINT_SAFEGUARD,			  /* 安全保护 */

	HINT_IMG_MAX,
} hint_img_e;

pos_and_addr_t hint_img_pos[] = {
	{80, 0, FLASH_ADDR_TEMP_ORANGE},       /* HINT_OVER_TEMP_IDLE */
	{80, 0, FLASH_ADDR_TEMP_ORANGE},       /* HINT_OVER_TEMP_CHG */
	{80, 0, FLASH_ADDR_TEMP_ORANGE},       /* HINT_OVER_TEMP_DSG */
	{80, 0, FLASH_ADDR_TEMP_BLUE},         /* HINT_LOW_TEMP */
	{80, 0, FLASH_ADDR_CIRCUIT_PROTECTION},/* HINT_SHORT_CIRCUIT */
	{80, 0, FLASH_ADDR_SAFE},			   /* HINT_SAFEGUARD */
};

pos_and_addr_t hint_text_img_pos[] = {
	{0, 80, FLASH_ADDR_NOAMAL_HIGH_TEMP_PRO},       /* HINT_OVER_TEMP_IDLE */
	{0, 80, FLASH_ADDR_CHARGE_HIGH_TEMP_PRO},       /* HINT_OVER_TEMP_CHG */
	{0, 80, FLASH_ADDR_DISCHARGE_HIGH_TEMP_PRO},    /* HINT_OVER_TEMP_DSG */
	{0, 80, FLASH_ADDR_LOW_TMP_TEXT},     			/* HINT_LOW_TEMP */
	{0, 80, FLASH_ADDR_CIRCUIT_PROTECTION_TEXT}, 	/* HINT_SHORT_CIRCUIT */
	{0, 80, FLASH_ADDR_SAFEGUARD}, 					/* HINT_SHORT_CIRCUIT */
};

/*
 * high_temp_pro — 过温保护提示页
 *
 *   type: HINT_OVER_TEMP_DSG (放电) / HINT_OVER_TEMP_CHG (充电) / HINT_OVER_TEMP_IDLE (静置)
 */
void high_temp_pro(uint8_t type)
{
	DispBlock(0, 0, ROW - 1, COL - 1);
	Dispphoto_Dispaly_flash(hint_img_pos[type].x, hint_img_pos[type].y, hint_img_pos[type].img_addr);
	Dispphoto_Dispaly_flash(hint_text_img_pos[type].x, hint_text_img_pos[type].y, hint_text_img_pos[type].img_addr);
	Dispphoto_Dispaly_flash(0, 116, FLASH_ADDR_TEMPERATURE_RECOVERY);
}

void low_temp_hint_page(void)
{
	DispBlock(0, 0, ROW - 1, COL - 1);
	Dispphoto_Dispaly_flash(hint_img_pos[HINT_LOW_TEMP].x, hint_img_pos[HINT_LOW_TEMP].y, hint_img_pos[HINT_LOW_TEMP].img_addr);
	Dispphoto_Dispaly_flash(hint_text_img_pos[HINT_LOW_TEMP].x, hint_text_img_pos[HINT_LOW_TEMP].y, hint_text_img_pos[HINT_LOW_TEMP].img_addr);
	Dispphoto_Dispaly_flash(0, 116, FLASH_ADDR_TEMPERATURE_RECOVERY);
}

/* 禁用提示页 — 全红 */
void disabled_hint_page(void)
{
	DispBlock(0, 0, ROW - 1, COL - 1);
	Dispphoto_Dispaly_flash(hint_img_pos[HINT_SAFEGUARD].x, hint_img_pos[HINT_SAFEGUARD].y, hint_img_pos[HINT_SAFEGUARD].img_addr);
	Dispphoto_Dispaly_flash(hint_text_img_pos[HINT_SAFEGUARD].x, hint_text_img_pos[HINT_SAFEGUARD].y, hint_text_img_pos[HINT_SAFEGUARD].img_addr);
}

void short_circuit_hint_page(void)
{
	DispBlock(0, 0, ROW - 1, COL - 1);
	Dispphoto_Dispaly_flash(hint_img_pos[HINT_SHORT_CIRCUIT].x, hint_img_pos[HINT_SHORT_CIRCUIT].y, hint_img_pos[HINT_SHORT_CIRCUIT].img_addr);
	Dispphoto_Dispaly_flash(hint_text_img_pos[HINT_SHORT_CIRCUIT].x, hint_text_img_pos[HINT_SHORT_CIRCUIT].y, hint_text_img_pos[HINT_SHORT_CIRCUIT].img_addr);
	Dispphoto_Dispaly_flash(0, 116, FLASH_ADDR_CIRCUIT_RECOVERY);
}

/* ================================================================
 * 电压 / 温度异常信息页
 *
 * 布局 (标签均左对齐 x=6, 后接文字隔 2px):
 *   异常信息  (80,6)
 *   行1 (6,47): 电压保护 / 温度保护 (82x16) + 条数 "index/total"
 *   行2 (6,73): 时间 (44x16) + "YYYY-MM-DD" + 5px + "HH:MM"
 *   行3 (6,99): 电压 (44x16) + "X.XXV" + 6px + 编号前6位
 *               / 充电·静置·放电温度 (78x16) + "XX^"
 *   行4:        电压时换行显示编号第7位起, x 对齐电压值
 *   无记录: (0,70) 无异常提示
 * ================================================================ */
#define ABN_LABEL_X     6      /* 标签左对齐 X */
#define ABN_GAP         0      /* 标签与后随文字间距 */
#define ABN_ROW1_Y      47
#define ABN_ROW2_Y      73
#define ABN_ROW3_Y      99
#define ABN_ROW4_Y      119    /* 行3 换行: 电芯编码 */
#define ABN_PROT_W      82     /* 电压保护 / 温度保护 宽 */
#define ABN_TIME_W      44     /* 时间标签宽 */
#define ABN_V_W         44     /* 电压标签宽 */
#define ABN_TMP_W       78     /* 温度标签宽 */

void abnormal_hint_page(uint8_t  type,        /* 0=电压 1=温度                */
                                uint8_t  index,       /* 第几条 (1-based)            */
                                uint8_t  total,       /* 总条数                      */
                                uint32_t timestamp,   /* Unix 时间戳                 */
                                uint16_t value,       /* 电压 mV / 温度 ℃ (整度)     */
                                const char *bat_num,  /* 电池编号 (type=1 时忽略)     */
                                uint8_t  chg_state)  /* 触发时的充放电状态           */
{
	uint16_t year;
	uint8_t  month, day, hour, min, sec;
	char     buf[20];
	uint8_t  p;
	uint16_t x;

	/* 清屏 */
	DispBlock(0, 0, ROW - 1, COL - 1);

	Dispphoto_Dispaly_flash(80, 6, FLASH_ADDR_ABNORMAL_INF);   /* 异常信息 (80,6) */

	/* 无记录时仅显示空状态提示 (居中: 122 宽, x=(240-122)/2=59, y=70) */
	if (total == 0) {
		Dispphoto_Dispaly_flash(59, 70,
			(type == 0) ? FLASH_ADDR_VOLTAGE_NO_ABNORMAL : FLASH_ADDR_TEMP_NO_ABNORMAL);
		return;
	}

	/* ---- 行1 (6,47): 保护标签 + 条数 "index/total" ---- */
	Dispphoto_Dispaly_flash(ABN_LABEL_X, ABN_ROW1_Y,
		(type == 0) ? FLASH_ADDR_VOLTAGE_PROTECTION : FLASH_ADDR_TMP_PROTECT);

	p = 0;
	if (index >= 100) { buf[p++] = '0' + index/100; index %= 100; }
	if (index >= 10)  { buf[p++] = '0' + index/10;  index %= 10;  }
	buf[p++] = '0' + index;
	buf[p++] = '/';
	if (total >= 100) { buf[p++] = '0' + total/100; total %= 100; }
	if (total >= 10)  { buf[p++] = '0' + total/10;  total %= 10;  }
	buf[p++] = '0' + total;
	buf[p] = '\0';
	display_string_16(buf, ABN_LABEL_X + ABN_PROT_W + ABN_GAP, ABN_ROW1_Y, DIGIT_16_COLOR_BLUE);

	/* ---- 行2 (6,73): 时间标签 + 日期 + 5px + 时间 ---- */
	Dispphoto_Dispaly_flash(ABN_LABEL_X, ABN_ROW2_Y, FLASH_ADDR_ABNORMAL_TIME);
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
	x = ABN_LABEL_X + ABN_TIME_W + ABN_GAP;
	display_string_16(buf, x, ABN_ROW2_Y, DIGIT_16_COLOR_BLUE);
	x += string_width_16(buf, DIGIT_16_COLOR_BLUE) + 5;

	buf[0] = '0' + hour/10;
	buf[1] = '0' + hour%10;
	buf[2] = ':';
	buf[3] = '0' + min/10;
	buf[4] = '0' + min%10;
	buf[5] = '\0';
	display_string_16(buf, x, ABN_ROW2_Y, DIGIT_16_COLOR_BLUE);

	/* ---- 行3 (6,99): 值标签 + 值 ---- */
	if (type == 0) {
		uint16_t v  = value / 1000;         /* mV → V */
		uint16_t vx;                        /* 电压值 x, 换行与之对齐 */
		uint8_t  k;

		Dispphoto_Dispaly_flash(ABN_LABEL_X, ABN_ROW3_Y, FLASH_ADDR_ABNORMAL_V);   /* 电压 */

		p = 0;
		if (v >= 100) { buf[p++] = '0' + v/100; v %= 100; }
		if (v >= 10)  { buf[p++] = '0' + v/10;  v %= 10;  }
		buf[p++] = '0' + v;
		buf[p++] = '.';
		buf[p++] = '0' + (value % 1000) / 100;
		buf[p++] = '0' + (value % 100) / 10;
		buf[p++] = 'V';
		buf[p]   = '\0';
		vx = ABN_LABEL_X + ABN_V_W + ABN_GAP;
		display_string_16(buf, vx, ABN_ROW3_Y, DIGIT_16_COLOR_BLUE);
		x = vx + string_width_16(buf, DIGIT_16_COLOR_BLUE) + 6;   /* 电压后 6px */

		/* 电芯编号: 前6位显示在电压后, 第7位起换行 (与电压值 x 对齐) */
		if (bat_num) {
			/* 第一行: 前6位 */
			for (k = 0; k < 6 && bat_num[k]; k++)
				buf[k] = bat_num[k];
			buf[k] = '\0';
			display_string_16(buf, x, ABN_ROW3_Y, DIGIT_16_COLOR_BLUE);

			/* 第二行: 第7位起 */
			p = 0;
			k = 0;
			while (bat_num[k] && k < 6) k++;      /* 跳到第7位 (或串尾) */
			while (bat_num[k] && p < sizeof(buf) - 1)
				buf[p++] = bat_num[k++];
			buf[p] = '\0';
			display_string_16(buf, vx, ABN_ROW4_Y, DIGIT_16_COLOR_BLUE);
		}
	} else {
		/* 温度: 充电/静置/放电温度标签 + "XX^" (整度, '^' 度符号) */
		uint16_t t  = value;
		uint32_t lbl;

		if (chg_state == CHG_STATE_CHARGING)
			lbl = FLASH_ADDR_CHARGE_HIGH_TEMP_INF;
		else if (chg_state == CHG_STATE_DISCHARGING)
			lbl = FLASH_ADDR_DISCHARGE_HIGH_TEMP_INF;
		else
			lbl = FLASH_ADDR_NOAMAL_HIGH_TEMP_INF;
		Dispphoto_Dispaly_flash(ABN_LABEL_X, ABN_ROW3_Y, lbl);

		p = 0;
		if (t >= 100) { buf[p++] = '0' + t/100; t %= 100; }
		if (t >= 10)  { buf[p++] = '0' + t/10;  t %= 10;  }
		buf[p++] = '0' + t;
		buf[p++] = '^';   /* 蓝色 Z_DEGREE 位图 */
		buf[p]   = '\0';
		display_string_16(buf, ABN_LABEL_X + ABN_TMP_W + ABN_GAP, ABN_ROW3_Y, DIGIT_16_COLOR_BLUE);
	}
}
