//
// Created by bakatrouble on 07/11/22.
//

#ifndef HAL_GUI_I_H
#define HAL_GUI_I_H

#include "gui.h"
#include "viewport.h"
#include "canvas.h"
#include <cmsis_os2.h>

struct Gui {
//    msg_t *input_queue;
//    flg_t *flags;
    osMessageQueueId_t input_queue;
    osEventFlagsId_t flags;
    ViewportArray_t viewports[GuiLayerCount];
    Canvas *canvas;
};

#endif //HAL_GUI_I_H
