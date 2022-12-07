add_library(tomlc99 INTERFACE)
target_sources(tomlc99 INTERFACE
        toml.c
        )
target_include_directories(tomlc99 INTERFACE
        .
        )