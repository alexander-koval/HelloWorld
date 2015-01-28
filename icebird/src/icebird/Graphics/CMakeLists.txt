set(INCROOT ${PROJECT_SOURCE_DIR}/include/icebird/Graphics)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/icebird/Graphics)

function(add_resources output)
    set(result)
    foreach(INPUT_FILE ${ARGN})
        file(RELATIVE_PATH SOURCE_FILE ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE})
        set(OUTPUT_FILE "${PROJECT_BINARY_DIR}/${INPUT_FILE}.o")
#        message("SHADER: " ${SOURCE_FILE})
        add_custom_command(OUTPUT ${OUTPUT_FILE}
            COMMAND ld -r -b binary -o ${OUTPUT_FILE} ${SOURCE_FILE}
            DEPENDS ${INPUT_FILE}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Embedding resource file ${OUTPUT_FILE}"
            VERBATIM
        )
        list(APPEND result ${OUTPUT_FILE})
    endforeach()
    set(${output} "${result}" PARENT_SCOPE)
endfunction()

file(GLOB icebird_graphics_source_files
    "${INCROOT}/Shader.hpp"
    "${SRCROOT}/Shader.cpp"
    "${INCROOT}/Shaders.hpp"
    "${SRCROOT}/Shaders.cpp"
    "${SRCROOT}/shaders/shaderpc.frag"
    "${SRCROOT}/shaders/shaderpc.vert"
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

add_resources(positionColor_frag shaders/v330/positionColor.frag shaders/v330/positionColor.vert)
#add_resources(positionColor_vert shaders/v330/positionColor.vert)

message("SHADER FRAG: " ${positionColor_frag})
message("SHADER VERT: " ${positionColor_vert})

add_library(icebird-graphics STATIC ${icebird_graphics_source_files} ${positionColor_frag} ${positionColor_vert})

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
