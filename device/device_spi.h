//
// Created by bakatrouble on 14/10/22.
//

#ifndef HAL_DEVICE_SPI_H
#define HAL_DEVICE_SPI_H

#include <stdbool.h>
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SPI_8BIT,
    SPI_16BIT,
} SPI_size;

typedef struct{
    SPI_size spi_sz;
    SPI_size dma_sz;
    bool dma_mem_inc;
} spi_config_t;

extern spi_config_t spi_config;

void spi_transmit(const uint8_t *buf, uint16_t n);
void spi_transmit_dma(uint8_t *buf, uint16_t n, bool wait);
void spi_set_size(SPI_size size);
void spi_set_mem_mode_dma(bool increase, SPI_size size);


#ifdef __cplusplus
}
#endif

#endif //HAL_DEVICE_SPI_H
