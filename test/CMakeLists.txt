
if(BUILD_TESTS)
    add_executable(system.io.tests
        catch.cpp
        test-directoryinfo.cpp
        test-fileinfo.cpp
        test-path.cpp
        test-directory.cpp
        )

    target_include_directories(system.io.tests
        PUBLIC
            $<INSTALL_INTERFACE:include>
        PRIVATE
            ../include
        )

    target_compile_definitions(system.io.tests
        PRIVATE
            TEST_WORKING_DIRECTORY="${CMAKE_BINARY_DIR}"
        )

    target_link_libraries(system.io.tests
        system.io
        )

    target_compile_features(system.io.tests
        PRIVATE cxx_auto_type
        PRIVATE cxx_nullptr
        )
endif(BUILD_TESTS)
