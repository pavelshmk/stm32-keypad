//
// Created by bakatrouble on 06/11/22.
//

#include "menu.h"
#include "viewport.h"
#include "gfx/menuitem_bg.h"
#include "input/input.h"
#include "FreeRTOS.h"

#define MENU_SELECT    (1 << 0)
#define MENU_BACK      (1 << 1)
#define MENU_MIN(a, b) ((a) > (b) ? (b) : (a))
#define MENU_MAX(a, b) ((a) < (b) ? (b) : (a))
#define MENU_WINDOW    (9)
#define MENU_MIN_PROGRESS_SEGMENT (8)

osEventFlagsAttr_t menu_flags_attr = {
        .name = "menu_flags",
};

void menu_adjust_window(GuiMenu *menu, bool increased) {
    if (GuiMenuItemsList_size(menu->items) > MENU_WINDOW) {
        if (menu->current_idx < menu->window_start) {
            menu->window_start = menu->current_idx;
        } else if (menu->current_idx > menu->window_start + MENU_WINDOW - 1) {
            menu->window_start = menu->current_idx - MENU_WINDOW + 1;
        }
    } else {
        menu->window_start = 0;
    }
}

void menu_input_callback(ViewportInputEvent *msg, GuiMenu *menu) {
    if (!(msg->flags & INPUT_EVENT_PRESS))
        return;
    switch (msg->scancode) {
        case KEY_CW:
            menu->current_idx = (menu->current_idx + 1) % (int)GuiMenuItemsList_size(menu->items);
            menu_adjust_window(menu, true);
            gui_redraw(msg->gui);
            break;
        case KEY_CCW:
            menu->current_idx--;
            if (menu->current_idx < 0)
                menu->current_idx += (int)GuiMenuItemsList_size(menu->items);
            menu_adjust_window(menu, false);
            gui_redraw(msg->gui);
            break;
        case KEY_CENTER:
            menu->selected = true;
            osEventFlagsSet(menu->event_flags, MENU_SELECT);
            break;
        case KEY_PUSH2:
            menu->selected = false;
            osEventFlagsSet(menu->event_flags, MENU_BACK);
            break;
        default:
            break;
    }
}

void menu_redraw_callback(Canvas *canvas, GuiMenu *menu) {
    size_t size = MENU_MIN(GuiMenuItemsList_size(menu->items), MENU_WINDOW);
    canvas_set_color(canvas, 0xFFFF);
    canvas_set_bgcolor(canvas, 0x0000);
    canvas_draw_bitmap_1(canvas, 0, (menu->current_idx - menu->window_start) * 14, menuitem_bg);
    canvas_set_font_bgcolor(canvas, 0x0000);
    for (int i=0; i < size; i++) {
        int idx = i + menu->window_start;
        if (idx == menu->current_idx) {
            canvas_set_font_color(canvas, 0xFFFF);
        } else {
            canvas_set_font_color(canvas, canvas_color565(0x7F7F7F));
        }
        canvas_puts(canvas, 4, (i * 14) + 11, (*GuiMenuItemsList_get(menu->items, idx))->label);
    }
    {  // progress
        canvas_draw_fast_vline(canvas, 127, 0, 128, canvas_le_to_be(canvas_color565(0x2F2F2F)));
        uint16_t segmentSize = MENU_MAX(128 / GuiMenuItemsList_size(menu->items), MENU_MIN_PROGRESS_SEGMENT);
        uint16_t segment_y = (128 - segmentSize) * menu->current_idx / (GuiMenuItemsList_size(menu->items) - 1);
        canvas_draw_fast_vline(canvas, 127, segment_y, segmentSize, 0xFFFF);
        canvas_draw_fast_vline(canvas, 126, segment_y, segmentSize, 0xFFFF);
    }
}

GuiMenu *menu_alloc(void) {
    GuiMenu *menu = pvPortMalloc(sizeof(GuiMenu));
    GuiMenuItemsList_init(menu->items);
    menu->current_idx = 0;
    menu->selected = false;
    menu->menu_viewport = viewport_alloc();
    menu->event_flags = osEventFlagsNew(&menu_flags_attr);
    viewport_set_input_callback(menu->menu_viewport, (ViewportInputCallback)menu_input_callback, menu);
    viewport_set_redraw_callback(menu->menu_viewport, (ViewportRedrawCallback)menu_redraw_callback, menu);
    return menu;
}

void menu_add_item(GuiMenu *menu, const char *label) {
    GuiMenuItem_t *item = pvPortMalloc(sizeof(GuiMenuItem_t));
    item->label = label;
    GuiMenuItemsList_push_back(menu->items, item);
}

void menu_destroy(GuiMenu *menu) {
    GuiMenuItemsList_it_t it;
    GuiMenuItemsList_it(it, menu->items);
    while (!GuiMenuItemsList_end_p(it)) {
        vPortFree(*GuiMenuItemsList_ref(it));
        GuiMenuItemsList_remove(menu->items, it);
    }
    viewport_destroy(menu->menu_viewport);
}

void menu_show(GuiMenu *menu, Viewport *app_viewport) {
    menu->app_viewport = app_viewport;
    menu->current_idx = 0;
    menu->window_start = 0;
    viewport_set_active(menu->menu_viewport, true);
    viewport_set_layer(menu->menu_viewport, app_viewport->layer);
    viewport_set_active(app_viewport, false);
    gui_add_viewport(app_viewport->gui, menu->menu_viewport);

    for (;;) {
        uint32_t flags = osEventFlagsWait(menu->event_flags, MENU_SELECT | MENU_BACK, osFlagsWaitAny, osWaitForever);
        if (flags && !(flags & 0xF0000000)) {
            break;
        }
    }

    viewport_set_active(app_viewport, true);
    viewport_set_active(menu->menu_viewport, false);
    gui_remove_viewport(app_viewport->gui, menu->menu_viewport);
}
