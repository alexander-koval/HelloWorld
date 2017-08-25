#set(INCROOT ${PROJECT_SOURCE_DIR}/include/Grafit/Window)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Grafit/Window)

file(GLOB grafit_window_source_files
#${INCROOT}/Window.hpp
${SRCROOT}/Window.cpp
#${INCROOT}/VideoMode.hpp
${SRCROOT}/VideoMode.cpp
)

source_group("" FILES ${grafit_window_source_files})
find_library(GRAFIT_GRAPHICS_LIBRARY grafit-graphics)

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

message("GLFW " ${GLFW_LIBRARY})
message("OPENGL_LIBRARY " ${OPENGL_LIBRARY})
message("GLFW_LIBRARIES " ${GLFW_LIBRARIES})

set(GRAPHIT_WINDOW_LIBRARY grafit-window)
add_library(grafit-window SHARED ${grafit_window_source_files})

target_link_libraries(grafit-window
    grafit-graphics
    ${GLFW_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARIES}
    ${grafit_window_extra_libs}
)

install(TARGETS ${GRAFIT_WINDOW_LIBRARY}
    ARCHIVE DESTINATION lib COMPONENT lib
    LIBRARY DESTINATION lib COMPONENT lib)
