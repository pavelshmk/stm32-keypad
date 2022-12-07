#include "applications.h"

extern void input_svc(void*);
extern void loader_svc(void*);
extern void gui_svc(void*);
extern void power_svc(void*);
extern void desktop_svc(void*);
extern void backlight_svc(void*);
extern void storage_svc(void*);
extern void usb_svc(void*);
extern void hid_svc(void*);
extern void input_tester_app(void*);
extern void msd_app(void*);

const Application SERVICES[] = {
        {
            .id = "input",
            .name = "Input",
            .entrypoint = input_svc,
            .stack = 1024,
        },
        {
            .id = "loader",
            .name = "Loader",
            .entrypoint = loader_svc,
            .stack = 1024,
        },
        {
            .id = "gui",
            .name = "Gui",
            .entrypoint = gui_svc,
            .stack = 1024,
        },
        {
            .id = "power",
            .name = "Power",
            .entrypoint = power_svc,
            .stack = 256,
        },
        {
            .id = "desktop",
            .name = "Desktop",
            .entrypoint = desktop_svc,
            .stack = 512,
        },
        {
            .id = "backlight",
            .name = "Backlight",
            .entrypoint = backlight_svc,
            .stack = 4096,
        },
        {
            .id = "storage",
            .name = "Storage",
            .entrypoint = storage_svc,
            .stack = 8192,
        },
        {
            .id = "usb",
            .name = "USB",
            .entrypoint = usb_svc,
            .stack = 1024,
        },
        {
            .id = "hid",
            .name = "HID",
            .entrypoint = hid_svc,
            .stack = 1024,
        },
};
const size_t SERVICES_COUNT = 9;

const Application APPS[] = {
        {
            .id = "input_tester",
            .name = "Input Tester",
            .entrypoint = input_tester_app,
            .stack = 4096,
        },
        {
            .id = "msd",
            .name = "MSD",
            .entrypoint = msd_app,
            .stack = 16384,
        },
};
const size_t APPS_COUNT = 2;

const char *input_tester = "input_tester";
const char *msd = "msd";
