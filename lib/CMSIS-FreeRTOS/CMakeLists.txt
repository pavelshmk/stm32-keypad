add_library(cmsis-freertos INTERFACE)
target_sources(cmsis-freertos INTERFACE
        Source/event_groups.c
        Source/list.c
        Source/queue.c
        Source/stream_buffer.c
        Source/tasks.c
        Source/timers.c
        Source/portable/GCC/ARM_CM4F/port.c
        Source/portable/MemMang/heap_4.c
        CMSIS/RTOS2/FreeRTOS/Source/cmsis_os2.c
        CMSIS/RTOS2/FreeRTOS/Source/freertos_evr.c
#        CMSIS/RTOS2/FreeRTOS/Source/handlers.c
        CMSIS/RTOS2/FreeRTOS/Source/os_systick.c
        CMSIS/RTOS2/FreeRTOS/Source/ARM/clib_arm.c
        )
target_include_directories(cmsis-freertos INTERFACE
        Source/include
        Source/portable/GCC/ARM_CM4F
        CMSIS/RTOS2/FreeRTOS/Include
)
