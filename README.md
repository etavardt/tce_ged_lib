# **tce_ged_lib Project**

## This project serves two purposes.
1) Create a C++ application/window framework that makes coding a C++ application cleaner and OOP oriented that can be distributed as a library/headers package.
2) Create a Graphical Application utilizing the framework, testing, and providing an example of its usage.

## The sub-projects
- tcelib
- ged

## External projects it utilizes
- **SDL2**: for cross platform usage of window creation, image handling, audio, etc...
- **easyloggingpp**: for logging info,errors,exceptions, etc...
- **libbacktrace**: for Exception's stacktrace
- **GoogleTest**: for unit testing

## The build method
- **CMAKE**

## My build platform
- MSYS2/Mingw64 on Windows 11

## Known issues
- Build platform creep into CMAKE files