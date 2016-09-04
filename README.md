# System.IO
Partial c++ header only implementation of .NET System.IO classes. Goal of this project is to have similar functionality from .NET System.IO available in c++. Currently (partial)implemented are:

* DirectoryInfo
* FileInfo
* FileSystemInfo
* Path

These sources contain the header files in the include directory and a set of tests to verify they are working correctly. 

## Example
Here you find a few examples from tests cases which illustrate how these classes work now:
```c++
file = FileInfo(Path::Combine("c:\\temp", "subdir\\myfile.ext"))
```
this will result in `c:\\temp\\subdir\\myfile.ext`