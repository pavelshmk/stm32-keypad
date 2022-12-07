//
// Created by bakatrouble on 08/11/22.
//

#ifndef HAL_CANVAS_I_H
#define HAL_CANVAS_I_H

#include "canvas.h"

struct Canvas {
//    Gui *gui;
    uint16_t color;
    uint16_t bg_color;
    u8g2_font_t font;
};

#endif //HAL_CANVAS_I_H
