#include "ui_array.h"

const cycle_array_t	cycle_pos_array[] = 
{
	/* 位置X，位置Y，状态0阈值-电量下限，状态1阈值-电量上限, 地址偏移*/
 	{0  , 90 , 46 , 46 , 2  },		/*   0 */
	{0  , 100, 47 , 48 , 3  },		/*   1 */
	{0  , 110, 48 , 49 , 5  },		/*   2 */
	{0  , 120, 50 , 51 , 7  },		/*   3 */
	{0  , 130, 51 , 52 , 9  },		/*   4 */
	{0  , 140, 53 , 53 , 11 },		/*   5 */
	{10 , 60 , 42 , 42 , 12 },		/*   6 */
	{10 , 70 , 43 , 43 , 13 },		/*   7 */
	{10 , 80 , 44 , 45 , 14 },		/*   8 */
	{10 , 90 , 45 , 46 , 16 },		/*   9 */
	{10 , 100, 47 , 48 , 18 },		/*  10 */
	{10 , 110, 48 , 49 , 20 },		/*  11 */
	{10 , 120, 50 , 51 , 22 },		/*  12 */
	{10 , 130, 51 , 52 , 24 },		/*  13 */
	{10 , 140, 53 , 53 , 26 },		/*  14 */
	{10 , 150, 54 , 55 , 27 },		/*  15 */
	{10 , 160, 56 , 56 , 29 },		/*  16 */
	{10 , 170, 57 , 57 , 30 },		/*  17 */
	{20 , 50 , 40 , 40 , 31 },		/*  18 */
	{20 , 60 , 40 , 41 , 32 },		/*  19 */
	{20 , 70 , 42 , 43 , 34 },		/*  20 */
	{20 , 80 , 44 , 44 , 36 },		/*  21 */
	{20 , 90 , 45 , 45 , 37 },		/*  22 */
	{20 , 140, 54 , 54 , 38 },		/*  23 */
	{20 , 150, 55 , 55 , 39 },		/*  24 */
	{20 , 160, 56 , 57 , 40 },		/*  25 */
	{20 , 170, 57 , 58 , 42 },		/*  26 */
	{20 , 180, 59 , 59 , 44 },		/*  27 */
	{30 , 30 , 38 , 38 , 0  },		/*  28 */
	{30 , 40 , 38 , 38 , 45 },		/*  29 */
	{30 , 50 , 38 , 39 , 46 },		/*  30 */
	{30 , 60 , 40 , 41 , 48 },		/*  31 */
	{30 , 70 , 42 , 42 , 0  },		/*  32 */
	{30 , 160, 58 , 58 , 0  },		/*  33 */
	{30 , 170, 58 , 59 , 50 },		/*  34 */
	{30 , 180, 59 , 60 , 52 },		/*  35 */
	{30 , 190, 61 , 61 , 54 },		/*  36 */
	{30 , 200, 63 , 63 , 0  },		/*  37 */
	{40 , 30 , 36 , 36 , 55 },		/*  38 */
	{40 , 40 , 36 , 37 , 56 },		/*  39 */
	{40 , 50 , 38 , 38 , 58 },		/*  40 */
	{40 , 180, 61 , 61 , 59 },		/*  41 */
	{40 , 190, 61 , 62 , 60 },		/*  42 */
	{40 , 200, 63 , 63 , 62 },		/*  43 */
	{50 , 20 , 34 , 34 , 63 },		/*  44 */
	{50 , 30 , 34 , 35 , 64 },		/*  45 */
	{50 , 40 , 36 , 36 , 66 },		/*  46 */
	{50 , 190, 63 , 63 , 67 },		/*  47 */
	{50 , 200, 63 , 64 , 68 },		/*  48 */
	{50 , 210, 65 , 65 , 70 },		/*  49 */
	{60 , 10 , 32 , 32 , 71 },		/*  50 */
	{60 , 20 , 32 , 33 , 72 },		/*  51 */
	{60 , 30 , 33 , 34 , 74 },		/*  52 */
	{60 , 200, 65 , 66 , 76 },		/*  53 */
	{60 , 210, 65 , 66 , 78 },		/*  54 */
	{60 , 220, 68 , 68 , 0  },		/*  55 */
	{70 , 10 , 31 , 31 , 80 },		/*  56 */
	{70 , 20 , 31 , 32 , 81 },		/*  57 */
	{70 , 30 , 33 , 33 , 0  },		/*  58 */
	{70 , 200, 67 , 67 , 0  },		/*  59 */
	{70 , 210, 67 , 68 , 83 },		/*  60 */
	{70 , 220, 68 , 68 , 85 },		/*  61 */
	{80 , 10 , 29 , 30 , 86 },		/*  62 */
	{80 , 20 , 30 , 30 , 88 },		/*  63 */
	{80 , 210, 69 , 69 , 89 },		/*  64 */
	{80 , 220, 69 , 70 , 90 },		/*  65 */
	{90 , 0  , 28 , 28 , 92 },		/*  66 */
	{90 , 10 , 28 , 28 , 93 },		/*  67 */
	{90 , 20 , 29 , 29 , 94 },		/*  68 */
	{90 , 210, 70 , 71 , 95 },		/*  69 */
	{90 , 220, 70 , 71 , 97 },		/*  70 */
	{90 , 230, 72 , 72 , 0  },		/*  71 */
	{100, 0  , 26 , 27 , 99 },		/*  72 */
	{100, 10 , 26 , 27 , 101},		/*  73 */
	{100, 220, 72 , 73 , 103},		/*  74 */
	{100, 230, 72 , 73 , 105},		/*  75 */
	{110, 0  , 25 , 25 , 107},		/*  76 */
	{110, 10 , 25 , 26 , 108},		/*  77 */
	{110, 220, 73 , 74 , 110},		/*  78 */
	{110, 230, 73 , 74 , 112},		/*  79 */
	{120, 0  , 23 , 24 , 114},		/*  80 */
	{120, 10 , 23 , 24 , 116},		/*  81 */
	{120, 220, 75 , 76 , 118},		/*  82 */
	{120, 230, 75 , 76 , 120},		/*  83 */
	{130, 0  , 22 , 23 , 122},		/*  84 */
	{130, 10 , 22 , 23 , 124},		/*  85 */
	{130, 220, 76 , 77 , 126},		/*  86 */
	{130, 230, 76 , 77 , 128},		/*  87 */
	{140, 0  , 22 , 22 , 0  },		/*  88 */
	{140, 10 , 20 , 21 , 130},		/*  89 */
	{140, 20 , 20 , 21 , 132},		/*  90 */
	{140, 210, 79 , 79 , 134},		/*  91 */
	{140, 220, 78 , 78 , 135},		/*  92 */
	{140, 230, 78 , 78 , 136},		/*  93 */
	{150, 10 , 19 , 20 , 137},		/*  94 */
	{150, 20 , 19 , 19 , 139},		/*  95 */
	{150, 210, 80 , 80 , 140},		/*  96 */
	{150, 220, 79 , 80 , 141},		/*  97 */
	{160, 10 , 18 , 18 , 143},		/*  98 */
	{160, 20 , 17 , 18 , 144},		/*  99 */
	{160, 30 , 17 , 17 , 0  },		/* 100 */
	{160, 200, 83 , 83 , 0  },		/* 101 */
	{160, 210, 81 , 82 , 146},		/* 102 */
	{160, 220, 81 , 81 , 148},		/* 103 */
	{170, 10 , 18 , 18 , 0  },		/* 104 */
	{170, 20 , 15 , 16 , 149},		/* 105 */
	{170, 30 , 15 , 16 , 151},		/* 106 */
	{170, 200, 83 , 84 , 153},		/* 107 */
	{170, 210, 82 , 83 , 155},		/* 108 */
	{170, 220, 82 , 82 , 157},		/* 109 */
	{180, 20 , 15 , 15 , 158},		/* 110 */
	{180, 30 , 13 , 14 , 159},		/* 111 */
	{180, 40 , 13 , 13 , 161},		/* 112 */
	{180, 190, 86 , 86 , 162},		/* 113 */
	{180, 200, 84 , 85 , 163},		/* 114 */
	{180, 210, 84 , 84 , 165},		/* 115 */
	{190, 30 , 13 , 13 , 166},		/* 116 */
	{190, 40 , 11 , 12 , 167},		/* 117 */
	{190, 50 , 11 , 11 , 169},		/* 118 */
	{190, 180, 88 , 88 , 170},		/* 119 */
	{190, 190, 86 , 87 , 171},		/* 120 */
	{190, 200, 86 , 86 , 173},		/* 121 */
	{200, 30 , 13 , 13 , 0  },		/* 122 */
	{200, 40 , 11 , 11 , 174},		/* 123 */
	{200, 50 , 9  , 10 , 175},		/* 124 */
	{200, 60 , 8  , 9  , 177},		/* 125 */
	{200, 70 , 8  , 8  , 0  },		/* 126 */
	{200, 160, 92 , 92 , 0  },		/* 127 */
	{200, 170, 90 , 91 , 179},		/* 128 */
	{200, 180, 88 , 89 , 181},		/* 129 */
	{200, 190, 88 , 88 , 183},		/* 130 */
	{200, 200, 88 , 88 , 0  },		/* 131 */
	{210, 50 , 9  , 9  , 184},		/* 132 */
	{210, 60 , 7  , 8  , 185},		/* 133 */
	{210, 70 , 6  , 7  , 187},		/* 134 */
	{210, 80 , 5  , 5  , 189},		/* 135 */
	{210, 90 , 4  , 4  , 190},		/* 136 */
	{210, 140, 95 , 96 , 191},		/* 137 */
	{210, 150, 94 , 94 , 193},		/* 138 */
	{210, 160, 92 , 93 , 194},		/* 139 */
	{210, 170, 90 , 91 , 196},		/* 140 */
	{210, 180, 90 , 90 , 198},		/* 141 */
	{220, 60 , 7  , 7  , 199},		/* 142 */
	{220, 70 , 6  , 6  , 200},		/* 143 */
	{220, 80 , 4  , 5  , 201},		/* 144 */
	{220, 90 , 3  , 3  , 203},		/* 145 */
	{220, 100, 1  , 2  , 204},		/* 146 */
	{220, 110, 1  , 1  , 206},		/* 147 */
	{220, 120, 99 , 99 , 207},		/* 148 */
	{220, 130, 97 , 98 , 208},		/* 149 */
	{220, 140, 95 , 96 , 210},		/* 150 */
	{220, 150, 94 , 95 , 212},		/* 151 */
	{220, 160, 93 , 93 , 214},		/* 152 */
	{220, 170, 93 , 93 , 0  },		/* 153 */
	{230, 90 , 3  , 3  , 215},		/* 154 */
	{230, 100, 1  , 2  , 216},		/* 155 */
	{230, 110, 1  , 1  , 218},		/* 156 */
	{230, 120, 99 , 99 , 219},		/* 157 */
	{230, 130, 97 , 98 , 220},		/* 158 */
	{230, 140, 97 , 97 , 0  },		/* 159 */
};

