set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)

enable_language(C CXX)

function(setup_project PROJECT_NAME)
    target_sources(${PROJECT_NAME} PRIVATE
            ${CMAKE_SOURCE_DIR}/common/startup.c
            ${CMAKE_SOURCE_DIR}/common/system_stm32f4xx.c
            ${CMAKE_SOURCE_DIR}/common/interrupt_handlers.c
    )

    target_compile_definitions(${PROJECT_NAME} PRIVATE
            -DUSE_HAL_DRIVER
            -DSTM32F412Rx
            )

    target_link_libraries(${PROJECT_NAME} PRIVATE
            hal
            cmsis-freertos
            cmsis5
            )

    target_compile_options(${PROJECT_NAME} PRIVATE
            -mcpu=cortex-m4
            -mthumb
            -mfpu=fpv4-sp-d16
            -mfloat-abi=hard

            -fdata-sections
            -ffunction-sections

            -Wall

            $<$<CONFIG:Debug>:-Og>
            )

    target_link_options(${PROJECT_NAME} PRIVATE
            -T${CMAKE_SOURCE_DIR}/common/STM32F412RGTX_FLASH.ld
            -mcpu=cortex-m4
            -mthumb
            -mfpu=fpv4-sp-d16
            -mfloat-abi=hard
            -specs=nano.specs
            -lc
            -lm
            -lnosys
            -Wl,-Map=${PROJECT_NAME}.map,--cref
            -Wl,--gc-sections
            )

    add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND arm-none-eabi-size ${PROJECT_NAME})
endfunction()
