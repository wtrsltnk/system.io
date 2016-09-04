#ifndef _SYSTEM_IO_DIRECTORYINFO_H_
#define _SYSTEM_IO_DIRECTORYINFO_H_

#include <string>
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

    DirectoryInfo Parent();
    std::string Name();

    bool Exists();
};

} // namespace IO
} // namespace System

#endif // _SYSTEM_IO_DIRECTORYINFO_H_

#ifdef SYSTEM_IO_DIRECTORYINFO_IMPLEMENTATION

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

DirectoryInfo DirectoryInfo::Parent()
{
    return DirectoryInfo(Path::GetDirectoryName(this->_fullPath));
}

std::string DirectoryInfo::Name()
{
    return Path::GetFileName(this->_fullPath);
}

#endif // SYSTEM_IO_DIRECTORYINFO_IMPLEMENTATION