const uint32_t off_time_offset_array[] =
{
	FLASH_ADDR_30S_OFFSET,
	FLASH_ADDR_1Min_OFFSET,
	FLASH_ADDR_5Min_OFFSET,
	FLASH_ADDR_30Min_OFFSET,
};

const flash_read_block_t bat_num_array[] = 
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */	
	{0							, 240 , 240 , 0   , 0  },		//用于刷新界面用
	
	{FLASH_ADDR_LOGO_PROT		, 25  , 30  , 207 , 7 },		//保护图标
	
	//电量百分比
	{FLASH_ADDR_BAT_NUM_0		, 40  , 60  , 38  , 86 },		//百位数
	{FLASH_ADDR_BAT_NUM_0		, 40  , 60  , 78  , 86 },		//十位数
	{FLASH_ADDR_BAT_NUM_0		, 40  , 60  , 123 , 86 },		//个位数
	{FLASH_ADDR_BAT_NUM_PER		, 20  , 20  , 168 , 126},		//百分号
	
	//C1 功率瓦数
	{FLASH_ADDR_WATT_FLAG		, 15  , 10  , 97  , 179},		//字母w
	{FLASH_ADDR_WATT_NUM_0		, 11  , 17  , 85  , 173},		//十分位
	{FLASH_ADDR_WATT_POINT		, 3   , 3   , 80  , 187},		//小数点
	{FLASH_ADDR_WATT_NUM_0		, 11  , 17  , 67  , 173},		//个位数
	{FLASH_ADDR_WATT_NUM_0		, 11  , 17  , 55  , 173},		//十位数
	
	//C1 LOGO
	{FLASH_ADDR_WATT_C1			, 18  , 13  , 79  , 197},		//字母 C1
	{FLASH_ADDR_WATT_DISCHG		, 9   , 11  , 98  , 198},		//放电图标

	//C2 功率瓦数
	{FLASH_ADDR_WATT_FLAG		, 15  , 10  , 171 , 179},		//字母w
	{FLASH_ADDR_WATT_NUM_0		, 11  , 17  , 159 , 173},		//十分位
	{FLASH_ADDR_WATT_POINT		, 3   , 3   , 155 , 187},		//小数点
	{FLASH_ADDR_WATT_NUM_0		, 11  , 17  , 141 , 173},		//个位数
	{FLASH_ADDR_WATT_NUM_0		, 11  , 17  , 129 , 173},		//十位数
	
	//C2 LOGO
	{FLASH_ADDR_WATT_C2			, 18  , 13  , 130 , 197},		//字母 C2
	{FLASH_ADDR_WATT_DISCHG		, 9   , 11  , 151 , 198},		//放电图标

	//充电时间
	{FLASH_ADDR_CHARGE_FLAG		, 10  , 16	, 73  , 151},		//闪电图标
	{FLASH_ADDR_TIME_NUM_0		, 7   , 10  , 91  , 153},		//十位数
	{FLASH_ADDR_TIME_NUM_0		, 7   , 10  , 99  , 153},		//个位数
	{FLASH_ADDR_TIME_H			, 9   , 10  , 107 , 153},		//字母H
	{FLASH_ADDR_TIME_NUM_0		, 7   , 10  , 125 , 153},		//十位数
	{FLASH_ADDR_TIME_NUM_0		, 7   , 10  , 133 , 153},		//个位数
	{FLASH_ADDR_TIME_M			, 10  , 10  , 141 , 153},		//字母M
};

