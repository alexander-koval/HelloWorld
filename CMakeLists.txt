project(HelloWorld)
cmake_minimum_required(VERSION 3.6)

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
    ${PROJECT_BINARY_DIR}/helloworld/libs
    CACHE PATH
    "Single Directory for all Libraries."
)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
#    ${PROJECT_BINARY_DIR}/application
#    CACHE PATH
#    "Single Directory for all Executables."
#)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/helloworld/libs
    CACHE PATH
    "Single Directory for all Libraries."
)

include_directories(
    ${PROJECT_SOURCE_DIR}/Grafit/extlibs/include
    ${PROJECT_SOURCE_DIR}/Grafit/modules/glm
    ${PROJECT_SOURCE_DIR}/Grafit/modules/stb
    ${PROJECT_SOURCE_DIR}/Grafit/modules/loki/include
)

message("DIRS: " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

if(APPLE)
#    include_directories(/System/Library/FRAMEWORKS)
#    find_library(COCOA_LIBRARY Cocoa)
#    find_library(OpenGL_LIBRARY OpenGL)
#    mark_as_advanced(COCOA_LIBRARY
#                      GLFW_LIBRARY
#                      OpenGL_LIBRARY)
#    set(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY})
link_directories(Grafit/extlibs/osx)
elseif(WIN32)
    link_directories(Grafit/extlibs/mingw)
else()
    link_directories(Grafit/extlibs/linux)
endif()

#set(GRAFIT_ENABLE_CXX_11 ON CACHE BOOL "ISO C++11 standart")
set(CMAKE_CXX_FLAGS "-std=c++17 -DSTB_IMAGE_IMPLEMENTATION")

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

#get_property(GRAFIT_LINK_DIRECTORIES DIRECTORY PROPERTY LINK_DIRECTORIES)
#find_library(GLFW_LIBRARY
#    NAMES glfw3.dll glfw.a libglfw.a glfw.a
#    PATHS GRAFIT_LINK_DIRECTORIES)

add_subdirectory(Grafit)
add_subdirectory(helloworld)

#install(TARGETS ${PROJECT_NAME} ${GRAFIT_SYSTEM_LIBRARY} ${GRAFIT_GRAPHICS_LIBRARY} ${GRAFIT_WINDOWS_LIBRARY}
#    RUNTIME DESTINATION bin
#    LIBRARY DESTINATION lib
#    ARCHIVE DESTINATION lib)

