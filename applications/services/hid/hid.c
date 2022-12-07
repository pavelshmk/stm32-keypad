//
// Created by bakatrouble on 13/11/22.
//

#include "hid.h"
#include "applications_exports.h"
#include "class/hid/hid_device.h"
#include "input/input.h"
#include "keycodes.h"
#include "pubsub.h"
#include "record.h"
#include "services.h"
#include "usb/usb.h"
#include <cwalk.h>
#include <ff.h>
#include <m-dict.h>
#include <malloc.h>
#include <toml.h>

const char *HID_SVC = "hid_svc";

osMessageQueueAttr_t hid_queue_attr = {
        .name = "hid_queue",
};

void hid_input_callback(const InputEvent *msg, HID *hid) {
    osMessageQueuePut(hid->queue, msg, 0, osWaitForever);
}

void hid_load_layout(HID *hid, const char *filename) {
    FIL *f = malloc(sizeof(FIL));
    char *path = malloc(128);
    cwk_path_join("layouts", filename, path, 128);
    f_open(f, path, FA_READ);
    FSIZE_t json_size = f_size(f);
    char *conf_contents = malloc(json_size);
    size_t read;
    f_read(f, conf_contents, json_size, &read);
    f_close(f);
    free(f);
    free(path);

    bool layers_failed = false;
    char *errbuf = malloc(200);
    toml_table_t *conf = toml_parse(conf_contents, errbuf, 200);
    if (!conf) {
        printf("[layout] parser fail: %s\r\n", errbuf);
        goto cleanup;
    }
    toml_table_t *layout = toml_table_in(conf, "layout");
    if (!layout) {
        printf("[layout] layout table not found\r\n");
        goto cleanup;
    }
    toml_array_t *layer = toml_array_in(layout, "layer1");
    if (!layer) {
        printf("[layout] layer1 field not found\r\n");
        goto cleanup;
    }
    if (toml_array_nelem(layer) != 5) {
        printf("[layout] layer1 array has invalid length (expected: %d)\r\n", 5);
        goto cleanup;
    }

    HIDLayout *hid_layout = malloc(sizeof(HIDLayout));
    hid_layout->layers_count = 1;
    for (uint8_t r =0; r < 5; r++) {
        toml_array_t *row = toml_array_at(layer, r);
        if (!row) {
            printf("[layout] layer1 row parsing failed\r\n");
            layers_failed = true;
            goto cleanup;
        }
        if (toml_array_nelem(row) != 3) {
            printf("[layout] layer1 row %d has invalid length (expected: %d)\r\n", r, 3);
            layers_failed = true;
            goto cleanup;
        }
        for (uint8_t c=0; c < 3; c++) {
            toml_datum_t key = toml_string_at(row, c);
            hid_layout->layers[0].keycodes[c][r] = keycode_lookup(key.u.s, strlen(key.u.s))->keycode;
            free(key.u.s);
        }
    }

    if (hid->layout != NULL) {
        free(hid->layout);
    }
    hid->layout = hid_layout;

cleanup:
    if (conf != NULL)
        toml_free(conf);
    if (layers_failed)
        free(hid_layout);
    free(conf_contents);
    free(errbuf);
}

DICT_DEF2(PressedScancodes, uint16_t, bool)

void hid_svc(void *p) {
    HID *hid = malloc(sizeof(HID));
    hid->active = true;
    hid->layer = 0;
    hid->layout = 0;
    hid->queue = osMessageQueueNew(8, sizeof(InputEvent), &hid_queue_attr);

    PubSub *pubsub = record_get(INPUT_PUBSUB);
    pubsub_subscribe(pubsub, hid_input_callback, hid);

    wait_for_service_to_start(SVC_STORAGE_RUNNING);
    hid_load_layout(hid, "test.toml");

    USB *usb = record_get(USB_SVC);
    record_create(HID_SVC, hid);

    mark_service_started(SVC_HID_RUNNING);


//    uint8_t layers_stack[10] = {0};
//    uint8_t *layers_ptr = layers_stack;
    PressedScancodes_t pressed_scancodes;
    PressedScancodes_init(pressed_scancodes);

    uint8_t keyboard_report[8];
    uint8_t nkro_report[18];
    uint16_t consumer_report;

    InputEvent msg;
    bool keys_changed;
    while (true) {
        if (osMessageQueueGet(hid->queue, &msg, 0, osWaitForever) == osOK) {
            if (!hid->active || !hid->layout)
                continue;

            keys_changed = false;
            if (!IS_SPECIAL_SCANCODE(msg.scancode)) {
                if (msg.flags & INPUT_EVENT_DOWN) {
                    PressedScancodes_set_at(pressed_scancodes, msg.scancode, true);
                    keys_changed = true;
                } else if (msg.flags & INPUT_EVENT_UP) {
                    PressedScancodes_erase(pressed_scancodes, msg.scancode);
                    keys_changed = true;
                }
            }

            if (keys_changed) {
                memset(keyboard_report, 0, sizeof(keyboard_report));
                memset(nkro_report, 0, sizeof(nkro_report));
                consumer_report = 0;
                uint8_t *keyboard_report_ptr = keyboard_report + 2;
                uint8_t *nkro_report_ptr = nkro_report + 2;

                PressedScancodes_it_t it;
                for (PressedScancodes_it(it, pressed_scancodes); !PressedScancodes_end_p(it); PressedScancodes_next(it)) {
                    uint16_t scancode = PressedScancodes_cref(it)->key;
                    uint16_t keycode = hid->layout->layers[hid->layer].keycodes[scancode & 0xFF][scancode >> 8];
                    switch (keycode >> 12) {
                    case 0:  // default
                        if (keyboard_report_ptr - keyboard_report < 8) {
                            *(keyboard_report_ptr++) = keycode & 0xFF;
                        } else if (nkro_report_ptr - nkro_report < 18) {
                            *(nkro_report_ptr++) = keycode & 0xFF;
                        }
                        break;
                    case 1:  // consumer
                        consumer_report = keycode & 0xFFF;
                        break;
                    case 2:  // custom
                        break;
                    case 3:  // layer change
                        //                    if (msg.flags & INPUT_EVENT_DOWN) {
                        //                        // pointer always points to current layer entry in stack
                        //                        *++layers_ptr = keycode & 0xFF;
                        //                        hid->layer = *layers_ptr;
                        //                    } else if (msg.flags & INPUT_EVENT_UP) {
                        //                        while (*(layers_ptr--) != (keycode & 0xFF));
                        //                        hid->layer = *layers_ptr;
                        //                    }
                        break;
                    }
                }

                tud_hid_report(REPORT_ID_KEYBOARD, keyboard_report, 8);
                tud_hid_report(REPORT_ID_KEYBOARD_NKRO, nkro_report, 18);
                tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &consumer_report, 2);
            }
        }
    }
}
