//
// Created by bakatrouble on 14/10/22.
//

#include "device_spi.h"
#include "device_gpio.h"

DMA_HandleTypeDef hdma_spi_tx;
SPI_HandleTypeDef hspi;

spi_config_t spi_config = {
        .spi_sz = SPI_8BIT,
        .dma_sz = SPI_8BIT,
        .dma_mem_inc = true,
};

void spi_init(void) {
    __HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_DMA2_CLK_ENABLE();


    gpio_pin_init(GPIOA, GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI1);
    gpio_pin_init(GPIOB, GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI1);

    hdma_spi_tx.Instance = DMA2_Stream2;
    hdma_spi_tx.Init.Channel = DMA_CHANNEL_2;
    hdma_spi_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi_tx.Init.Mode = DMA_NORMAL;
    hdma_spi_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&hdma_spi_tx);

    __HAL_LINKDMA(&hspi, hdmatx, hdma_spi_tx);

    hspi.Instance = SPI1;
    hspi.Init.Mode = SPI_MODE_MASTER;
    hspi.Init.Direction = SPI_DIRECTION_2LINES;
    hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi.Init.NSS = SPI_NSS_SOFT;
    hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi.Init.CRCPolynomial = 10;
    HAL_SPI_Init(&hspi);

    HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
}

void spi_transmit(const uint8_t *buf, uint16_t n) {
    HAL_SPI_Transmit(&hspi, buf, n, HAL_MAX_DELAY);
}

void spi_transmit_dma(uint8_t *buf, uint16_t n, bool wait) {
    HAL_SPI_Transmit_DMA(&hspi, buf, n);
    if (wait) {
        while(HAL_DMA_GetState(hspi.hdmatx) != HAL_DMA_STATE_READY);
    }
}

void spi_set_size(SPI_size size) {
    if (spi_config.spi_sz != size) {
        __HAL_SPI_DISABLE(&hspi);
        spi_config.spi_sz = size;


        if (size == SPI_16BIT) {
            hspi.Init.DataSize = SPI_DATASIZE_16BIT;
            SET_BIT(hspi.Instance->CR1, SPI_CR1_DFF);
        } else {
            hspi.Init.DataSize = SPI_DATASIZE_8BIT;
            CLEAR_BIT(hspi.Instance->CR1, SPI_CR1_DFF);
        }
    }
}

void spi_set_mem_mode_dma(bool increase, SPI_size size) {
    spi_set_size(size);
    if (spi_config.dma_sz != size || spi_config.dma_mem_inc != increase) {
        spi_config.dma_sz = size;
        spi_config.dma_mem_inc = increase;
        __HAL_DMA_DISABLE(hspi.hdmatx);
        while((hspi.hdmatx->Instance->CR & DMA_SxCR_EN) != RESET);

        if (increase) {
            hspi.hdmatx->Init.MemInc = DMA_MINC_ENABLE;
            SET_BIT(hspi.hdmatx->Instance->CR, DMA_SxCR_MINC);
        } else {
            hspi.hdmatx->Init.MemInc = DMA_MINC_DISABLE;
            SET_BIT(hspi.hdmatx->Instance->CR, DMA_SxCR_MINC);
        }

        if (size == SPI_16BIT) {
            hspi.hdmatx->Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
            hspi.hdmatx->Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
            MODIFY_REG(hspi.hdmatx->Instance->CR,
                         DMA_SxCR_PSIZE_Msk | DMA_SxCR_MSIZE_Msk,
                         1<<DMA_SxCR_PSIZE_Pos | 1<<DMA_SxCR_MSIZE_Pos);
        } else {
            hspi.hdmatx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
            hspi.hdmatx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
            MODIFY_REG(hspi.hdmatx->Instance->CR,
                         DMA_SxCR_PSIZE_Msk | DMA_SxCR_MSIZE_Msk,
                         0);
        }
    }
}

void DMA2_Stream2_IRQHandler(void) {
    HAL_DMA_IRQHandler(&hdma_spi_tx);
}
