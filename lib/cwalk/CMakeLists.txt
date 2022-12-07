add_library(cwalk INTERFACE)
target_sources(cwalk INTERFACE
        cwalk.c
        )
target_include_directories(cwalk INTERFACE
        .
        )