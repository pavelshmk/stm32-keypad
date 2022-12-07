#include "stm32f4xx_hal.h"

TIM_HandleTypeDef htim4;

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority) {
    RCC_ClkInitTypeDef    clkconfig;
    uint32_t              uwTimclock, uwAPB1Prescaler = 0U;

    uint32_t              uwPrescalerValue = 0U;
    uint32_t              pFLatency;
    __HAL_RCC_TIM4_CLK_ENABLE();

    /* Get clock configuration */
    HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

    /* Get APB1 prescaler */
    uwAPB1Prescaler = clkconfig.APB1CLKDivider;
    /* Compute TIM4 clock */
    if (uwAPB1Prescaler == RCC_HCLK_DIV1)
    {
        uwTimclock = HAL_RCC_GetPCLK1Freq();
    }
    else
    {
        uwTimclock = 2UL * HAL_RCC_GetPCLK1Freq();
    }

    /* Compute the prescaler value to have TIM4 counter clock equal to 1MHz */
    uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000U) - 1U);

    htim4.Instance = TIM4;
    htim4.Init.Period = (1000000U / 1000U) - 1U;
    htim4.Init.Prescaler = uwPrescalerValue;
    htim4.Init.ClockDivision = 0;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    HAL_TIM_Base_Init(&htim4);
    HAL_TIM_Base_Start_IT(&htim4);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
    HAL_NVIC_SetPriority(TIM4_IRQn, TICK_INT_PRIORITY, 0U);

    __HAL_TIM_ENABLE_IT(&htim4, TIM_IT_UPDATE);

    return HAL_OK;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM4) {
        HAL_IncTick();
    }
}

void TIM4_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim4);
}
