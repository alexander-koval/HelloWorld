set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Grafit)

file(GLOB grafit_graphics_source_files
    "${SRCROOT}/Graphics/Shader.cpp"
    "${SRCROOT}/Graphics/OpenGL.cpp"
    "${SRCROOT}/Graphics/GL/glad.c"
    "${SRCROOT}/Graphics/Triangle.cpp"
    "${SRCROOT}/Graphics/Image.cpp"
    "${SRCROOT}/Graphics/Bitmap.cpp"
    "${SRCROOT}/Graphics/Texture.cpp"
    "${SRCROOT}/Graphics/Color.cpp"
    "${SRCROOT}/Graphics/VertexArray.cpp"
    "${SRCROOT}/Graphics/Geometry/Math.cpp"
    "${SRCROOT}/Graphics/View.cpp"
    "${SRCROOT}/Graphics/Transform.cpp"
    "${SRCROOT}/Graphics/Transformable.cpp"
    "${SRCROOT}/Graphics/RenderTarget.cpp"
    "${SRCROOT}/Graphics/RenderStates.cpp"
    "${SRCROOT}/Graphics/BlendMode.cpp"
    "${SRCROOT}/Graphics/VBO.cpp"
    "${SRCROOT}/Graphics/Sprite.cpp"
    "${SRCROOT}/Graphics/shaders/shaders.cpp"
    "${SRCROOT}/Graphics/shaders/v330/positioncolor.frag"
    "${SRCROOT}/Graphics/shaders/v330/positioncolor.vert"
    "${SRCROOT}/Graphics/shaders/v330/positiontexture.frag"
    "${SRCROOT}/Graphics/shaders/v330/positiontexture.vert"
    "${SRCROOT}/Graphics/shaders/v330/luma/luma.frag"
    "${SRCROOT}/Graphics/shaders/v330/dither/2x2.frag"
    "${SRCROOT}/Graphics/shaders/v330/dither/4x4.frag"
    "${SRCROOT}/Graphics/shaders/v330/dither/8x8.frag"
    "${SRCROOT}/Graphics/shaders/v330/hsv2rgb/hsv2rgb.frag"
)

file(GLOB grafit_system_source_files
    "${SRCROOT}/System/Clock.cpp"
    "${SRCROOT}/System/Lock.cpp"
    "${SRCROOT}/System/Mutex.cpp"
    "${SRCROOT}/System/Sleep.cpp"
    "${SRCROOT}/System/String.cpp"
    "${SRCROOT}/System/Thread.cpp"
    "${SRCROOT}/System/ThreadLocal.cpp"
    "${SRCROOT}/System/Time.cpp"
    "${SRCROOT}/System/Assert.cpp"
    "${SRCROOT}/System/Exception.cpp"
    "${SRCROOT}/System/File.cpp"
    "${SRCROOT}/System/Path.cpp"
    "${SRCROOT}/System/SystemInfo.cpp"
    "${SRCROOT}/System/Signals/Connection.cpp"
    "${SRCROOT}/System/Uuid.cpp"
    "${SRCROOT}/System/RefCounter.cpp"
    "${SRCROOT}/System/ResourceManager.cpp"
    "${SRCROOT}/System/Promise/EventLoop.cpp"
    "${SRCROOT}/System/IO/Stream.cpp"
    "${SRCROOT}/System/IO/FileStream.cpp"
    "${SRCROOT}/System/IO/FileSystem.cpp"
    "${SRCROOT}/System/IO/PhysfsFileSystem.cpp"
    "${SRCROOT}/System/IO/VirtualFileSystem.cpp"
)

if(WIN32)
    set(grafit_system_extra_libs "-lwinmm")
    file(GLOB grafit_system_platform_source_files
        "${SRCROOT}/System/Win32/ClockImpl.hpp"
        "${SRCROOT}/System/Win32/ClockImpl.cpp"
        "${SRCROOT}/System/Win32/MutexImpl.hpp"
        "${SRCROOT}/System/Win32/MutexImpl.cpp"
        "${SRCROOT}/System/Win32/SleepImpl.hpp"
        "${SRCROOT}/System/Win32/SleepImpl.cpp"
        "${SRCROOT}/System/Win32/ThreadImpl.hpp"
        "${SRCROOT}/System/Win32/ThreadImpl.cpp"
        "${SRCROOT}/System/Win32/ThreadLocalImpl.hpp"
        "${SRCROOT}/System/Win32/ThreadLocalImpl.cpp"
        "${SRCROOT}/System/Win32/SystemInfoImpl.hpp"
        "${SRCROOT}/System/Win32/SystemInfoImpl.cpp"
        "${SRCROOT}/System/Win32/FileImpl.hpp"
        "${SRCROOT}/System/Win32/FileImpl.cpp"
    )
    source_group("Win32" FILES ${grafit_system_platform_source_files})
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    set(grafit_system_extra_libs ${COCOA_LIBRARY})
    file(GLOB grafit_system_platform_source_files
        "${SRCROOT}/System/Unix/ClockImpl.hpp"
        "${SRCROOT}/System/Unix/ClockImpl.cpp"
        "${SRCROOT}/System/Unix/MutexImpl.hpp"
        "${SRCROOT}/System/Unix/MutexImpl.cpp"
        "${SRCROOT}/System/Unix/SleepImpl.hpp"
        "${SRCROOT}/System/Unix/SleepImpl.cpp"
        "${SRCROOT}/System/Unix/ThreadImpl.hpp"
        "${SRCROOT}/System/Unix/ThreadImpl.cpp"
        "${SRCROOT}/System/Unix/ThreadLocalImpl.hpp"
        "${SRCROOT}/System/Unix/ThreadLocalImpl.cpp"
        "${SRCROOT}/System/OSX/SystemInfoImpl.hpp"
        "${SRCROOT}/System/OSX/SystemInfoImpl.mm"
    )
    source_group("OSX" FILES ${grafit_system_platform_source_files})
