//
// Created by bakatrouble on 16/10/22.
//

#ifndef HAL_BACKLIGHT_H
#define HAL_BACKLIGHT_H

#include <cmsis_os2.h>

#define BACKLIGHT_PIXELS 15
#define backlight_color_rgb(r, g, b) (((uint32_t)r << 16) | ((uint32_t)g << 8) | ((uint32_t)b << 0))

#ifdef __cplusplus
extern "C" {
#endif

typedef union {
    struct {
        uint8_t b;
        uint8_t r;
        uint8_t g;
    } color;
    uint32_t data;
} PixelRGB;

typedef struct {
    PixelRGB pixels[BACKLIGHT_PIXELS];
    uint32_t dma_buffer[BACKLIGHT_PIXELS * 40 + 1];
    osEventFlagsId_t flags;
//    flg_t *flags;
    osMutexId_t mutex;
//    mtx_t *mutex;
} Backlight;

void backlight_fill(Backlight *backlight, uint32_t rgb);
void backlight_setpixel(Backlight *backlight, uint8_t idx, uint32_t rgb);

#ifdef __cplusplus
}
#endif

#endif //HAL_BACKLIGHT_H
