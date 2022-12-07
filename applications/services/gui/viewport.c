//
// Created by bakatrouble on 06/11/22.
//

#include "viewport.h"
#include "viewport_i.h"
#include "record.h"
#include "applications.h"
#include "gui_i.h"
#include "FreeRTOS.h"

Viewport *viewport_alloc() {
    Viewport *viewport = pvPortMalloc(sizeof(Viewport));
    viewport->gui = record_get(GUI_SVC);
    viewport->redraw_callback = NULL;
    viewport->input_callback = NULL;
    viewport->layer = GuiLayerApp;
    return viewport;
}

void viewport_destroy(Viewport *viewport) {
    vPortFree(viewport);
}

bool viewport_draw(Viewport *viewport, Canvas *canvas) {
    if (viewport != NULL && viewport->redraw_callback != NULL) {
        viewport->redraw_callback(canvas, viewport->redraw_callback_ctx);
        return true;
    }
    return false;
}

bool viewport_is_active(Viewport *viewport) {
    return viewport->active;
}

void viewport_set_active(Viewport *viewport, bool active) {
    viewport->active = active;
}

void viewport_set_layer(Viewport *viewport, GuiLayers layer) {
    viewport->layer = layer;
}

GuiLayers viewport_get_layer(Viewport *viewport) {
    return viewport->layer;
}

bool viewport_process_input(Viewport *viewport, ViewportInputEvent *msg) {
    if (viewport != NULL && viewport->input_callback != NULL) {
        viewport->input_callback(msg, viewport->input_callback_ctx);
    }
}

void viewport_set_redraw_callback(Viewport *viewport, ViewportRedrawCallback callback, void *ctx) {
    viewport->redraw_callback = callback;
    viewport->redraw_callback_ctx = ctx;
}

void viewport_set_input_callback(Viewport *viewport, ViewportInputCallback callback, void *ctx) {
    viewport->input_callback = callback;
    viewport->input_callback_ctx = ctx;
}
