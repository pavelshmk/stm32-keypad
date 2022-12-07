add_library(FatFs INTERFACE)
target_sources(FatFs INTERFACE
        ff.c
        ffsystem.c
        ffunicode.c)
target_include_directories(FatFs INTERFACE
        .)
