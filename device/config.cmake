include_guard(GLOBAL)

add_library(device INTERFACE)

target_include_directories(device INTERFACE
		${CMAKE_CURRENT_LIST_DIR}
)

target_sources(device INTERFACE
		${CMAKE_CURRENT_LIST_DIR}/device_init.c
		${CMAKE_CURRENT_LIST_DIR}/device_leds.c
		${CMAKE_CURRENT_LIST_DIR}/device_uart.c
		${CMAKE_CURRENT_LIST_DIR}/device_spi.c
		${CMAKE_CURRENT_LIST_DIR}/device_display.c
		${CMAKE_CURRENT_LIST_DIR}/device_lcd_fonts.c
		${CMAKE_CURRENT_LIST_DIR}/device_buzzer.c
		${CMAKE_CURRENT_LIST_DIR}/device_power.c
        ${CMAKE_CURRENT_LIST_DIR}/device_input.c
		${CMAKE_CURRENT_LIST_DIR}/device_backlight.c
		${CMAKE_CURRENT_LIST_DIR}/device_usb.c
		${CMAKE_CURRENT_LIST_DIR}/device_flash.c
		)
