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
	

/**
 * @brief  DMA IRQ HANDLER
 * @param  None
 * @retval None
 */
void DMA_Handler(void)
{
	if (md_dma_is_enabled_it_done(MD_DMA_CH_0) && md_dma_is_active_flag_done(MD_DMA_CH_0))
	{
		md_dma_clear_flag_done(MD_DMA_CH_0);
		md_spi_disable_tx_dma(SPI0);
		spi_dma_send_ok = 1;
		spi_dma_send_clc = 0;
	}

	if (md_dma_is_enabled_it_done(MD_DMA_CH_1) && md_dma_is_active_flag_done(MD_DMA_CH_1))
	{
		md_dma_clear_flag_done(MD_DMA_CH_1);
		md_spi_disable_rx_dma(SPI0);
	}

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


