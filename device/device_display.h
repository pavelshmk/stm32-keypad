#ifndef __SSD1351_H__
#define __SSD1351_H__

#include "device_lcd_fonts.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************/

// Color definitions
#define	SSD1351_BLACK   0x0000
#define	SSD1351_BLUE    0x001F
#define	SSD1351_RED     0xF800
#define	SSD1351_GREEN   0x07E0
#define SSD1351_CYAN    0x07FF
#define SSD1351_MAGENTA 0xF81F
#define SSD1351_YELLOW  0xFFE0
#define SSD1351_WHITE   0xFFFF
#define SSD1351_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

// call before initializing any SPI devices
void display_unselect();

void display_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
void display_write_string(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void display_fill_rectangle(uint16_t x_, uint16_t y_, uint16_t w, uint16_t h, uint16_t color);
void display_fill_screen(uint16_t color);
void display_draw_bitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
void display_invert_colors(bool invert);
void display_update(void);
void display_update_no_dma(void);
void display_draw_bitmap_1(uint16_t x_, uint16_t y_, uint8_t *bitmap, uint16_t w, uint16_t h, uint16_t color, uint16_t bgcolor);

#ifdef __cplusplus
}
#endif

#endif // __SSD1351_H__
