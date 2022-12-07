#include "device_uart.h"
#include <ringbuffer.h>
#include "device_gpio.h"

ring_buffer_t tx_fifo, rx_fifo;

static inline void uart_enable_txei(void) {
    SET_BIT(USART1->CR1, USART_CR1_TXEIE);
}

static inline void uart_disable_txei(void) {
    CLEAR_BIT(USART1->CR1, USART_CR1_TXEIE);
}

static inline void uart_enable_rxnei(void) {
    SET_BIT(USART1->CR1, USART_CR1_RXNEIE);
}

UART_HandleTypeDef huart1;

void uart_init(void) {
    gpio_pin_init(GPIOA, GPIO_PIN_10 | GPIO_PIN_15, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF7_USART1);

    __HAL_RCC_USART1_CLK_ENABLE();

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 921600;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart1);

    // init ring buffers
    ring_buffer_init(&tx_fifo);
    ring_buffer_init(&rx_fifo);

    uart_enable_rxnei();

    NVIC_EnableIRQ(USART1_IRQn);
}

void uart_ring_put(uint8_t c) {
    while (RING_BUFFER_SIZE - ring_buffer_num_items(&tx_fifo) < 5);  // wait for ring buf to free up
    NVIC_DisableIRQ(USART1_IRQn);
    ring_buffer_queue(&tx_fifo, c);
    uart_enable_txei();
    NVIC_EnableIRQ(USART1_IRQn);
}

uint8_t uart_ring_get(void) {
    char ret;
    NVIC_DisableIRQ(USART1_IRQn);
    ring_buffer_dequeue(&rx_fifo, &ret);
    NVIC_EnableIRQ(USART1_IRQn);
    return ret;
}

void uart_transmit(const uint8_t *buf, size_t n) {
    while (n) {
        uart_ring_put(*buf);
        buf++;
        n--;
    }
}

uint16_t uart_available(void) {
    return ring_buffer_num_items(&rx_fifo);
}

void uart_wait_for_transfer(void) {
    while (!ring_buffer_is_empty(&tx_fifo)) {
        HAL_Delay(10);
    }
}

void USART1_IRQHandler(void) {
    // rx enabled and rx not empty
    if((USART1->SR & USART_SR_RXNE) && (USART1->CR1 & USART_CR1_RXNEIE)) {
        char b = (char)USART1->DR;
        ring_buffer_queue(&rx_fifo, b);
    }

    // tx enabled and tx empty
    if ((USART1->SR & USART_SR_TXE) && (USART1->CR1 & USART_CR1_TXEIE)) {
        if (ring_buffer_is_empty(&tx_fifo)) {
            uart_disable_txei();
        } else {
            char data;
            ring_buffer_dequeue(&tx_fifo, &data);
            USART1->SR;
            USART1->DR = data;  // send
        }
    }
}
