set(INCROOT ${PROJECT_SOURCE_DIR}/include/icebird/Graphics)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/icebird/Graphics)

file(GLOB icebird_graphics_source_files
    "${INCROOT}/Shader.hpp"
    "${SRCROOT}/Shader.cpp"
)

#include_directories(${INCROOT})

source_group("" FILES ${icebird_graphics_source_files})

# find external libraries
if(NOT SFML_OPENGL_ES)
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
    if(SFML_OS_LINUX)
        find_package(X11 REQUIRED)
    endif()
    include_directories(${FREETYPE_INCLUDE_DIRS} ${GLEW_INCLUDE_PATH} ${JPEG_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
endif()

add_library(icebird-graphics STATIC ${icebird_graphics_source_files})

target_link_libraries(icebird-graphics
    EGL
    X11
    Xxf86vm
    Xrandr
    Xi
    Xinerama
    Xcursor
    pthread
    glfw
    GLU
    GL
)
