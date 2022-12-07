//
// Created by bakatrouble on 13/11/22.
//

#ifndef KEYPAD_CMSIS_FREERTOS_HID_H
#define KEYPAD_CMSIS_FREERTOS_HID_H

#include <stm32f4xx_hal.h>
#include <cmsis_os2.h>
#include <keycodes.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct HIDLayout HIDLayout;
typedef struct HID HID;

struct HIDLayout {
    struct {
        uint16_t keycodes[3][5];
    } layers[9];
    uint8_t layers_count;
};

struct HID {
    bool active;
    uint8_t layer;
    HIDLayout *layout;
    osMessageQueueId_t queue;
};

#ifdef __cplusplus
}
#endif

#endif //KEYPAD_CMSIS_FREERTOS_HID_H
