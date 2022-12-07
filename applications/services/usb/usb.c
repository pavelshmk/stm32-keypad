//
// Created by bakatrouble on 12/11/22.
//

#include <malloc.h>
#include "usb.h"
#include "tusb.h"
#include "class/msc/msc_device.h"
#include "device_flash.h"
#include "record.h"
#include "services.h"

const char *USB_SVC = "usb_svc";

/* A combination of interfaces must have a unique product id, since PC will save device driver after the first plug.
 * Same VID/PID with different interface e.g MSC (first), then CDC (later) will possibly cause system error on PC.
 *
 * Auto ProductID layout's Bitmap:
 *   [MSB]         HID | MSC | CDC          [LSB]
 */
#define _PID_MAP(itf, n)  ( (CFG_TUD_##itf) << (n) )
#define USB_PID           (0x4000 | _PID_MAP(CDC, 0) | _PID_MAP(MSC, 1) | _PID_MAP(HID, 2) | \
                           _PID_MAP(MIDI, 3) | _PID_MAP(VENDOR, 4) )

#define USB_VID   0xBACA
#define USB_BCD   0x0200
#define NKRO_EPSIZE 16

#define TUD_HID_REPORT_DESC_KEYBOARD_NKRO(...) \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP     )                    ,\
  HID_USAGE      ( HID_USAGE_DESKTOP_KEYBOARD )                    ,\
  HID_COLLECTION ( HID_COLLECTION_APPLICATION )                    , /* Report ID if any */\
    __VA_ARGS__ /* 8 bits Modifier Keys (Shfit, Control, Alt) */ \
    HID_USAGE_PAGE ( HID_USAGE_PAGE_KEYBOARD )                     ,\
      HID_USAGE_MIN    ( 224                                    )  ,\
      HID_USAGE_MAX    ( 231                                    )  ,\
      HID_LOGICAL_MIN  ( 0                                      )  ,\
      HID_LOGICAL_MAX  ( 1                                      )  ,\
      HID_REPORT_COUNT ( 8                                      )  ,\
      HID_REPORT_SIZE  ( 1                                      )  ,\
      HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE )  , /* 8 bit reserved */ \
      HID_REPORT_COUNT ( 1                                      )  ,\
      HID_REPORT_SIZE  ( 8                                      )  ,\
      HID_INPUT        ( HID_CONSTANT                           )  , /* Output 5-bit LED Indicator Kana | Compose | ScrollLock | CapsLock | NumLock */ \
    HID_USAGE_PAGE  ( HID_USAGE_PAGE_LED                   )       ,\
      HID_USAGE_MIN    ( 1                                       ) ,\
      HID_USAGE_MAX    ( 5                                       ) ,\
      HID_REPORT_COUNT ( 5                                       ) ,\
      HID_REPORT_SIZE  ( 1                                       ) ,\
      HID_OUTPUT       ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE  ) , /* led padding */ \
      HID_REPORT_COUNT ( 1                                       ) ,\
      HID_REPORT_SIZE  ( 3                                       ) ,\
      HID_OUTPUT       ( HID_CONSTANT                            ) , /* 6-byte Keycodes */ \
    HID_USAGE_PAGE ( HID_USAGE_PAGE_KEYBOARD )                     ,\
      HID_USAGE_MIN    ( 0                                      )  ,\
      HID_USAGE_MAX    ( (NKRO_EPSIZE - 1) * 8 - 1              )  ,\
      HID_LOGICAL_MIN  ( 0                                      )  ,\
      HID_LOGICAL_MAX  ( 1                                      )  ,\
      HID_REPORT_COUNT ( (NKRO_EPSIZE - 1) * 8                  )  ,\
      HID_REPORT_SIZE  ( 1                                      )  ,\
      HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE )  ,\
  HID_COLLECTION_END \

//--------------------------------------------------------------------+
// Device Descriptors
//--------------------------------------------------------------------+
tusb_desc_device_t const desc_device = {
        .bLength            = sizeof(tusb_desc_device_t),
        .bDescriptorType    = TUSB_DESC_DEVICE,
        .bcdUSB             = USB_BCD,
        .bDeviceClass       = 0x00,
        .bDeviceSubClass    = 0x00,
        .bDeviceProtocol    = 0x00,
        .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

        .idVendor           = USB_VID,
        .idProduct          = USB_PID,
        .bcdDevice          = 0x0100,

        .iManufacturer      = 0x01,
        .iProduct           = 0x02,
        .iSerialNumber      = 0x03,

        .bNumConfigurations = 0x01
};

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const *tud_descriptor_device_cb(void) {
    return (uint8_t const *) &desc_device;
}

