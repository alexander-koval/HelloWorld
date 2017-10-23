cmake_minimum_required(VERSION 3.0)
project(Grafit)

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

if(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel") AND UNIX))
        option(GRAFIT_ENABLE_CXX_98 "Enable C++ 98" OFF)
        option(GRAFIT_ENABLE_CXX_0X "Enable C++ 0x" OFF)
        option(GRAFIT_ENABLE_CXX_11 "Enable C++ 11" OFF)
        option(GRAFIT_ENABLE_CXX_1Y "Enable C++ 1y" OFF)
        option(GRAFIT_ENABLE_CXX_14 "Enable C++ 14" ON)
        option(GRAFIT_ENABLE_CXX_17 "Enable C++ 17" OFF)

        if(GRAFIT_ENABLE_CXX_17)
                set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++17")
                set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
        elseif(GRAFIT_ENABLE_CXX_14)
                set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++14")
                set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
        elseif(GRAFIT_ENABLE_CXX_1Y)
                set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++1y")
                set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
        elseif(GRAFIT_ENABLE_CXX_11)
                set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
                set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        elseif(GRAFIT_ENABLE_CXX_0X)
                set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
                set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        elseif(GRAFIT_ENABLE_CXX_98)
                set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++98")
                set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")
        endif()
endif()

#include_directories(src)
include_directories(include)
include_directories(extlibs/include)
include_directories(modules/glfw/include)
include_directories(modules/stb/)
include_directories(modules/glm)

if(WIN32)
    link_directories(extlibs/mingw)
elseif(APPLE)
    link_directories(extlibs/osx)
else()
    link_directories(extlibs/linux)
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

add_subdirectory(modules/glfw)
#add_subdirectory(modules/physfs)
#add_subdirectory(modules/poco)
add_subdirectory(src/Grafit)
#add_subdirectory(src/Grafit/Graphics)
#add_subdirectory(src/Grafit/Window)
#add_subdirectory(src/Grafit/System)

#set( Boost_USE_STATIC_LIBS ON CACHE BOOL "Use Boost static libraries" )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW examples" )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW tests" )
set( GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW documentation" )
set( GLFW_INSTALL OFF CACHE BOOL "Generate GLFW installation" )
set( BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" )


set(PHYSFS_ARCHIVE_ZIP TRUE CACHE BOOL "Enable ZIP support")
set(PHYSFS_ARCHIVE_7Z TRUE CACHE BOOL "Enable 7zip support")
set(PHYSFS_ARCHIVE_GRP FALSE CACHE BOOL "Enable Build Engine GRP support")
set(PHYSFS_ARCHIVE_WAD FALSE CACHE BOOL "Enable Doom WAD support")
set(PHYSFS_ARCHIVE_HOG FALSE CACHE BOOL "Enable Descent I/II HOG support")
set(PHYSFS_ARCHIVE_MVL FALSE CACHE BOOL "Enable Descent I/II MVL support")
set(PHYSFS_ARCHIVE_QPAK FALSE CACHE BOOL "Enable Quake I/II QPAK support")
set(PHYSFS_ARCHIVE_SLB FALSE CACHE BOOL "Enable I-War / Independence War SLB support")
set(PHYSFS_ARCHIVE_ISO9660 FALSE CACHE BOOL "Enable ISO9660 support")
set(PHYSFS_ARCHIVE_VDF FALSE CACHE BOOL "Enable Gothic I/II VDF archive support")
set(PHYSFS_BUILD_STATIC TRUE CACHE BOOL "Build static library")
set(PHYSFS_BUILD_SHARED FALSE CACHE BOOL "Build shared library")

#install(TARGETS ${GRAFIT_SYSTEM_LIBRARY} ${GRAFIT_GRAPHICS_LIBRARY} ${GRAFIT_WINDOWS_LIBRARY}
#    RUNTIME DESTINATION bin
#    LIBRARY DESTINATION lib
#    ARCHIVE DESTINATION lib)
