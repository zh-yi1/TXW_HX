#ifndef __BAT_SOC_H
#define __BAT_SOC_H

#include "global_define.h"


#define DISP_CYCLE_POS_MAX		(160)

//能量环半圆位置
#define DISP_CYCLE_HALF_BAT_NUM	(98)
#define DISP_CYCLE_HALF_POS_0	(148)
#define DISP_CYCLE_HALF_POS_1	(157)

//能量环尺寸
#define DISP_CYCLE_SIZE_X		(9)
#define DISP_CYCLE_SIZE_Y		(9)

//电量数字尺寸
#define DISP_BAT_NUM_SIZE_X		(39)
#define DISP_BAT_NUM_SIZE_Y		(59)

//电量百分号尺寸
#define DISP_BAT_PER_SIZE_X		(19)
#define DISP_BAT_PER_SIZE_Y		(19)

//电量百分号
#define DISP_BAT_NUM_PER_X		(168)
#define DISP_BAT_NUM_PER_Y		(126)

//电量个位
#define disp_bat_num_00x_X		(123)
#define disp_bat_num_00x_Y		(87)

//电量十位
#define disp_bat_num_0x0_X		(77)
#define disp_bat_num_0x0_Y		(87)

//电量百位
#define disp_bat_num_x00_X		(35)
#define disp_bat_num_x00_Y		(87)

/************ 功率 ***********/
//功率数字尺寸
#define DISP_WATT_NUM_SIZE_X	(10)
#define DISP_WATT_NUM_SIZE_Y	(16)

//功率小数点尺寸
#define DISP_WATT_POINT_SIZE_X	(2)
#define DISP_WATT_POINT_SIZE_Y	(2)

//功率W符号尺寸
#define DISP_WATT_FLAG_SIZE_X	(14)
#define DISP_WATT_FLAG_SIZE_Y	(9)

//功率端口符号尺寸
#define DISP_WATT_PORT_SIZE_X	(17)
#define DISP_WATT_PORT_SIZE_Y	(12)

//功率端口符号尺寸
#define DISP_WATT_DISCHG_SIZE_X	(8)
#define DISP_WATT_DISCHG_SIZE_Y	(8)

/********* C1 功率  *********/
//功率十分位
#define DISP_C1_WATT_00X_X		(85)
#define DISP_C1_WATT_00X_Y		(173)

//功率个位
#define DISP_C1_WATT_0X0_X		(67)
#define DISP_C1_WATT_0X0_Y		(173)

//功率十位
#define DISP_C1_WATT_X00_X		(55)
#define DISP_C1_WATT_X00_Y		(173)

//功率小数点
#define DISP_C1_WATT_POINT_X	(80)
#define DISP_C1_WATT_POINT_Y	(187)

//功率W符号
#define DISP_C1_WATT_CHAR_X		(97)
#define DISP_C1_WATT_CHAR_Y		(180)

//功率C1符号
#define DISP_C1_PORT_CHAR_X		(79)
#define DISP_C1_PORT_CHAR_Y		(197)

//功率三角符号
#define DISP_C1_DISCHG_CHAR_X	(98)
#define DISP_C1_DISCHG_CHAR_Y	(200)

/********* C2 功率  *********/
//功率十分位
#define DISP_C2_WATT_00X_X		(159)
#define DISP_C2_WATT_00X_Y		(173)

//功率个位
#define DISP_C2_WATT_0X0_X		(141)
#define DISP_C2_WATT_0X0_Y		(173)

//功率十位
#define DISP_C2_WATT_X00_X		(129)
#define DISP_C2_WATT_X00_Y		(173)

//功率小数点
#define DISP_C2_WATT_POINT_X	(155)
#define DISP_C2_WATT_POINT_Y	(187)

//功率W符号
#define DISP_C2_WATT_CHAR_X		(171)
#define DISP_C2_WATT_CHAR_Y		(180)

//功率C2符号
#define DISP_C2_PORT_CHAR_X		(130)
#define DISP_C2_PORT_CHAR_Y		(197)

//功率三角符号
#define DISP_C2_DISCHG_CHAR_X	(151)
#define DISP_C2_DISCHG_CHAR_Y	(200)



void ui_bat_soc(void);


#endif 
