#include "bat_soc.h"

static void			ui_bat_soc_updata				(void);
static void			ui_bat_soc_draw					(void);

static void			ui_bat_num_base_draw			(const flash_read_block_t *flash_block, uint32_t flash_read_addr, uint8_t lenght_flash_block);

static void 		ui_bat_num_black_draw			(void);
static void 		ui_bat_num_protect_draw			(void);
static void 		ui_bat_num_draw					(void);
static void 		ui_bat_num_c1_watt_draw			(void);
static void 		ui_bat_num_c1_logo_draw			(void);
static void 		ui_bat_num_c2_watt_draw			(void);
static void 		ui_bat_num_c2_logo_draw			(void);
static void 		ui_bat_num_chg_time_draw		(void);
static void 		ui_bat_cycle_draw				(void);

static uint32_t 	disp_cycle_flash_addr_get		(uint8_t cycle_pos, uint8_t bat_num);


void ui_bat_soc(void)
{
	switch(ui_ctrl.disp_step)
	{
		case DISP_STEP_REFLASH:
			ui_bat_soc_updata();
			ui_ctrl.bat_soc.disp_bat_num_state = 0;
			break;
		
		case DISP_STEP_DISP:
			ui_bat_soc_draw();
			break;
		
		case DISP_STEP_WAITCMD:
			ui_bat_soc_updata();
			break;
		
		default:
			break;
	}
}

static void ui_bat_soc_updata(void)
{
	if((ui_ctrl.bat_soc.disp_bat_num == ui_ctrl.iic_data.disp_bat_num_read)
		&&(ui_ctrl.bat_soc.port_c1_watt == ui_ctrl.iic_data.port_c1_watt_read)
		&&(ui_ctrl.bat_soc.port_c2_watt == ui_ctrl.iic_data.port_c2_watt_read)
		&&(ui_ctrl.bat_soc.disp_ctrl.byte == ui_ctrl.iic_data.disp_ctrl_read.byte)
		&&(ui_ctrl.bat_soc.sys_status.byte == ui_ctrl.iic_data.sys_status_read.byte)
		&&(ui_ctrl.bat_soc.chg_time_h == ui_ctrl.iic_data.chg_time_h_read)
		&&(ui_ctrl.bat_soc.chg_time_m == ui_ctrl.iic_data.chg_time_m_read)
		&&(ui_ctrl.disp_step != DISP_STEP_REFLASH))
	{	
		return;
	}
	
	//更新数据
	ui_ctrl.bat_soc.disp_bat_num = ui_ctrl.iic_data.disp_bat_num_read;
	ui_ctrl.bat_soc.port_c1_watt = ui_ctrl.iic_data.port_c1_watt_read;
	ui_ctrl.bat_soc.port_c2_watt = ui_ctrl.iic_data.port_c2_watt_read;
	
	ui_ctrl.bat_soc.chg_time_h = ui_ctrl.iic_data.chg_time_h_read;
	ui_ctrl.bat_soc.chg_time_m = ui_ctrl.iic_data.chg_time_m_read;

	ui_ctrl.bat_soc.disp_ctrl.byte = ui_ctrl.iic_data.disp_ctrl_read.byte;
	ui_ctrl.bat_soc.sys_status.byte = ui_ctrl.iic_data.sys_status_read.byte;
	
	if(ui_ctrl.disp_step == DISP_STEP_WAITCMD)
		ui_ctrl.bat_soc.disp_bat_soc_step = DISP_STEP_PROTECT;
	else
		ui_ctrl.bat_soc.disp_bat_soc_step = DISP_STEP_BLACK;

	ui_ctrl.disp_step = DISP_STEP_DISP;

	
	ui_ctrl.disp_block = 0;
	ui_ctrl.disp_pos = 0;
}

