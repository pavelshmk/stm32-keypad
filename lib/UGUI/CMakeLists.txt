add_library(ugui INTERFACE)
target_sources(ugui INTERFACE
        ugui.c
        ugui_button.c
        ugui_checkbox.c
        ugui_image.c
        ugui_progress.c
        ugui_textbox.c
        )
target_include_directories(ugui INTERFACE
        .)

file(GLOB ugui_fonts ${CMAKE_CURRENT_LIST_DIR}/Fonts/*.c)
foreach(font_file ${ugui_fonts})
    string(REGEX REPLACE "^.*\\/(.*)\\.c$" "\\1" font ${font_file})
    add_library(ugui_${font} INTERFACE)
    target_sources(ugui_${font} INTERFACE ${font_file})
    target_link_libraries(ugui_${font} INTERFACE ugui)
    add_library(ugui::${font} ALIAS ugui_${font})
endforeach()