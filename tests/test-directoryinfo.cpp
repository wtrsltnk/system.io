
#include "catch.hpp"

#include "system.io.directoryinfo.h"

using namespace System::IO;

TEST_CASE("DirectoryInfo")
{
    auto dir = DirectoryInfo("c:\\temp\\subdir\\");
    SECTION("Fullname()")
    {
        REQUIRE(dir.FullName() == "c:\\temp\\subdir");
    }
    SECTION("Parent()")
    {
        auto parent = dir.Parent();
        REQUIRE(parent.FullName() == "c:\\temp");
    }
    SECTION("Name()")
    {
        REQUIRE(dir.Name() == "subdir");
    }
}
