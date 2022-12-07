//
// Created by bakatrouble on 09/11/22.
//

#include "device_leds.h"
#include "device_gpio.h"

void leds_init(void) {
    GPIOA->BSRR = (uint32_t)GPIO_PIN_8 | (uint32_t)GPIO_PIN_9 | (uint32_t)GPIO_PIN_10;
    gpio_pin_init(GPIOA, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0);
}
