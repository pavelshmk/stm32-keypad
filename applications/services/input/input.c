#include <sys/cdefs.h>
//
// Created by bakatrouble on 07/11/22.
//

#include "input.h"
#include <device.h>
#include <pubsub.h>
#include <record.h>
#include "device_input_pins.h"
#include "services.h"
#include "FreeRTOS.h"
#include <cmsis_os2.h>
#include <memory.h>

#define INPUT_KEYS_COUNT 15
#define PUSH1_IDX 0
#define PUSH2_IDX 1
#define CENTER_IDX 2

#define LONGPRESS_DURATION 300

const char *INPUT_PUBSUB = "inp_pubsub";

osMessageQueueAttr_t input_svc_queue_attr = {
        .name = "input_svc_queue",
};

void input_set_row(uint8_t idx) {
    uint32_t msk = ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin;
    switch (idx) {
        case 0:
            msk &= ~(uint32_t)ROW1_Pin;
            msk |= (uint32_t)ROW1_Pin << 16;
            break;
        case 1:
            msk &= ~(uint32_t)ROW2_Pin;
            msk |= (uint32_t)ROW2_Pin << 16;
            break;
        case 2:
            msk &= ~(uint32_t)ROW3_Pin;
            msk |= (uint32_t)ROW3_Pin << 16;
            break;
        case 3:
            msk &= ~(uint32_t)ROW4_Pin;
            msk |= (uint32_t)ROW4_Pin << 16;
            break;
        case 4:
            msk &= ~(uint32_t)ROW5_Pin;
            msk |= (uint32_t)ROW5_Pin << 16;
            break;
    }
    GPIOC->BSRR = msk;
}

const uint16_t cols[] = { COL1_Pin, COL2_Pin, COL3_Pin };
const uint16_t rows[] = { ROW1_Pin, ROW2_Pin, ROW3_Pin, ROW4_Pin, ROW5_Pin };

typedef struct {
    bool pressed;
    uint32_t pressedTick;
    bool long_press_sent;
} KeyStatus;

typedef struct {
    KeyStatus key_statuses[INPUT_KEYS_COUNT + 3];
    osMessageQueueId_t queue;
//    msg_t *queue;
    InputEvent *msg;
} Input;

void input_process_key_status(Input *input, uint32_t tick, uint32_t scancode, uint8_t idx, bool down) {
    if (down && !input->key_statuses[idx].pressed) {
        input->msg->flags = INPUT_EVENT_DOWN;
        input->msg->scancode = scancode;
        osMessageQueuePut(input->queue, input->msg, sizeof(InputEvent), osWaitForever);
        input->key_statuses[idx].pressed = true;
        input->key_statuses[idx].pressedTick = tick;
        input->key_statuses[idx].long_press_sent = false;
    } else if (!down && input->key_statuses[idx].pressed) {
        input->msg->flags = INPUT_EVENT_UP;
        input->msg->scancode = scancode;
        if (!input->key_statuses[idx].long_press_sent) {
            input->msg->flags |= INPUT_EVENT_PRESS;
        }
        osMessageQueuePut(input->queue, input->msg, sizeof(InputEvent), osWaitForever);
        input->key_statuses[idx].pressed = false;
    }
}

_Noreturn void input_svc(void *p) {
    InputEvent *msg = pvPortMalloc(sizeof(InputEvent));

    PubSub *pubsub = pubsub_alloc();
    record_create(INPUT_PUBSUB, pubsub);
    Input *input = pvPortMalloc(sizeof(Input));
    memset(input, 0, sizeof(Input));
    input->queue = osMessageQueueNew(16, sizeof(InputEvent), &input_svc_queue_attr);
//    input->queue = msg_create(16, sizeof(InputEvent));
    input->msg = msg;

    mark_service_started(SVC_INPUT_RUNNING);

    size_t read;
    bool cw;
    int8_t lastEncoderValue = TIM5->CNT;
    while (true) {
        uint32_t tick = HAL_GetTick();

        for (uint16_t i=0; i < INPUT_KEYS_COUNT + 3; i++) {
            if (
                    input->key_statuses[i].pressed &&
                    !input->key_statuses[i].long_press_sent &&
                    tick - input->key_statuses[i].pressedTick >= LONGPRESS_DURATION
            ) {
                if (i >= 15) {
                    msg->scancode = i - 15 + 0xFF00;
                } else {
                    msg->scancode = ((i / 3) << 8) | (i % 3);
                }
                msg->flags = INPUT_EVENT_LONGPRESS;
                osMessageQueuePut(input->queue, msg, sizeof(InputEvent), 0);
                input->key_statuses[i].long_press_sent = true;
            }
        }

        __HAL_FLASH_INSTRUCTION_CACHE_DISABLE();
        for (uint8_t r = 0; r < 5; r++) {
            for (uint8_t c = 0; c < 3; c++) {
                input_set_row(r);
                bool keyPressed = !HAL_GPIO_ReadPin(GPIOC, cols[c]);
                input_process_key_status(input, tick, r << 8 | c, r * 3 + c, keyPressed);
                input_set_row(0xFF);
                for (uint8_t i=0; i < 0x02; i++) {
                    asm("nop");
                }
            }
        }
        __HAL_FLASH_INSTRUCTION_CACHE_ENABLE();

        {
            bool push1Pressed = !HAL_GPIO_ReadPin(GPIOC, PUSH1_Pin);
            input_process_key_status(input, tick, KEY_PUSH1, INPUT_KEYS_COUNT + PUSH1_IDX, push1Pressed);
        }
        {
            bool push2Pressed = !HAL_GPIO_ReadPin(GPIOC, PUSH2_Pin);
            input_process_key_status(input, tick, KEY_PUSH2, INPUT_KEYS_COUNT + PUSH2_IDX, push2Pressed);
        }
        {
            bool centerPressed = !HAL_GPIO_ReadPin(GPIOC, ROT_PUSH_Pin);
            input_process_key_status(input, tick, KEY_CENTER, INPUT_KEYS_COUNT + CENTER_IDX, centerPressed);
        }

        {
            uint32_t currentEncoderValue = TIM5->CNT;
            if (currentEncoderValue != lastEncoderValue) {
                if (lastEncoderValue == 15 && currentEncoderValue == 0) {
                    msg->scancode = KEY_CW;
                } else if (lastEncoderValue == 0 && currentEncoderValue == 15) {
                    msg->scancode = KEY_CCW;
                } else if (currentEncoderValue > lastEncoderValue) {
                    msg->scancode = KEY_CW;
                } else if (currentEncoderValue < lastEncoderValue) {
                    msg->scancode = KEY_CCW;
                }
                msg->flags = INPUT_EVENT_PRESS;
                osMessageQueuePut(input->queue, msg, sizeof(InputEvent), 0);
                lastEncoderValue = currentEncoderValue;
            }
        }


//        while (osMessageQueueGet(inputs_isr_mq, &cw, sizeof(bool), &read) == E_SUCCESS) {
//            msg->flags = INPUT_EVENT_PRESS;
//            msg->scancode = cw ? KEY_CW : KEY_CCW;
//            osMessageQueuePut(input->queue, msg, sizeof(InputEvent));
//        }

        while (osMessageQueueGet(input->queue, msg, 0, 0) == osOK) {
            pubsub_publish(pubsub, msg);
        }
        osDelay(1);
    }
}
