add_library(ringbuffer INTERFACE)
target_sources(ringbuffer INTERFACE ringbuffer.c)
target_include_directories(ringbuffer INTERFACE .)

