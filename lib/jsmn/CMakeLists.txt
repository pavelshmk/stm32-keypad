add_library(jsmn INTERFACE)
target_sources(jsmn INTERFACE
        jsmn.c
        )
target_include_directories(jsmn INTERFACE
        .
        )
target_compile_definitions(jsmn INTERFACE
        -DJSMN_HEADER
        -DJSMN_STATIC
        )