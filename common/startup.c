/******************************************************************************

   @file    startup.c
   @author  Rajmund Szymanski
   @date    06.06.2022
   @brief   Startup file for STM32F407VG uC

 ******************************************************************************

   Copyright (c) 2018-2022 Rajmund Szymanski. All rights reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 ******************************************************************************/

#define __PROGRAM_START

#include <stdio.h>
#include "stm32f4xx.h"
#include "device.h"
//#include "device_lcd.h"

/*******************************************************************************
 Default fault handler
*******************************************************************************/

static uint8_t fh_buf[16];
static
void Fault_Handler() {
//    struct {
//        uint32_t r0;
//        uint32_t r1;
//        uint32_t r2;
//        uint32_t r3;
//        uint32_t r12;
//        uint32_t lr;
//        uint32_t pc;
//        uint32_t psr;
//    } *stack_ptr; //Указатель на текущее значение стека(SP)
//
//    asm(
//            "TST lr, #4 \n" //Тестируем 3ий бит указателя стека(побитовое И)
//            "ITE EQ \n"   //Значение указателя стека имеет бит 3?
//            "MRSEQ %[ptr], MSP  \n"  //Да, сохраняем основной указатель стека
//            "MRSNE %[ptr], PSP  \n"  //Нет, сохраняем указатель стека процесса
//            : [ptr] "=r"(stack_ptr)
//    );
//
//    display_fill_screen(0x0000);
//    display_write_string(0, 0, "***HardFault***", Font_7x10, 0xFFFF, 0x0000);
//    display_write_string(0, 10, "CFSR: 0x", Font_7x10, 0xFFFF, 0x0000);
//    sprintf(fh_buf, "%08X", SCB->CFSR);
//    display_write_string(7*8, 10, fh_buf, Font_7x10, 0xFFFF, 0x0000);
//    if (SCB->CFSR == 0x82) {
//        display_write_string(0, 20, "Nullptr?", Font_7x10, 0xFFFF, 0x0000);
//    }
//    display_update_no_dma();

    __disable_irq();

    /* Go into an infinite loop */
    for (;;);
}


/* Default _exit handler */
__WEAK
void _exit(int code) {
    (void) code;

    /* Go into an infinite loop */
    for (;;);
}

/*******************************************************************************
 Specific definitions for the compiler
*******************************************************************************/

#include "startup.h"

/*******************************************************************************
 Default reset handler
*******************************************************************************/

__WEAK __NO_RETURN
void Reset_Handler(void) {
    __main();
}

/*******************************************************************************
 Declaration of exception handlers
*******************************************************************************/

/* Core exception handlers */
__ALIAS(Fault_Handler) void NMI_Handler(void);

__ALIAS(Fault_Handler) void HardFault_Handler(void);

__ALIAS(Fault_Handler) void MemManage_Handler(void);

__ALIAS(Fault_Handler) void BusFault_Handler(void);

__ALIAS(Fault_Handler) void UsageFault_Handler(void);

__ALIAS(Fault_Handler) void SVC_Handler(void);

__ALIAS(Fault_Handler) void DebugMon_Handler(void);

__ALIAS(Fault_Handler) void PendSV_Handler(void);

__ALIAS(Fault_Handler) void SysTick_Handler(void);

/* External interrupt handlers */
__ALIAS(Fault_Handler) void WWDG_IRQHandler(void);

__ALIAS(Fault_Handler) void PVD_IRQHandler(void);

__ALIAS(Fault_Handler) void TAMP_STAMP_IRQHandler(void);

__ALIAS(Fault_Handler) void RTC_WKUP_IRQHandler(void);

__ALIAS(Fault_Handler) void FLASH_IRQHandler(void);

__ALIAS(Fault_Handler) void RCC_IRQHandler(void);

__ALIAS(Fault_Handler) void EXTI0_IRQHandler(void);

__ALIAS(Fault_Handler) void EXTI1_IRQHandler(void);

__ALIAS(Fault_Handler) void EXTI2_IRQHandler(void);

__ALIAS(Fault_Handler) void EXTI3_IRQHandler(void);

__ALIAS(Fault_Handler) void EXTI4_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA1_Stream0_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA1_Stream1_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA1_Stream2_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA1_Stream3_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA1_Stream4_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA1_Stream5_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA1_Stream6_IRQHandler(void);

__ALIAS(Fault_Handler) void ADC_IRQHandler(void);

