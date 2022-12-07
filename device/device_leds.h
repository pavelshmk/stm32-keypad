//
// Created by bakatrouble on 09/11/22.
//

#ifndef HAL_DEVICE_LEDS_H
#define HAL_DEVICE_LEDS_H

#include <stdbool.h>
#include <stm32f4xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

inline void leds_set_r(bool r) {
    GPIOA->BSRR = (uint32_t)GPIO_PIN_8 << (!r ? 0 : 16);
}
inline void leds_set_g(bool g) {
    GPIOA->BSRR = (uint32_t)GPIO_PIN_9 << (!g ? 0 : 16);
}
inline void leds_set_b(bool b) {
    GPIOA->BSRR = (uint32_t)GPIO_PIN_10 << (!b ? 0 : 16);
}
inline void leds_set(bool r, bool g, bool b) {
    uint32_t value = 0;
    value |= (uint32_t)GPIO_PIN_8 << (!r ? 0 : 16);
    value |= (uint32_t)GPIO_PIN_9 << (!g ? 0 : 16);
    value |= (uint32_t)GPIO_PIN_10 << (!b ? 0 : 16);
    GPIOA->BSRR = value;
}

#ifdef __cplusplus
}
#endif

#endif //HAL_DEVICE_LEDS_H