static void ui_bat_soc_draw(void)
{
	switch(ui_ctrl.bat_soc.disp_bat_soc_step)
	{
		case DISP_STEP_BLACK:
		{
			ui_bat_num_black_draw();
			break;
		}

		case DISP_STEP_PROTECT:
		{
			ui_bat_num_protect_draw();
			break;
		}

		case DISP_STEP_BAT_NUM:
		{
			ui_bat_num_draw();
			break;
		}

		case DISP_STEP_C1_WATT:
		{
			ui_bat_num_c1_watt_draw();
			break;
		}

		case DISP_STEP_C1_LOGO:
		{
			ui_bat_num_c1_logo_draw();
			break;
		}

		case DISP_STEP_C2_WATT:
		{
			ui_bat_num_c2_watt_draw();
			break;
		}

		case DISP_STEP_C2_LOGO:
		{
			ui_bat_num_c2_logo_draw();
			break;
		}

		case DISP_STEP_CHG_TIME:
		{
			ui_bat_num_chg_time_draw();
			break;
		}
		
		case DISP_STEP_CYCLE:
		{
			ui_bat_cycle_draw();
			break;
		}
	}
}

static void ui_bat_num_black_draw(void)
{
	const flash_read_block_t *flash_block = ui_black_array + ui_ctrl.disp_block;
	uint32_t flash_read_addr = 0;

	ui_bat_num_base_draw(flash_block, flash_read_addr, length_ui_black);
}

static void ui_bat_num_protect_draw(void)
{
	const flash_read_block_t *flash_block = prot_disp_array + ui_ctrl.disp_block;

	uint32_t flash_read_addr = flash_block->flash_read_addr + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
	
	if(ui_ctrl.bat_soc.disp_ctrl.temp_protect == 0)
		flash_read_addr = 0;

	ui_bat_num_base_draw(flash_block, flash_read_addr, length_prot_disp);
}

static void ui_bat_num_draw(void)
{
	const flash_read_block_t *flash_block = soc_full_array + ui_ctrl.disp_block;
	uint32_t flash_read_addr = flash_block->flash_read_addr + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
	
	if(ui_ctrl.bat_soc.disp_bat_num < 100)
	{
		
		if(ui_ctrl.bat_soc.disp_bat_num_state != 1)
		{
			ui_ctrl.bat_soc.disp_bat_num_state = 1;
		}
		else
		{
			if(ui_ctrl.disp_block == 0 && ui_ctrl.disp_pos == 0)
			{
				ui_ctrl.disp_block = 1;
			}
		}
		flash_block = soc_disp_array + ui_ctrl.disp_block;
		flash_read_addr = flash_block->flash_read_addr + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
	}
	else
	{
		if(ui_ctrl.bat_soc.disp_bat_num_state != 2)
		{
			ui_ctrl.bat_soc.disp_bat_num_state = 2;
		}
		else
		{
			if(ui_ctrl.disp_block == 0 && ui_ctrl.disp_pos == 0)
			{
				ui_ctrl.disp_block = 1;
			}
		}
		flash_block = soc_full_array + ui_ctrl.disp_block;
		flash_read_addr = flash_block->flash_read_addr + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
	}
	
	
	switch(ui_ctrl.disp_block)
	{
		case 0:
		{
			flash_read_addr = 0;
			break;
		}
		
		case 1:
		{
			if(ui_ctrl.bat_soc.disp_bat_num < 100)
				flash_read_addr = 0;
			else
				flash_read_addr += FLASH_ADDR_BAT_NUM_OFFSET;
			
			break;
		}
		
		case 2:
		{
			if(ui_ctrl.bat_soc.disp_bat_num < 10)
				flash_read_addr = 0;
			else
				flash_read_addr += FLASH_ADDR_BAT_NUM_OFFSET * (ui_ctrl.bat_soc.disp_bat_num / 10 % 10);
			
			break;
		}
		
		case 3:
		{
			flash_read_addr += FLASH_ADDR_BAT_NUM_OFFSET * (ui_ctrl.bat_soc.disp_bat_num % 10);
			break;
		}
	}
	
	ui_bat_num_base_draw(flash_block, flash_read_addr, length_soc_full);
}

