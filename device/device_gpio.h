//
// Created by bakatrouble on 06/11/22.
//

#ifndef HAL_DEVICE_GPIO_H
#define HAL_DEVICE_GPIO_H

#include "stm32f4xx_hal.h"

inline static
void gpio_pin_init(GPIO_TypeDef *def, uint32_t pin, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t alternate) {
    switch ((uint32_t)def) {
        case GPIOA_BASE:
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        case GPIOB_BASE:
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        case GPIOC_BASE:
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        case GPIOD_BASE:
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;
        case GPIOH_BASE:
            __HAL_RCC_GPIOH_CLK_ENABLE();
            break;
    }
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = mode;
    GPIO_InitStruct.Pull = pull;
    GPIO_InitStruct.Speed = speed;
    GPIO_InitStruct.Alternate = alternate;
    HAL_GPIO_Init(def, &GPIO_InitStruct);
}

#endif //HAL_DEVICE_GPIO_H
