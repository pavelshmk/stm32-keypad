//
// Created by bakatrouble on 12/11/22.
//

#ifndef KEYPAD_CMSIS_FREERTOS_USB_H
#define KEYPAD_CMSIS_FREERTOS_USB_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    REPORT_ID_KEYBOARD = 1,
    REPORT_ID_KEYBOARD_NKRO,
    REPORT_ID_MOUSE,
    REPORT_ID_CONSUMER_CONTROL,
    REPORT_ID_GAMEPAD,
    REPORT_ID_COUNT
};

typedef struct USB USB;

struct USB {
    bool msc_enabled;
};

#ifdef __cplusplus
}
#endif

#endif //KEYPAD_CMSIS_FREERTOS_USB_H
