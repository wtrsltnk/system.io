#include <system.io/File.h>
#include <fstream>
#include <streambuf>

using namespace System::IO;

// Appends lines to a file, and then closes the file. If the specified file does not exist, this method creates a file, writes the specified lines to the file, and then closes the file.
void File::AppendAllLines(std::string const &path, std::vector<std::string> const &lines)
{ }

// Opens a file, appends the specified string to the file, and then closes the file. If the file does not exist, this method creates a file, writes the specified string to the file, then closes the file.
void File::AppendAllText(std::string const &path, std::string const &text)
{ }

// Opens a binary file, reads the contents of the file into a byte array, and then closes the file.
std::vector<unsigned char> File::ReadAllBytes(std::string const &path)
{
    std::vector<unsigned char> result;

    std::ifstream input(path, std::ifstream::binary);

    if (!input.good())
    {
        throw std::ios_base::failure("could not open input file for writing");
    }

    while (input.good())
    {
        result.push_back(input.get());
    }
    input.close();

    return result;
}

// Opens a text file, reads all lines of the file, and then closes the file.
std::vector<std::string> File::ReadAllLines(std::string const &path)
{
    std::vector<std::string> result;

    std::ifstream input(path);

    if (!input.good())
    {
        throw std::ios_base::failure("could not open input file for writing");
    }

    for(std::string line; std::getline(input, line); )
    {
        result.push_back(line);
    }
    input.close();

    return result;
}

// Opens a text file, reads all lines of the file, and then closes the file.
std::string File::ReadAllText(std::string const &path)
{
    std::ifstream input(path);

    if (!input.good())
    {
        throw std::ios_base::failure("could not open input file for writing");
    }

    std::string result((std::istreambuf_iterator<char>(input)),
                     std::istreambuf_iterator<char>());

    input.close();

    return result;
}

// Creates a new file, writes the specified byte array to the file, and then closes the file. If the target file already exists, it is overwritten.
void File::WriteAllBytes(std::string const &path, std::vector<unsigned char> const &bytes)
{
    std::ofstream output(path, std::ofstream::binary);

    if (!output.good())
    {
        throw std::ios_base::failure("could not open output file for writing");
    }

    output.write((char *)bytes.data(), bytes.size());

    output.close();
}

// Creates a new file, writes a collection of strings to the file, and then closes the file.
void File::WriteAllLines(std::string const &path, std::vector<std::string> const &lines)
{
    std::ofstream output(path);

    if (!output.good())
    {
        throw std::ios_base::failure("could not open output file for writing");
    }

    for (auto line : lines)
    {
        output.write(line.data(), line.size());
        output.write("\n", 1);
    }

    output.close();
}

// Creates a new file, writes the specified string to the file, and then closes the file. If the target file already exists, it is overwritten.
void File::WriteAllText(std::string const &path, std::string const &text)
{
    std::ofstream output(path);

    if (!output.good())
    {
        throw std::ios_base::failure("could not open output file for writing");
    }

    output.write(text.data(), text.size());

    output.close();}

#ifdef _WIN32
#include <windows.h>
#endif

// Copies an existing file to a new file. Overwriting a file of the same name is not allowed.
void File::Copy(std::string const &sourceFileName, std::string const &destFileName)
{
    Copy(sourceFileName, destFileName, false);
}

// Copies an existing file to a new file. Overwriting a file of the same name is allowed.
void File::Copy(std::string const &sourceFileName, std::string const &destFileName, bool overwrite)
{
#ifdef _WIN32
    CopyFile(sourceFileName.c_str(), destFileName.c_str(), overwrite ? FALSE : TRUE);
#endif // _WIN32
}

// Deletes the specified file.
void File::Delete(std::string const &path)
{
#ifdef _WIN32
    DeleteFile(path.c_str());
#endif // _WIN32
}

// Determines whether the specified file exists.
bool File::Exists(std::string const &path)
{
#ifdef _WIN32
    DWORD attr = GetFileAttributes(path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES)
    {
        return false;  //something is wrong with your path!
    }

    if (attr & FILE_ATTRIBUTE_DIRECTORY)
    {
        return false;   // this is a directory!
    }

    return true;    // this is not a directory!
#endif // _WIN32

    return false;
}

// Moves a specified file to a new location, providing the option to specify a new file name.
void File::Move(std::string const &sourceFileName, std::string const &destFileName)
{
#ifdef _WIN32
    MoveFile(sourceFileName.c_str(), destFileName.c_str());
#endif // _WIN32
}
