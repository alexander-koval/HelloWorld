set(INCROOT ${PROJECT_SOURCE_DIR}/include/icebird/Graphics)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/icebird/Graphics)

file(GLOB icebird_graphics_source_files
    "${INCROOT}/Shader.hpp"
    "${SRCROOT}/Shader.cpp"
    "${INCROOT}/GL/OpenGL.hpp"
    "${SRCROOT}/GL/OpenGL.cpp"
    "${INCROOT}/GL/glad.h"
    "${SRCROOT}/GL/glad.c"
    "${INCROOT}/Triangle.hpp"
    "${SRCROOT}/Triangle.cpp"
    "${INCROOT}/ImageData.hpp"
    "${SRCROOT}/ImageData.cpp"
    "${INCROOT}/Image.hpp"
    "${SRCROOT}/Image.cpp"
    "${INCROOT}/Texture.hpp"
    "${SRCROOT}/Texture.cpp"
    "${INCROOT}/Color.hpp"
    "${INCROOT}/Color.inl"
    "${SRCROOT}/Color.cpp"
    "${INCROOT}/Vertex.hpp"
    "${INCROOT}/Vertex.inl"
    "${INCROOT}/Geometry/Mat4.hpp"
    "${INCROOT}/Geometry/Mat4.inl"
    "${INCROOT}/Geometry/Mat3.hpp"
    "${INCROOT}/Geometry/Mat3.inl"
    "${INCROOT}/Geometry/Vector2.hpp"
    "${INCROOT}/Geometry/Vector2.inl"
    "${INCROOT}/VBO.hpp"
    "${SRCROOT}/VBO.cpp"
    "${INCROOT}/shaders/shaders.hpp"
    "${SRCROOT}/shaders/shaders.cpp"
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
#    find_package(GLEW REQUIRED)
    if(SFML_OS_LINUX)
        find_package(X11 REQUIRED)
    endif()
    include_directories(${FREETYPE_INCLUDE_DIRS} ${GLEW_INCLUDE_PATH} ${JPEG_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
endif()

#set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/SOIL/src")
#set(LIBSOIL_LIBDIR "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
#find_package(SOIL REQUIRED)
add_shaders(shaders
                shaders/v330/positioncolor.frag
                shaders/v330/positioncolor.vert
                shaders/v330/positiontexture.frag
                shaders/v330/positiontexture.vert
            )

message("SHADER " ${shaders})

add_library(icebird-graphics STATIC ${icebird_graphics_source_files} ${shaders})

if(APPLE)
set(DESKTOP_LIBS Cocoa)
elseif(WIN32)
else()
set(DESKTOP_LIBS X11 Xxf86vm Xrandr Xi Xinerama Xcursor pthread dl)
endif()

target_link_libraries(icebird-graphics
#    EGL
#    glfw
#    GLU
#    GL
    SOIL
    ${DESKTOP_LIBS}
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARIES}
    ${EXTRA_LIBS}
)
