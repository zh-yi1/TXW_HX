#include "hint_page.h"

typedef enum
{
	HINT_OVER_TEMP_IDLE = 0,  /* 静置过温保护 (对齐 CHG_STATE_IDLE) */
	HINT_OVER_TEMP_CHG  = 1,  /* 充电过温保护 (对齐 CHG_STATE_CHARGING) */
	HINT_OVER_TEMP_DSG  = 2,  /* 放电过温保护 (对齐 CHG_STATE_DISCHARGING) */
	HINT_SHORT_CIRCUIT,       /* 短路保护 */
	HINT_SAFEGUARD,			  /* 安全保护 */

	HINT_IMG_MAX,
} hint_img_e;

pos_and_addr_t hint_img_pos[] = {
	{80, 0, FLASH_ADDR_TEMP_ORANGE},       /* HINT_OVER_TEMP_IDLE */
	{80, 0, FLASH_ADDR_TEMP_ORANGE},       /* HINT_OVER_TEMP_CHG */
	{80, 0, FLASH_ADDR_TEMP_ORANGE},       /* HINT_OVER_TEMP_DSG */
	{80, 0, FLASH_ADDR_CIRCUIT_PROTECTION},/* HINT_SHORT_CIRCUIT */
	{80, 0, FLASH_ADDR_SAFE},			   /* HINT_SAFEGUARD */
};

