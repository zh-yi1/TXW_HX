;*******************************************************************************
; *file       : startup_es32f010x.s
; *description: ES32F010x Device Startup File
; *author     : Eastsoft MCU Software Team
; *version    : V0.01
; *data       : 9/1/2020
;
; *Copyright (C) 2020 Shanghai Eastsoft Microelectronics Co., Ltd.
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
;*******************************************************************************


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000600

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                ; External Interrupts
                DCD     Reset_Handler          ;1, Reset Handler
                DCD     NMI_Handler          ;2, NMI Handler
                DCD     HardFault_Handler          ;3, HardFault Handler
                DCD     0                    ;4, Reserved
                DCD     0                    ;5, Reserved
                DCD     0                    ;6, Reserved
                DCD     0                    ;7, Reserved
                DCD     0                    ;8, Reserved
                DCD     0                    ;9, Reserved
                DCD     0                    ;10, Reserved
                DCD     SVCall_Handler          ;11, SVCall Handler
                DCD     0                    ;12, Reserved
                DCD     0                    ;13, Reserved
                DCD     PendSV_Handler          ;14, PendSV Handler
                DCD     SysTick_Handler          ;15, SysTick Handler
                DCD     WWDT_Handler          ;16, WWDT IRQHandler
                DCD     IWDT_Handler          ;17, IWDT IRQHandler
                DCD     LVD_Handler          ;18, LVD IRQHandler
                DCD     0                    ;19, Reserved
                DCD     CMU_Handler          ;20, CMU IRQHandler
                DCD     EXTI0_3_Handler          ;21, EXTI0_3 IRQHandler
                DCD     EXTI4_7_Handler          ;22, EXTI4_7 IRQHandler
                DCD     EXTI8_11_Handler          ;23, EXTI8_11 IRQHandler
                DCD     EXTI12_15_Handler          ;24, EXTI12_15 IRQHandler
                DCD     DMA_Handler          ;25, DMA IRQHandler
                DCD     ACMP0_Handler          ;26, CMP0 IRQHandler
                DCD     ACMP1_Handler          ;27, CMP1 IRQHandler
                DCD     ADC0_Handler          ;28, ADC IRQHandler
                DCD     AD16C4T_UP_Handler          ;29, AD16C4T_UP IRQHandler
                DCD     AD16C4T_CC_Handler          ;30, AD16C4T_CC IRQHandler
                DCD     BSTIM0_Handler          ;31, BSTIM0 IRQHandler
                DCD     0                       ;32, 　 Reserved
                DCD     GPTIMC0_Handler          ;33, GPTIMC0 IRQHandler
                DCD     GPTIMC1_Handler          ;34, GPTIMC1 IRQHandler
                DCD     GPTIMC2_Handler          ;35, GPTIMC2 IRQHandler
                DCD     0                           ;36, 　 Reserved
                DCD     AD16C4T_Handler          ;37, AD16C4T IRQHandler
                DCD     0                           ;38, 　 Reserved
                DCD     I2C0_Handler          ;39, I2C0 IRQHandler
                DCD     I2C1_Handler          ;40, I2C1 IRQHandler
                DCD     SPI0_Handler          ;41, SPI0 IRQHandler
                DCD     0                        ;42, 　 Reserved
                DCD     0                        ;43, 　 Reserved
                DCD     0                        ;44, 　　 Reserved
                DCD     USART0_Handler          ;45, USART0 IRQHandler
                DCD     USART1_Handler          ;46, USART1 IRQHandler
                DCD     0                        ;47, 　 Reserved


                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception IRQHandlers (infinite loops which can be modified)

NMI_Handler  		PROC
						EXPORT  NMI_Handler            [WEAK]
						B       .
						ENDP
							
HardFault_Handler  		PROC
						EXPORT  HardFault_Handler
						ISB
						PUSH	{R0-R3, LR}
						LDR		R0,		=0x40080000
						LDR		R1,		=0x55AA6996
						STR		R1,		[R0]

						LDR		R2,		=0x40080824
						LDR		R3,		=0x00000001
						STR		R3,		[R2]
						
						NOP
						
						ENDP
							
SVCall_Handler  		PROC
						EXPORT  SVCall_Handler            [WEAK]
						B       .
						ENDP
PendSV_Handler  		PROC
						EXPORT  PendSV_Handler            [WEAK]
						B       .
						ENDP
SysTick_Handler  		PROC
						EXPORT  SysTick_Handler            [WEAK]
						B       .
						ENDP

Default_Handler PROC



                EXPORT  WWDT_Handler    [WEAK]
                EXPORT  IWDT_Handler    [WEAK]
                EXPORT  LVD_Handler    [WEAK]
                EXPORT  CMU_Handler    [WEAK]
                EXPORT  EXTI0_3_Handler    [WEAK]
                EXPORT  EXTI4_7_Handler    [WEAK]
                EXPORT  EXTI8_11_Handler    [WEAK]
                EXPORT  EXTI12_15_Handler    [WEAK]
                EXPORT  DMA_Handler    [WEAK]
                EXPORT  ACMP0_Handler    [WEAK]
                EXPORT  ACMP1_Handler    [WEAK]
                EXPORT  ADC0_Handler    [WEAK]
                EXPORT  AD16C4T_UP_Handler    [WEAK]
                EXPORT  AD16C4T_CC_Handler    [WEAK]
                EXPORT  BSTIM0_Handler    [WEAK]
                EXPORT  GPTIMC0_Handler    [WEAK]
                EXPORT  GPTIMC1_Handler    [WEAK]
                EXPORT  GPTIMC2_Handler    [WEAK]
                EXPORT  AD16C4T_Handler    [WEAK]
                EXPORT  I2C0_Handler    [WEAK]
                EXPORT  I2C1_Handler    [WEAK]
                EXPORT  SPI0_Handler    [WEAK]
                EXPORT  USART0_Handler    [WEAK]
                EXPORT  USART1_Handler    [WEAK]



WWDT_Handler
IWDT_Handler
LVD_Handler
CMU_Handler
EXTI0_3_Handler
EXTI4_7_Handler
EXTI8_11_Handler
EXTI12_15_Handler
DMA_Handler
ACMP0_Handler
ACMP1_Handler
ADC0_Handler
AD16C4T_UP_Handler
AD16C4T_CC_Handler
BSTIM0_Handler
GPTIMC0_Handler
GPTIMC1_Handler
GPTIMC2_Handler
AD16C4T_Handler
I2C0_Handler
I2C1_Handler
SPI0_Handler
USART0_Handler
USART1_Handler


                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF

                END


