//
// Created by bakatrouble on 16/10/22.
//

#include <memory.h>
#include "backlight.h"
#include "record.h"
#include "stm32f4xx_hal.h"
#include "services.h"
#include "FreeRTOS.h"

#define BACKLIGHT_F_DIRTY (1 << 0)
#define NEOPIXEL_ZERO 26
#define NEOPIXEL_ONE 66
#define color_r(rgb) ((rgb >> 16) & 0xFF)
#define color_g(rgb) ((rgb >>  8) & 0xFF)
#define color_b(rgb) ((rgb >>  0) & 0xFF)

const char *BACKLIGHT_SVC = "backlight";

extern TIM_HandleTypeDef htim3;
extern osEventFlagsId_t backlight_dma_idle_flg;
//extern flg_t backlight_dma_flg[];

osEventFlagsAttr_t backlight_svc_flags_attr = {
        .name = "backlight_svc_flags",
        .attr_bits = 1,
};
osMutexAttr_t backlight_svc_mutex_attr = {
        .name = "backlight_svc_mutex",
};

void backlight_setpixel_int(Backlight *backlight, uint8_t idx, uint32_t rgb) {
    backlight->pixels[idx].color.r = color_r(rgb);
    backlight->pixels[idx].color.g = color_g(rgb);
    backlight->pixels[idx].color.b = color_b(rgb);
}

void backlight_fill(Backlight *backlight, uint32_t rgb) {
    osMutexAcquire(backlight->mutex, osWaitForever);
//    mtx_lock(backlight->mutex);

    for (uint8_t i=0; i < BACKLIGHT_PIXELS; i++) {
        backlight_setpixel_int(backlight, i, rgb);
    }

    osEventFlagsSet(backlight->flags, BACKLIGHT_F_DIRTY);
//    flg_set(backlight->flags, BACKLIGHT_F_DIRTY);
    osMutexRelease(backlight->mutex);
//    mtx_unlock(backlight->mutex);
}

void backlight_setpixel(Backlight *backlight, uint8_t idx, uint32_t rgb) {
    osMutexAcquire(backlight->mutex, osWaitForever);
//    mtx_lock(backlight->mutex);

    backlight_setpixel_int(backlight, idx, rgb);

    osEventFlagsSet(backlight->flags, BACKLIGHT_F_DIRTY);
//    flg_set(backlight->flags, BACKLIGHT_F_DIRTY);
    osMutexRelease(backlight->mutex);
//    mtx_unlock(backlight->mutex);
}

void backlight_svc(void *p) {
    Backlight *backlight = pvPortMalloc(sizeof(Backlight));
    memset(backlight->pixels, 0, sizeof(backlight->pixels));
    memset(backlight->dma_buffer, 0, sizeof(backlight->dma_buffer));
    backlight->flags = osEventFlagsNew(&backlight_svc_flags_attr);
    backlight->mutex = osMutexNew(&backlight_svc_mutex_attr);
//    backlight->flags = flg_create(0);
//    backlight->mutex = mtx_create(mtxNormal, 0);
    record_create(BACKLIGHT_SVC, backlight);

    mark_service_started(SVC_BACKLIGHT_RUNNING);

    while (true) {
        uint32_t flags = osEventFlagsWait(backlight->flags, BACKLIGHT_F_DIRTY, osFlagsWaitAny, osWaitForever);
        if (flags && !(flags & 0xF0000000)) {
            osEventFlagsWait(backlight_dma_idle_flg, 1, osFlagsWaitAny, osWaitForever);
//            flg_wait(backlight_dma_flg, 1, flgAny);
            osMutexAcquire(backlight->mutex, osWaitForever);
//    mtx_lock(backlight->mutex);

            htim3.Instance->CCR1 = 0;
            uint32_t *_pBuff = backlight->dma_buffer + 64;
            for (uint8_t i=0; i < BACKLIGHT_PIXELS; i++) {
                for (int8_t j = 23; j >= 0; j--){
                    if ((backlight->pixels[i].data >> j) & 0x01) {
                        *_pBuff = NEOPIXEL_ONE;
                    } else {
                        *_pBuff = NEOPIXEL_ZERO;
                    }
                    _pBuff++;
                }
            }

            osMutexRelease(backlight->mutex);
//    mtx_unlock(backlight->mutex);

            HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_3, backlight->dma_buffer, BACKLIGHT_PIXELS * 32 + 1);
        }
    }
}
