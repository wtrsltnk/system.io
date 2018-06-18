
if(BUILD_TESTS)
    add_executable(system.io.tests
        catch.cpp
        test-directoryinfo.cpp
        test-fileinfo.cpp
        test-path.cpp
        test-directory.cpp
        )

    target_link_libraries(system.io.tests
        system.xml
        )

    target_compile_features(system.io.tests
        PRIVATE cxx_auto_type
        PRIVATE cxx_nullptr
        )
endif(BUILD_TESTS)
