;*******************************************************************************
; file       : startup_es32f0283.s
; description: ES32F00283 Device Startup File
; author     : Eastsoft MCU Software Team
; data       : 2/24/2021
; Copyright (C) 2020 Eastsoft Communication(TW) System Co., Limited. ALL rights reserved.
;*******************************************************************************

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)
        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)				    ;0,  load top of stack
        DCD     Reset_Handler			    ;1,  reset handler
        DCD     NMI_Handler				    ;2,  nmi handler
        DCD     HARDFAULT_Handler		    ;3,  hard fault handler
        DCD     0					        ;4,  MPU Fault Handler
        DCD     0					        ;5,  Bus Fault Handler
        DCD     0					        ;6,  Usage Fault Handler
        DCD     0					        ;7,  Reserved
        DCD     0					        ;8,  Reserved
        DCD     0					        ;9,  Reserved
        DCD     0					        ;10, Reserved
        DCD     SVC_Handler				    ;11, svcall handler
        DCD     0					        ;12, Reserved
        DCD     0					        ;13, Reserved
        DCD     PENDSV_Handler              ;14, PENDSV Handler
        DCD     SYSTICK_Handler             ;15, SYSTICK Handler
        DCD     WWDT_IRQHandler             ;16, WWDT IRQHandler
        DCD     PVD_IRQHandler              ;17, PVD IRQHandler
        DCD     RTC_IRQHandler              ;18, RTC IRQHandler
        DCD     WAKEUP_IRQHandler           ;19, WAKEUP IRQHandler
        DCD     RCU_CSU_IRQHandler          ;20, RCU_CSU IRQHandler
        DCD     EXTI_0to1_IRQHandler        ;21, EXTI_0to1 IRQHandler
        DCD     EXTI_2to3_IRQHandler        ;22, EXTI_2to3 IRQHandler
        DCD     EXTI_4to15_IRQHandler       ;23, EXTI_4to15 IRQHandler
        DCD     SPI3_IRQHandler             ;24, SPI3 IRQHandler
        DCD     DMA1_CH0_IRQHandler         ;25, DMA1_CH1 IRQHandler
        DCD     DMA1_CH12_IRQHandler        ;26, DMA1_CH12 IRQHandler
        DCD     DMA1_CH345_IRQHandler       ;27, DMA1_CH345 IRQHandler
        DCD     ADC_COMP_IRQHandler         ;28, ADC_COMP IRQHandler
        DCD     AD16C4T1_IRQHandler         ;29, AD16C4T1 IRQHandler
        DCD     BS16T1_IRQHandler           ;30, BS16T1 IRQHandler
        DCD     GP32C4T1_IRQHandler         ;31, GP32C4T1 IRQHandler
        DCD     GP16C4T1_IRQHandler         ;32, GP16C4T1 IRQHandler
        DCD     GP16C4T2_IRQHandler         ;33, GP16C4T2 IRQHandler
        DCD     GP16C4T3_IRQHandler         ;34, GP16C4T3 IRQHandler
        DCD     GP16C2T1_IRQHandler         ;35, GP16C2T1 IRQHandler
        DCD     GP16C2T2_IRQHandler         ;36, GP16C2T2 IRQHandler
        DCD     GP16C2T3_IRQHandler         ;37, GP16C2T3 IRQHandler
        DCD     GP16C2T4_IRQHandler         ;38, GP16C2T4 IRQHandler
        DCD     I2C1_IRQHandler             ;39, I2C1 IRQHandler
        DCD     I2C2_IRQHandler             ;40, I2C2 IRQHandler
        DCD     SPI1_IRQHandler             ;41, SPI1 IRQHandler
        DCD     SPI2_IRQHandler             ;42, SPI2 IRQHandler
        DCD     UART1_IRQHandler            ;43, UART1 IRQHandler
        DCD     UART2_IRQHandler            ;44, UART2 IRQHandler
        DCD     UART3_IRQHandler            ;45, UART3 IRQHandler
        DCD     UART4_KBCU_IRQHandler       ;46, UART4_KBCU IRQHandler
        DCD     USB_IRQHandler              ;47, USB IRQHandler
        
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, =__iar_program_start
        BX      R0
        
        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HARDFAULT_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HARDFAULT_Handler
        B HARDFAULT_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler
		
    	PUBWEAK PENDSV_Handler
    	SECTION .text:CODE:NOROOT:REORDER(1)
