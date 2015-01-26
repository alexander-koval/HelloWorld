project(icebird)
cmake_minimum_required(VERSION 2.8)

set(ICEBIRD_VERSION_MAJOR 0)
set(ICEBIRD_VERSION_MINOR 1)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/")

add_subdirectory(src/icebird)
