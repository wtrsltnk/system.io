#include <FileInfo.h>
#include <Path.h>
#include <FileSystemInfo.h>
#include <DirectoryInfo.h>

using namespace System::IO;

FileInfo::FileInfo(std::string const &path)
{
    this->Init(path);
}

FileInfo::~FileInfo()
{ }

void FileInfo::Init(std::string const &path)
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
