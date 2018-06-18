cmake_minimum_required(VERSION 3.7)

project(system.io)

option(BUILD_TESTS "Build test programs" OFF)

add_subdirectory(src)
add_subdirectory(test)
