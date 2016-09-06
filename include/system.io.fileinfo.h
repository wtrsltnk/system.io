#ifndef _SYSTEM_IO_FILEINFO_H_
#define _SYSTEM_IO_FILEINFO_H_

#include <string>
#include "system.io.filesysteminfo.h"
#include "system.io.directoryinfo.h"

namespace System
{
namespace IO
{

class FileInfo : public FileSystemInfo
{
    std::string _name;
    void Init(const std::string& path);
public:
    FileInfo(const std::string& path);
    virtual ~FileInfo();

    std::string Name() const;
    DirectoryInfo Directory() const;

};

} // namespace IO
} // namespace System

#endif // _SYSTEM_IO_FILEINFO_H_

#ifdef SYSTEM_IO_FILEINFO_IMPLEMENTATION

#ifndef _SYSTEM_IO_FILEINFO_IMPLEMENTED_
#define _SYSTEM_IO_FILEINFO_IMPLEMENTED_

#define SYSTEM_IO_PATH_IMPLEMENTATION
#include "system.io.path.h"

#define SYSTEM_IO_FILESYSTEMINFO_IMPLEMENTATION
#include "system.io.filesysteminfo.h"

#define SYSTEM_IO_DIRECTORYINFO_IMPLEMENTATION
#include "system.io.directoryinfo.h"

using namespace System::IO;

FileInfo::FileInfo(const std::string& path)
{
    this->Init(path);
}

FileInfo::~FileInfo()
{ }

void FileInfo::Init(const std::string& path)
{
    this->_originalPath = path;
    this->_fullPath = Path::GetFullPath(path);
    this->_name = Path::GetFileName(this->_fullPath);
}

std::string FileInfo::Name() const
{
    return this->_name;
}

DirectoryInfo FileInfo::Directory() const
{
    return DirectoryInfo(Path::GetDirectoryName(this->_fullPath));
}

#endif // _SYSTEM_IO_FILEINFO_IMPLEMENTED_
#endif // SYSTEM_IO_FILEINFO_IMPLEMENTATION