static void ui_bat_num_c1_watt_draw(void)
{
	const flash_read_block_t *flash_block = c1_watt_array + ui_ctrl.disp_block;

	uint32_t flash_read_addr = flash_block->flash_read_addr + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
	
	switch(ui_ctrl.disp_block)
	{
		case 0:
		{
			if(!ui_ctrl.bat_soc.sys_status.port_c1_status)
			{
				if(ui_ctrl.bat_soc.disp_ctrl.chg_time_disp || ui_ctrl.bat_soc.sys_status.port_c2_status)
					flash_read_addr = FLASH_ADDR_WATT_FLAG_NULL + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
				else
					flash_read_addr = 0;
			}			
			break;
		}

		case 1:
		{
			if(!ui_ctrl.bat_soc.sys_status.port_c1_status)
			{
				if(ui_ctrl.bat_soc.disp_ctrl.chg_time_disp || ui_ctrl.bat_soc.sys_status.port_c2_status)
					flash_read_addr = FLASH_ADDR_WATT_NUM_0_NULL + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
				else
					flash_read_addr = 0;
			}
			else
				flash_read_addr += FLASH_ADDR_WATT_NUM_OFFSET * (ui_ctrl.bat_soc.port_c1_watt % 10);
			break;
		}

		case 2:
		{
			if(!ui_ctrl.bat_soc.sys_status.port_c1_status)
			{
				if(ui_ctrl.bat_soc.disp_ctrl.chg_time_disp || ui_ctrl.bat_soc.sys_status.port_c2_status)
					flash_read_addr = FLASH_ADDR_WATT_POINT_NULL + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
				else
					flash_read_addr = 0;
			}
			break;
		}
		
		case 3:
		{
			if(!ui_ctrl.bat_soc.sys_status.port_c1_status)
			{
				if(ui_ctrl.bat_soc.disp_ctrl.chg_time_disp || ui_ctrl.bat_soc.sys_status.port_c2_status)
					flash_read_addr = FLASH_ADDR_WATT_NUM_0_NULL + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
				else
					flash_read_addr = 0;
			}
			else
				flash_read_addr += FLASH_ADDR_WATT_NUM_OFFSET * (ui_ctrl.bat_soc.port_c1_watt / 10 % 10);
			break;
		}
		
		case 4:
		{
			if(ui_ctrl.bat_soc.sys_status.port_c1_status)
			{
				if(ui_ctrl.bat_soc.port_c1_watt >= 100)
					flash_read_addr += FLASH_ADDR_WATT_NUM_OFFSET * (ui_ctrl.bat_soc.port_c1_watt / 100 % 10);
				else
					flash_read_addr = 0;
			}
			else
			{
				flash_read_addr = 0;
			}
			break;
		}
	}

	ui_bat_num_base_draw(flash_block, flash_read_addr, length_c1_watt);
}

static void ui_bat_num_c1_logo_draw(void)
{
	const flash_read_block_t *flash_block = c1_logo_array + ui_ctrl.disp_block;

	uint32_t flash_read_addr = flash_block->flash_read_addr + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
	
	switch(ui_ctrl.disp_block)
	{
		case 0:
		{
			if(!ui_ctrl.bat_soc.sys_status.port_c1_status)
			{
				if(ui_ctrl.bat_soc.disp_ctrl.chg_time_disp || ui_ctrl.bat_soc.sys_status.port_c2_status)
					flash_read_addr = FLASH_ADDR_WATT_C1_NULL + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
				else
					flash_read_addr = 0;
			}
			break;
		}

		case 1:
		{
			if(ui_ctrl.bat_soc.sys_status.port_c1_status == 1)
				flash_read_addr = FLASH_ADDR_WATT_CHARGE + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
			else if(ui_ctrl.bat_soc.sys_status.port_c1_status == 2)
				flash_read_addr = FLASH_ADDR_WATT_DISCHG + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
			else
				flash_read_addr = 0;
			break;
		}
	}

	ui_bat_num_base_draw(flash_block, flash_read_addr, length_c1_logo);
}

