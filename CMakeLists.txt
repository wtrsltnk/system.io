cmake_minimum_required(VERSION 3.3)

project(system.io)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_definitions(-DWORKING_DIR="${CMAKE_BINARY_DIR}")

add_executable(system.io.tests
    tests/test-directoryinfo.cpp
    tests/test-fileinfo.cpp
    tests/test-path.cpp
    tests/test-directory.cpp
    src/catch.cpp
    src/system.io.cpp
    )

# This is needed for test-directory.cpp
target_compile_definitions(system.io.tests
    PRIVATE TEST_WORKING_DIRECTORY="${CMAKE_CURRENT_BINARY_DIR}"
    )

target_include_directories(system.io.tests
    PRIVATE include
    )

add_test(
    NAME
        system.io.tests
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND
        system.io.tests
    )

include(CTest)
