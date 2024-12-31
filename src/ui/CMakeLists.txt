SET(SOURCES screens/ui_main.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_pointer_png.c)

add_library(ui ${SOURCES})
