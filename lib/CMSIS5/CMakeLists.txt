add_library(cmsis5 INTERFACE)
target_include_directories(cmsis5 INTERFACE
        CMSIS/Core/Include
        CMSIS/RTOS2/Include
        Device/ST/STM32F4xx/Include
        )
