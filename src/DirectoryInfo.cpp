#include <system.io.directoryinfo.h>
#include <system.io.directory.h>
#include <system.io.path.h>
#include <system.io.filesysteminfo.h>

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
