
#include "../src/catch.hpp"

#include "system.io.fileinfo.h"
#include "system.io.path.h"

using namespace System::IO;

TEST_CASE("FileInfo")
{
    auto file = FileInfo("c:\\temp\\subdir\\myfile.ext");
    SECTION("Fullname()")
    {
        REQUIRE(file.FullName() == "c:\\temp\\subdir\\myfile.ext");
    }
    SECTION("Directory()")
    {
        auto directory = file.Directory();
        REQUIRE(directory.FullName() == "c:\\temp\\subdir");
    }
    SECTION("Extention()")
    {
        REQUIRE(file.Extension() == ".ext");
    }
    SECTION("Name()")
    {
        REQUIRE(file.Name() == "myfile.ext");
    }
    SECTION("FullName()")
    {
        REQUIRE(file.FullName() == "c:\\temp\\subdir\\myfile.ext");
    }

    SECTION("FullName() with .. and . in the path")
    {
        file = FileInfo("c:\\temp\\..\\subdir\\.\\myfile.ext");
        REQUIRE(file.FullName() == "c:\\subdir\\myfile.ext");
    }

    SECTION("FullName() with alternative directory seperators")
    {
        file = FileInfo("c:\\temp/subdir\\myfile.ext");
        REQUIRE(file.FullName() == "c:\\temp\\subdir\\myfile.ext");
    }

    SECTION("Example from readme")
    {
        file = FileInfo(Path::Combine("c:\\temp", "subdir\\myfile.ext"));
        REQUIRE(file.FullName() == "c:\\temp\\subdir\\myfile.ext");
    }
}
