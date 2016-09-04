# System.IO
Partial c++ header only implementation of .NET System.IO classes. Goal of this project is to have similar functionality from .NET System.IO available in c++. Currently (partial)implemented are:

* DirectoryInfo
* FileInfo
* FileSystemInfo
* Path

These sources contain the header files in the include directory and a set of tests to verify they are working correctly. 

## Example
Here you find a few examples from tests cases which illustrate how these classes work now:

### Example #1 Path & FileInfo
```cpp
auto file = FileInfo(Path::Combine("c:\\temp", "subdir\\myfile.ext"));
cout << file.FullName();
```
this will result in `c:\temp\subdir\myfile.ext`

### Example #2 FileInfo
```cpp
auto file = FileInfo("c:\\temp\\..\\subdir\\.\\myfile.ext");
cout << file.FullName();
```
this will result in `c:\subdir\myfile.ext`

### Example #3 FileInfo
```cpp
auto file = FileInfo("c:\\temp/subdir\\myfile.ext");
cout << file.FullName();
```
this will result in `c:\temp\subdir\myfile.ext`

### Example #4 FileInfo
```cpp
auto file = FileInfo("c:\\temp\\subdir\\myfile.ext");
auto directory = file.Directory();
cout << directory.FullName();
```
this will result in `c:\temp\subdir`

More examples can be found in the tests for [FileInfo](https://github.com/wtrsltnk/system.io/blob/master/tests/test-fileinfo.cpp).


### Example #5 Path
```cpp
cout << Path::Combine("c:\\temp", "subdir\\file.txt");
```
this will result in `c:\temp\subdir\file.txt`

### Example #6 Path
```cpp
cout << Path::Combine("c:\\temp", "c:\\temp.txt");
```
this will result in `c:\temp.txt`

### Example #7 Path
```cpp
cout << Path::Combine("", "subdir\\file.txt");
```
this will result in `subdir\file.txt`

More examples can be found in the tests for [Path](https://github.com/wtrsltnk/system.io/blob/master/tests/test-path.cpp).


