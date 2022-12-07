//
// Created by bakatrouble on 15/10/22.
//

#include "device_gpio.h"
#include "device_input_pins.h"
#include <cmsis_os2.h>

TIM_HandleTypeDef htim5;

void inputs_init(void) {
    TIM_Encoder_InitTypeDef sConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    __HAL_RCC_TIM5_CLK_ENABLE();

    gpio_pin_init(GPIOC, COL1_Pin | COL2_Pin | COL3_Pin | PUSH1_Pin | PUSH2_Pin | ROT_PUSH_Pin, GPIO_MODE_INPUT,
                  GPIO_PULLUP, 0, 0);
    gpio_pin_init(GPIOC, ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,
                  GPIO_SPEED_FREQ_VERY_HIGH, 0);
    gpio_pin_init(GPIOA, ROT_A_Pin | ROT_B_Pin, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_AF2_TIM5);

    htim5.Instance = TIM5;
    htim5.Init.Prescaler = 1;
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim5.Init.Period = 15;
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
    sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
    sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
    sConfig.IC1Filter = 15;
    sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
    sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
    sConfig.IC2Filter = 15;
    HAL_TIM_Encoder_Init(&htim5, &sConfig);
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig);
//    // TI1 edge detector
//    TIM5->SMCR = (TIM5->SMCR & ~(TIM_SMCR_TS_0 | TIM_SMCR_TS_1)) | TIM_SMCR_TS_2;
//    // enable interrupt
//    TIM5->DIER |= TIM_DIER_TIE;

//    HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
//    HAL_NVIC_SetPriority(EXTI1_IRQn, 5, 0);
//    HAL_NVIC_SetPriority(EXTI3_IRQn, 5, 0);
//    HAL_NVIC_SetPriority(TIM5_IRQn, 5, 0);
//    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
//    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
//    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
//    HAL_NVIC_EnableIRQ(TIM5_IRQn);

    HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_1);
}

//void HAL_GPIO_EXTI_Callback(uint16_t pin) {
//    inputs_msg_t msg;
//    switch (pin) {
//        case PUSH1_Pin:
//            msg.type = INPUT_PUSH1;
//            msg.pressed = !HAL_GPIO_ReadPin(GPIOC, PUSH1_Pin);
//            msg_pushISR(inputs_isr_mq, &msg, sizeof(msg));
//            break;
//        case PUSH2_Pin:
//            msg.type = INPUT_PUSH2;
//            msg.pressed = !HAL_GPIO_ReadPin(GPIOC, PUSH2_Pin);
//            msg_pushISR(inputs_isr_mq, &msg, sizeof(msg));
//            break;
//        case ROT_PUSH_Pin:
//            msg.type = INPUT_ROT_PUSH;
//            msg.pressed = !HAL_GPIO_ReadPin(GPIOC, ROT_PUSH_Pin);
//            msg_pushISR(inputs_isr_mq, &msg, sizeof(msg));
//            break;
//    }
//}

//void EXTI0_IRQHandler(void) {
//    HAL_GPIO_EXTI_IRQHandler(PUSH1_Pin);
//}
//
//void EXTI1_IRQHandler(void) {
//    HAL_GPIO_EXTI_IRQHandler(PUSH2_Pin);
//}
//
//void EXTI3_IRQHandler(void) {
//    HAL_GPIO_EXTI_IRQHandler(ROT_PUSH_Pin);
//}

//uint32_t lastEncoderValue = 0;
//void TIM5_IRQHandler(void) {
//    if(TIM5->SR & TIM_SR_TIF){
//        bool msg;
//        uint32_t currentEncoderValue = TIM5->CNT;
//        if (currentEncoderValue != lastEncoderValue) {
//            if (lastEncoderValue == 15 && currentEncoderValue == 0) {
//                msg = true;
//            } else if (lastEncoderValue == 0 && currentEncoderValue == 15) {
//                msg = false;
//            } else if (currentEncoderValue > lastEncoderValue) {
//                msg = true;
//            } else if (currentEncoderValue < lastEncoderValue) {
//                msg = false;
//            }
//            msg_pushISR(inputs_isr_mq, &msg, sizeof(msg));
//            lastEncoderValue = currentEncoderValue;
//        }
//
//        /* Clear interrupt */
//        TIM5->SR &= ~TIM_SR_TIF;
//    }
//}