const flash_read_block_t ui_black_array[] = 
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */	
	{0							, 240 , 240 , 0   , 0  },		//用于刷新界面用
};

const flash_read_block_t prot_disp_array[] = 
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */	
	{FLASH_ADDR_LOGO_PROT		, 25  , 30  , 207 , 7 },		//保护图标
};

const flash_read_block_t soc_disp_array[] =
{
	//电量百分比
	{0							, 150 , 60  , 50  , 86 },		//用于刷新界面用
	
	{0							, 40  , 60  , 38  , 86 },		//百位数
	{FLASH_ADDR_BAT_NUM_0		, 40  , 60  , 78  , 86 },		//十位数
	{FLASH_ADDR_BAT_NUM_0		, 40  , 60  , 123 , 86 },		//个位数
	{FLASH_ADDR_BAT_NUM_PER		, 20  , 20  , 168 , 126},		//百分号
};

const flash_read_block_t soc_full_array[] =
{
	//电量百分比
	{0							, 150 , 60  , 50  , 86 },		//用于刷新界面用

	{FLASH_ADDR_BAT_NUM_0		, 40  , 60  , 50  , 86 },		//百位数
	{FLASH_ADDR_BAT_NUM_0		, 40  , 60  , 90  , 86 },		//十位数
	{FLASH_ADDR_BAT_NUM_0		, 40  , 60  , 135 , 86 },		//个位数
	{FLASH_ADDR_BAT_NUM_PER		, 20  , 20  , 180 , 126},		//百分号
};

