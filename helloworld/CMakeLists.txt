file(GLOB hello_world_source_files
    "main.cpp"
)

add_executable(${PROJECT_NAME} ${hello_world_source_files})

target_link_libraries(${PROJECT_NAME}
    icebird-graphics
    glfw
    GLEW
    GLU
    GL
)
