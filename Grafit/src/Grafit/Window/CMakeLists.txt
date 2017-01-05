set(INCROOT ${PROJECT_SOURCE_DIR}/include/Grafit/Window)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Grafit/Window)

file(GLOB grafit_window_source_files
${INCROOT}/Window.hpp
${SRCROOT}/Window.cpp
${INCROOT}/VideoMode.hpp
${SRCROOT}/VideoMode.cpp
)

source_group("" FILES ${grafit_window_source_files})

add_library(grafit-window SHARED ${grafit_window_source_files})

target_link_libraries(grafit-window
    glfw
    grafit-graphics
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARIES}
    ${EXTRA_LIBS}
)
