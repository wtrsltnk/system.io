cmake_minimum_required(VERSION 3.3)

project(system.io)
enable_testing()

set(TESTFILES
    tests/test-directoryinfo.cpp
    tests/test-fileinfo.cpp
    tests/test-path.cpp
    )

set(HEADERS
    include/system.io.directoryinfo.h
    include/system.io.fileinfo.h
    include/system.io.filesysteminfo.h
    include/system.io.path.h
    include/catch.hpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_definitions(-DWORKING_DIR="${CMAKE_BINARY_DIR}")

include_directories(include)

foreach(file ${TESTFILES})
    get_filename_component(filename ${file} NAME FALSE)
    string(REGEX REPLACE ".cpp\$" "" test "${filename}")
    add_executable(${test} 
        ${file} 
        ${HEADERS} 
        src/catch.cpp
        src/system.io.cpp
        )
    add_test(
        NAME
            ${test}
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND
            ${test}
        )
endforeach()

include(CTest)
