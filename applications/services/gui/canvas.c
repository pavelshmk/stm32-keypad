//
// Created by bakatrouble on 07/11/22.
//

#include "canvas_i.h"
#include "FreeRTOS.h"

char printf_buf[256];

Canvas *canvas_alloc() {
    Canvas *canvas = pvPortMalloc(sizeof(Canvas));
    canvas->font.canvas = canvas;
    u8g2_SetFont(&canvas->font, u8g2_font_haxrcorp4089_tr);
    u8g2_SetFontDirection(&canvas->font, 0);
    u8g2_SetFontMode(&canvas->font, 0);
    canvas->color = 0xFFFF;
    canvas->bg_color = 0x0000;
    canvas_clear(canvas);
    canvas_commit(canvas);
    return canvas;
}

void canvas_fill(Canvas *canvas, uint16_t color) {
    UNUSED(canvas);
    display_fill_screen(color);
}

inline void canvas_clear(Canvas *canvas) {
    canvas_fill(canvas, 0x0000);
}

void canvas_puts(Canvas *canvas, uint8_t x, uint8_t y, const char *str) {
//    display_write_string(x, y, str, *canvas->font, canvas->color, canvas->bg_color);
    u8g2_DrawStr(&canvas->font, x, y, str);
}

void canvas_set_font(Canvas *canvas, const uint8_t *font) {
    u8g2_SetFont(&canvas->font, u8g2_font_haxrcorp4089_tr);
}

void canvas_set_font_color(Canvas *canvas, uint16_t color) {
    color = (color << 8) | (color >> 8);
    u8g2_SetForegroundColor(&canvas->font, color);
}

void canvas_set_font_bgcolor(Canvas *canvas, uint16_t color) {
    color = (color << 8) | (color >> 8);
    u8g2_SetBackgroundColor(&canvas->font, color);
}

void canvas_set_color(Canvas *canvas, uint16_t color) {
    canvas->color = color;
}

void canvas_set_bgcolor(Canvas *canvas, uint16_t color) {
    canvas->bg_color = color;
}

void canvas_commit(Canvas *canvas) {
    display_update();
}

void canvas_draw_bitmap_1(Canvas *canvas, uint16_t x, uint16_t y, const CanvasBitmapDef *bitmapDef) {
    display_draw_bitmap_1(x, y, bitmapDef->data, bitmapDef->w, bitmapDef->h, canvas->color, canvas->bg_color);
}

void canvas_draw_fast_vline(Canvas *canvas, uint16_t x, uint16_t y_, uint16_t len, uint16_t color) {
    for (uint16_t y = y_; y < y_ + len; y++) {
        display_draw_pixel(x, y, color);
    }
}

void canvas_draw_fast_hline(Canvas *canvas, uint16_t x_, uint16_t y, uint16_t len, uint16_t color) {
    for (uint16_t x = x_; x < x_ + len; x++) {
        display_draw_pixel(x, y, color);
    }
}
