cmake_minimum_required(VERSION 3.3)

project(system.io)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_library(system.io
    src/Directory.cpp
    src/DirectoryInfo.cpp
    src/File.cpp
    src/FileInfo.cpp
    src/FileSystemInfo.cpp
    src/Path.cpp
    )

target_include_directories(system.io
    PUBLIC include
    )

add_executable(system.io.tests
    tests/test-directoryinfo.cpp
    tests/test-fileinfo.cpp
    tests/test-path.cpp
    tests/test-directory.cpp
    src/catch.cpp
    )

# This is needed for test-directory.cpp
target_compile_definitions(system.io.tests
    PRIVATE TEST_WORKING_DIRECTORY="${CMAKE_CURRENT_BINARY_DIR}"
    )

target_link_libraries(system.io.tests
    system.io
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
