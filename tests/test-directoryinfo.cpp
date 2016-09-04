
#include "../src/catch.hpp"

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

    SECTION("GetFiles()")
    {
        REQUIRE(dir.GetFiles().size() == 0);
    }

    SECTION("GetFiles() in windows folder")
    {
        dir = DirectoryInfo("C:\\Windows");
        REQUIRE(dir.GetFiles().size() > 0);
        REQUIRE(dir.FullName() == dir.GetFiles()[0].substr(0, dir.FullName().size()));
    }

    SECTION("GetFiles() exe files in windows folder")
    {
        dir = DirectoryInfo("C:\\Windows");
        REQUIRE(dir.GetFiles("*.exe").size() > 0);
        REQUIRE(dir.FullName() == dir.GetFiles("*.exe")[0].substr(0, dir.FullName().size()));
    }

    SECTION("GetDirectories() in windows folder")
    {
        dir = DirectoryInfo("C:\\Windows");
        REQUIRE(dir.GetDirectories().size() > 0);
        REQUIRE(dir.FullName() == dir.GetDirectories()[0].substr(0, dir.FullName().size()));
    }
}
