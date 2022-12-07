//
// Created by bakatrouble on 15/10/22.
//

#ifndef HAL_DEVICE_BUZZER_H
#define HAL_DEVICE_BUZZER_H

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void buzzer_start(void);
void buzzer_stop(void);
void buzzer_set_frequency(uint32_t frequency);

#ifdef __cplusplus
}
#endif

#endif //HAL_DEVICE_BUZZER_H