pos_and_addr_t hint_text_img_pos[] = {
	{0, 80, FLASH_ADDR_NOAMAL_HIGH_TEMP_PRO},       /* HINT_OVER_TEMP_IDLE */
	{0, 80, FLASH_ADDR_CHARGE_HIGH_TEMP_PRO},       /* HINT_OVER_TEMP_CHG */
	{0, 80, FLASH_ADDR_DISCHARGE_HIGH_TEMP_PRO},    /* HINT_OVER_TEMP_DSG */
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
 *   标题 (0,0)     电压异常 / 温度异常, 240x32
 *   行1 (y=53)     "第n条，共m条" 整屏居中
 *                  第/条/共 各 18 宽, "，" 12 宽, 数字用 16 号字体
 *   行2 (y=77)     "时间：" + "YYYY-MM-DD" + 5px + "HH:MM", 整屏居中
 *   行3 (y=101)    电压页: "电压：" @31, 电压值 @75, 编号前 6 位 @132
 *                  温度页: 充电/放电/静置温度标签 (78x16) + 温度值, 整屏居中
 *   行4 (y=119)    电压页: 编号第 7 位起 @45
 *   无记录         "无异常记录" (124x20) @ (58,77), 标题仍按类型显示
 *
 *   两页的标题/行1/行2 完全一致, 只有行3 起分叉。文字统一 16 号字体。
 * ================================================================ */
#define ABN_CNT_Y       53     /* 行1: 第n条，共m条 */
#define ABN_TIME_Y      77     /* 行2: 时间 */
#define ABN_ROW3_Y      101    /* 行3: 电压 + 编号前6位 */
#define ABN_SN2_Y       119    /* 行4: 编号第7位起 */

#define ABN_W_DI        18     /* 第 */
#define ABN_W_TIAO      18     /* 条 */
#define ABN_W_GONG      18     /* 共 */
#define ABN_W_DOUHAO    12     /* ， */

#define ABN_LABEL_W     44     /* "时间："/"电压：" 标签宽 */
#define ABN_TIME_GAP    5      /* 日期与时分之间的间隔 */

#define ABN_VOLT_LBL_X  31     /* "电压：" 起点 */
#define ABN_VOLT_VAL_X  75     /* 电压值起点 (31+44) */
#define ABN_SN1_X       132    /* 编号前 6 位起点 */
#define ABN_SN2_X       45     /* 编号第 7 位起起点 */

#define ABN_TMP_W       78     /* 温度标签宽 */

#define ABN_NONE_X      58     /* 无异常记录 (124x20), 58 = 整屏居中 */
#define ABN_NONE_Y      77

void abnormal_hint_page(uint8_t  type,        /* 0=电压 1=温度                */
                                uint16_t index,       /* 第几条 (1-based)            */
                                uint16_t total,       /* 总条数                      */
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

	char     buf2[8];
	uint16_t w;

	/* 清屏 */
	DispBlock(0, 0, ROW - 1, COL - 1);

	/* 标题 (0,0) 240x32 */
	Dispphoto_Dispaly_flash(0, 0,
		(type == 0) ? FLASH_ADDR_VOLTAGE_ABNORMAL : FLASH_ADDR_TEMP_ABNORMAL);

	/* 无记录: 标题下方只显示"无异常记录" (124x20, 58 即整屏居中) */
	if (total == 0) {
		Dispphoto_Dispaly_flash(ABN_NONE_X, ABN_NONE_Y, FLASH_ADDR_NO_ABNORMAL);
		return;
	}

	/* ---- 行1 (y=53): "第n条，共m条" 整屏居中 ----
	   固定图 第/条/共 各 18, "，" 12, 共 5 张 = 84; 数字宽按字体表算 */
	p = 0;
	if (index >= 1000) { buf[p++] = '0' + index/1000; index %= 1000; }
	if (index >= 100 || p) { buf[p++] = '0' + index/100; index %= 100; }
	if (index >= 10 || p)  { buf[p++] = '0' + index/10;  index %= 10;  }
	buf[p++] = '0' + (uint8_t)index;
	buf[p] = '\0';

	p = 0;
	if (total >= 1000) { buf2[p++] = '0' + total/1000; total %= 1000; }
	if (total >= 100 || p) { buf2[p++] = '0' + total/100; total %= 100; }
	if (total >= 10 || p)  { buf2[p++] = '0' + total/10;  total %= 10;  }
	buf2[p++] = '0' + (uint8_t)total;
	buf2[p] = '\0';

	w = (uint16_t)(ABN_W_DI + ABN_W_TIAO + ABN_W_DOUHAO + ABN_W_GONG + ABN_W_TIAO)
	  + string_width_16(buf) + string_width_16(buf2);
	x = (w < ROW) ? (uint16_t)((ROW - w) / 2) : 0;

	Dispphoto_Dispaly_flash(x, ABN_CNT_Y, FLASH_ADDR_DI);        x += ABN_W_DI;
	display_string_16(buf, x, ABN_CNT_Y);                        x += string_width_16(buf);
	Dispphoto_Dispaly_flash(x, ABN_CNT_Y, FLASH_ADDR_TIAO);      x += ABN_W_TIAO;
	Dispphoto_Dispaly_flash(x, ABN_CNT_Y, FLASH_ADDR_DOUHAO);    x += ABN_W_DOUHAO;
	Dispphoto_Dispaly_flash(x, ABN_CNT_Y, FLASH_ADDR_GONG);      x += ABN_W_GONG;
	display_string_16(buf2, x, ABN_CNT_Y);                       x += string_width_16(buf2);
	Dispphoto_Dispaly_flash(x, ABN_CNT_Y, FLASH_ADDR_TIAO);

	/* ---- 行2 (y=77): "时间：YYYY-MM-DD HH:MM" 整屏居中, 日期与时分间隔 5px ---- */
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

	buf2[0] = '0' + hour/10;
	buf2[1] = '0' + hour%10;
	buf2[2] = ':';
	buf2[3] = '0' + min/10;
	buf2[4] = '0' + min%10;
	buf2[5] = '\0';

	w = (uint16_t)ABN_LABEL_W + string_width_16(buf) + ABN_TIME_GAP + string_width_16(buf2);
	x = (w < ROW) ? (uint16_t)((ROW - w) / 2) : 0;

	Dispphoto_Dispaly_flash(x, ABN_TIME_Y, FLASH_ADDR_ABNORMAL_TIME);
	x += ABN_LABEL_W;
	display_string_16(buf, x, ABN_TIME_Y);
	x += string_width_16(buf) + ABN_TIME_GAP;
	display_string_16(buf2, x, ABN_TIME_Y);

	/* ---- 行3/行4: 值标签 + 值 ---- */
	if (type == 0) {
		uint16_t v = value / 1000;         /* mV → V */
		uint8_t  k;

		/* "电压：" (31,101), 电压值 (75,101) */
		Dispphoto_Dispaly_flash(ABN_VOLT_LBL_X, ABN_ROW3_Y, FLASH_ADDR_ABNORMAL_V);

		p = 0;
		if (v >= 100) { buf[p++] = '0' + v/100; v %= 100; }
		if (v >= 10)  { buf[p++] = '0' + v/10;  v %= 10;  }
		buf[p++] = '0' + v;
		buf[p++] = '.';
		buf[p++] = '0' + (value % 1000) / 100;
		buf[p++] = '0' + (value % 100) / 10;
		buf[p++] = 'V';
		buf[p]   = '\0';
		display_string_16(buf, ABN_VOLT_VAL_X, ABN_ROW3_Y);

		/* 电芯编号: 前6位 (132,101), 第7位起换行 (45,119) */
		if (bat_num) {
			for (k = 0; k < 6 && bat_num[k]; k++)
				buf[k] = bat_num[k];
			buf[k] = '\0';
			display_string_16(buf, ABN_SN1_X, ABN_ROW3_Y);

			p = 0;
			k = 0;
			while (bat_num[k] && k < 6) k++;      /* 跳到第7位 (或串尾) */
			while (bat_num[k] && p < sizeof(buf) - 1)
				buf[p++] = bat_num[k++];
			buf[p] = '\0';
			display_string_16(buf, ABN_SN2_X, ABN_SN2_Y);
		}
	} else {
		/* 温度: 充电/放电/静置温度标签 (78x16) + 温度值, 标签与值一起整屏居中 */
		uint16_t t = value;
		uint32_t lbl;

		if (chg_state == CHG_STATE_CHARGING)
			lbl = FLASH_ADDR_CHARGE_TEMP;
		else if (chg_state == CHG_STATE_DISCHARGING)
			lbl = FLASH_ADDR_DISCHARGE_TEMP;
		else
			lbl = FLASH_ADDR_NOAMAL_TEMP;

		p = 0;
		if (t >= 100) { buf[p++] = '0' + t/100; t %= 100; }
		if (t >= 10)  { buf[p++] = '0' + t/10;  t %= 10;  }
		buf[p++] = '0' + t;
		buf[p++] = '^';   /* 度符号 */
		buf[p]   = '\0';

		w = (uint16_t)ABN_TMP_W + string_width_16(buf);
		x = (w < ROW) ? (uint16_t)((ROW - w) / 2) : 0;

		Dispphoto_Dispaly_flash(x, ABN_ROW3_Y, lbl);
		display_string_16(buf, x + ABN_TMP_W, ABN_ROW3_Y);
	}
}
