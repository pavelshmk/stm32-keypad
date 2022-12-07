//
// Created by bakatrouble on 06/11/22.
//

#ifndef HAL_VIEWPORT_I_H
#define HAL_VIEWPORT_I_H

#include "viewport.h"
#include "gui.h"

struct ViewportInputEvent {
    Gui *gui;
    uint8_t flags;
    uint32_t scancode;
    size_t queue_size;
};

struct Viewport {
    Gui *gui;
    bool active;
    GuiLayers layer;

    ViewportInputCallback input_callback;
    void *input_callback_ctx;

    ViewportRedrawCallback redraw_callback;
    void *redraw_callback_ctx;
};

#endif //HAL_VIEWPORT_I_H
