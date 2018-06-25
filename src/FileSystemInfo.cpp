#include <system.io/system.io.filesysteminfo.h>
#include <system.io/system.io.path.h>
#include <system.io/system.io.file.h>

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

bool FileSystemInfo::Exists() const
{
    return File::Exists(_fullPath);
}
