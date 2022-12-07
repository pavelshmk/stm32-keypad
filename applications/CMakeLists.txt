include(applications.cmake)

add_library(applications INTERFACE)
target_include_directories(applications INTERFACE
        services
        .
)
target_sources(applications INTERFACE
        applications.c
        ${APPLICATIONS_SOURCES}
)
