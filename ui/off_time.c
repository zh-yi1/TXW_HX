#include "off_time.h"

static void				ui_off_time_draw					(void);

void ui_screen_off_time(void)
{
	switch(ui_ctrl.disp_step)
	{
		case DISP_STEP_REFLASH:
			ui_ctrl.disp_step = DISP_STEP_DISP;
		
			ui_ctrl.disp_block = 0;
			ui_ctrl.disp_pos = 0;
		
			ui_ctrl.reflash_disp = 0;
			ui_ctrl.off_time_level = ui_ctrl.iic_data.sys_status_read.screen_off_time;
			break;
		
		case DISP_STEP_DISP:
			ui_off_time_draw();
			break;
		
		case DISP_STEP_WAITCMD:
			if(ui_ctrl.off_time_level != ui_ctrl.iic_data.sys_status_read.screen_off_time)
			{
				ui_ctrl.off_time_level = ui_ctrl.iic_data.sys_status_read.screen_off_time;
				ui_ctrl.reflash_disp = 1;
				
				ui_ctrl.disp_step = DISP_STEP_DISP;
				ui_ctrl.disp_block = 1;
			}
			break;
		
		default:
			break;
	}
}

static void ui_off_time_draw(void)
{
	uint16_t send_buff_size = FLASH_READ_BUF_SIZE;
	uint16_t disp_pos_max = 0;
	uint32_t flash_read_addr = 0;
	int32_t flash_read_addr_offset = 0;

	uint8_t length_block = length_off_time;

	if(ui_ctrl.iic_data.language_set)
		length_block = length_off_time_cn;
	
	if(ui_ctrl.disp_block < length_block)
	{
		const flash_read_block_t *flash_block = off_time_array + ui_ctrl.disp_block;

		if(ui_ctrl.iic_data.language_set)
			flash_block = off_time_cn_array + ui_ctrl.disp_block;
		
		disp_pos_max = (flash_block->size_y * flash_block->size_x * 2 + READ_BUFFER_MAX - 1) / READ_BUFFER_MAX;

		if(ui_ctrl.disp_pos >= disp_pos_max)
		{
			if(spi_dma_send_ok)
			{
				ui_ctrl.disp_block += 1;
				
				if(ui_ctrl.reflash_disp && ui_ctrl.disp_block >= OT_REFLASH_POS)
					ui_ctrl.disp_block = length_block;

				ui_ctrl.disp_pos = 0;
			}
			return;
		}
		
//		if(spi_dma_send_ok || ui_ctrl.disp_pos == 0)
		if(spi_dma_send_ok)
		{
			if(ui_ctrl.disp_pos == 0)
			{
				BlockWrite(flash_block->position_x, flash_block->position_x + flash_block->size_x - 1,\
							flash_block->position_y, flash_block->position_y + flash_block->size_y - 1);
			}
			
			if(ui_ctrl.disp_block && ui_ctrl.disp_block < OT_REFLASH_POS)
			{
				if((ui_ctrl.disp_block - 1) % 4 == ui_ctrl.off_time_level)
				{
					if(ui_ctrl.disp_block < 5)
					{
						flash_read_addr_offset = FLASH_ADDR_BLOCK1_OFFSET;
					}
					else
					{
						if(ui_ctrl.iic_data.language_set)
							flash_read_addr_offset -= off_time_cn_offset_array[ui_ctrl.off_time_level];
						else
							flash_read_addr_offset = off_time_offset_array[ui_ctrl.off_time_level];
					}
				}
			}
			
			flash_read_addr = flash_block->flash_read_addr + flash_read_addr_offset + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
			
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
		ui_ctrl.disp_step = DISP_STEP_WAITCMD;
	}
}



