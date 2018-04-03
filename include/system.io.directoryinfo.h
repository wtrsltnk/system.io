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
    void Init(std::string const &path);
public:
    DirectoryInfo(std::string const &path);
    virtual ~DirectoryInfo();

    DirectoryInfo Parent() const;
    DirectoryInfo Root() const;
    std::string Name() const;
    virtual bool Exists() const;
    void Create() const;

    std::vector<std::string> GetDirectories() const;
    std::vector<std::string> GetDirectories(std::string const &searchPattern) const;
    std::vector<std::string> GetFiles() const;
    std::vector<std::string> GetFiles(std::string const &searchPattern) const;

    bool operator == (const DirectoryInfo& other) const;
};

} // namespace IO
} // namespace System

#endif // _SYSTEM_IO_DIRECTORYINFO_H_

#ifdef SYSTEM_IO_DIRECTORYINFO_IMPLEMENTATION

#ifndef _SYSTEM_IO_DIRECTORYINFO_IMPLEMENTED_
#define _SYSTEM_IO_DIRECTORYINFO_IMPLEMENTED_

#include "system.io.directory.h"
#include "system.io.path.h"
#include "system.io.filesysteminfo.h"

using namespace System::IO;

DirectoryInfo::DirectoryInfo(std::string const &path)
    : FileSystemInfo()
{
    this->Init(path);
}

DirectoryInfo::~DirectoryInfo()
{ }

bool DirectoryInfo::operator == (const DirectoryInfo& other) const
{
    return FullName() == other.FullName();
}

void DirectoryInfo::Init(std::string const &path)
{
    this->_originalPath = path;
    this->_fullPath = Path::GetFullPath(path);
}

DirectoryInfo DirectoryInfo::Parent() const
{
    return DirectoryInfo(Path::GetDirectoryName(this->_fullPath));
}

DirectoryInfo DirectoryInfo::Root() const
{
    return DirectoryInfo(Path::GetPathRoot(this->_fullPath));
}

std::string DirectoryInfo::Name() const
{
    return Path::GetFileName(this->_fullPath);
}

bool DirectoryInfo::Exists() const
{
    return Directory::Exists(this->FullName());
}

std::vector<std::string> DirectoryInfo::GetDirectories() const
{
    return this->GetDirectories("*");
}

void DirectoryInfo::Create() const
{
    // Don't make if this is the root
    if (*this == Root())
    {
        return;
    }

    if (!Parent().Exists())
    {
        Parent().Create();
    }

    Directory::CreateDirectoryFromPath(this->FullName());
}

std::vector<std::string> DirectoryInfo::GetDirectories(std::string const &searchPattern) const
{
    return Directory::GetDirectories(this->FullName());
}

std::vector<std::string> DirectoryInfo::GetFiles() const
{
    return this->GetFiles("*");
}

std::vector<std::string> DirectoryInfo::GetFiles(std::string const &searchPattern) const
{
    return Directory::GetFiles(this->FullName());
}

#define SYSTEM_IO_DIRECTORYINFO_IMPLEMENTATION
#include "system.io.directory.h"

#define SYSTEM_IO_PATH_IMPLEMENTATION
#include "system.io.path.h"

#define SYSTEM_IO_FILESYSTEMINFO_IMPLEMENTATION
#include "system.io.filesysteminfo.h"

#endif // _SYSTEM_IO_DIRECTORYINFO_IMPLEMENTED_
#endif // SYSTEM_IO_DIRECTORYINFO_IMPLEMENTATION
