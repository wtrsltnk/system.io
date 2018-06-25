#include <system.io/system.io.path.h>
#include <system.io/system.io.directory.h>
#include <sstream>
#include <algorithm>

using namespace System::IO;

#ifdef _WIN32
char Path::DirectorySeparatorChar = '\\';
char Path::AltDirectorySeparatorChar = '/';
char Path::InvalidPathChars[] = { '\"', '<', '>', '|', '\0',
                                  static_cast<char>(1), static_cast<char>(2),
                                  static_cast<char>(3), static_cast<char>(4),
                                  static_cast<char>(5), static_cast<char>(6),
                                  static_cast<char>(7), static_cast<char>(8),
                                  static_cast<char>(9), static_cast<char>(10),
                                  static_cast<char>(11), static_cast<char>(12),
                                  static_cast<char>(13), static_cast<char>(14),
                                  static_cast<char>(15), static_cast<char>(16),
                                  static_cast<char>(17), static_cast<char>(18),
                                  static_cast<char>(19), static_cast<char>(20),
                                  static_cast<char>(21), static_cast<char>(22),
                                  static_cast<char>(23), static_cast<char>(24),
                                  static_cast<char>(25), static_cast<char>(26),
                                  static_cast<char>(27), static_cast<char>(28),
                                  static_cast<char>(29), static_cast<char>(30),
                                  static_cast<char>(31)
                                };
char Path::VolumeSeparatorChar = ':';
#else
char Path::DirectorySeparatorChar = '/';
char Path::AltDirectorySeparatorChar = '\\';
char Path::InvalidPathChars[] = { '\"', '<', '>', '|', '\0',
                                  static_cast<char>(1), static_cast<char>(2),
                                  static_cast<char>(3), static_cast<char>(4),
                                  static_cast<char>(5), static_cast<char>(6),
                                  static_cast<char>(7), static_cast<char>(8),
                                  static_cast<char>(9), static_cast<char>(10),
                                  static_cast<char>(11), static_cast<char>(12),
                                  static_cast<char>(13), static_cast<char>(14),
                                  static_cast<char>(15), static_cast<char>(16),
                                  static_cast<char>(17), static_cast<char>(18),
                                  static_cast<char>(19), static_cast<char>(20),
                                  static_cast<char>(21), static_cast<char>(22),
                                  static_cast<char>(23), static_cast<char>(24),
                                  static_cast<char>(25), static_cast<char>(26),
                                  static_cast<char>(27), static_cast<char>(28),
                                  static_cast<char>(29), static_cast<char>(30),
                                  static_cast<char>(31)
                                };
char Path::VolumeSeparatorChar = ':';
#endif

std::string Path::Combine(std::string const &path1, std::string const &path2)
{
    //  If path2 includes a root, path2 is returned
    if (Path::IsPathRooted(path2)) return path2;

    if (path1.length() == 0) return path2;

    std::string _path1(path1);
    std::string _path2(path2);

    if (_path1[_path1.length()-1] != Path::DirectorySeparatorChar
            && _path1[_path1.length()-1] != Path::AltDirectorySeparatorChar
            && _path1[_path1.length()-1] != Path::VolumeSeparatorChar)
        _path1 += Path::DirectorySeparatorChar;

    return _path1 + _path2;
}

std::string Path::GetDirectoryName(std::string const &path)
{
    if (path[path.length() - 2] == Path::VolumeSeparatorChar) return "";

    std::string seperators;
    seperators += Path::DirectorySeparatorChar;
    seperators += Path::AltDirectorySeparatorChar;

    auto lastSeperator = path.find_last_of(seperators);

    if (lastSeperator != std::string::npos)
    {
        auto result = path.substr(0, lastSeperator);
        if (result[result.length() - 1] == Path::VolumeSeparatorChar) result += Path::DirectorySeparatorChar;
        return result;
    }

    return path;
}

std::string Path::GetExtension(std::string const &path)
{
    auto filename = Path::GetFileName(path);
    auto lastSeperator = filename.find_last_of(".");

    if (lastSeperator != std::string::npos)
    {
        return filename.substr(lastSeperator);
    }

    return "";
}

std::string Path::GetFileName(std::string const &path)
{
    std::string seperators;
    seperators += Path::DirectorySeparatorChar;
    seperators += Path::AltDirectorySeparatorChar;

    auto lastSeperator = path.find_last_of(seperators);

    if (lastSeperator != std::string::npos)
    {
        auto result = path.substr(lastSeperator + 1);
        return result;
    }

    return path;
}

std::string Path::GetFileNameWithoutExtension(std::string const &path)
{
    auto filename = Path::GetFileName(path);
    auto lastSeperator = filename.find_last_of(".");

    if (lastSeperator != std::string::npos)
    {
        return filename.substr(0, lastSeperator);
    }

    return "";
}

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::string join(char delimiter, const std::vector<std::string>& v)
{
    std::stringstream ss;
    for(size_t i = 0; i < v.size(); ++i)
    {
      if(i != 0)
        ss << delimiter;
      ss << v[i];
    }
    return ss.str();
}

std::string Path::GetFullPath(std::string const &path)
{
    std::string _path = path;
    if (_path[_path.length() - 1] == Path::DirectorySeparatorChar
            || _path[_path.length() - 1] == Path::AltDirectorySeparatorChar)
        _path = _path.substr(0, _path.length() - 1);

    std::string cwd = Directory::GetCurrentWorkingDirectory();

    if (Path::IsPathRooted(_path))
    {
        if (_path[1] != Path::VolumeSeparatorChar && _path[1] != Path::DirectorySeparatorChar)
        {
            _path = cwd.substr(0, 2) + _path;
        }
    }
    else
    {
        _path = cwd + Path::DirectorySeparatorChar + _path;
    }

    std::replace(_path.begin(), _path.end(), Path::AltDirectorySeparatorChar, Path::DirectorySeparatorChar);

    std::vector<std::string> elems;
    split(_path, Path::DirectorySeparatorChar, elems);

    std::vector<std::string> filtered;
    for(size_t i = 0; i < elems.size(); ++i)
    {
        if (elems[i] == ".") continue;
        if (elems[i] == "..") continue;
        if (i < elems.size() - 1 && elems[i+1] == "..") continue;
        filtered.push_back(elems[i]);
    }

    return join(Path::DirectorySeparatorChar, filtered);
}

std::string Path::GetPathRoot(std::string const &path)
{
    if (!Path::IsPathRooted(path))
    {
        return "";
    }

    if (path[0] == Path::DirectorySeparatorChar)
    {
        return std::string(1, Path::DirectorySeparatorChar);
    }

    std::vector<std::string> elems;
    split(path, Path::DirectorySeparatorChar, elems);

    if (elems.size() > 0)
    {
        auto root = elems[0];
        if (root.size() == 2 && root[1] == Path::VolumeSeparatorChar)
        {
            return root + Path::DirectorySeparatorChar;
        }
    }

    return "";
}

bool Path::IsPathRooted(std::string const &path)
{
    auto length = path.length();

    // path starts with directory seperator
    if (length >= 1 && (path[0] == Path::DirectorySeparatorChar || path[0] == Path::AltDirectorySeparatorChar)) return true;

    // path starts with drive
    if (length >= 2 && (path[1] == Path::VolumeSeparatorChar)) return true;

    return false;
}
