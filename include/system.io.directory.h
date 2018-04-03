#ifndef SYSTEM_IO_DIRECTORY_H
#define SYSTEM_IO_DIRECTORY_H

#include <string>
#include <vector>

namespace System
{
namespace IO
{

class Directory
{
public:
    // Creates all directories and subdirectories in the specified path unless they already exist.
    static bool CreateDirectoryFromPath(std::string const &path);

    // Determines whether the given path refers to an existing directory on disk.
    static bool Exists(std::string const &path);

    // Gets the current working directory of the application.
    static std::string GetCurrentWorkingDirectory();

    // Returns the names of subdirectories (including their paths) in the specified directory.
    static std::vector<std::string> GetDirectories(std::string const &path);

    // Returns the names of subdirectories (including their paths) that match the specified search pattern in the specified directory.
    static std::vector<std::string> GetDirectories(std::string const &path, std::string const &searchPattern);

    // Returns the names of files (including their paths) in the specified directory.
    static std::vector<std::string> GetFiles(std::string const &path);

    // Returns the names of files (including their paths) that match the specified search pattern in the specified directory.
    static std::vector<std::string> GetFiles(std::string const &path, std::string const &searchPattern);

};

} // namespace IO
} // namespace System

#endif // SYSTEM_IO_DIRECTORY_H

#ifdef SYSTEM_IO_DIRECTORY_IMPLEMENTATION

#ifndef _SYSTEM_IO_DIRECTORY_IMPLEMENTED_
#define _SYSTEM_IO_DIRECTORY_IMPLEMENTED_

using namespace System::IO;

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#endif

bool Directory::CreateDirectoryFromPath(std::string const &path)
{
    mkdir(path.c_str());

    return true;
}

bool Directory::Exists(std::string const &path)
{
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES)
    {
        return false;  //something is wrong with your path!
    }

    if (attr & FILE_ATTRIBUTE_DIRECTORY)
    {
        return true;   // this is a directory!
    }
#endif // _WIN32

    return false;    // this is not a directory!
}

// Gets the current working directory of the application.
std::string Directory::GetCurrentWorkingDirectory()
{
    std::string result;

#ifdef _WIN32
    TCHAR NPath[MAX_PATH];

    GetCurrentDirectory(MAX_PATH, NPath);

    result = std::string(NPath);
#endif // _WIN32

    return result;
}

// Returns the names of subdirectories (including their paths) in the specified directory.
std::vector<std::string> Directory::GetDirectories(std::string const &path)
{
    return Directory::GetDirectories(path, "*");
}

// Returns the names of files (including their paths) that match the specified search pattern in the specified directory.
std::vector<std::string> Directory::GetDirectories(std::string const &path, std::string const &searchPattern)
{
    std::vector<std::string> files;

#ifdef _WIN32
    HANDLE hFind;
    WIN32_FIND_DATA data;

    hFind = FindFirstFile(Path::Combine(path, searchPattern).c_str(), &data);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (data.cFileName[0] == '.' && data.cFileName[1] == '\0') continue;
            if (data.cFileName[0] == '.' && data.cFileName[1] == '.') continue;

            if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                files.push_back(Path::Combine(path, data.cFileName));
            }
        }
        while (FindNextFile(hFind, &data));
        FindClose(hFind);
    }
#endif // _WIN32

    return files;
}

// Returns the names of files (including their paths) in the specified directory.
std::vector<std::string> Directory::GetFiles(std::string const &path)
{
    return Directory::GetFiles(path, "*");
}

// Returns the names of files (including their paths) that match the specified search pattern in the specified directory.
std::vector<std::string> Directory::GetFiles(std::string const &path, std::string const &searchPattern)
{
    std::vector<std::string> files;

#ifdef _WIN32
    HANDLE hFind;
    WIN32_FIND_DATA data;

    auto tmp = Path::Combine(path, searchPattern);
    hFind = FindFirstFile(tmp.c_str(), &data);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                files.push_back(Path::Combine(path, data.cFileName));
            }
        }
        while (FindNextFile(hFind, &data));
        FindClose(hFind);
    }
#endif // _WIN32

    return files;
}

#endif // _SYSTEM_IO_DIRECTORY_IMPLEMENTED_
#endif // SYSTEM_IO_DIRECTORY_IMPLEMENTATION
