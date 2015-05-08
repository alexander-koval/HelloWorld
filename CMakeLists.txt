project(HelloWorld)
cmake_minimum_required(VERSION 2.8)

set(HelloWorld_VERSION_MAJOR 0)
set(HelloWorld_VERSION_MINOR 1)

option(DEBUG_MODE "Debug or Release?" ON)

if(DEBUG_MODE)
    add_definitions(-DDEBUG_MODE)
    set(CMAKE_BUILD_TYPE Debug)
else(DEBUG_MODE)
    set(CMAKE_BUILD_TYPE Release)
endif(DEBUG_MODE)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/application/libs
    CACHE PATH
    "Single Directory for all Libraries."
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/application
    CACHE PATH
    "Single Directory for all Executables."
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/application/libs
    CACHE PATH
    "Single Directory for all Libraries."
)

include_directories(
    ${PROJECT_SOURCE_DIR}/Grafit/include
    ${PROJECT_SOURCE_DIR}/Grafit/extlibs/include
    ${PROJECT_SOURCE_DIR}/Grafit/modules/glm
    ${PROJECT_SOURCE_DIR}/Grafit/modules/stb
)

message("DIRS: " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

if(APPLE)
    include_directories(/System/Library/Frameworks)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    MARK_AS_ADVANCED (COCOA_LIBRARY
                      GLFW_LIBRARY
                      OpenGL_LIBRARY)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY})
endif()

set(GRAFIT_ENABLE_CXX_11 ON CACHE BOOL "ISO C++11 standart")
set(CMAKE_CXX_FLAGS "-std=c++11 -DSTB_IMAGE_IMPLEMENTATION")

link_directories(
    ${PROJECT_BINARY_DIR}/application/libs
)

add_subdirectory(Grafit)
add_subdirectory(helloworld)
