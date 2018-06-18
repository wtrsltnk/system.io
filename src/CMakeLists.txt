
add_library(system.io
    Directory.cpp
    DirectoryInfo.cpp
    File.cpp
    FileInfo.cpp
    FileSystemInfo.cpp
    Path.cpp
    )

target_include_directories(system.io
    PUBLIC
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ../include
    )

target_compile_features(system.io
    PRIVATE
        cxx_auto_type
        cxx_nullptr
        cxx_range_for
    )

install(
    TARGETS
        system.io
    EXPORT
        system.io
    DESTINATION
        "lib"
    )

install(
    FILES
        ${system.io_SOURCE_DIR}/include/system.io/Directory.h
        ${system.io_SOURCE_DIR}/include/system.io/DirectoryInfo.h
        ${system.io_SOURCE_DIR}/include/system.io/File.h
        ${system.io_SOURCE_DIR}/include/system.io/FileInfo.h
        ${system.io_SOURCE_DIR}/include/system.io/FileSystemInfo.h
        ${system.io_SOURCE_DIR}/include/system.io/Path.h
    DESTINATION
        "include/system.io"
    )

install(
    EXPORT
        system.io
    FILE
        system.io-config.cmake
    DESTINATION
        "cmake"
    )
