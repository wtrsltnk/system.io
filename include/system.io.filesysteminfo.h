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

    virtual std::string Name() = 0;
    virtual std::string FullName();
    virtual std::string Extension();

};

} // namespace IO
} // namespace System

#endif // _SYSTEM_IO_FILESYSTEMINFO_H_

#ifdef SYSTEM_IO_FILESYSTEMINFO_IMPLEMENTATION

using namespace System::IO;

FileSystemInfo::FileSystemInfo()
{ }

FileSystemInfo::~FileSystemInfo()
{ }

std::string FileSystemInfo::FullName()
{
    return this->_fullPath;
}

std::string FileSystemInfo::Extension()
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

#endif // SYSTEM_IO_FILESYSTEMINFO_IMPLEMENTATION
