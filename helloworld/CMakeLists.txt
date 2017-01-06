file(GLOB hello_world_source_files
    "main.cpp"
)

include_directories(
    ${PROJECT_SOURCE_DIR}/Grafit/include
    ${PROJECT_SOURCE_DIR}/Grafit/extlibs/include
    ${PROJECT_SOURCE_DIR}/Grafit/modules/glm
    ${PROJECT_SOURCE_DIR}/Grafit/modules/stb
    ${PROJECT_SOURCE_DIR}/Grafit/modules/loki/include
)

if(APPLE)
#    include(GmtHelperMacros)
    #dsymutil
    find_program(DSYMUTIL dsymutil)
    #dwarfdump
#    find_program(DWARFDUMP dwarfdump)

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
    file(GLOB COPY_RLIBS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/*.dylib)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${hello_world_source_files} ${COPY_RESOURCES} ${COPY_RLIBS})

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E make_directory
                        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${RLIBDIR})

    foreach(library ${COPY_RLIBS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                            COMMAND ${CMAKE_COMMAND} -E copy
                            ${library} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${RLIBDIR})
    endforeach()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E make_directory
                        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SHAREDIR})
    foreach(resource ${COPY_RESOURCES})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                            COMMAND ${CMAKE_COMMAND} -E copy
                            ${resource} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SHAREDIR})
    endforeach()

    if(DSYMUTIL)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                            COMMAND ${DSYMUTIL} $<TARGET_FILE:${PROJECT_NAME}>
                            ARGS -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${BUNDLE_NAME}.dSYM
                            COMMENT "Generating .dSYM bundle for ${PROJECT_NAME}"
                            COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${PROJECT_NAME}>
                            COMMENT "Strip debug information from ${PROJECT_NAME}"
                            VERBATIM)
    endif()
    set_target_properties(${BUNDLE_BINARIES} PROPERTIES
                            MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLFW_VERSION}
                            MACOSX_BUNDLE_LONG_VERSION_STRING ${GLFW_VERSION_FULL})


    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "HelloWorld")
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "output")

elseif(WIN32)
    file(GLOB COPY_RESOURCES ${PROJECT_SOURCE_DIR}/media/*.png)
    set(BUNDLE_NAME ${PROJECT_NAME})
    add_executable(${PROJECT_NAME} WIN32 ${hello_world_source_files})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E make_directory
                        Resources
                        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    foreach(resource ${COPY_RESOURCES})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                            COMMAND ${CMAKE_COMMAND} -E copy
                            ${resource} Resources
                            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endforeach()
else()
    find_program(OBJCOPY objcopy)
    file(GLOB COPY_RESOURCES ${PROJECT_SOURCE_DIR}/media/*.png)
    set(BUNDLE_NAME ${PROJECT_NAME})
    add_executable(${PROJECT_NAME} ${hello_world_source_files})

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E make_directory
                        Resources
                        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    foreach(resource ${COPY_RESOURCES})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                            COMMAND ${CMAKE_COMMAND} -E copy
                            ${resource} Resources
                            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endforeach()
    if(OBJCOPY)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                            COMMAND ${OBJCOPY} $<TARGET_FILE:${PROJECT_NAME}>
                            ARGS --only-keep-debug $<TARGET_FILE:${PROJECT_NAME}>.dSYM
                            COMMENT "Generating binary with debug information"
                            COMMAND ${OBJCOPY} $<TARGET_FILE:${PROJECT_NAME}>
                            ARGS --add-gnu-debuglink=$<TARGET_FILE:${PROJECT_NAME}>.dSYM
                            COMMENT "Link binary file with debug information"
                            COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${PROJECT_NAME}>
                            COMMENT "Strip debug information from ${PROJECT_NAME}"
                            VERBATIM)
    endif(OBJCOPY)
endif()

target_link_libraries(${PROJECT_NAME}
    grafit-system
    grafit-graphics
    grafit-window
)
