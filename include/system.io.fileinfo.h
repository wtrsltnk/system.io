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

    std::string Name();
    DirectoryInfo Directory();

};

} // namespace IO
} // namespace System

#endif // _SYSTEM_IO_FILEINFO_H_

#ifdef SYSTEM_IO_FILEINFO_IMPLEMENTATION

#include "system.io.path.h"

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

std::string FileInfo::Name()
{
    return this->_name;
}

DirectoryInfo FileInfo::Directory()
{
    return DirectoryInfo(Path::GetDirectoryName(this->_fullPath));
}

#endif // SYSTEM_IO_FILEINFO_IMPLEMENTATION
