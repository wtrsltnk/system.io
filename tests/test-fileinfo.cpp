
#include "../src/catch.hpp"

#include "system.io.fileinfo.h"
#include "system.io.path.h"

using namespace System::IO;

TEST_CASE("FileInfo")
{
    SECTION("Fullname()")
    {
        auto file = FileInfo("c:\\temp\\subdir\\myfile.ext");
        REQUIRE(file.FullName() == "c:\\temp\\subdir\\myfile.ext");
    }
    SECTION("Extention()")
    {
        auto file = FileInfo("c:\\temp\\subdir\\myfile.ext");
        REQUIRE(file.Extension() == ".ext");
    }
    SECTION("Name()")
    {
        auto file = FileInfo("c:\\temp\\subdir\\myfile.ext");
        REQUIRE(file.Name() == "myfile.ext");
    }
    SECTION("FullName()")
    {
        auto file = FileInfo("c:\\temp\\subdir\\myfile.ext");
        REQUIRE(file.FullName() == "c:\\temp\\subdir\\myfile.ext");
    }
}

TEST_CASE("FileInfo - Examples from readme")
{
    SECTION("Example #1")
    {
        auto file = FileInfo(Path::Combine("c:\\temp", "subdir\\myfile.ext"));
        REQUIRE(file.FullName() == "c:\\temp\\subdir\\myfile.ext");
    }

    SECTION("Example #2")
    {
        auto file = FileInfo("c:\\temp\\..\\subdir\\.\\myfile.ext");
        REQUIRE(file.FullName() == "c:\\subdir\\myfile.ext");
    }

    SECTION("Example #3")
    {
        auto file = FileInfo("c:\\temp/subdir\\myfile.ext");
        REQUIRE(file.FullName() == "c:\\temp\\subdir\\myfile.ext");
    }

    SECTION("Example #4")
    {
        auto file = FileInfo("c:\\temp\\subdir\\myfile.ext");
        auto directory = file.Directory();
        REQUIRE(directory.FullName() == "c:\\temp\\subdir");
    }
}
