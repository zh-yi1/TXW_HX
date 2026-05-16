#include "bat_info.h"

static void				ui_bat_info_draw					(void);
static void				ui_bat_info_normal_draw				(void);
static void				ui_bat_info_temp_draw				(void);
static void				ui_bat_info_base_draw				(const flash_read_block_t *flash_block, uint32_t flash_read_addr, uint8_t lenght_flash_block);
static uint32_t			disp_bat_info_flash_addr_get		(uint32_t flash_addr_base);
static uint32_t			disp_bat_temp_flash_addr_get		(void);

const uint8_t temp_f_transform[] = 
{
	0	, //-18
	1	, //-17
	3	, //-16
	5	, //-15
	7	, //-14
	9	, //-13
	10	, //-12
	12	, //-11
	14	, //-10
	16	, //-9
	18	, //-8
	19	, //-7
	21	, //-6
	23	, //-5
	25	, //-4
	27	, //-3
	28	, //-2
	30	, //-1
	32	, //0
	34	, //1
	36	, //2
	37	, //3
	39	, //4
	41	, //5
	43	, //6
	45	, //7
	46	, //8
	48	, //9
	50	, //10
	52	, //11
	54	, //12
	55	, //13
	57	, //14
	59	, //15
	61	, //16
	63	, //17
	64	, //18
	66	, //19
	68	, //20
	70	, //21
	72	, //22
	73	, //23
	75	, //24
	77	, //25
	79	, //26
	81	, //27
	82	, //28
	84	, //29
	86	, //30
	88	, //31
	90	, //32
	91	, //33
	93	, //34
	95	, //35
	97	, //36
	99	, //37
	100	, //38
	102	, //39
	104	, //40
	106	, //41
	108	, //42
	109	, //43
	111	, //44
	113	, //45
	115	, //46
	117	, //47
	118	, //48
	120	, //49
	122	, //50
	124	, //51
	126	, //52
	127	, //53
	129	, //54
	131	, //55
	133	, //56
	135	, //57
	136	, //58
	138	, //59
	140	, //60
	142	, //61
	144	, //62
	145	, //63
	147	, //64
	149	, //65
	151	, //66
	153	, //67
	154	, //68
	156	, //69
	158	, //70
	160	, //71
	162	, //72
	163	, //73
	165	, //74
	167	, //75
	169	, //76
	171	, //77
	172	, //78
	174	, //79
	176	, //80
};

void ui_bat_info(void)
{
	switch(ui_ctrl.disp_step)
	{
		case DISP_STEP_REFLASH:
			ui_ctrl.disp_step = DISP_STEP_DISP;
		
			ui_ctrl.disp_block = 0;
			ui_ctrl.disp_pos = 0;
		
			ui_ctrl.reflash_disp = 0;
			ui_ctrl.bat_info.disp_bat_info_step = 0;
		
			ui_ctrl.bat_info.bat_health = ui_ctrl.iic_data.bat_health_read;
			ui_ctrl.bat_info.bat_cycle = ui_ctrl.iic_data.bat_cycle_read;
			ui_ctrl.bat_info.bat_temp_c = ui_ctrl.iic_data.bat_temp_c_read;
			ui_ctrl.bat_info.bat_temp_f = temp_f_transform[ui_ctrl.bat_info.bat_temp_c + 18];
			break;
		
		case DISP_STEP_DISP:
			ui_bat_info_draw();
			break;
		
		case DISP_STEP_WAITCMD:
			if((ui_ctrl.bat_info.bat_health != ui_ctrl.iic_data.bat_health_read)
			||(ui_ctrl.bat_info.bat_cycle != ui_ctrl.iic_data.bat_cycle_read)
			||(ui_ctrl.bat_info.bat_temp_c != ui_ctrl.iic_data.bat_temp_c_read)
			)
			{
				ui_ctrl.bat_info.bat_health = ui_ctrl.iic_data.bat_health_read;
				ui_ctrl.bat_info.bat_cycle = ui_ctrl.iic_data.bat_cycle_read;
				ui_ctrl.bat_info.bat_temp_c = ui_ctrl.iic_data.bat_temp_c_read;
				ui_ctrl.bat_info.bat_temp_f = temp_f_transform[ui_ctrl.bat_info.bat_temp_c + 18];
				
				ui_ctrl.disp_step = DISP_STEP_DISP;
				ui_ctrl.bat_info.disp_bat_info_step = 0;
				ui_ctrl.reflash_disp = 1;
				ui_ctrl.disp_block = 1;
			}
			break;
		
		default:
			break;
	}
	
}