__ALIAS(Fault_Handler) void CAN1_TX_IRQHandler(void);

__ALIAS(Fault_Handler) void CAN1_RX0_IRQHandler(void);

__ALIAS(Fault_Handler) void CAN1_RX1_IRQHandler(void);

__ALIAS(Fault_Handler) void CAN1_SCE_IRQHandler(void);

__ALIAS(Fault_Handler) void EXTI9_5_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM1_BRK_TIM9_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM1_UP_TIM10_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM1_TRG_COM_TIM11_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM1_CC_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM2_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM3_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM4_IRQHandler(void);

__ALIAS(Fault_Handler) void I2C1_EV_IRQHandler(void);

__ALIAS(Fault_Handler) void I2C1_ER_IRQHandler(void);

__ALIAS(Fault_Handler) void I2C2_EV_IRQHandler(void);

__ALIAS(Fault_Handler) void I2C2_ER_IRQHandler(void);

__ALIAS(Fault_Handler) void SPI1_IRQHandler(void);

__ALIAS(Fault_Handler) void SPI2_IRQHandler(void);

__ALIAS(Fault_Handler) void USART1_IRQHandler(void);

__ALIAS(Fault_Handler) void USART2_IRQHandler(void);

__ALIAS(Fault_Handler) void USART3_IRQHandler(void);

__ALIAS(Fault_Handler) void EXTI15_10_IRQHandler(void);

__ALIAS(Fault_Handler) void RTC_Alarm_IRQHandler(void);

__ALIAS(Fault_Handler) void OTG_FS_WKUP_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM8_BRK_TIM12_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM8_UP_TIM13_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM8_TRG_COM_TIM14_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM8_CC_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA1_Stream7_IRQHandler(void);

__ALIAS(Fault_Handler) void SDIO_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM5_IRQHandler(void);

__ALIAS(Fault_Handler) void SPI3_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM6_IRQHandler(void);

__ALIAS(Fault_Handler) void TIM7_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA2_Stream0_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA2_Stream1_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA2_Stream2_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA2_Stream3_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA2_Stream4_IRQHandler(void);

__ALIAS(Fault_Handler) void DFSDM1_FLT0_IRQHandler(void);

__ALIAS(Fault_Handler) void DFSDM1_FLT1_IRQHandler(void);

__ALIAS(Fault_Handler) void CAN2_TX_IRQHandler(void);

__ALIAS(Fault_Handler) void CAN2_RX0_IRQHandler(void);

__ALIAS(Fault_Handler) void CAN2_RX1_IRQHandler(void);

__ALIAS(Fault_Handler) void CAN2_SCE_IRQHandler(void);

__ALIAS(Fault_Handler) void OTG_FS_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA2_Stream5_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA2_Stream6_IRQHandler(void);

__ALIAS(Fault_Handler) void DMA2_Stream7_IRQHandler(void);

__ALIAS(Fault_Handler) void USART6_IRQHandler(void);

__ALIAS(Fault_Handler) void I2C3_EV_IRQHandler(void);

__ALIAS(Fault_Handler) void I2C3_ER_IRQHandler(void);

__ALIAS(Fault_Handler) void RNG_IRQHandler(void);

__ALIAS(Fault_Handler) void FPU_IRQHandler(void);

__ALIAS(Fault_Handler) void SPI4_IRQHandler(void);

__ALIAS(Fault_Handler) void SPI5_IRQHandler(void);

__ALIAS(Fault_Handler) void QUADSPI_IRQHandler(void);

__ALIAS(Fault_Handler) void FMPI2C1_EV_IRQHandler(void);

__ALIAS(Fault_Handler) void FMPI2C1_ER_IRQHandler(void);

/*******************************************************************************
 Vector table
*******************************************************************************/