PENDSV_Handler
    	B PENDSV_Handler

   	PUBWEAK SYSTICK_Handler
    	SECTION .text:CODE:NOROOT:REORDER(1)
SYSTICK_Handler
    	B SYSTICK_Handler

        PUBWEAK WWDT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDT_IRQHandler
        B WWDT_IRQHandler

	PUBWEAK PVD_IRQHandler
	SECTION .text:CODE:NOROOT:REORDER(1)
PVD_IRQHandler
	B PVD_IRQHandler
		
	PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK WAKEUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WAKEUP_IRQHandler
        B WAKEUP_IRQHandler
        
        PUBWEAK RCU_CSU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCU_CSU_IRQHandler
        B RCU_CSU_IRQHandler

        PUBWEAK EXTI_0to1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI_0to1_IRQHandler
        B EXTI_0to1_IRQHandler

        PUBWEAK EXTI_2to3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI_2to3_IRQHandler
        B EXTI_2to3_IRQHandler

        PUBWEAK EXTI_4to15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI_4to15_IRQHandler
        B EXTI_4to15_IRQHandler
        
        PUBWEAK SPI3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI3_IRQHandler
        B SPI3_IRQHandler

        PUBWEAK DMA1_CH0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH0_IRQHandler
        B DMA1_CH0_IRQHandler

 	PUBWEAK DMA1_CH12_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH12_IRQHandler
        B DMA1_CH12_IRQHandler

        PUBWEAK DMA1_CH345_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH345_IRQHandler
        B DMA1_CH345_IRQHandler

        PUBWEAK ADC_COMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_COMP_IRQHandler
        B ADC_COMP_IRQHandler

        PUBWEAK AD16C4T1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
AD16C4T1_IRQHandler
        B AD16C4T1_IRQHandler

        PUBWEAK BS16T1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
BS16T1_IRQHandler
        B BS16T1_IRQHandler

        PUBWEAK GP32C4T1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP32C4T1_IRQHandler
        B GP32C4T1_IRQHandler

        PUBWEAK GP16C4T1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C4T1_IRQHandler
        B GP16C4T1_IRQHandler

        PUBWEAK GP16C4T2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C4T2_IRQHandler
        B GP16C4T2_IRQHandler

        PUBWEAK GP16C4T3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C4T3_IRQHandler
        B GP16C4T3_IRQHandler

        PUBWEAK GP16C2T1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C2T1_IRQHandler
        B GP16C2T1_IRQHandler

        PUBWEAK GP16C2T2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C2T2_IRQHandler
        B GP16C2T2_IRQHandler

        PUBWEAK GP16C2T3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C2T3_IRQHandler
        B GP16C2T3_IRQHandler

        PUBWEAK GP16C2T4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C2T4_IRQHandler
        B GP16C2T4_IRQHandler

        PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_IRQHandler
        B I2C1_IRQHandler

	PUBWEAK I2C2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_IRQHandler
        B I2C2_IRQHandler

	PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

	PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

	PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART1_IRQHandler
        B UART1_IRQHandler

	PUBWEAK UART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART2_IRQHandler
        B UART2_IRQHandler

	PUBWEAK UART3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART3_IRQHandler
        B UART3_IRQHandler

	PUBWEAK UART4_KBCU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART4_KBCU_IRQHandler
        B UART4_KBCU_IRQHandler

	PUBWEAK USB_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_IRQHandler
        B USB_IRQHandler

        END