const flash_read_block_t c1_watt_array[] =
{
	//C1 功率瓦数
	{FLASH_ADDR_WATT_FLAG		, 15  , 10  , 97  , 179},		//字母w
	{FLASH_ADDR_WATT_NUM_0		, 11  , 17  , 85  , 173},		//十分位
	{FLASH_ADDR_WATT_POINT		, 3   , 3   , 80  , 187},		//小数点
	{FLASH_ADDR_WATT_NUM_0		, 11  , 17  , 67  , 173},		//个位数
	{FLASH_ADDR_WATT_NUM_0		, 11  , 17  , 55  , 173},		//十位数
};

const flash_read_block_t c1_logo_array[] =
{
	//C1 LOGO
	{FLASH_ADDR_WATT_C1			, 18  , 13  , 79  , 197},		//字母 C1
	{FLASH_ADDR_WATT_DISCHG		, 9   , 11  , 98  , 198},		//状态图标

};

const flash_read_block_t c2_watt_array[] =
{
	//C2 功率瓦数
	{FLASH_ADDR_WATT_FLAG		, 15  , 10  , 171 , 179},		//字母w
	{FLASH_ADDR_WATT_NUM_0		, 11  , 17  , 159 , 173},		//十分位
	{FLASH_ADDR_WATT_POINT		, 3   , 3   , 155 , 187},		//小数点
	{FLASH_ADDR_WATT_NUM_0		, 11  , 17  , 141 , 173},		//个位数
	{FLASH_ADDR_WATT_NUM_0		, 11  , 17  , 129 , 173},		//十位数
};

const flash_read_block_t c2_logo_array[] =
{
	//C2 LOGO
	{FLASH_ADDR_WATT_C2			, 18  , 13  , 130 , 197},		//字母 C2
	{FLASH_ADDR_WATT_DISCHG		, 9   , 11  , 151 , 198},		//状态图标
};

const flash_read_block_t chg_time_array[] =
{
	//充电时间
	{FLASH_ADDR_CHARGE_FLAG		, 10  , 16	, 73  , 151},		//闪电图标
	{FLASH_ADDR_TIME_NUM_0		, 7   , 10  , 91  , 153},		//十位数
	{FLASH_ADDR_TIME_NUM_0		, 7   , 10  , 99  , 153},		//个位数
	{FLASH_ADDR_TIME_H			, 9   , 10  , 107 , 153},		//字母H
	{FLASH_ADDR_TIME_NUM_0		, 7   , 10  , 125 , 153},		//十位数
	{FLASH_ADDR_TIME_NUM_0		, 7   , 10  , 133 , 153},		//个位数
	{FLASH_ADDR_TIME_M			, 10  , 10  , 141 , 153},		//字母M
};

const flash_read_block_t bat_info_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 240 , 240 , 0   , 0  },		//用于刷新界面用
	
	{0							, 51  , 17  , 24  , 74 },		//用于刷新界面用

	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 24  , 74 },		//百位数（如果小于100则是十位数）
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 36  , 74 },		//十位数（如果小于100则是个位数）
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 48  , 74 },		//个位数（如果小于100则不使用）
	{FLASH_ADDR_BAT_INFO_PER	, 15  , 16  , 60  , 75 },		//百分号 %（如果小于100则左移12px）
	
	{0							, 48  , 17  , 24  , 128},		//用于刷新界面用

	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 24  , 128},		//千位数（小于10）
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 36  , 128},		//百位数（小于100）
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 48  , 128},		//十位数（小于1000）
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 60  , 128},		//个位数（小于10000）

	/*19*/
	{FLASH_ADDR_TITLE_BATTERY	, 66  , 21  , 24  , 20 },		//Battery
	{FLASH_ADDR_TITLE_INFO		, 106 , 18  , 94  , 19 },		//Information
	{FLASH_ADDR_LONG			, 32  , 14  , 25  , 43 },		//Long
	{FLASH_ADDR_PRESS			, 37  , 11  , 63  , 43 },		//Press
	{FLASH_ADDR_TO				, 13  , 11  , 104 , 44 },		//to
	{FLASH_ADDR_WORD_ENTER		, 34  , 11  , 122 , 43 },		//Enter
	{FLASH_ADDR_SETTINGS		, 55  , 15  , 160 , 42 },		//Settings
	{FLASH_ADDR_WORD_BATTERY	, 48  , 14  , 25  , 97 },		//Battery
	{FLASH_ADDR_WORD_HEALTH		, 42  , 12  , 78  , 97 },		//Health
	{FLASH_ADDR_WORD_BATTERY	, 48  , 14  , 25  , 151},		//Battery
	{FLASH_ADDR_WORD_CYCLE		, 36  , 15  , 77  , 150},		//Cycle
	{FLASH_ADDR_WORD_BATTERY	, 48  , 14  , 25  , 205},		//Battery
	{FLASH_ADDR_WORD_TEMP		, 85  , 14  , 77  , 205},		//Temperature
};

