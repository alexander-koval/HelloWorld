set(INCROOT ${PROJECT_SOURCE_DIR}/include/icebird/System)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/icebird/System)

file(GLOB icebird_system_source_files
    ${INCROOT}/Math/Vector2.hpp
    ${SRCROOT}/Math/Vector2.cpp
)

source_group("" FILES ${icebird_system_source_files})

add_library(icebird-system STATIC ${icebird_system_source_files})
