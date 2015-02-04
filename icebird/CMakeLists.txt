project(icebird)
cmake_minimum_required(VERSION 2.8)

set(ICEBIRD_VERSION_MAJOR 0)
set(ICEBIRD_VERSION_MINOR 1)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/")

function(add_resources output)
    set(result)
    foreach(INPUT_FILE ${ARGN})
        file(RELATIVE_PATH SOURCE_FILE ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE})
        set(OUTPUT_FILE "${PROJECT_BINARY_DIR}/${INPUT_FILE}.o")
#        message("SHADER: " ${SOURCE_FILE})
        add_custom_command(OUTPUT ${OUTPUT_FILE}
            COMMAND ld -r -b binary -o ${OUTPUT_FILE} ${SOURCE_FILE}
            DEPENDS ${INPUT_FILE}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Embedding resource file ${OUTPUT_FILE}"
            VERBATIM
        )
        list(APPEND result ${OUTPUT_FILE})
    endforeach()
    set(${output} "${result}" PARENT_SCOPE)
endfunction()

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

add_subdirectory(src/icebird)
add_subdirectory(projects/glfw)
add_subdirectory(projects/SOIL)
