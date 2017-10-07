
#include "../src/catch.hpp"

#include "system.io.path.h"

#include <string>

using namespace System::IO;

// Test cases from .NET documentation @
// https://msdn.microsoft.com/en-us/library/system.io.path.combine(v=vs.110).aspx
// https://msdn.microsoft.com/en-us/library/fyy7a5kt(v=vs.110).aspx
TEST_CASE("Path::Combine(const std::string& path1, const std::string& path2)")
{
    SECTION("drive and folder + relative file")
    {
        REQUIRE(Path::Combine("c:\\temp", "subdir\\file.txt") == "c:\\temp\\subdir\\file.txt");
    }

    SECTION("drive and folder + drive and file")
    {
        REQUIRE(Path::Combine("c:\\temp", "c:\\temp.txt") == "c:\\temp.txt");
    }

    SECTION("drive and file + relative file")
    {
        REQUIRE(Path::Combine("c:\\temp.txt", "subdir\\file.txt") == "c:\\temp.txt\\subdir\\file.txt");
    }

    SECTION("special characters")
    {
        REQUIRE(Path::Combine("c:^*&)(_=@#'\\^&#2.*(.txt", "subdir\\file.txt") == "c:^*&)(_=@#'\\^&#2.*(.txt\\subdir\\file.txt");
    }

    SECTION("empty string + relative file")
    {
        REQUIRE(Path::Combine("", "subdir\\file.txt") == "subdir\\file.txt");
    }
}

// Test cases from .NET documentation @
// https://msdn.microsoft.com/en-us/library/system.io.path.getdirectoryname(v=vs.110).aspx
TEST_CASE("Path::GetDirectoryName(const std::string& path)")
{
    SECTION("with filename")
    {
        REQUIRE(Path::GetDirectoryName("C:\\MyDir\\MySubDir\\myfile.ext") == "C:\\MyDir\\MySubDir");
    }

    SECTION("with foldername")
    {
        REQUIRE(Path::GetDirectoryName("C:\\MyDir\\MySubDir") == "C:\\MyDir");
    }

    SECTION("ending with seperator")
    {
        REQUIRE(Path::GetDirectoryName("C:\\MyDir\\") == "C:\\MyDir");
    }

    SECTION("with foldername")
    {
        REQUIRE(Path::GetDirectoryName("C:\\MyDir") == "C:\\");
    }

    SECTION("only disk path")
    {
        REQUIRE(Path::GetDirectoryName("C:\\") == "");
    }
}

// Test cases from .NET documentation @
// https://msdn.microsoft.com/en-us/library/system.io.path.getextension(v=vs.110).aspx
TEST_CASE("Path::GetExtension(const std::string& path)")
{
    SECTION("with filename and extension")
    {
        REQUIRE(Path::GetExtension("C:\\mydir.old\\myfile.ext") == ".ext");
    }

    SECTION("without filename and extension")
    {
        REQUIRE(Path::GetExtension("C:\\mydir.old\\") == "");
    }
}

// Test cases from .NET documentation @
// https://msdn.microsoft.com/en-us/library/system.io.path.getfilename(v=vs.110).aspx
TEST_CASE("Path::GetFileName(const std::string& path)")
{
    SECTION("with filename and extension")
    {
        REQUIRE(Path::GetFileName("C:\\mydir.old\\myfile.ext") == "myfile.ext");
    }

    SECTION("without filename and extension")
    {
        REQUIRE(Path::GetFileName("C:\\mydir.old\\") == "");
    }
}

// Test cases from .NET documentation @
// https://msdn.microsoft.com/en-us/library/system.io.path.getfilenamewithoutextension(v=vs.110).aspx
TEST_CASE("Path::GetFileNameWithoutExtension(const std::string& path)")
{
    SECTION("with filename and extension")
    {
        REQUIRE(Path::GetFileNameWithoutExtension("C:\\mydir.old\\myfile.ext") == "myfile");
    }

    SECTION("without filename and extension")
    {
        REQUIRE(Path::GetFileNameWithoutExtension("C:\\mydir.old\\") == "");
    }
}

// Test cases from .NET documentation @
// https://msdn.microsoft.com/en-us/library/system.io.path.getfullpath(v=vs.110).aspx
TEST_CASE("Path::GetFullPath(const std::string& path)")
{
    auto cwd = std::string(WORKING_DIR);
    std::replace(cwd.begin(), cwd.end(), Path::AltDirectorySeparatorChar, Path::DirectorySeparatorChar);
    auto root = cwd.substr(0, 3);

    SECTION("with directory")
    {
        REQUIRE(Path::GetFullPath("mydir") == cwd + "\\mydir");
    }

    SECTION("with file")
    {
        REQUIRE(Path::GetFullPath("myfile.ext") == cwd + "\\myfile.ext");
    }

    SECTION("with rooted directory")
    {
        REQUIRE(Path::GetFullPath("\\mydir") == root + "mydir");
    }

    SECTION("with drive")
    {
        REQUIRE(Path::GetFullPath("c:\\mydir") == "c:\\mydir");
    }
}

// Test cases from .NET documentation @
// https://msdn.microsoft.com/en-us/library/system.io.path.ispathrooted(v=vs.110).aspx
TEST_CASE("Path::IsPathRooted(const std::string& path)")
{
    SECTION("with drive")
    {
        REQUIRE(Path::IsPathRooted("C:\\mydir\\myfile.ext") == true);
    }

    SECTION("with network root")
    {
        REQUIRE(Path::IsPathRooted("\\\\myPc\\mydir\\mypath") == true);
    }

    SECTION("relative path")
    {
        REQUIRE(Path::IsPathRooted("mydir\\subdir\\") == false);
    }
}

// Test cases from .NET documentation @
// https://msdn.microsoft.com/en-us/library/system.io.path.getpathroot(v=vs.110).aspx
TEST_CASE("Path::GetPathRoot(const std::string& path)")
{
    SECTION("root character")
    {
        REQUIRE(Path::GetPathRoot("\\mydir\\") == "\\");
    }

    SECTION("no root")
    {
        REQUIRE(Path::GetPathRoot("myfile.ext") == "");
    }

    SECTION("drive")
    {
        REQUIRE(Path::GetPathRoot("C:\\mydir\\myfile.ext") == "C:\\");
    }
}