void (*const __VECTOR_TABLE[])(void) __VECTOR_TABLE_ATTRIBUTE =
   {
           /* Initial stack pointer */
           __CAST(&_estack),

           /* Core exception handlers */
           Reset_Handler,      /* Reset                                   */
           NMI_Handler,        /* Non-maskable interrupt                  */
           HardFault_Handler,  /* All classes of faults                   */
           MemManage_Handler,  /* Memory management                       */
           BusFault_Handler,   /* Pre-fetch fault, memory access fault    */
           UsageFault_Handler, /* Undefined instruction or illegal state  */
           0, 0, 0, 0,         /* Reserved                                */
           SVC_Handler,        /* System service call via SWI instruction */
           DebugMon_Handler,   /* Debug Monitor                           */
           0,                  /* Reserved                                */
           PendSV_Handler,     /* Pendable request for system service     */
           SysTick_Handler,    /* System tick timer                       */

#ifndef __NO_EXTERNAL_INTERRUPTS

           /* External interrupt handlers */
           WWDG_IRQHandler,  // 16
           PVD_IRQHandler,
           TAMP_STAMP_IRQHandler,
           RTC_WKUP_IRQHandler,
           FLASH_IRQHandler,
           RCC_IRQHandler,
           EXTI0_IRQHandler,
           EXTI1_IRQHandler,
           EXTI2_IRQHandler,
           EXTI3_IRQHandler,
           EXTI4_IRQHandler,
           DMA1_Stream0_IRQHandler,
           DMA1_Stream1_IRQHandler,
           DMA1_Stream2_IRQHandler,
           DMA1_Stream3_IRQHandler,
           DMA1_Stream4_IRQHandler,
           DMA1_Stream5_IRQHandler,
           DMA1_Stream6_IRQHandler,
           ADC_IRQHandler,
           CAN1_TX_IRQHandler,
           CAN1_RX0_IRQHandler,
           CAN1_RX1_IRQHandler,
           CAN1_SCE_IRQHandler,
           EXTI9_5_IRQHandler,
           TIM1_BRK_TIM9_IRQHandler,
           TIM1_UP_TIM10_IRQHandler,
           TIM1_TRG_COM_TIM11_IRQHandler,
           TIM1_CC_IRQHandler,
           TIM2_IRQHandler,
           TIM3_IRQHandler,
           TIM4_IRQHandler,
           I2C1_EV_IRQHandler,
           I2C1_ER_IRQHandler,
           I2C2_EV_IRQHandler,
           I2C2_ER_IRQHandler,
           SPI1_IRQHandler,
           SPI2_IRQHandler,
           USART1_IRQHandler,
           USART2_IRQHandler,
           USART3_IRQHandler,
           EXTI15_10_IRQHandler,
           RTC_Alarm_IRQHandler,
           OTG_FS_WKUP_IRQHandler,
           TIM8_BRK_TIM12_IRQHandler,
           TIM8_UP_TIM13_IRQHandler,
           TIM8_TRG_COM_TIM14_IRQHandler,
           TIM8_CC_IRQHandler,
           DMA1_Stream7_IRQHandler,
           0,
           SDIO_IRQHandler,
           TIM5_IRQHandler,
           SPI3_IRQHandler,
           0,
           0,
           TIM6_IRQHandler,
           TIM7_IRQHandler,
           DMA2_Stream0_IRQHandler,
           DMA2_Stream1_IRQHandler,
           DMA2_Stream2_IRQHandler,
           DMA2_Stream3_IRQHandler,
           DMA2_Stream4_IRQHandler,
           DFSDM1_FLT0_IRQHandler,
           DFSDM1_FLT1_IRQHandler,
           CAN2_TX_IRQHandler,
           CAN2_RX0_IRQHandler,
           CAN2_RX1_IRQHandler,
           CAN2_SCE_IRQHandler,
           OTG_FS_IRQHandler,
           DMA2_Stream5_IRQHandler,
           DMA2_Stream6_IRQHandler,
           DMA2_Stream7_IRQHandler,
           USART6_IRQHandler,
           I2C3_EV_IRQHandler,
           I2C3_ER_IRQHandler,
           0,
           0,
           0,
           0,
           0,
           0,
           RNG_IRQHandler,
           FPU_IRQHandler,
           0,                                 /* Reserved                                    */
           0,                                 /* Reserved                                    */
           SPI4_IRQHandler,                   /* SPI4                                        */
           SPI5_IRQHandler,                   /* SPI5                                        */
           0,                                 /* Reserved                                    */
           0,                                 /* Reserved                                    */
           0,                                 /* Reserved                                    */
           0,                                 /* Reserved                                    */
           0,                                 /* Reserved                                    */
           0,                                 /* Reserved                                    */
           QUADSPI_IRQHandler,                /* QuadSPI                                     */
           0,                                 /* Reserved                                    */
           0,                                 /* Reserved                                    */
           FMPI2C1_EV_IRQHandler,             /* FMPI2C1 Event                               */
           FMPI2C1_ER_IRQHandler,             /* FMPI2C1 Error                               */

#endif//__NO_EXTERNAL_INTERRUPTS
};

/******************************************************************************/
