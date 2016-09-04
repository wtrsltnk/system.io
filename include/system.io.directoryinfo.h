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

    DirectoryInfo Parent();
    std::string Name();

    std::vector<std::string> GetFiles();
    std::vector<std::string> GetFiles(const std::string& searchPattern);
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

DirectoryInfo DirectoryInfo::Parent()
{
    return DirectoryInfo(Path::GetDirectoryName(this->_fullPath));
}

std::string DirectoryInfo::Name()
{
    return Path::GetFileName(this->_fullPath);
}

std::vector<std::string> DirectoryInfo::GetFiles()
{
    std::vector<std::string> files;
    return files;
}

std::vector<std::string> DirectoryInfo::GetFiles(const std::string& searchPattern)
{
    std::vector<std::string> files;
    return files;
}

#endif // _SYSTEM_IO_DIRECTORYINFO_IMPLEMENTED_
#endif // SYSTEM_IO_DIRECTORYINFO_IMPLEMENTATION
