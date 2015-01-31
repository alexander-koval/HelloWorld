set(INCROOT ${PROJECT_SOURCE_DIR}/include/icebird/Graphics)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/icebird/Graphics)

file(GLOB icebird_graphics_source_files
    "${INCROOT}/Shader.hpp"
    "${SRCROOT}/Shader.cpp"
    "${INCROOT}/Shaders.hpp"
    "${SRCROOT}/Shaders.cpp"
    "${INCROOT}/GL/OpenGL.hpp"
    "${SRCROOT}/GL/OpenGL.cpp"
    "${INCROOT}/Triangle.hpp"
    "${SRCROOT}/Triangle.cpp"
    "${SRCROOT}/shaders/v330/positionColor.frag"
    "${SRCROOT}/shaders/v330/positionColor.vert"
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

add_resources(positionColor shaders/v330/positionColor.frag shaders/v330/positionColor.vert)
#add_resources(positionColor_vert shaders/v330/positionColor.vert)

message("SHADER " ${positionColor})

add_library(icebird-graphics STATIC ${icebird_graphics_source_files} ${positionColor})

target_link_libraries(icebird-graphics
#    EGL
#    X11
#    Xxf86vm
#    Xrandr
#    Xi
#    Xinerama
#    Xcursor
#    pthread
#    glfw
#    GLU
#    GL
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARIES}
    ${EXTRA_LIBS}
)
