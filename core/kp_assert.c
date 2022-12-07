#include <stdio.h>
#include "kp_assert.h"
#include "device.h"

char assert_buf[256];

void assert_failure(const char *expr, const char *msg, const char *file, int line) {
    display_fill_screen(0x0000);
    display_write_string(0, 0, "***Assert fail***", Font_7x10, 0xFFFF, 0x0000);
    display_write_string(0, 10, "See UART for more", Font_7x10, 0xFFFF, 0x0000);
    display_write_string(0, 30, msg, Font_7x10, 0xFFFF, 0x0000);
    display_update_no_dma();

    printf("\r\n\r\n\r\n***Assert fail***\r\n");
    uart_wait_for_transfer();
    printf("%s\r\n", msg);
    uart_wait_for_transfer();
    printf("Expression: %s\r\nFile: %s:%d\r\n\r\n\r\n", expr, file, line);
    uart_wait_for_transfer();

    __disable_irq();

    /* Go into an infinite loop */
    for (;;);
}
