#ifndef __UI_ARRAY_H
#define __UI_ARRAY_H

#include "global_define.h"

typedef struct
{
	uint8_t position_y;				//flash纵坐标
	uint8_t position_x;				//flash横坐标
	
	uint8_t bat_num_l;				//状态0阈值-电量下限
	uint8_t bat_num_h;				//状态1阈值-电量上限
	
	uint8_t pos_offset;				//地址偏移 - *200
}cycle_array_t;

typedef struct
{
	uint32_t flash_read_addr;		//flash地址

	uint8_t size_x;					//flash横向尺寸
	uint8_t size_y;					//flash纵向尺寸

	uint8_t position_x;				//flash横坐标
	uint8_t position_y;				//flash纵坐标
}flash_read_block_t;

extern const uint32_t 				off_time_offset_array[];
extern const uint32_t 				off_time_cn_offset_array[];

extern const flash_read_block_t		ui_black_array[];
extern const flash_read_block_t		prot_disp_array[];
extern const flash_read_block_t		soc_disp_array[];
extern const flash_read_block_t		soc_full_array[];
extern const flash_read_block_t		c1_watt_array[];
extern const flash_read_block_t		c1_logo_array[];
extern const flash_read_block_t		c2_watt_array[];
extern const flash_read_block_t		c2_logo_array[];
extern const flash_read_block_t		chg_time_array[];

extern const cycle_array_t 			cycle_pos_array[];
extern const flash_read_block_t		bat_num_array[];
extern const flash_read_block_t		bat_info_array[];
extern const flash_read_block_t		bat_temp_1_array[];
extern const flash_read_block_t		bat_temp_2_array[];
extern const flash_read_block_t		bat_temp_3_array[];
extern const flash_read_block_t		bat_temp_4_array[];
extern const flash_read_block_t		bat_temp_5_array[];
extern const flash_read_block_t		bat_temp_6_array[];
extern const flash_read_block_t		off_time_array[];
extern const flash_read_block_t		brightness_array[];
extern const flash_read_block_t		port_status_array[];
extern const flash_read_block_t		protect_array[];

extern const uint8_t length_ui_black;
extern const uint8_t length_prot_disp;
extern const uint8_t length_soc_disp;
extern const uint8_t length_soc_full;
extern const uint8_t length_c1_watt;
extern const uint8_t length_c1_logo;
extern const uint8_t length_c2_watt;
extern const uint8_t length_c2_logo;
extern const uint8_t length_chg_time;

extern const uint8_t length_bat_cycle;
extern const uint8_t length_bat_num;
extern const uint8_t length_bat_info;
extern const uint8_t length_bat_temp_1;
extern const uint8_t length_bat_temp_2;
extern const uint8_t length_bat_temp_3;
extern const uint8_t length_bat_temp_4;
extern const uint8_t length_bat_temp_5;
extern const uint8_t length_bat_temp_6;
extern const uint8_t length_off_time;
extern const uint8_t length_brightness;
extern const uint8_t length_port_status;
extern const uint8_t length_protect;


/******************************************** 中文界面 ******************************************/
extern const flash_read_block_t bat_info_cn_array[];
extern const flash_read_block_t off_time_cn_array[];
extern const flash_read_block_t brightness_cn_array[];
extern const flash_read_block_t port_status_cn_array[];
extern const flash_read_block_t protect_cn_array[];

extern const uint8_t length_bat_info_cn;
extern const uint8_t length_off_time_cn;
extern const uint8_t length_brightness_cn;
extern const uint8_t length_port_status_cn;
extern const uint8_t length_protect_cn;

#endif 
