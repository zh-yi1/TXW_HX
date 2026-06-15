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
	// if (md_timer_get_update_valid_interrupt_flag_uei(AD16C4T) == 1)
	// {
	// 	md_timer_clear_update_interrupt_flag_ueic(AD16C4T);
	// }

	return;
}

/**
 * @brief  AD16C4T0_CC_Handler
 * @retval None
 */
void AD16C4T_CC_Handler(void)
{
	/* Handle TIM interrupt */
	// if (md_timer_get_cc1_valid_interrupt_flag_ch1cci(AD16C4T) == 1U)
	// {
	// 	md_timer_clear_cc1_interrupt_flag_ch1ccic(AD16C4T);
	// }

	// if (md_timer_get_cc2_valid_interrupt_flag_ch2cci(AD16C4T) == 1U)
	// {
	// 	md_timer_clear_cc2_interrupt_flag_ch2ccic(AD16C4T);
	// }

	// if (md_timer_get_cc3_valid_interrupt_flag_ch3cci(AD16C4T) == 1U)
	// {
	// 	md_timer_clear_cc3_interrupt_flag_ch3ccic(AD16C4T);
	// }

	// if (md_timer_get_cc4_valid_interrupt_flag_ch4cci(AD16C4T) == 1U)
	// {
	// 	md_timer_clear_cc4_interrupt_flag_ch4ccic(AD16C4T);
	// }
}
#ifndef DEBUG_EN
/**
  * @brief  USART1 interrupt handler — RXNE: store byte into ring buffer
  */
void USART1_Handler(void)
{
	/* ---- RX not empty: read byte into ring buffer ---- */
	if (md_usart_is_enabled_it_rxne(USART1) && md_usart_is_active_flag_rxne(USART1))
	{
		md_usart_clear_flag_rxne(USART1);

		usart_rx_buf[usart_rx_head] = md_usart_recv_data8(USART1);
		usart_rx_head = (usart_rx_head + 1) % USART_RX_BUF_SIZE;

		/* Overrun protection: if head catches tail, advance tail */
		if (usart_rx_head == usart_rx_tail)
			usart_rx_tail = (usart_rx_tail + 1) % USART_RX_BUF_SIZE;
	}
}
#endif /* !DEBUG_EN */


