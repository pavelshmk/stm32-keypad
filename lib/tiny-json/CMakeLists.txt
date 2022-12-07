add_library(tiny-json INTERFACE)
target_sources(tiny-json INTERFACE
        tiny-json.c
        )
target_include_directories(tiny-json INTERFACE
        .
        )