static void ui_bat_num_c2_watt_draw(void)
{
	const flash_read_block_t *flash_block = c2_watt_array + ui_ctrl.disp_block;

	uint32_t flash_read_addr = flash_block->flash_read_addr + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
	
	switch(ui_ctrl.disp_block)
	{
		case 0:
		{
			if(!ui_ctrl.bat_soc.sys_status.port_c2_status)
			{
				if(ui_ctrl.bat_soc.disp_ctrl.chg_time_disp || ui_ctrl.bat_soc.sys_status.port_c1_status)
					flash_read_addr = FLASH_ADDR_WATT_FLAG_NULL + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
				else
					flash_read_addr = 0;
			}			
			break;
		}

		case 1:
		{
			if(!ui_ctrl.bat_soc.sys_status.port_c2_status)
			{
				if(ui_ctrl.bat_soc.disp_ctrl.chg_time_disp || ui_ctrl.bat_soc.sys_status.port_c1_status)
					flash_read_addr = FLASH_ADDR_WATT_NUM_0_NULL + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
				else
					flash_read_addr = 0;
			}
			else
				flash_read_addr += FLASH_ADDR_WATT_NUM_OFFSET * (ui_ctrl.bat_soc.port_c2_watt % 10);
			break;
		}

		case 2:
		{
			if(!ui_ctrl.bat_soc.sys_status.port_c2_status)
			{
				if(ui_ctrl.bat_soc.disp_ctrl.chg_time_disp || ui_ctrl.bat_soc.sys_status.port_c1_status)
					flash_read_addr = FLASH_ADDR_WATT_POINT_NULL + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
				else
					flash_read_addr = 0;
			}
			break;
		}
		
		case 3:
		{
			if(!ui_ctrl.bat_soc.sys_status.port_c2_status)
			{
				if(ui_ctrl.bat_soc.disp_ctrl.chg_time_disp || ui_ctrl.bat_soc.sys_status.port_c1_status)
					flash_read_addr = FLASH_ADDR_WATT_NUM_0_NULL + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
				else
					flash_read_addr = 0;
			}
			else
				flash_read_addr += FLASH_ADDR_WATT_NUM_OFFSET * (ui_ctrl.bat_soc.port_c2_watt / 10 % 10);
			break;
		}
		
		case 4:
		{
			if(ui_ctrl.bat_soc.sys_status.port_c2_status)
			{
				if(ui_ctrl.bat_soc.port_c2_watt >= 100)
					flash_read_addr += FLASH_ADDR_WATT_NUM_OFFSET * (ui_ctrl.bat_soc.port_c2_watt / 100% 10);
				else
					flash_read_addr = 0;
			}
			else
			{
				flash_read_addr = 0;
			}
			break;
		}
	}

	ui_bat_num_base_draw(flash_block, flash_read_addr, length_c2_watt);
}

static void ui_bat_num_c2_logo_draw(void)
{
	const flash_read_block_t *flash_block = c2_logo_array + ui_ctrl.disp_block;

	uint32_t flash_read_addr = flash_block->flash_read_addr + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
	
	switch(ui_ctrl.disp_block)
	{
		case 0:
		{
			if(!ui_ctrl.bat_soc.sys_status.port_c2_status)
			{
				if(ui_ctrl.bat_soc.disp_ctrl.chg_time_disp || ui_ctrl.bat_soc.sys_status.port_c1_status)
					flash_read_addr = FLASH_ADDR_WATT_C2_NULL + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
				else
					flash_read_addr = 0;
			}
			break;
		}

		case 1:
		{
			if(ui_ctrl.bat_soc.sys_status.port_c2_status == 1)
				flash_read_addr = FLASH_ADDR_WATT_CHARGE + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
			else if(ui_ctrl.bat_soc.sys_status.port_c2_status == 2)
				flash_read_addr = FLASH_ADDR_WATT_DISCHG + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;
			else
				flash_read_addr = 0;
			break;
		}
	}

	ui_bat_num_base_draw(flash_block, flash_read_addr, length_c2_logo);
}

