#include "gui_i.h"
#include "record.h"
#include "device.h"
#include "pubsub.h"
#include "viewport_i.h"
#include "input/input.h"
#include "applications.h"
#include "services.h"
#include "FreeRTOS.h"

const char *GUI_SVC = "gui_svc";

osMessageQueueAttr_t gui_svc_input_queue_attr = {
        .name = "gui_svc_input_queue",
};
osEventFlagsAttr_t gui_svc_flags_attr = {
        .name = "gui_svc_flags",
};

void gui_redraw(Gui *gui) {
    osEventFlagsSet(gui->flags, GUI_FLAG_REDRAW);
}

void gui_input_callback(const InputEvent *msg, Gui *gui) {
    osMessageQueuePut(gui->input_queue, msg, 0, 0);
    osEventFlagsSet(gui->flags, GUI_FLAG_INPUT);
}

Viewport *gui_find_active_viewport(Gui *gui, GuiLayers layer) {
    ViewportArray_it_t it;
    ViewportArray_it(it, gui->viewports[layer]);
    while (!ViewportArray_end_p(it)) {
        if (viewport_is_active(*ViewportArray_ref(it))) {
            return *ViewportArray_ref(it);
        } else {
            ViewportArray_next(it);
        }
    }
    return NULL;
}

Viewport *gui_find_active_viewport_on_all_layers(Gui *gui) {
     Viewport *viewport = gui_find_active_viewport(gui, GuiLayerApp);
     if (viewport == NULL)
         viewport = gui_find_active_viewport(gui, GuiLayerDesktop);
     return viewport;
}

void gui_draw(Gui *gui) {
    canvas_clear(gui->canvas);

    Viewport *active_viewport = gui_find_active_viewport(gui, GuiLayerApp);

    if (!viewport_draw(active_viewport, gui->canvas)) {
        active_viewport = gui_find_active_viewport(gui, GuiLayerDesktop);
        viewport_draw(active_viewport, gui->canvas);
    }

    canvas_commit(gui->canvas);
}

void gui_input(Gui *gui, InputEvent *msg, size_t queue_size) {
    Viewport *active_viewport = gui_find_active_viewport_on_all_layers(gui);
    ViewportInputEvent evt = {
            .gui = gui,
            .flags = msg->flags,
            .scancode = msg->scancode,
            .queue_size = queue_size,
    };
    viewport_process_input(active_viewport, &evt);
}

void gui_add_viewport(Gui *gui, Viewport *viewport) {
    ViewportArray_push_back(gui->viewports[viewport->layer], viewport);
    viewport->gui = gui;
    gui_redraw(gui);
}

void gui_remove_viewport(Gui *gui, Viewport *viewport) {
    ViewportArray_it_t it;
    ViewportArray_it(it, gui->viewports[viewport->layer]);
    while (!ViewportArray_end_p(it)) {
        if (*ViewportArray_ref(it) == viewport) {
            ViewportArray_remove(gui->viewports[viewport->layer], it);
        } else {
            ViewportArray_next(it);
        }
    }
}

_Noreturn void gui_svc(void *p) {
    Gui* gui = pvPortMalloc(sizeof(Gui));
    gui->input_queue = osMessageQueueNew(8, sizeof(InputEvent), &gui_svc_input_queue_attr);
    gui->flags = osEventFlagsNew(&gui_svc_flags_attr);
    gui->canvas = canvas_alloc();
    for (uint8_t i=0; i < GuiLayerCount; i++) {
        ViewportArray_init(gui->viewports[i]);
    }
    record_create(GUI_SVC, gui);

    mark_service_started(SVC_GUI_RUNNING);

    pubsub_subscribe(record_get(INPUT_PUBSUB), gui_input_callback, gui);
    InputEvent inputMsg;

    for (;;) {
        uint32_t flags = osEventFlagsWait(gui->flags, GUI_FLAG_INPUT | GUI_FLAG_REDRAW, osFlagsWaitAny, osWaitForever);
        if (flags && !(flags & 0xF0000000)) {
            if (flags & GUI_FLAG_INPUT) {
                while (osMessageQueueGet(gui->input_queue, &inputMsg, 0, 0) == osOK) {
                    gui_input(gui, &inputMsg, osMessageQueueGetCount(gui->input_queue));
                }
            }
            if (flags & GUI_FLAG_REDRAW) {
                gui_draw(gui);
            }
        }
    }
}
