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
    "${SRCROOT}/shaders/v330/positioncolor.frag"
    "${SRCROOT}/shaders/v330/positioncolor.vert"
    "${SRCROOT}/shaders/v330/positiontexture.frag"
    "${SRCROOT}/shaders/v330/positiontexture.vert"
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

message("DIRS: " ${PROJECT_SOURCE_DIR})

#add_resources(positionColor shaders/v330/positioncolor.frag shaders/v330/positioncolor.vert)
#add_resources(positionTexture shaders/v330/positiontexture.frag shaders/v330/positiontexture.vert)

add_shaders(shaders shaders/shaders.cpp
                shaders/v330/positioncolor.frag
                shaders/v330/positioncolor.vert
#                shaders/v330/positiontexture.frag
#                shaders/v330/positiontexture.vert
            )

message("SHADER " ${shaders})

add_library(icebird-graphics STATIC ${icebird_graphics_source_files} ${shaders})

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
    SOIL
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARIES}
    ${EXTRA_LIBS}
)
