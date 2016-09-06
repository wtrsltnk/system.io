#ifndef _SYSTEM_IO_FILESYSTEMINFO_H_
#define _SYSTEM_IO_FILESYSTEMINFO_H_

#include <string>

namespace System
{
namespace IO
{

class FileSystemInfo
{
protected:
    std::string _originalPath;
    std::string _fullPath;

    FileSystemInfo();
public:
    virtual ~FileSystemInfo();

    virtual std::string Name() const = 0;
    virtual std::string FullName() const;
    virtual std::string Extension() const;
    bool Exists() const;

};

} // namespace IO
} // namespace System

#endif // _SYSTEM_IO_FILESYSTEMINFO_H_

#ifdef SYSTEM_IO_FILESYSTEMINFO_IMPLEMENTATION

#ifndef _SYSTEM_IO_FILESYSTEMINFO_IMPLEMENTED_
#define _SYSTEM_IO_FILESYSTEMINFO_IMPLEMENTED_

#define SYSTEM_IO_PATH_IMPLEMENTATION
#include "system.io.path.h"

using namespace System::IO;

FileSystemInfo::FileSystemInfo()
{ }

FileSystemInfo::~FileSystemInfo()
{ }

std::string FileSystemInfo::FullName() const
{
    return this->_fullPath;
}

std::string FileSystemInfo::Extension() const
{
    auto i = this->_fullPath.length();
    while (--i > 0)
    {
        if (this->_fullPath[i] == Path::DirectorySeparatorChar) return "";
        if (this->_fullPath[i] == Path::AltDirectorySeparatorChar) return "";
        if (this->_fullPath[i] == '.') return this->_fullPath.substr(i);
    }
    return "";
}

#ifdef _WIN32
#include <windows.h>
#endif

bool FileSystemInfo::Exists() const
{
#ifdef _WIN32
    WIN32_FIND_DATA FindFileData;
    HANDLE handle = FindFirstFile(this->_fullPath.c_str(), &FindFileData);
    if (handle != INVALID_HANDLE_VALUE)
    {
        FindClose(handle);
        return true;
    }
#endif

    return false;
}

#endif // _SYSTEM_IO_FILESYSTEMINFO_IMPLEMENTED_
#endif // SYSTEM_IO_FILESYSTEMINFO_IMPLEMENTATION
