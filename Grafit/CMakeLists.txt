project(Grafit)
cmake_minimum_required(VERSION 3.0)

set(Grafit_VERSION_MAJOR 0)
set(Grafit_VERSION_MINOR 1)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/")

#include ("${CMAKE_MODULE_PATH}/AddBoost.cmake")

function(add_shaders output)
    set(result)
    foreach(INPUT_FILE ${ARGN})
        file(RELATIVE_PATH SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE})
        set(OUTPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE}.c")
        add_custom_command(OUTPUT ${OUTPUT_FILE}
            COMMAND xxd -i ${SOURCE_FILE} > ${OUTPUT_FILE}
            DEPENDS ${INPUT_FILE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Embedding shader to file ${OUTPUT_FILE}"
            VERBATIM
        )
        list(APPEND result ${OUTPUT_FILE})
    endforeach()
    set(${output} ${result} PARENT_SCOPE)
endfunction()

#set( Boost_USE_STATIC_LIBS ON CACHE BOOL "Use Boost static libraries" )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW examples" )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW tests" )
set( GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW documentation" )
set( GLFW_INSTALL OFF CACHE BOOL "Generate GLFW installation" )
set( BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" )

include_directories(extlibs/include)
include_directories(modules/glfw/include)
include_directories(modules/stb/)

if(WIN32)
    message(${PROJECT_SOURCE_DIR}/extlibs/mingw)
    link_directories(${PROJECT_SOURCE_DIR}/extlibs/mingw)
elseif(APPLE)
    link_directories(${PROJECT_SOURCE_DIR}/extlibs/osx)
else()
    link_directories(${PROJECT_SOURCE_DIR}/extlibs/linux)
endif()

if(APPLE)
add_definitions(-DGLFW_EXPOSE_NATIVE_COCOA -DGLFW_EXPOSE_NATIVE_NSGL -DGRAFIT_SYSTEM_MACOS)
elseif(WIN32)
set(GLFW_USE_DWM_SWAP_INTERVAL ON)
add_definitions(-DGLFW_EXPOSE_NATIVE_WIN32
                -DGLFW_EXPOSE_NATIVE_WGL
                -DGRAFIT_SYSTEM_WINDOWS)
else()
add_definitions(-DGLFW_EXPOSE_NATIVE_X11 -DGLFW_EXPOSE_NATIVE_GLX -DGRAFIT_SYSTEM_LINUX)
endif()

#add_subdirectory(modules/glfw)
#add_subdirectory(modules/glm)
add_subdirectory(src/Grafit)
