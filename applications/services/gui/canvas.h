//
// Created by bakatrouble on 07/11/22.
//

#ifndef HAL_CANVAS_H
#define HAL_CANVAS_H

#include <device.h>
#include "canvas_u8g2_font.h"

#define canvas_color565(rgb) ((((rgb >> 16) & 0xF8) << 8) | (((rgb >> 8) & 0xFC) << 3) | ((rgb & 0xF8) >> 3))
#define canvas_le_to_be(x) (((x) << 8) | ((x) >> 8))
//#define canvas_color565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

#define canvas_printf(canvas, x, y, fmt, ...) \
        sprintf(printf_buf, fmt, _VA_FLG(__VA_ARGS__)); canvas_puts(canvas, x, y, printf_buf)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Canvas Canvas;

typedef struct {
    uint16_t w;
    uint16_t h;
    uint8_t *data;
} CanvasBitmapDef;

Canvas *canvas_alloc();
void canvas_fill(Canvas *canvas, uint16_t color);
void canvas_clear(Canvas *canvas);
void canvas_puts(Canvas *canvas, uint8_t x, uint8_t y, const char *str);
void canvas_set_font(Canvas *canvas, const uint8_t *font);
void canvas_set_color(Canvas *canvas, uint16_t color);
void canvas_set_bgcolor(Canvas *canvas, uint16_t color);
void canvas_set_font_color(Canvas *canvas, uint16_t color);
void canvas_set_font_bgcolor(Canvas *canvas, uint16_t color);
void canvas_draw_bitmap_1(Canvas *canvas, uint16_t x, uint16_t y, const CanvasBitmapDef *bitmapDef);
void canvas_draw_fast_vline(Canvas *canvas, uint16_t x, uint16_t y, uint16_t len, uint16_t color_be);
void canvas_draw_fast_hline(Canvas *canvas, uint16_t x, uint16_t y, uint16_t len, uint16_t color_be);
void canvas_commit(Canvas *canvas);

extern char printf_buf[256];

#ifdef __cplusplus
}
#endif


#endif //HAL_CANVAS_H
