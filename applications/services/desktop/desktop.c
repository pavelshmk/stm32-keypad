//
// Created by bakatrouble on 08/11/22.
//

#include "gui/gui.h"
#include "gui/menu.h"
#include "record.h"
#include "applications_exports.h"
#include "loader/loader.h"
#include "services.h"

void desktop_svc(void *p) {
    wait_for_service_to_start(SVC_GUI_RUNNING);

    Gui *gui = record_get(GUI_SVC);
    Loader *loader = record_get(LOADER_SVC);
    Viewport *viewport = viewport_alloc();
    viewport_set_layer(viewport, GuiLayerDesktop);

    GuiMenu *menu = menu_alloc();
    menu_add_item(menu, "Input tester");
    menu_add_item(menu, "Format storage");
    menu_add_item(menu, "Dummy");

    gui_add_viewport(gui, viewport);

    mark_service_started(SVC_DESKTOP_RUNNING);

    while (true) {
        menu_show(menu, viewport);
        if (menu->selected) {
            switch (menu->current_idx) {
                case 0:
                    loader_start(loader, input_tester, NULL);
                    break;
                case 1:
                    loader_start(loader, msd, NULL);
                    break;
            }
        }
    }
}