const flash_read_block_t bat_temp_1_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 110 , 19  , 24  , 181},		//用于刷新界面用
	
	{FLASH_ADDR_BAT_INFO_NUM_N	, 8   , 5   , 24  , 189},		//负号
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 32  , 182},		//十位数
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 44  , 182},		//个位数
	{FLASH_ADDR_SYMBOL_C		, 19  , 18  , 56  , 181},		//摄氏度 ℃

	{FLASH_ADDR_SYMBOL_SLASH	, 10  , 18  , 76  , 182},		//斜杠
	
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 86 , 182},		//个位数
	{FLASH_ADDR_SYMBOL_F		, 20  , 18  , 98 , 182},		//华氏度 ℉
};

const flash_read_block_t bat_temp_2_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 110 , 19  , 24  , 181},		//用于刷新界面用
	
	{FLASH_ADDR_BAT_INFO_NUM_N	, 8   , 5   , 24  , 189},		//负号
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 32  , 182},		//十位数
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 44  , 182},		//个位数
	{FLASH_ADDR_SYMBOL_C		, 19  , 18  , 56  , 181},		//摄氏度 ℃

	{FLASH_ADDR_SYMBOL_SLASH	, 10  , 18  , 76  , 182},		//斜杠
	
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 86  , 182},		//十位数
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 98 , 182},		//个位数
	{FLASH_ADDR_SYMBOL_F		, 20  , 18  , 110 , 182},		//华氏度 ℉
};

const flash_read_block_t bat_temp_3_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 110 , 19  , 24  , 181},		//用于刷新界面用
	
	{FLASH_ADDR_BAT_INFO_NUM_N	, 8   , 5   , 24  , 189},		//负号
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 32  , 182},		//个位数
	{FLASH_ADDR_SYMBOL_C		, 19  , 18  , 44  , 181},		//摄氏度 ℃

	{FLASH_ADDR_SYMBOL_SLASH	, 10  , 18  , 64  , 182},		//斜杠
	
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 74  , 182},		//十位数
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 86 , 182},		//个位数
	{FLASH_ADDR_SYMBOL_F		, 20  , 18  , 98 , 182},		//华氏度 ℉
};

const flash_read_block_t bat_temp_4_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 110 , 19  , 24  , 181},		//用于刷新界面用
	
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 24  , 182},		//个位数
	{FLASH_ADDR_SYMBOL_C		, 19  , 18  , 36  , 181},		//摄氏度 ℃
	

	{FLASH_ADDR_SYMBOL_SLASH	, 10  , 18  , 56  , 182},		//斜杠
	
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 66  , 182},		//十位数
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 78 , 182},		//个位数
	{FLASH_ADDR_SYMBOL_F		, 20  , 18  , 90 , 182},		//华氏度 ℉
};

const flash_read_block_t bat_temp_5_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 110 , 19  , 24  , 181},		//用于刷新界面用
	
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 24  , 182},		//十位数
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 36  , 182},		//个位数
	{FLASH_ADDR_SYMBOL_C		, 19  , 18  , 48  , 181},		//摄氏度 ℃
	

	{FLASH_ADDR_SYMBOL_SLASH	, 10  , 18  , 68  , 182},		//斜杠
	
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 78  , 182},		//十位数
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 90 , 182},		//个位数
	{FLASH_ADDR_SYMBOL_F		, 20  , 18  , 102 , 182},		//华氏度 ℉
};

const flash_read_block_t bat_temp_6_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 110 , 19  , 24  , 181},		//用于刷新界面用
	
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 24  , 182},		//十位数
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 36  , 182},		//个位数
	{FLASH_ADDR_SYMBOL_C		, 19  , 18  , 48  , 181},		//摄氏度 ℃

	{FLASH_ADDR_SYMBOL_SLASH	, 10  , 18  , 68  , 182},		//斜杠
	
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 78  , 182},		//百位数
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 90  , 182},		//十位数
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 102 , 182},		//个位数
	{FLASH_ADDR_SYMBOL_F		, 20  , 18  , 114 , 182},		//华氏度 ℉
};

const flash_read_block_t off_time_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 240 , 240 , 0   , 0  },		//用于刷新界面用
	
	{FLASH_ADDR_BLACK_BLOCK1	, 88  , 45  , 27  , 75 },		//黑块1 位置1
	{FLASH_ADDR_BLACK_BLOCK1	, 88  , 45  , 125 , 75 },		//黑块1 位置2
	{FLASH_ADDR_BLACK_BLOCK1	, 88  , 45  , 27  , 137},		//黑块1 位置3
	{FLASH_ADDR_BLACK_BLOCK1	, 88  , 45  , 125 , 137},		//黑块1 位置4
	
	{FLASH_ADDR_30S_BLACK		, 32  , 15  , 55  , 90 },		//30S
	{FLASH_ADDR_1Min_BLACK		, 48  , 16  , 145 , 89 },		//1Min
	{FLASH_ADDR_5Min_BLACK		, 49  , 16  , 47  , 151},		//5Min
	{FLASH_ADDR_30Min_BLACK		, 60  , 16  , 139 , 151},		//30Min

	{FLASH_ADDR_TITLE_SCREEN	, 62  , 17  , 24  , 20 },		//Screen
	{FLASH_ADDR_TITLE_OFF		, 29  , 18  , 91  , 19 },		//Off
	{FLASH_ADDR_TITLE_TIME		, 46  , 18  , 123 , 19 },		//Time
	{FLASH_ADDR_PRESS			, 37  , 11  , 25  , 43 },		//Press
	{FLASH_ADDR_TWICE			, 35  , 12  , 66  , 43 },		//twice
	{FLASH_ADDR_TO				, 13  , 11  , 106 , 44 },		//to
	{FLASH_ADDR_SWITCH			, 43  , 13  , 123 , 42 },		//switch
	{FLASH_ADDR_LONG			, 32  , 14  , 23  , 206},		//Long
	{FLASH_ADDR_PRESS			, 37  , 11  , 62  , 206},		//Press
	{FLASH_ADDR_TO				, 13  , 11  , 104 , 206},		//to
	{FLASH_ADDR_EXIT			, 24  , 12  , 121 , 205},		//Exit
	{FLASH_ADDR_SETTINGS		, 55  , 15  , 150 , 205},		//Settings
};

