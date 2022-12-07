//
// Created by bakatrouble on 06/11/22.
//

#ifndef HAL_MENU_H
#define HAL_MENU_H

#include <stm32f4xx.h>
#include <m-array.h>
#include "viewport_i.h"
#include <cmsis_os2.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GuiMenuItem_t GuiMenuItem_t;

struct GuiMenuItem_t {
    const char *label;
};


ARRAY_DEF(GuiMenuItemsList, GuiMenuItem_t*, M_PTR_OPLIST)

typedef struct {
    GuiMenuItemsList_t items;
    int current_idx;
    int window_start;
    bool selected;
    Viewport *app_viewport;
    Viewport *menu_viewport;
    osEventFlagsId_t event_flags;
} GuiMenu;

GuiMenu *menu_alloc(void);
void menu_add_item(GuiMenu *menu, const char *label);
void menu_destroy(GuiMenu *menu);
void menu_show(GuiMenu *menu, Viewport *app_viewport);

#ifdef __cplusplus
}
#endif

#endif //HAL_MENU_H
