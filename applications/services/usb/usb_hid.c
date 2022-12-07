#include "usb.h"
#include "tusb.h"

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
    // TODO not Implemented
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
    (void) instance;

    if (report_type == HID_REPORT_TYPE_OUTPUT)
    {
        // Set keyboard LED e.g Capslock, Numlock etc...
        if (report_id == REPORT_ID_KEYBOARD)
        {
            // bufsize should be (at least) 1
            if ( bufsize < 1 ) return;

//            uint8_t const kbd_leds = buffer[0];
//
//            if (kbd_leds & KEYBOARD_LED_CAPSLOCK)
//            {
//                // Capslock On: disable blink, turn led on
//                xTimerStop(blinky_tm, portMAX_DELAY);
//                board_led_write(true);
//            }else
//            {
//                // Caplocks Off: back to normal blink
//                board_led_write(false);
//                xTimerStart(blinky_tm, portMAX_DELAY);
//            }
        }
    }
}