//--------------------------------------------------------------------+
// HID Report Descriptor
//--------------------------------------------------------------------+

uint8_t const desc_hid_report[] = {
        TUD_HID_REPORT_DESC_KEYBOARD     (HID_REPORT_ID(REPORT_ID_KEYBOARD)),
        TUD_HID_REPORT_DESC_KEYBOARD_NKRO(HID_REPORT_ID(REPORT_ID_KEYBOARD_NKRO)),
        TUD_HID_REPORT_DESC_MOUSE        (HID_REPORT_ID(REPORT_ID_MOUSE)),
        TUD_HID_REPORT_DESC_CONSUMER     (HID_REPORT_ID(REPORT_ID_CONSUMER_CONTROL)),
        TUD_HID_REPORT_DESC_GAMEPAD      (HID_REPORT_ID(REPORT_ID_GAMEPAD)),
};

// Invoked when received GET HID REPORT DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance) {
    (void) instance;
    return desc_hid_report;
}

#define EPNUM_HID_IN 0x81
#define EPNUM_MSC_OUT 0x03
#define EPNUM_MSC_IN 0x82

uint8_t const desc_configuration_hid[] = {
        // Config number, interface count, string index, total length, attribute, power in mA
        TUD_CONFIG_DESCRIPTOR(1, 1, 0, (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN), TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP,
                              100),
        // Interface number, string index, protocol, report descriptor len, EP In address, size & polling interval
        TUD_HID_DESCRIPTOR(0, 0, HID_ITF_PROTOCOL_NONE, sizeof(desc_hid_report), EPNUM_HID_IN, CFG_TUD_HID_EP_BUFSIZE,
                           5),
};

uint8_t const desc_configuration_hid_msc[] = {
        // Config number, interface count, string index, total length, attribute, power in mA
        TUD_CONFIG_DESCRIPTOR(1, 2, 0, (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN + TUD_MSC_DESC_LEN),
                              TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),
        // Interface number, string index, protocol, report descriptor len, EP In address, size & polling interval
        TUD_HID_DESCRIPTOR(0, 4, HID_ITF_PROTOCOL_NONE, sizeof(desc_hid_report), EPNUM_HID_IN, CFG_TUD_HID_EP_BUFSIZE,
                           5),

        TUD_MSC_DESCRIPTOR(1, 5, EPNUM_MSC_OUT, EPNUM_MSC_IN, 64),
};

// Invoked when received GET CONFIGURATION DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const *tud_descriptor_configuration_cb(uint8_t index) {
    (void) index; // for multiple configurations
//    if (((USB*)(record_get(USB_SVC)))->msc_enabled) {
        return desc_configuration_hid_msc;
//    } else {
//        return desc_configuration_hid;
//    }
}

//--------------------------------------------------------------------+
// String Descriptors
//--------------------------------------------------------------------+

// array of pointer to string descriptors
char const *string_desc_arr[] = {
        (const char[]) {0x09, 0x04}, // 0: is supported language is English (0x0409)
        "bakatrouble",                 // 1: Manufacturer
        "Keypad",                      // 2: Product
        "123456",                      // 3: Serials, should use chip ID
        "Keypad HID",                  // 4: HID interface name
        "Keypad MSC",                  // 5: MSC interface name
};

static uint16_t _desc_str[32];

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void) langid;

    uint8_t chr_count;

    if (index == 0) {
        memcpy(&_desc_str[1], string_desc_arr[0], 2);
        chr_count = 1;
    } else {
        // Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors

        if (!(index < sizeof(string_desc_arr) / sizeof(string_desc_arr[0]))) return NULL;

        const char *str = string_desc_arr[index];

        // Cap at max char
        chr_count = (uint8_t) strlen(str);
        if (chr_count > 31) chr_count = 31;

        // Convert ASCII string into UTF-16
        for (uint8_t i = 0; i < chr_count; i++) {
            _desc_str[1 + i] = str[i];
        }
    }

    // first byte is length (including header), second byte is string type
    _desc_str[0] = (uint16_t) ((TUSB_DESC_STRING << 8) | (2 * chr_count + 2));

    return _desc_str;
}

void usb_svc(void *p) {
    UNUSED(p);

    USB *usb = malloc(sizeof(USB));
    usb->msc_enabled = false;

    record_create(USB_SVC, usb);

    mark_service_started(SVC_USB_RUNNING);

    tud_init(BOARD_TUD_RHPORT);
    while (true) {
        tud_task();
//        osDelay(1);
    }
}
