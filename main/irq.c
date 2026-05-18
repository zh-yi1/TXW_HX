#include "global_define.h"

/**
 * @brief  NMI IRQ handler
 * @retval None
 */
void NMI_Handler(void)
{
	/* Added Emergency operation */
	return;
}

/**
 * @brief  Hardfault IRQ handler, already defined in startup file
 * @retval None
 */

/**
 * @brief  Supervisor Call IRQ handler
 * @retval None
 */
void SVC_Handler(void)
{
	/* Added system callback */
	return;
}

/**
 * @brief  Debug Monitor IRQ handler
 * @retval None
 */
void DebugMon_Handler(void)
{
	/* Added debug operation */
	return;
}

/**
 * @brief  PendSV IRQ handler
 * @retval None
 */
void PendSV_Handler(void)
{
	/* Added thread switching operation */
	return;
}

/**
 * @brief  SysTick IRQ handler
 * @retval None
 */
void SysTick_Handler(void)
{
	work_time.timer_1ms = 1;
	
	work_time.count_10ms++;
	if(work_time.count_10ms >= 10)
	{
		work_time.count_10ms = 0;
		work_time.timer_10ms = 1;
		
		work_time.count_100ms++;
	}
	
	if(work_time.count_100ms >= 10)
	{
		work_time.count_100ms = 0;
		work_time.timer_100ms = 1;
	}
	
	md_inc_tick();
	return;
}
	
/*I2C interrupt service function*/
void I2C1_Handler()
{
	/*Send buffer empty*/
	if ((md_i2c_is_active_flag_txbe(I2C1) == 1) && md_i2c_is_enable_it_buf(I2C1) && md_i2c_is_enable_it_evt(I2C1))
	{

		//  md_i2c_transmit_data8(I2C1, iic_send_buf[iic_send_ind++]);
		iic_send_add = iic_recv_buf[0];
		md_i2c_transmit_data8(I2C1, iic_send_buf[iic_send_add]);
		iic_send_ind++;
		clear_buf(iic_recv_buf);
	}

	/*Receive buffer is not empty*/
	if ((md_i2c_is_active_flag_rxne(I2C1) == 1) && md_i2c_is_enable_it_buf(I2C1) && md_i2c_is_enable_it_evt(I2C1))
	{
		iic_recv_buf[iic_recv_ind++] = md_i2c_receive_data8(I2C1);

		if (iic_recv_ind >= iic_recv_len)
		{
			iic_recv_ind = 0;
		}
	}

	/*From the machine address matching*/
	if (md_i2c_is_active_flag_addr(I2C1) && md_i2c_is_enable_it_evt(I2C1))
	{
		md_i2c_clear_flag_addr(I2C1);
		md_i2c_enable_it_buf(I2C1);
	}

	/*Failed to reply*/
	if (md_i2c_is_active_flag_af(I2C1) && md_i2c_is_enable_it_err(I2C1))
	{
		md_i2c_clear_flag_af(I2C1); /*Clear reply marks a failure*/
		md_i2c_disable_it_buf(I2C1);
		iic_recv_ind = 0;
		iic_send_ind = 0;
	}

	/*The bus stop bit is detected*/
	if (md_i2c_is_active_flag_stop(I2C1) && md_i2c_is_enable_it_evt(I2C1))
	{
		md_i2c_clear_flag_stop(I2C1); /*To generate the stop bit*/
		md_i2c_disable_it_buf(I2C1);
		
		if (iic_send_ind == 0 && iic_recv_ind == 2)
		{

			iic_send_buf[iic_recv_buf[0]] = iic_recv_buf[1];
			clear_buf(iic_recv_buf);
		}

		iic_recv_ind = 0;
		iic_send_ind = 0;
	}

	/*SMBALARM*/
	if (md_i2c_is_active_smbus_flag_alert(I2C1) && md_i2c_is_enable_it_err(I2C1))
	{
		md_i2c_clear_smbus_flag_alert(I2C1);
	}

	/*SMBTO*/
	if (md_i2c_is_active_smbus_flag_timeout(I2C1) && md_i2c_is_enable_it_err(I2C1))
	{
		md_i2c_clear_smbus_flag_timeout(I2C1);
	}

	/*PECERR*/
	if (md_i2c_is_active_smbus_flag_pecerr(I2C1) && md_i2c_is_enable_it_err(I2C1))
	{
		md_i2c_clear_smbus_flag_pecerr(I2C1);
	}

	/*ROUERR*/
	if (md_i2c_is_active_flag_ovr(I2C1) && md_i2c_is_enable_it_err(I2C1))
	{
		md_i2c_clear_flag_ovr(I2C1);
	}

	/*LARB*/
	if (md_i2c_is_active_flag_arlo(I2C1) && md_i2c_is_enable_it_err(I2C1))
	{
		md_i2c_clear_flag_arlo(I2C1);
	}

	/*BUSERR*/
	if (md_i2c_is_active_flag_berr(I2C1) && md_i2c_is_enable_it_err(I2C1))
	{
		md_i2c_clear_flag_berr(I2C1);
	}
}