static void ui_bat_num_chg_time_draw(void)
{
	const flash_read_block_t *flash_block = chg_time_array + ui_ctrl.disp_block;

	uint32_t flash_read_addr = flash_block->flash_read_addr + ui_ctrl.disp_pos * FLASH_READ_BUF_SIZE;

	switch(ui_ctrl.disp_block)
	{
		case 1:
		{
			flash_read_addr += FLASH_ADDR_TIME_NUM_OFFSET * (ui_ctrl.bat_soc.chg_time_h / 10);
			break;
		}

		case 2:
		{
			flash_read_addr += FLASH_ADDR_TIME_NUM_OFFSET * (ui_ctrl.bat_soc.chg_time_h % 10);
			break;
		}

		case 4:
		{
			flash_read_addr += FLASH_ADDR_TIME_NUM_OFFSET * (ui_ctrl.bat_soc.chg_time_m / 10);
			break;
		}

		case 5:
		{
			flash_read_addr += FLASH_ADDR_TIME_NUM_OFFSET * (ui_ctrl.bat_soc.chg_time_m % 10);
			break;
		}
	}

	if(!ui_ctrl.bat_soc.disp_ctrl.chg_time_disp)
		flash_read_addr = 0;

	ui_bat_num_base_draw(flash_block, flash_read_addr, length_chg_time);
}

//绘制圆环
static void ui_bat_cycle_draw(void)
{
	if(ui_ctrl.disp_pos >= length_bat_cycle)
	{
		if(spi_dma_send_ok)
		{
			ui_ctrl.disp_pos = 0;
			ui_ctrl.disp_block = 0;
			ui_ctrl.disp_step = DISP_STEP_WAITCMD;
		}
		return;
	}
		
	uint8_t block_write_x = 0;
	uint8_t block_write_y = 0;
	uint32_t flash_read_addr = 0;
	
	block_write_x = cycle_pos_array[ui_ctrl.disp_pos].position_x;
	block_write_y = cycle_pos_array[ui_ctrl.disp_pos].position_y;
	flash_read_addr = disp_cycle_flash_addr_get(ui_ctrl.disp_pos, ui_ctrl.bat_soc.disp_bat_num);

//	if(spi_dma_send_ok || ui_ctrl.disp_pos == 0)
	if(spi_dma_send_ok)
	{
		flash_read_buf(flash_read_addr, spi_dma_buf, FLASH_READ_BUF_SIZE);
		BlockWrite(block_write_x, block_write_x + DISP_CYCLE_SIZE_X, block_write_y, block_write_y + DISP_CYCLE_SIZE_Y);
		
		dma_send_enable(0);
		
		spi_dma_send_ok = 0;
		ui_ctrl.disp_pos++;
	}
}

static uint32_t disp_cycle_flash_addr_get(uint8_t cycle_pos, uint8_t bat_num)
{
	if(bat_num && bat_num <= DISP_CYCLE_HALF_BAT_NUM)
	{
		if(cycle_pos == DISP_CYCLE_HALF_POS_0)
		{
			return FLASH_ADDR_CYCLE_HALF_0;
		}
		else if(cycle_pos == DISP_CYCLE_HALF_POS_1)
		{
			return FLASH_ADDR_CYCLE_HALF_1;
		}
	}
	
	if(bat_num >= cycle_pos_array[cycle_pos].bat_num_l)
	{
		if((cycle_pos_array[cycle_pos].pos_offset == 0) || (bat_num > cycle_pos_array[cycle_pos].bat_num_h))
		{
			return FLASH_ADDR_CYCLE_FULL + cycle_pos * 200;
		}
		else
		{
			return FLASH_ADDR_CYCLE_DIFF + (cycle_pos_array[cycle_pos].pos_offset + bat_num - cycle_pos_array[cycle_pos].bat_num_l) * 200;
		}
	}
	else
	{
		return cycle_pos * 200;
	}
}

static void ui_bat_num_base_draw(const flash_read_block_t *flash_block, uint32_t flash_read_addr, uint8_t lenght_flash_block)
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
		ui_ctrl.bat_soc.disp_bat_soc_step += 1;
		ui_ctrl.disp_block = 0;
		ui_ctrl.disp_pos = 0;
	}
}


