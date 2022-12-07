cmake_minimum_required(VERSION 3.21)
include (cmake/stm32f412rgx.cmake)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/cmake/arm-none-eabi-gcc.cmake)
set(PROJECT_NAME keypad-cmsis-freertos)

project(${PROJECT_NAME})

add_subdirectory(lib)
add_subdirectory(applications)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
        core/kp_assert.c
        core/pubsub.c
        core/record.c
        core/services.c
        main.c
        src/retarget.c
        src/sysmem.c
        src/FreeRTOSConfig.c
        src/qspi_diskio.c
        common/hal_tick.c
        )

target_include_directories(${PROJECT_NAME} PRIVATE
        include
        core
        )

include(device/config.cmake)

target_link_libraries(${PROJECT_NAME} PRIVATE
        device
        m-lib
        ringbuffer
        tinyusb
        applications
        FatFs
        tomlc99
        cwalk
        )

add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND "${CMAKE_CURRENT_LIST_DIR}/scripts/gather_manifests.py")

setup_project(${PROJECT_NAME})