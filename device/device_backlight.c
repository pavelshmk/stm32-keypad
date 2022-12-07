#include "stm32f4xx_hal.h"
#include "device_gpio.h"
#include <cmsis_os2.h>

DMA_HandleTypeDef hdma_tim3_ch3;
TIM_HandleTypeDef htim3;

osEventFlagsId_t backlight_dma_idle_flg;
osEventFlagsAttr_t backlight_dma_idle_flg_attrs = {
        .name = "backlight_dma_idle_flg",
        .attr_bits = 1,
};

void backlight_init(void) {
    backlight_dma_idle_flg = osEventFlagsNew(&backlight_dma_idle_flg_attrs);
    osEventFlagsSet(backlight_dma_idle_flg, 1);

    gpio_pin_init(GPIOB, GPIO_PIN_0, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF2_TIM3);

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();

    hdma_tim3_ch3.Instance = DMA1_Stream7;
    hdma_tim3_ch3.Init.Channel = DMA_CHANNEL_5;
    hdma_tim3_ch3.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_tim3_ch3.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim3_ch3.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim3_ch3.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim3_ch3.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim3_ch3.Init.Mode = DMA_NORMAL;
    hdma_tim3_ch3.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    hdma_tim3_ch3.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&hdma_tim3_ch3);

    HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);

    __HAL_LINKDMA(&htim3, hdma[TIM_DMA_ID_CC3], hdma_tim3_ch3);

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 0;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 114 - 1;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim3);

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);

    HAL_TIM_PWM_Init(&htim3);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3);
}

void DMA1_Stream7_IRQHandler(void) {
    HAL_DMA_IRQHandler(&hdma_tim3_ch3);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3) {
        HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_3);
        osEventFlagsSet(backlight_dma_idle_flg, 1);
    }
}