const flash_read_block_t brightness_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 240 , 240 , 0   , 0  },		//用于刷新界面用
	
	{FLASH_ADDR_BLACK_BLOCK2	, 186 , 45  , 25  , 75 },		//黑块2 位置1
	{FLASH_ADDR_BLACK_BLOCK2	, 186 , 45  , 25  , 137},		//黑块2 位置2

	{FLASH_ADDR_BN_H_BLACK		, 41  , 20  , 98  , 87 },		//High
	{FLASH_ADDR_BN_L_BLACK		, 36  , 16  , 100 , 151},		//Low
	
	{FLASH_ADDR_TITLE_SCREEN	, 62  , 17  , 24  , 20 },		//Screen
	{FLASH_ADDR_TITLE_BRIGHTNESS, 97  , 22  , 91  , 19 },		//Brightness
	{FLASH_ADDR_PRESS			, 37  , 11  , 25  , 43 },		//Press
	{FLASH_ADDR_TWICE			, 35  , 12  , 66  , 43 },		//twice
	{FLASH_ADDR_TO				, 13  , 11  , 106 , 44 },		//to
	{FLASH_ADDR_SWITCH			, 43  , 13  , 123 , 42 },		//switch
	{FLASH_ADDR_LONG			, 32  , 14  , 23  , 206},		//Long
	{FLASH_ADDR_PRESS			, 37  , 11  , 62  , 206},		//Press
	{FLASH_ADDR_TO				, 13  , 11  , 104 , 206},		//to
	{FLASH_ADDR_EXIT			, 24  , 12  , 121 , 205},		//Exit
	{FLASH_ADDR_SETTINGS		, 55  , 15  , 150 , 205},		//Settings
};

const flash_read_block_t port_status_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 240 , 240 , 0   , 0  },		//用于刷新界面用
	
	{FLASH_ADDR_BLACK_BLOCK2	, 186 , 45  , 25  , 75 },		//黑块2 位置1
	{FLASH_ADDR_BLACK_BLOCK2	, 186 , 45  , 25  , 137 },		//黑块2 位置2
	
	{FLASH_ADDR_PORT_IO_BLACK	, 152 , 20  , 42  , 87 },		//Input and Output
	{FLASH_ADDR_PORT_O_BLACK	, 107 , 21  , 65  , 151},		//Output Only
	
	{FLASH_ADDR_TITLE_C1   		, 23  , 17  , 24  , 20 },		//C1
	{FLASH_ADDR_TITLE_PORT 		, 38  , 17  , 54  , 20 },		//Port
	{FLASH_ADDR_TITLE_STATUS	, 59  , 17  , 97  , 20 },		//Status
	{FLASH_ADDR_PRESS			, 37  , 11  , 25  , 43 },		//Press
	{FLASH_ADDR_TWICE			, 35  , 12  , 66  , 43 },		//twice
	{FLASH_ADDR_TO				, 13  , 11  , 106 , 44 },		//to
	{FLASH_ADDR_SWITCH			, 43  , 13  , 123 , 42 },		//switch
	{FLASH_ADDR_LONG			, 32  , 14  , 23  , 206},		//Long
	{FLASH_ADDR_PRESS			, 37  , 11  , 62  , 206},		//Press
	{FLASH_ADDR_TO				, 13  , 11  , 104 , 206},		//to
	{FLASH_ADDR_EXIT			, 24  , 12  , 121 , 205},		//Exit
	{FLASH_ADDR_SETTINGS		, 55  , 15  , 150 , 205},		//Settings
};