static void ui_bat_info_draw(void)
{
	switch(ui_ctrl.bat_info.disp_bat_info_step)
	{
		case 0:
		{
			ui_bat_info_normal_draw();
			break;
		}
		
		case 1:
		{
			ui_bat_info_temp_draw();
			break;
		}
		
		default:
		{
			ui_ctrl.bat_info.disp_bat_info_step = 0;
			break;
		}
	}
			
}

static void ui_bat_info_normal_draw(void)
{
	uint16_t send_buff_size = FLASH_READ_BUF_SIZE;
	uint16_t disp_pos_max = 0;
	uint32_t flash_read_addr = 0;
	
	uint16_t bat_health_x_offset = 0;
	uint8_t length_block = length_bat_info;

	if(ui_ctrl.iic_data.language_set)
		length_block = length_bat_info_cn;
	
	if(ui_ctrl.disp_block < length_block)
	{
		const flash_read_block_t *flash_block = bat_info_array + ui_ctrl.disp_block;

		if(ui_ctrl.iic_data.language_set)
			flash_block = bat_info_cn_array + ui_ctrl.disp_block;
		
		disp_pos_max = (flash_block->size_y * flash_block->size_x * 2 + READ_BUFFER_MAX - 1) / READ_BUFFER_MAX;

		if(ui_ctrl.disp_pos >= disp_pos_max)
		{
			if(spi_dma_send_ok)
			{
				ui_ctrl.disp_block += 1;

				ui_ctrl.disp_pos = 0;
			}
			return;
		}
		
		if(spi_dma_send_ok)
		{
			if(ui_ctrl.disp_pos == 0)
			{
				if(ui_ctrl.bat_info.bat_health < 100)
				{
					if(ui_ctrl.disp_block == 3 || ui_ctrl.disp_block == 4 || ui_ctrl.disp_block == 5)
						bat_health_x_offset = 12;
				}
				
				BlockWrite(flash_block->position_x - bat_health_x_offset, flash_block->position_x - bat_health_x_offset + flash_block->size_x - 1,\
							flash_block->position_y, flash_block->position_y + flash_block->size_y - 1);
			}
			
			flash_read_addr = disp_bat_info_flash_addr_get(flash_block->flash_read_addr);

			if(flash_block->flash_read_addr && flash_read_addr)
				flash_read_buf(flash_read_addr, spi_dma_buf, FLASH_READ_BUF_SIZE);
			else
				memset(spi_dma_buf, 0x0, FLASH_READ_BUF_SIZE);
			
			if(ui_ctrl.disp_pos == disp_pos_max - 1)
			{
				send_buff_size = flash_block->size_y * flash_block->size_x * 2 - ui_ctrl.disp_pos  * READ_BUFFER_MAX;
			}
			
			dma_send_enable(send_buff_size);
			
			spi_dma_send_ok = 0;
			ui_ctrl.disp_pos++;
		}
	}
	else
	{
//		ui_ctrl.disp_step = DISP_STEP_WAITCMD;
		ui_ctrl.bat_info.disp_bat_info_step += 1;
		ui_ctrl.disp_block = 0;
		ui_ctrl.disp_pos = 0;
	}
}