else()
    file(GLOB grafit_system_platform_source_files
        "${SRCROOT}/System/Unix/ClockImpl.hpp"
        "${SRCROOT}/System/Unix/ClockImpl.cpp"
        "${SRCROOT}/System/Unix/MutexImpl.hpp"
        "${SRCROOT}/System/Unix/MutexImpl.cpp"
        "${SRCROOT}/System/Unix/SleepImpl.hpp"
        "${SRCROOT}/System/Unix/SleepImpl.cpp"
        "${SRCROOT}/System/Unix/ThreadImpl.hpp"
        "${SRCROOT}/System/Unix/ThreadImpl.cpp"
        "${SRCROOT}/System/Unix/ThreadLocalImpl.hpp"
        "${SRCROOT}/System/Unix/ThreadLocalImpl.cpp"
        "${SRCROOT}/System/Unix/SystemInfoImpl.hpp"
        "${SRCROOT}/System/Unix/SystemInfoImpl.cpp"
        "${SRCROOT}/System/Unix/FileImpl.hpp"
        "${SRCROOT}/System/Unix/FileImpl.cpp"
    )
    source_group("Unix" FILES ${grafit_system_platform_source_files})
endif()

file(GLOB grafit_window_source_files
    "${SRCROOT}/Window/Window.cpp"
    "${SRCROOT}/Window/VideoMode.cpp"
)

source_group("System" FILES ${grafit_system_source_files})
source_group("Graphics" FILES ${grafit_graphics_source_files})
source_group("Window" FILES ${grafit_window_source_files})

if(WIN32)
    find_library(OPENGL_LIBRARY OpenGL32)
    find_library(GDI_LIBRARY GDI32)
    list(APPEND grafit_window_extra_libs "-lopengl32 -lgdi32")
elseif(APPLE)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
    mark_as_advanced(COCOA_FRAMEWORK
                     IOKIT_FRAMEWORK
                     CORE_FOUNDATION_FRAMEWORK
                     CORE_VIDEO_FRAMEWORK)
    list(APPEND glfw_LIBRARIES "${COCOA_FRAMEWORK}"
                               "${OPENGL_gl_LIBRARY}"
                               "${IOKIT_FRAMEWORK}"
                               "${CORE_FOUNDATION_FRAMEWORK}"
                               "${CORE_VIDEO_FRAMEWORK}")
    list(APPEND grafit_window_extra_libs "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo")
else()
    list(APPEND grafit_window_extra_libs "-lX11 -lXxf86vm -lXrandr -lXi -lXinerama -lXcursor -lpthread -ldl")
endif()

find_package(OpenGL REQUIRED)

get_property(GRAFIT_LINK_DIRECTORIES DIRECTORY PROPERTY LINK_DIRECTORIES)
find_library(GLFW_LIBRARY
    NAMES glfw3.a libglfw3.a
    PATHS ${GRAFIT_LINK_DIRECTORIES})

find_library(PHYSFS_LIBRARY
    NAMES libphysfs.a
    PATHS ${GRAFIT_LINK_DIRECTORIES})

message("GLFW " ${GLFW_LIBRARY})
message("OPENGL_LIBRARY " ${OPENGL_LIBRARY})
message("GLFW_LIBRARIES " ${GLFW_LIBRARIES})

add_shaders(shaders
                Graphics/shaders/v330/positioncolor.frag
                Graphics/shaders/v330/positioncolor.vert
                Graphics/shaders/v330/positiontexture.frag
                Graphics/shaders/v330/positiontexture.vert
                Graphics/shaders/v330/luma/luma.frag
                Graphics/shaders/v330/dither/2x2.frag
                Graphics/shaders/v330/dither/4x4.frag
                Graphics/shaders/v330/dither/8x8.frag
#                Graphics/shaders/v330/hsv2rgb/hsv2rgb.frag
                Graphics/shaders/v330/water/water2d.frag
            )

message("SHADER " ${shaders})

include_directories(${FREETYPE_INCLUDE_DIRS} ${GLEW_INCLUDE_PATH} ${JPEG_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

add_library(grafit STATIC
    ${grafit_system_source_files}
    ${grafit_system_platform_source_files}
    ${grafit_graphics_source_files}
    ${grafit_window_source_files}
    ${shaders})
target_link_libraries(grafit
    ${GLFW_LIBRARY}
    ${PHYSFS_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARIES}
    ${grafit_window_extra_libs}
)
set(GRAFIT_LIBRARY grafit)

install(TARGETS ${GRAFIT_LIBRARY}
    ARCHIVE DESTINATION lib COMPONENT lib
    LIBRARY DESTINATION lib COMPONENT lib)
