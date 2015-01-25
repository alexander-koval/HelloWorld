set(INCROOT ${PROJECT_SOURCE_DIR}/include/icebird/Window)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/icebird/Window)

file(GLOB icebird_window_source_files
${INCROOT}/Window.hpp
${SRCROOT}/Window.cpp
)

#include_directories(${INCROOT})

source_group("" FILES ${icebird_window_source_files})

add_library(icebird-window STATIC ${icebird_window_source_files})

target_link_libraries(icebird-window
    X11
    Xxf86vm
    Xrandr
    Xi
    Xinerama
    Xcursor
    pthread
    glfw
)
