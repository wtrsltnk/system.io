#ifndef _SYSTEM_IO_FILEINFO_H_
#define _SYSTEM_IO_FILEINFO_H_

#include "FileSystemInfo.h"
#include "DirectoryInfo.h"
#include <string>

namespace System
{
namespace IO
{

class FileInfo : public FileSystemInfo
{
    std::string _name;
    void Init(std::string const &path);
public:
    FileInfo(std::string const &path);
    virtual ~FileInfo();

    std::string Name() const;
    DirectoryInfo Directory() const;

};

} // namespace IO
} // namespace System

#endif // _SYSTEM_IO_FILEINFO_H_
