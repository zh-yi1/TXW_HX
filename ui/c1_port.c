#include "c1_port.h"

static void				ui_port_status_draw					(void);

void ui_c1_port_status(void)
{
	switch(ui_ctrl.disp_step)
	{
		case DISP_STEP_REFLASH:
			ui_ctrl.disp_step = DISP_STEP_DISP;
		
			ui_ctrl.disp_block = 0;
			ui_ctrl.disp_pos = 0;
		
			ui_ctrl.reflash_disp = 0;
			ui_ctrl.input_output_flag = ui_ctrl.iic_data.sys_status_read.port_c1_set;
			break;
		
		case DISP_STEP_DISP:
			ui_port_status_draw();
			break;
		
		case DISP_STEP_WAITCMD:
			if(ui_ctrl.input_output_flag != ui_ctrl.iic_data.sys_status_read.port_c1_set)
			{
				ui_ctrl.input_output_flag = ui_ctrl.iic_data.sys_status_read.port_c1_set;
				ui_ctrl.reflash_disp = 1;
				
				ui_ctrl.disp_step = DISP_STEP_DISP;
				ui_ctrl.disp_block = 1;
			}
			break;
		
		default:
			break;
	}
}


static void ui_port_status_draw(void)
{
	uint16_t send_buff_size = FLASH_READ_BUF_SIZE;
	uint16_t disp_pos_max = 0;
	uint32_t flash_read_addr = 0;
	uint32_t flash_read_addr_offset = 0;
	uint8_t length_block = length_port_status;

	if(ui_ctrl.iic_data.language_set)
		length_block = length_port_status_cn;
	
	if(ui_ctrl.disp_block < length_block)
	{
		const flash_read_block_t *flash_block = port_status_array + ui_ctrl.disp_block;

		if(ui_ctrl.iic_data.language_set)
			flash_block = port_status_cn_array + ui_ctrl.disp_block;
		
		disp_pos_max = (flash_block->size_y * flash_block->size_x * 2 + READ_BUFFER_MAX - 1) / READ_BUFFER_MAX;

		if(ui_ctrl.disp_pos >= disp_pos_max)
		{
			if(spi_dma_send_ok)
			{
				ui_ctrl.disp_block += 1;
				
				if(ui_ctrl.reflash_disp && ui_ctrl.disp_block >= PS_REFLASH_POS)
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

			if(ui_ctrl.disp_block < OT_REFLASH_POS)
			{
				if(ui_ctrl.input_output_flag)
				{
					if(ui_ctrl.disp_block == 2)
					{
						flash_read_addr_offset = FLASH_ADDR_BLOCK2_OFFSET;
					}
					else if(ui_ctrl.disp_block == 3)
					{
						flash_read_addr_offset = FLASH_ADDR_PORT_IO_OFFSET;

						if(ui_ctrl.iic_data.language_set)
							flash_read_addr_offset = FLASH_ADDR_CN_PORT_IO_OFFSET;
					}
				}
				else
				{
					if(ui_ctrl.disp_block == 1)
					{
						flash_read_addr_offset = FLASH_ADDR_BLOCK2_OFFSET;
					}
					else if(ui_ctrl.disp_block == 4)
					{
						flash_read_addr_offset = FLASH_ADDR_PORT_O_OFFSET;

						if(ui_ctrl.iic_data.language_set)
							flash_read_addr_offset = FLASH_ADDR_CN_PORT_O_OFFSET;
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

