#include <sys/cdefs.h>
//
// Created by bakatrouble on 06/11/22.
//

#ifndef HAL_GUI_H
#define HAL_GUI_H

#include "viewport.h"

#define GUI_FLAG_REDRAW (1 << 0)
#define GUI_FLAG_INPUT  (1 << 1)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Gui Gui;

void gui_redraw(Gui *gui);
void gui_add_viewport(Gui *gui, Viewport *viewport);
void gui_remove_viewport(Gui *gui, Viewport *viewport);

#ifdef __cplusplus
}
#endif

#endif //HAL_GUI_H