static uint32_t disp_bat_info_flash_addr_get(uint32_t flash_addr_base)
{
	uint32_t flash_addr_offset = 0;
	
	switch(ui_ctrl.disp_block)
	{
		case 2:
			if(ui_ctrl.bat_info.bat_health >= 100)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF;
			}
			else
			{
				return 0;
			}
			break;
		case 3:
			if(ui_ctrl.bat_info.bat_health < 100)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_health / 10);
			}
			break;
		case 4:
			if(ui_ctrl.bat_info.bat_health < 100)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_health % 10);
			}
			break;
			
		case 7:
			if(ui_ctrl.bat_info.bat_cycle >= 1000)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_cycle / 1000);
			}
			else if(ui_ctrl.bat_info.bat_cycle >= 100)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_cycle / 100);
			}
			else if(ui_ctrl.bat_info.bat_cycle >= 10)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_cycle / 10);
			}
			else
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * ui_ctrl.bat_info.bat_cycle;
			}
			break;
		case 8:
			if(ui_ctrl.bat_info.bat_cycle >= 1000)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_cycle / 100 % 10);
			}
			else if(ui_ctrl.bat_info.bat_cycle >= 100)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_cycle / 10 % 10);
			}
			else if(ui_ctrl.bat_info.bat_cycle >= 10)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_cycle % 10);
			}
			else
			{
				return 0;
			}
			break;
		case 9:
			if(ui_ctrl.bat_info.bat_cycle >= 1000)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_cycle % 100 / 10);
			}
			else if(ui_ctrl.bat_info.bat_cycle >= 100)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_cycle % 10);
			}
			else
			{
				return 0;
			}
			break;
		case 10:
			if(ui_ctrl.bat_info.bat_cycle >= 1000)
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_cycle % 10);
			else
				return 0;
			break;
			
		default:
			break;
	}
	
	return flash_addr_base + flash_addr_offset + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
	
}

static void ui_bat_info_temp_draw(void)
{
	const flash_read_block_t *flash_block = bat_temp_1_array + ui_ctrl.disp_block;
	uint8_t length_temp_flash = length_bat_temp_1;

	uint32_t flash_read_addr = 0;
	
	if(ui_ctrl.bat_info.bat_temp_c <= -13)
	{
		ui_ctrl.bat_info.bat_temp_state = 1;
		flash_block = bat_temp_1_array + ui_ctrl.disp_block;
		length_temp_flash = length_bat_temp_1;
	}
	else if(ui_ctrl.bat_info.bat_temp_c <= -10)
	{
		ui_ctrl.bat_info.bat_temp_state = 2;
		flash_block = bat_temp_2_array + ui_ctrl.disp_block;
		length_temp_flash = length_bat_temp_2;
	}
	else if(ui_ctrl.bat_info.bat_temp_c <= -1)
	{
		ui_ctrl.bat_info.bat_temp_state = 3;
		flash_block = bat_temp_3_array + ui_ctrl.disp_block;
		length_temp_flash = length_bat_temp_3;
	}
	else if(ui_ctrl.bat_info.bat_temp_c <= 9)
	{
		ui_ctrl.bat_info.bat_temp_state = 4;
		flash_block = bat_temp_4_array + ui_ctrl.disp_block;
		length_temp_flash = length_bat_temp_4;
	}
	else if(ui_ctrl.bat_info.bat_temp_c <= 37)
	{
		ui_ctrl.bat_info.bat_temp_state = 5;
		flash_block = bat_temp_5_array + ui_ctrl.disp_block;
		length_temp_flash = length_bat_temp_5;
	}
	else
	{
		ui_ctrl.bat_info.bat_temp_state = 6;
		flash_block = bat_temp_6_array + ui_ctrl.disp_block;
		length_temp_flash = length_bat_temp_6;
	}
	
	flash_read_addr = flash_block->flash_read_addr + disp_bat_temp_flash_addr_get() + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
	
	if(ui_ctrl.disp_block == 0)
		flash_read_addr = 0;
	
	ui_bat_info_base_draw(flash_block, flash_read_addr, length_temp_flash);
}

