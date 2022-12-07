#include <sys/cdefs.h>
//
// Created by bakatrouble on 07/11/22.
//

#ifndef HAL_INPUT_H
#define HAL_INPUT_H

#include <stdint.h>

#define IS_SPECIAL_SCANCODE(code) (((code) & 0xFF00) == 0xFF00)

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    INPUT_EVENT_DOWN = 1 << 0,
    INPUT_EVENT_UP = 1 << 1,
    INPUT_EVENT_PRESS = 1 << 2,
    INPUT_EVENT_LONGPRESS = 1 << 3,
} InputEventType;

typedef struct {
    uint8_t flags;
    uint16_t scancode;  // row << 8 | col
} InputEvent;

typedef enum {
    KEY_PUSH1 = 0xFF00,
    KEY_PUSH2,
    KEY_CENTER,
    KEY_CW,
    KEY_CCW,
} InputScancode;

#ifdef __cplusplus
}
#endif

#endif //HAL_INPUT_H
