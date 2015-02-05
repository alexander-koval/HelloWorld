file(GLOB hello_world_source_files
    "main.cpp"
)

if(APPLE)
    set(BUNDLE_NAME ${PROJECT_NAME}.app)
    set(BUNDLE_PATH "${CMAKE_INSTALL_PREFIX}/${BUNDLE_NAME}")
    set(BINDIR ${BUNDLE_NAME}/Contents/MacOS)
    set(LIBDIR ${BINDIR})
    set(RLIBDIR ${BUNDLE_NAME}/Contents/Frameworks)
    set(SHAREDIR ${BUNDLE_NAME}/Contents/Resources)
    set(PLUGINSDIR ${BUNDLE_NAME}/Contents/PlugIns)
    set(IMPORTSDIR ${BINDIR})
    set(BUNDLE_BINARIES ${PROJECT_NAME})

    # Locate all recourses
    file(GLOB COPY_RESOURCES ${PROJECT_SOURCE_DIR}/media/*.png)

    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${hello_world_source_files} ${COPY_RESOURCES})

    set_source_files_properties(
        "${COPY_RESOURCES}"
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources
    )

    set_target_properties(${BUNDLE_BINARIES} PROPERTIES
                            MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLFW_VERSION}
                            MACOSX_BUNDLE_LONG_VERSION_STRING ${GLFW_VERSION_FULL})


    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "HelloWorld")
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "output")
elseif(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${hello_world_source_files})
    add_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "output")

else()
    set(BUNDLE_NAME ${PROJECT_NAME})
#    set(BUNDLE_PATH ${CMAKE_INSTALL_PREFIX})
    add_executable(${PROJECT_NAME} ${hello_world_source_files})

    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_CURRENT_SOURCE_DIR}/media Resources
                        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

target_link_libraries(${PROJECT_NAME}
    icebird-graphics
    GLEW
    glfw3
    ${GLFW_LIBRARIES}
    ${EXTRA_LIBS}
)