const flash_read_block_t protect_array[] =
{
	/* FLASH地址，		尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 240 , 240 , 0   , 0  },		//用于刷新界面用
	
	{FLASH_ADDR_LOGO			, 80  , 80  , 80  , 45 },		//保护LOGO
	{FLASH_ADDR_WORD_1			, 43  , 15  , 32  , 151},		//Circuit
	{FLASH_ADDR_WORD_2			, 67  , 15  , 80  , 151},		//protection
	{FLASH_ADDR_WORD_3			, 56  , 15  , 152 , 151},		//enabled.
	{FLASH_ADDR_WORD_4			, 44  , 15  , 36  , 171},		//Please
	{FLASH_ADDR_WORD_5			, 45  , 15  , 85  , 171},		//unplug
	{FLASH_ADDR_WORD_6			, 24  , 15  , 135 , 171},		//and
	{FLASH_ADDR_WORD_7			, 41  , 15  , 164 , 171},		//replug
	{FLASH_ADDR_WORD_8			, 21  , 12  , 84  , 191},		//the
	{FLASH_ADDR_WORD_9			, 46  , 12  , 110 , 191},		//device.
};

const uint8_t length_ui_black		= sizeof(ui_black_array)	/ sizeof(ui_black_array[0]);
const uint8_t length_prot_disp		= sizeof(prot_disp_array)	/ sizeof(prot_disp_array[0]);
const uint8_t length_soc_disp		= sizeof(soc_disp_array)	/ sizeof(soc_disp_array[0]);
const uint8_t length_soc_full		= sizeof(soc_full_array)	/ sizeof(soc_full_array[0]);
const uint8_t length_c1_watt		= sizeof(c1_watt_array)		/ sizeof(c1_watt_array[0]);
const uint8_t length_c1_logo		= sizeof(c1_logo_array)		/ sizeof(c1_logo_array[0]);
const uint8_t length_c2_watt		= sizeof(c2_watt_array)		/ sizeof(c2_watt_array[0]);
const uint8_t length_c2_logo		= sizeof(c2_logo_array)		/ sizeof(c2_logo_array[0]);
const uint8_t length_chg_time		= sizeof(chg_time_array)	/ sizeof(chg_time_array[0]);

const uint8_t length_bat_cycle		= sizeof(cycle_pos_array)	/ sizeof(cycle_pos_array[0]);
const uint8_t length_bat_num		= sizeof(bat_num_array)		/ sizeof(bat_num_array[0]);
const uint8_t length_bat_info		= sizeof(bat_info_array)	/ sizeof(bat_info_array[0]);
const uint8_t length_bat_temp_1		= sizeof(bat_temp_1_array)	/ sizeof(bat_temp_1_array[0]);
const uint8_t length_bat_temp_2		= sizeof(bat_temp_2_array)	/ sizeof(bat_temp_2_array[0]);
const uint8_t length_bat_temp_3		= sizeof(bat_temp_3_array)	/ sizeof(bat_temp_3_array[0]);
const uint8_t length_bat_temp_4		= sizeof(bat_temp_4_array)	/ sizeof(bat_temp_4_array[0]);
const uint8_t length_bat_temp_5		= sizeof(bat_temp_5_array)	/ sizeof(bat_temp_5_array[0]);
const uint8_t length_bat_temp_6		= sizeof(bat_temp_6_array)	/ sizeof(bat_temp_6_array[0]);
const uint8_t length_off_time		= sizeof(off_time_array)	/ sizeof(off_time_array[0]);
const uint8_t length_brightness		= sizeof(brightness_array)	/ sizeof(brightness_array[0]);
const uint8_t length_port_status	= sizeof(port_status_array) / sizeof(port_status_array[0]);
const uint8_t length_protect		= sizeof(protect_array)		/ sizeof(protect_array[0]);

/******************************************** 中文界面 ******************************************/
const uint32_t off_time_cn_offset_array[] =
{
	FLASH_ADDR_CN_30S_OFFSET,
	FLASH_ADDR_CN_1Min_OFFSET,
	FLASH_ADDR_CN_5Min_OFFSET,
	FLASH_ADDR_CN_30Min_OFFSET,
};

const flash_read_block_t bat_info_cn_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 240 , 240 , 0   , 0  },		//用于刷新界面用
	
	{0							, 51  , 17  , 24  , 74 },		//用于刷新界面用

	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 24  , 74 },		//百位数（如果小于100则是十位数）
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 36  , 74 },		//十位数（如果小于100则是个位数）
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 48  , 74 },		//个位数（如果小于100则不使用）
	{FLASH_ADDR_BAT_INFO_PER	, 15  , 16  , 60  , 75 },		//百分号 %（如果小于100则左移12px）
	
	{0							, 48  , 17  , 24  , 128},		//用于刷新界面用

	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 24  , 128},		//千位数（小于10）
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 36  , 128},		//百位数（小于100）
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 48  , 128},		//十位数（小于1000）
	{FLASH_ADDR_BAT_INFO_NUM0	, 12  , 17  , 60  , 128},		//个位数（小于10000）

	{FLASH_ADDR_CN_BAT_INFO		, 79  , 20  , 25  , 18 },		//电池信息
	{FLASH_ADDR_CN_LONG_PRESS	, 30  , 15  , 24  , 41 },		//长按
	{FLASH_ADDR_CN_ENTER		, 30  , 15  , 54  , 41 },		//进入
	{FLASH_ADDR_CN_SETTING		, 30  , 15  , 84  , 41 },		//设置

	{FLASH_ADDR_CN_BATTERY		, 30  , 15  , 24  , 95 },		//电池
	{FLASH_ADDR_CN_HEALTH		, 45  , 15  , 54  , 95 },		//健康度
	
	{FLASH_ADDR_CN_BATTERY		, 30  , 15  , 24  , 149},		//电池
	{FLASH_ADDR_CN_CYCLE		, 60  , 15  , 54  , 149},		//健循环次数
	
	{FLASH_ADDR_CN_BATTERY		, 30  , 15  , 24  , 203},		//电池
	{FLASH_ADDR_CN_TEMP			, 30  , 15  , 54  , 203},		//温度
};

