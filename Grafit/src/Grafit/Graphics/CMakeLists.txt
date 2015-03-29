set(INCROOT ${PROJECT_SOURCE_DIR}/include/Grafit/Graphics)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Grafit/Graphics)

file(GLOB Grafit_graphics_source_files
    "${INCROOT}/Shader.hpp"
    "${SRCROOT}/Shader.cpp"
    "${INCROOT}/GL/OpenGL.hpp"
    "${SRCROOT}/GL/OpenGL.cpp"
    "${INCROOT}/GL/glad.h"
    "${INCROOT}/GL/KHR/khrplatform.h"
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
    "${INCROOT}/Geometry/Vector3.hpp"
    "${INCROOT}/Geometry/Vector3.inl"
    "${INCROOT}/Drawable.hpp"
    "${INCROOT}/Transform.hpp"
    "${SRCROOT}/Transform.cpp"
    "${INCROOT}/Transformable.hpp"
    "${SRCROOT}/Transformable.cpp"
    "${INCROOT}/VBO.hpp"
    "${SRCROOT}/VBO.cpp"
    "${INCROOT}/shaders/shaders.hpp"
    "${SRCROOT}/shaders/shaders.cpp"
    "${SRCROOT}/shaders/v330/positioncolor.frag"
    "${SRCROOT}/shaders/v330/positioncolor.vert"
    "${SRCROOT}/shaders/v330/positiontexture.frag"
    "${SRCROOT}/shaders/v330/positiontexture.vert"
    "${SRCROOT}/shaders/luma/luma.glsl"
    "${SRCROOT}/shaders/dither/2x2.glsl"
    "${SRCROOT}/shaders/dither/4x4.glsl"
    "${SRCROOT}/shaders/dither/8x8.glsl"
    "${SRCROOT}/shaders/hsv2rgb/hsv2rgb.glsl"
)

#include_directories(${INCROOT})

source_group("" FILES ${Grafit_graphics_source_files})

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
                shaders/luma/luma.glsl
                shaders/dither/2x2.glsl
                shaders/dither/4x4.glsl
                shaders/dither/8x8.glsl
                shaders/hsv2rgb/hsv2rgb.glsl
            )

message("SHADER " ${shaders})

add_library(Grafit-graphics STATIC ${Grafit_graphics_source_files} ${shaders})

if(APPLE)
find_library(COCOA_LIBRARY Cocoa)
set(DESKTOP_LIBS ${COCOA_LIBRARY})
elseif(WIN32)
else()
set(DESKTOP_LIBS X11 Xxf86vm Xrandr Xi Xinerama Xcursor pthread dl)
endif()

target_link_libraries(Grafit-graphics
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