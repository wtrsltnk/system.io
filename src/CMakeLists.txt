
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
        ${system.io_SOURCE_DIR}/include/system.io/system.io.directory.h
        ${system.io_SOURCE_DIR}/include/system.io/system.io.directoryinfo.h
        ${system.io_SOURCE_DIR}/include/system.io/system.io.file.h
        ${system.io_SOURCE_DIR}/include/system.io/system.io.fileinfo.h
        ${system.io_SOURCE_DIR}/include/system.io/system.io.filesysteminfo.h
        ${system.io_SOURCE_DIR}/include/system.io/system.io.path.h
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
