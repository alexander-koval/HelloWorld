file(GLOB hello_world_source_files
    "main.cpp"
)

if(APPLE)
    set(BUNDLE_BINARIES ${PROJECT_NAME})
    set_target_properties(${BUNDLE_BINARIES} PROPERTIES
                            MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLFW_VERSION}
                            MACOSX_BUNDLE_LONG_VERSION_STRING ${GLFW_VERSION_FULL})

    # Locate all recourses
    file(GLOB COPY_RESOURCES ${PROJECT_SOURCE_DIR}/media/*.png)
    set_source_files_properties(
        "${COPY_RESOURCES}"
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "HelloWorld")
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "output")
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${hello_world_source_files} ${COPY_RESOURCES})
elseif(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${hello_world_source_files})
    add_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "output")
else()
    set(BUNDLE_NAME ${PROJECT_NAME})
#    set(BUNDLE_PATH ${CMAKE_INSTALL_PREFIX})
    add_executable(${PROJECT_NAME} ${hello_world_source_files})
endif()

target_link_libraries(${PROJECT_NAME}
    icebird-graphics
    glfw3
    GLEW
    ${EXTRA_LIBS}
)
