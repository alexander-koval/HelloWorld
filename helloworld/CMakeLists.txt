file(GLOB hello_world_source_files
    "main.cpp"
)

if(APPLE)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${hello_world_source_files})
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "HelloWorld")
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "output")
elseif(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${hello_world_source_files})
    add_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "output")
else()
    add_executable(${PROJECT_NAME} ${hello_world_source_files})
endif()

target_link_libraries(${PROJECT_NAME}
    icebird-graphics
    glfw3
    GLEW
    ${EXTRA_LIBS}
)

if(APPLE)
    set(BUNDLE_BINARIES ${PROJECT_NAME})
    set_target_properties(${BUNDLE_BINARIES} PROPERTIES
                            MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLFW_VERSION}
                            MACOSX_BUNDLE_LONG_VERSION_STRING ${GLFW_VERSION_FULL})
endif()
