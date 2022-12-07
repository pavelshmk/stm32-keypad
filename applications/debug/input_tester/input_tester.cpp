//
// Created by bakatrouble on 15/10/22.
//

#include <deque>
#include <string>
#include "record.h"
#include "gui/gui.h"
#include "gui/viewport_i.h"
#include "backlight/backlight.h"
#include "applications.h"
#include "input/input.h"
#include "FreeRTOS.h"
#include <hid/hid.h>

typedef struct {
    osEventFlagsId_t flags;
//    flg_t *flags;
    std::deque<std::string> *list;
} InputTesterApp;

osEventFlagsAttr_t input_tester_app_flags_attr = {
        .name = "input_tester_app",
};

void input_tester_redraw_callback(Canvas *canvas, InputTesterApp *ctx) {
    uint8_t i = 0;
    canvas_set_font_color(canvas, 0xFFFF);
    canvas_set_font_bgcolor(canvas, 0x0000);
    for (const auto &item: *ctx->list) {
        canvas_puts(canvas, 8, 10 * i++ + 10, item.c_str());
    }
}

void input_tester_input_callback(ViewportInputEvent *msg, InputTesterApp *ctx) {
    char buf[32];
    bool key_received = false;
    if (msg->flags & INPUT_EVENT_LONGPRESS && msg->scancode == KEY_PUSH2) {
        osEventFlagsSet(ctx->flags, (uint32_t)1);
        return;
    }
    if (msg->flags & INPUT_EVENT_PRESS) {
        switch (msg->scancode) {
            case KEY_CW:
                sprintf(buf, "ROT      cw");
                key_received = true;
                break;
            case KEY_CCW:
                sprintf(buf, "ROT      ccw");
                key_received = true;
                break;
        }
    }
    if (msg->flags & (INPUT_EVENT_DOWN | INPUT_EVENT_UP)) {
        uint8_t keyDown = msg->flags & INPUT_EVENT_DOWN;
        switch (msg->scancode) {
            case KEY_PUSH1:
                sprintf(buf, "PUSH1    %s", (keyDown ? "pressed" : "released"));
                key_received = true;
                break;
            case KEY_PUSH2:
                sprintf(buf, "PUSH2    %s", (keyDown ? "pressed" : "released"));
                key_received = true;
                break;
            case KEY_CENTER:
                sprintf(buf, "CENTER   %s", (keyDown ? "pressed" : "released"));
                key_received = true;
                break;
            default:
                if (keyDown)
                    buzzer_start();
                else
                    buzzer_stop();
                backlight_setpixel(
                        (Backlight *) record_get(BACKLIGHT_SVC),
                        uint16_t(msg->scancode >> 8) * 3 + uint16_t(msg->scancode & 0xFF),
                        keyDown ? 0xFFFFFF : 0
                );
                sprintf(buf, "key %u:%-2u %s",
                        uint16_t(msg->scancode & 0xFF),
                        uint16_t(msg->scancode >> 8),
                        (keyDown ? "pressed" : "released")
                );
                printf("%s\r\n", buf);
                key_received = true;
                break;
        }
    }
    if (!key_received)
        return;
    ctx->list->emplace_back(buf);
    while (ctx->list->size() > 12) {
        ctx->list->pop_front();
    }
    if (msg->queue_size == 0) {
        gui_redraw(msg->gui);
    }
}

extern "C" void input_tester_app() {
    std::deque<std::string> list;
    list.emplace_back("---Input tester---");

    auto *app = static_cast<InputTesterApp *>(pvPortMalloc(sizeof(InputTesterApp)));
    app->list = &list;
    app->flags = osEventFlagsNew(&input_tester_app_flags_attr);

    HID *hid = static_cast<HID*>(record_get(HID_SVC));
    hid->active = false;
    Gui *gui = static_cast<Gui *>(record_get(GUI_SVC));
    auto *viewport = viewport_alloc();
    viewport_set_active(viewport, true);
    viewport_set_redraw_callback(viewport, reinterpret_cast<ViewportRedrawCallback>(input_tester_redraw_callback), app);
    viewport_set_input_callback(viewport, reinterpret_cast<ViewportInputCallback>(input_tester_input_callback), app);
    gui_add_viewport(gui, viewport);
    buzzer_set_frequency(440);

    gui_redraw(gui);

    while (true) {
        uint32_t flags = osEventFlagsWait(app->flags, (uint32_t)1, osFlagsWaitAny, osWaitForever);
        if (flags && !(flags & 0xF0000000)) {
            break;
        }
    }

    gui_remove_viewport(gui, viewport);
    viewport_destroy(viewport);
    vPortFree(app);
    gui_redraw(gui);

    hid->active = true;

    osThreadExit();
}
