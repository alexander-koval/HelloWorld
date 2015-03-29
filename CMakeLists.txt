project(HelloWorld)
cmake_minimum_required(VERSION 2.8)

set(HelloWorld_VERSION_MAJOR 0)
set(HelloWorld_VERSION_MINOR 1)

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
)

if(APPLE)
    include_directories(/System/Library/Frameworks)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL )
    MARK_AS_ADVANCED (COCOA_LIBRARY
                      GLFW_LIBRARY
                      OpenGL_LIBRARY)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY})
endif()

link_directories(
    ${PROJECT_BINARY_DIR}/application/libs
)

add_subdirectory(Grafit)
add_subdirectory(helloworld)
