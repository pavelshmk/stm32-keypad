//
// Created by bakatrouble on 06/11/22.
//

#ifndef HAL_VIEWPORT_H
#define HAL_VIEWPORT_H

#include <m-array.h>
#include "device.h"
#include "canvas.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ViewportInputEvent ViewportInputEvent;
typedef struct Viewport Viewport;
typedef void (*ViewportInputCallback)(ViewportInputEvent* event, void* context);
typedef void (*ViewportRedrawCallback)(Canvas *canvas, void* context);

typedef enum {
    GuiLayerDesktop,
    GuiLayerApp,
    GuiLayerCount,
} GuiLayers;

ARRAY_DEF(ViewportArray, Viewport*, M_PTR_OPLIST)

Viewport *viewport_alloc();
void viewport_destroy(Viewport *viewport);
bool viewport_draw(Viewport *viewport, Canvas *canvas);
bool viewport_is_active(Viewport *viewport);
bool viewport_process_input(Viewport *viewport, ViewportInputEvent *msg);
void viewport_set_active(Viewport *viewport, bool active);
void viewport_set_redraw_callback(Viewport *viewport, ViewportRedrawCallback callback, void *ctx);
void viewport_set_input_callback(Viewport *viewport, ViewportInputCallback callback, void *ctx);
void viewport_set_layer(Viewport *viewport, GuiLayers layer);
GuiLayers viewport_get_layer(Viewport *viewport);

#ifdef __cplusplus
}
#endif

#endif //HAL_VIEWPORT_H
