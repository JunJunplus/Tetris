cmake_minimum_required(VERSION 3.12.2)

set (CMAKE_C_COMPILER "/usr/local/arm/5.4.0/bin/arm-linux-gcc")

project(main)

include_directories(./inc)

link_directories(./lib)

aux_source_directory(./src s)

add_executable(main ${s})

target_link_libraries(main pthread font m)