/**
 * @brief  DMA IRQ HANDLER
 * @param  None
 * @retval None
 */
void DMA_Handler(void)
{
	uint8_t tx_ok = 0, rx_ok = 0;

	if (md_dma_is_enabled_it_done(MD_DMA_CH_0) && md_dma_is_active_flag_done(MD_DMA_CH_0))
	{
		md_dma_clear_flag_done(MD_DMA_CH_0);
		md_spi_disable_tx_dma(SPI0);

		if (dma_chain_state == DMA_CHAIN_LCD_PUSH)
		{
			dma_chain_done = 1;
			spi_dma_send_clc = 0;
		}
		else if (dma_chain_state == DMA_CHAIN_FLASH_READ)
		{
			tx_ok = 1;
		}
	}

	if (md_dma_is_enabled_it_done(MD_DMA_CH_1) && md_dma_is_active_flag_done(MD_DMA_CH_1))
	{
		md_dma_clear_flag_done(MD_DMA_CH_1);
		md_spi_disable_rx_dma(SPI0);

		if (dma_chain_state == DMA_CHAIN_FLASH_READ)
			rx_ok = 1;
	}

	if (dma_chain_state == DMA_CHAIN_FLASH_READ && tx_ok && rx_ok)
		dma_chain_done = 1;

	return;
}

/**
 * @brief  AD16C4T0_UP_Handler
 * @retval None
 */
void AD16C4T_UP_Handler(void)
{
	if (md_timer_get_update_valid_interrupt_flag_uei(AD16C4T) == 1)
	{
		md_timer_clear_update_interrupt_flag_ueic(AD16C4T);
	}

	return;
}

/**
 * @brief  AD16C4T0_CC_Handler
 * @retval None
 */
void AD16C4T_CC_Handler(void)
{
	/* Handle TIM interrupt */
	if (md_timer_get_cc1_valid_interrupt_flag_ch1cci(AD16C4T) == 1U)
	{
		md_timer_clear_cc1_interrupt_flag_ch1ccic(AD16C4T);
	}

	if (md_timer_get_cc2_valid_interrupt_flag_ch2cci(AD16C4T) == 1U)
	{
		md_timer_clear_cc2_interrupt_flag_ch2ccic(AD16C4T);
	}

	if (md_timer_get_cc3_valid_interrupt_flag_ch3cci(AD16C4T) == 1U)
	{
		md_timer_clear_cc3_interrupt_flag_ch3ccic(AD16C4T);
	}

	if (md_timer_get_cc4_valid_interrupt_flag_ch4cci(AD16C4T) == 1U)
	{
		md_timer_clear_cc4_interrupt_flag_ch4ccic(AD16C4T);
	}
}


