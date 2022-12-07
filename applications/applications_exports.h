#pragma once

// cstr_exports
extern const char *INPUT_PUBSUB;
extern const char *LOADER_SVC;
extern const char *GUI_SVC;
extern const char *POWER_SVC;
extern const char *DESKTOP_SVC;
extern const char *BACKLIGHT_SVC;
extern const char *STORAGE_SVC;
extern const char *USB_SVC;
extern const char *HID_SVC;

// app names
extern const char *input_tester;
extern const char *msd;

// service start flags
#define SVC_INPUT_RUNNING (1 << 0)
#define SVC_LOADER_RUNNING (1 << 1)
#define SVC_GUI_RUNNING (1 << 2)
#define SVC_POWER_RUNNING (1 << 3)
#define SVC_DESKTOP_RUNNING (1 << 4)
#define SVC_BACKLIGHT_RUNNING (1 << 5)
#define SVC_STORAGE_RUNNING (1 << 6)
#define SVC_USB_RUNNING (1 << 7)
#define SVC_HID_RUNNING (1 << 8)