static uint32_t disp_bat_temp_flash_addr_get(void)
{
	uint32_t flash_addr_offset = 0;
	
	/*
		0	1	2	3	4	5	6	7	8	9
	1	空	-	十	个	℃	/	个	℉			 (-18~-13℃)
	2	空	-	十	个	℃	/	十	个	℉		 (-12~-10℃)
	3	空	-	个	℃	/	十	个	℉			 (-9~-1℃)
	4	空	个	℃	/	十	个	℉				 (0~-9℃)
	5	空	十	个	℃	/	十	个	℉			 (10~-37℃)
	6	空	十	个	℃	/	百	十	个	℉		 (37℃~80℃）
	*/
	
	switch(ui_ctrl.disp_block)
	{
		case 1:
		{
			if(ui_ctrl.bat_info.bat_temp_state >= 4)
			{
				if(ui_ctrl.bat_info.bat_temp_c >= 10)
				{
					flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_temp_c / 10);
				}
				else
				{
					flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_temp_c % 10);
				}
			}
			break;
		}
			
		case 2:
		{
			if(ui_ctrl.bat_info.bat_temp_state >= 5)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_temp_c % 10);
			}
			else if(ui_ctrl.bat_info.bat_temp_state <= 3)
			{
				if(ui_ctrl.bat_info.bat_temp_c <= -10)
				{
					flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * ((0-ui_ctrl.bat_info.bat_temp_c) / 10);
				}
				else
				{
					flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * ((0-ui_ctrl.bat_info.bat_temp_c) % 10);
				}
			}
			break;
		}
			
		case 3:
		{
			if(ui_ctrl.bat_info.bat_temp_state <= 2)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * ((0-ui_ctrl.bat_info.bat_temp_c) % 10);
			}
			break;
		}
			
		case 4:
		{
			if(ui_ctrl.bat_info.bat_temp_state == 4)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_temp_f / 10);
			}
			break;
		}
			
		case 5:
		{
			if(ui_ctrl.bat_info.bat_temp_state == 3 || ui_ctrl.bat_info.bat_temp_state == 5)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_temp_f / 10);
			}
			else if(ui_ctrl.bat_info.bat_temp_state == 4)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_temp_f % 10);
			}
			else if(ui_ctrl.bat_info.bat_temp_state == 6)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_temp_f / 100);
			}
			break;
		}
			
		case 6:
		{
			if(ui_ctrl.bat_info.bat_temp_state == 1)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * ui_ctrl.bat_info.bat_temp_f;
			}
			else if(ui_ctrl.bat_info.bat_temp_state == 3 || ui_ctrl.bat_info.bat_temp_state == 5)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_temp_f % 10);
			}
			else if(ui_ctrl.bat_info.bat_temp_state == 2)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_temp_f / 10);
			}
			else if(ui_ctrl.bat_info.bat_temp_state == 6)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_temp_f % 100 / 10);
			}
			break;
		}
			
		case 7:
		{
			if(ui_ctrl.bat_info.bat_temp_state == 2 || ui_ctrl.bat_info.bat_temp_state == 6)
			{
				flash_addr_offset = FLASH_ADDR_BAT_INFO_NUM_OFF * (ui_ctrl.bat_info.bat_temp_f % 10);
			}
			break;
		}
			
			
		default:
			break;
	}
	
	return flash_addr_offset;
	
}

static void ui_bat_info_base_draw(const flash_read_block_t *flash_block, uint32_t flash_read_addr, uint8_t lenght_flash_block)
{
	uint16_t send_buff_size = FLASH_READ_BUF_SIZE;
	uint16_t disp_pos_max = 0;
	
	if(ui_ctrl.disp_block < lenght_flash_block)
	{
		disp_pos_max = (flash_block->size_y * flash_block->size_x * 2 + READ_BUFFER_MAX - 1) / READ_BUFFER_MAX;

		if(ui_ctrl.disp_pos >= disp_pos_max)
		{
			if(spi_dma_send_ok)
			{
				ui_ctrl.disp_block += 1;
				ui_ctrl.disp_pos = 0;
			}
			return;
		}

		if(spi_dma_send_ok)
		{
			if(ui_ctrl.disp_pos == 0)
			{
				BlockWrite(flash_block->position_x, flash_block->position_x + flash_block->size_x - 1,\
							flash_block->position_y, flash_block->position_y + flash_block->size_y - 1);
			}
			
			if(flash_read_addr)
				flash_read_buf(flash_read_addr, spi_dma_buf, FLASH_READ_BUF_SIZE);
			else
				memset(spi_dma_buf, 0x0, FLASH_READ_BUF_SIZE);
			
			if(ui_ctrl.disp_pos == disp_pos_max - 1)
			{
				send_buff_size = flash_block->size_y * flash_block->size_x * 2 - ui_ctrl.disp_pos  * READ_BUFFER_MAX;
			}
			
			dma_send_enable(send_buff_size);
			
			spi_dma_send_ok = 0;
			ui_ctrl.disp_pos++;
		}
	}
	else
	{
		ui_ctrl.disp_step = DISP_STEP_WAITCMD;
	}
}