const flash_read_block_t off_time_cn_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 240 , 240 , 0   , 0  },		//用于刷新界面用
	
	{FLASH_ADDR_BLACK_BLOCK1	, 88  , 45  , 27  , 75 },		//黑块1 位置1
	{FLASH_ADDR_BLACK_BLOCK1	, 88  , 45  , 125 , 75 },		//黑块1 位置2
	{FLASH_ADDR_BLACK_BLOCK1	, 88  , 45  , 27  , 137},		//黑块1 位置3
	{FLASH_ADDR_BLACK_BLOCK1	, 88  , 45  , 125 , 137},		//黑块1 位置4
	
	{FLASH_ADDR_CN_30S_WHITE	, 42  , 20  , 50  , 87 },		//30S
	{FLASH_ADDR_CN_1Min_WHITE	, 54  , 20  , 142 , 87 },		//1Min
	{FLASH_ADDR_CN_5Min_WHITE	, 55  , 20  , 43  , 149},		//5Min
	{FLASH_ADDR_CN_30Min_WHITE	, 67  , 20  , 135 , 149},		//30Min

	{FLASH_ADDR_CN_SRCEEN_OFF	, 80  , 20  , 80  , 18 },		//熄屏时间
	{FLASH_ADDR_CN_KEY_SWITCH	, 60  , 15  , 90  , 41 },		//双击切换
	{FLASH_ADDR_CN_LONG_PRESS	, 30  , 15  , 75  , 203},		//长按
	{FLASH_ADDR_CN_EXIT			, 30  , 15  , 105 , 203},		//退出
	{FLASH_ADDR_CN_SETTING		, 30  , 15  , 135 , 203},		//设置
};

const flash_read_block_t brightness_cn_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 240 , 240 , 0   , 0  },		//用于刷新界面用
	
	{FLASH_ADDR_BLACK_BLOCK2	, 186 , 45  , 25  , 75 },		//黑块2 位置1
	{FLASH_ADDR_BLACK_BLOCK2	, 186 , 45  , 25  , 137},		//黑块2 位置2

	{FLASH_ADDR_CN_BN_H_BLACK	, 20  , 20  , 108 , 85 },		//High
	{FLASH_ADDR_CN_BN_L_BLACK	, 20  , 20  , 108 , 149},		//Low
	
	{FLASH_ADDR_CN_SRCEEN_BRIGHT, 80  , 20  , 80  , 18 },		//屏幕亮度
	{FLASH_ADDR_CN_KEY_SWITCH	, 60  , 15  , 90  , 41 },		//双击切换
	{FLASH_ADDR_CN_LONG_PRESS	, 30  , 15  , 75  , 203},		//长按
	{FLASH_ADDR_CN_EXIT			, 30  , 15  , 105 , 203},		//退出
	{FLASH_ADDR_CN_SETTING		, 30  , 15  , 135 , 203},		//设置
};

const flash_read_block_t port_status_cn_array[] =
{
	/* FLASH地址，				尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 240 , 240 , 0   , 0  },		//用于刷新界面用
	
	{FLASH_ADDR_BLACK_BLOCK2	, 186 , 45  , 25  , 75 },		//黑块2 位置1
	{FLASH_ADDR_BLACK_BLOCK2	, 186 , 45  , 25  , 137 },		//黑块2 位置2
	
	{FLASH_ADDR_CN_PORT_IO_BLACK, 97  , 20  , 69  , 85 },		//Input and Output
	{FLASH_ADDR_CN_PORT_O_BLACK	, 57  , 20  , 89  , 148},		//Output Only
	
	{FLASH_ADDR_CN_TITLE_C1   	, 22  , 20  , 68  , 18 },		//C1
	{FLASH_ADDR_CN_PORT_STATUS 	, 80  , 20  , 92  , 18 },		//接口状态
	{FLASH_ADDR_CN_KEY_SWITCH	, 60  , 15  , 90  , 41 },		//双击切换
	{FLASH_ADDR_CN_LONG_PRESS	, 30  , 15  , 75  , 203},		//长按
	{FLASH_ADDR_CN_EXIT			, 30  , 15  , 105 , 203},		//退出
	{FLASH_ADDR_CN_SETTING		, 30  , 15  , 135 , 203},		//设置
};

const flash_read_block_t protect_cn_array[] =
{
	/* FLASH地址，		尺寸X, 尺寸Y, 位置X，位置Y */
	{0							, 240 , 240 , 0   , 0  },		//用于刷新界面用
	
	{FLASH_ADDR_LOGO			, 80  , 80  , 80  , 45 },		//保护LOGO
	{FLASH_ADDR_CN_WORD_1		, 105 , 15  , 68  , 150},
	{FLASH_ADDR_CN_WORD_2		, 150 , 15  , 45  , 170},
};

const uint8_t length_bat_info_cn	= sizeof(bat_info_cn_array)		/ sizeof(bat_info_cn_array[0]);
const uint8_t length_off_time_cn	= sizeof(off_time_cn_array)		/ sizeof(off_time_cn_array[0]);
const uint8_t length_brightness_cn	= sizeof(brightness_cn_array)	/ sizeof(brightness_cn_array[0]);
const uint8_t length_port_status_cn	= sizeof(port_status_cn_array)	/ sizeof(port_status_cn_array[0]);
const uint8_t length_protect_cn		= sizeof(protect_cn_array)		/ sizeof(protect_cn_array[0]);






