#include "../src/catch.hpp"

#include <Directory.h>
#include <DirectoryInfo.h>
#include <Path.h>

using namespace System::IO;

TEST_CASE("Directory::GetCurrentWorkingDirectory()")
{
    REQUIRE(Directory::GetCurrentWorkingDirectory() == DirectoryInfo(TEST_WORKING_DIRECTORY).FullName());
}

TEST_CASE("Directory::Exists()")
{
    auto tempFolder = Path::Combine(DirectoryInfo(TEST_WORKING_DIRECTORY).FullName(), "tempFolder");

    Directory::Delete(tempFolder);

    REQUIRE(Directory::Exists(tempFolder) == false);

    Directory::CreateDirectoryFromPath(tempFolder);

    REQUIRE(Directory::Exists(tempFolder) == true);

    Directory::Delete(tempFolder);

    REQUIRE(Directory::Exists(tempFolder) == false);
}