#ifndef _SYSTEM_IO_DIRECTORYINFO_H_
#define _SYSTEM_IO_DIRECTORYINFO_H_

#include <string>
#include <vector>
#include "system.io.filesysteminfo.h"

namespace System
{
namespace IO
{

class DirectoryInfo : public FileSystemInfo
{
    std::string _name;
    void Init(const std::string& path);
public:
    DirectoryInfo(const std::string& path);
    virtual ~DirectoryInfo();

    DirectoryInfo Parent() const;
    std::string Name() const;
    virtual bool Exists() const;
    void Create() const;

    std::vector<std::string> GetDirectories() const;
    std::vector<std::string> GetDirectories(const std::string& searchPattern) const;
    std::vector<std::string> GetFiles() const;
    std::vector<std::string> GetFiles(const std::string& searchPattern) const;
};

} // namespace IO
} // namespace System

#endif // _SYSTEM_IO_DIRECTORYINFO_H_

#ifdef SYSTEM_IO_DIRECTORYINFO_IMPLEMENTATION

#ifndef _SYSTEM_IO_DIRECTORYINFO_IMPLEMENTED_
#define _SYSTEM_IO_DIRECTORYINFO_IMPLEMENTED_

#define SYSTEM_IO_PATH_IMPLEMENTATION
#include "system.io.path.h"

#define SYSTEM_IO_FILESYSTEMINFO_IMPLEMENTATION
#include "system.io.filesysteminfo.h"

using namespace System::IO;

DirectoryInfo::DirectoryInfo(const std::string& path)
    : FileSystemInfo()
{
    this->Init(path);
}

DirectoryInfo::~DirectoryInfo()
{ }

void DirectoryInfo::Init(const std::string& path)
{
    this->_originalPath = path;
    this->_fullPath = Path::GetFullPath(path);
}

DirectoryInfo DirectoryInfo::Parent() const
{
    return DirectoryInfo(Path::GetDirectoryName(this->_fullPath));
}

std::string DirectoryInfo::Name() const
{
    return Path::GetFileName(this->_fullPath);
}

bool DirectoryInfo::Exists() const
{
    DWORD attr = GetFileAttributesA(this->FullName().c_str());
    if (attr == INVALID_FILE_ATTRIBUTES)
        return false;  //something is wrong with your path!

    if (attr & FILE_ATTRIBUTE_DIRECTORY)
        return true;   // this is a directory!

    return false;    // this is not a directory!
}

std::vector<std::string> DirectoryInfo::GetDirectories() const
{
    return this->GetDirectories("*");
}

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#endif

void DirectoryInfo::Create() const
{
    // todo
    // mkdir(this->FullName().c_str());
}

std::vector<std::string> DirectoryInfo::GetDirectories(const std::string& searchPattern) const
{
    std::vector<std::string> files;

#ifdef _WIN32
    HANDLE hFind;
    WIN32_FIND_DATA data;

    hFind = FindFirstFile(Path::Combine(this->FullName(), searchPattern).c_str(), &data);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (data.cFileName[0] == '.' && data.cFileName[1] == '\0') continue;
            if (data.cFileName[0] == '.' && data.cFileName[1] == '.') continue;

            if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                auto dir = DirectoryInfo(Path::Combine(this->FullName(), data.cFileName));
                files.push_back(dir.FullName());
            }
        }
        while (FindNextFile(hFind, &data));
        FindClose(hFind);
    }
#endif

    return files;
}

std::vector<std::string> DirectoryInfo::GetFiles() const
{
    return this->GetFiles("*");
}

std::vector<std::string> DirectoryInfo::GetFiles(const std::string& searchPattern) const
{
    std::vector<std::string> files;

#ifdef _WIN32
    HANDLE hFind;
    WIN32_FIND_DATA data;

    auto tmp = Path::Combine(this->FullName(), searchPattern);
    hFind = FindFirstFile(tmp.c_str(), &data);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                auto file = DirectoryInfo(Path::Combine(this->FullName(), data.cFileName));
                files.push_back(file.FullName());
            }
        }
        while (FindNextFile(hFind, &data));
        FindClose(hFind);
    }
#endif

    return files;
}

#endif // _SYSTEM_IO_DIRECTORYINFO_IMPLEMENTED_
#endif // SYSTEM_IO_DIRECTORYINFO_IMPLEMENTATION
