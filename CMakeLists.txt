cmake_minimum_required(VERSION 3.16)
project(msvc_cli C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cli
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hw
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hw/driver
)

file(GLOB_RECURSE SOURCES
    "src/*.c"
)

add_executable(msvc_cli ${SOURCES})

target_link_libraries(msvc_cli PRIVATE Kernel32 Winmm)

target_compile_options(msvc_cli PRIVATE
    "/utf-8"
)