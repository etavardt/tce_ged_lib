# **tce_ged_lib Project**

## This project serves two purposes.
1. Create a C++ application/window framework that makes coding a C++ application cleaner and OOP oriented that can be distributed as a library/headers package.
2. Create a Graphical Application utilizing the framework, testing, and providing an example of its usage.

## The sub-projects
- tcelib
- ged

## External projects it utilizes
- **SDL2**: for cross platform usage of window creation, image handling, audio, etc...
- **SDL2 CMake modules** [GITHUB](https://github.com/aminosbh/sdl2-cmake-modules) [GITLABS](https://gitlab.com/aminosbh/sdl2-cmake-modules)
- **easyloggingpp**: for logging info,errors,exceptions, etc... [GITHUB](https://github.com/amrayn/easyloggingpp)
- **libbacktrace**: for Exception's stacktrace [GITHUB](https://github.com/etavardt/libbacktrace.git)
- **GoogleTest**: for unit testing [Google GITHUB](https://google.github.io/googletest/quickstart-cmake.html)

## The build method
- **CMAKE**

## Build Notes
- The file "easlogging++.cc" is built into tcelib, therefore it does not need to be built into your project if you link the tcelib library. Only the header file, "easlogging++.h", needs to be in your include path.

## My build platform
- MSYS2/Mingw64 on Windows 11

## Known issues
- Build platform creep into CMAKE files