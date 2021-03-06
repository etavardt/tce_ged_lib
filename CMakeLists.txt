#set(CMAKE_VERBOSE_MAKEFILE ON)
cmake_minimum_required(VERSION 3.21.1)

project(tce LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

include(FetchContent)
include(CMakePrintHelpers) #Example usage: cmake_print_variables(SOURCE_FILES)

#cmake_print_variables(CMAKE_COMMAND)
#cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)

FetchContent_Declare(
    libbacktrace
    GIT_REPOSITORY https://github.com/etavardt/libbacktrace.git
    #GIT_TAG        ???
)

# Check if population has already been performed
FetchContent_GetProperties(libbacktrace)
string(TOLOWER "libbacktrace" lcName)
if(NOT ${lcName}_POPULATED)
  # Fetch the content using previously declared details
  FetchContent_Populate(libbacktrace)

  # Set custom variables, policies, etc.
  # ...

  # Bring the populated content into the build
  add_subdirectory(${${lcName}_SOURCE_DIR} ${${lcName}_BINARY_DIR})
endif()
cmake_print_variables(lcName)
cmake_print_variables(${lcName}_POPULATED)
cmake_print_variables(${lcName}_SOURCE_DIR)
cmake_print_variables(${lcName}_BINARY_DIR)

# This declares a dependency on GoogleTest which is downloaded from GitHub.
# See https://google.github.io/googletest/quickstart-cmake.html

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Find SDL2, SDL2_image and SDL2_gfx librarie
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_mixer REQUIRED)


# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)

# find_package(PNG REQUIRED)
# find_package(Freetype REQUIRED)
# # find_package(OpenGL REQUIRED)

# find_library(SDL2_LIBRARY SDL2)
# find_library(SDL2MAIN_LIBRARY SDL2main)

# find_library(PNG_LIBRARY png)
# find_library(JPEG_LIBRARY jpeg)
# find_library(TIFF_LIBRARY tiff)
# find_library(WEBP_LIBRARY webp)
# find_library(LZ_LIBRARY lz)



# #find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
# #find_library(SDL2_LIBRARY NAME SDL2)
# cmake_print_variables(SDL2_INCLUDE_DIR)
# cmake_print_variables(SDL2_LIBRARY)
# cmake_print_variables(FREETYPE_INCLUDE_DIRS)
# cmake_print_variables(FREETYPE_LIBRARIES)
# cmake_print_variables(SDL2_LIBRARY)


# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(tcelib)
add_subdirectory(ged)
#add_subdirectory(cppcheck)
