//
// Created by bakatrouble on 12/11/22.
//

#ifndef KEYPAD_CMSIS_FREERTOS_STORAGE_H
#define KEYPAD_CMSIS_FREERTOS_STORAGE_H

#include <stdbool.h>
#include "ff.h"
#include <cmsis_os2.h>
#include <stm32f4xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Storage Storage;

struct Storage {
    bool mounted;
    FATFS fs;
    osMessageQueueId_t queue;
};

#ifdef __cplusplus
}
#endif

#endif //KEYPAD_CMSIS_FREERTOS_STORAGE_H
