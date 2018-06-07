#include <system.io.directory.h>
#include <system.io.file.h>
#include <system.io.path.h>

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#endif

using namespace System::IO;

bool Directory::CreateDirectoryFromPath(std::string const &path)
{
    mkdir(path.c_str());

    return true;
}

// Deletes an empty directory from a specified path.
void Directory::Delete(std::string const &path)
{
#ifdef _WIN32
    RemoveDirectory(path.c_str());
#endif // _WIN32
}

// Deletes the specified directory and, if indicated, any subdirectories and files in the directory.
void Directory::Delete(std::string const &path, bool recursive)
{
#ifdef _WIN32
    if (recursive)
    {
        auto files = Directory::GetFiles(path);
        for (auto file : files)
        {
            File::Delete(file);
        }
        auto subDirectories = Directory::GetDirectories(path);
        for (auto subDirectory : subDirectories)
        {
            Directory::Delete(subDirectory);
        }
    }
    RemoveDirectory(path.c_str());
#endif // _WIN32
}

bool Directory::Exists(std::string const &path)
{
#ifdef _WIN32
    DWORD attr = GetFileAttributes(path.c_str());
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
