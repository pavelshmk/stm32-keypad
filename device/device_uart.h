//
// Created by bakatrouble on 14/10/22.
//

#ifndef STATEOS_NASA_DEVICE_UART_H
#define STATEOS_NASA_DEVICE_UART_H

#ifdef  __cplusplus
extern "C" {
#endif//__cplusplus

#include <stddef.h>
#include "stm32f4xx.h"

void uart_ring_put(uint8_t c);
uint8_t uart_ring_get(void);
void uart_transmit(const uint8_t *buf, size_t n);
uint16_t uart_available(void);
void uart_wait_for_transfer(void);

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif //STATEOS_NASA_DEVICE_UART_H
