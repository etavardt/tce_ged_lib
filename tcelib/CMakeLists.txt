project(tcelib LANGUAGES CXX)

include(CMakePrintHelpers)
#Example usage: cmake_print_variables(SOURCE_FILES)
# cmake_print_variables(CMAKE_CPP_LINKER_LAUNCHER)
cmake_print_variables(libbacktrace_SOURCE_DIR)

cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)

include_directories(
    src/include/tcelib
    src/include/tcelib/SDL2
    ../3rdParty/easyloggingpp/src/
    ${libbacktrace_SOURCE_DIR}/src/
    ${libbacktrace_BINARY_DIR}/gen
)

file(GLOB SOURCE_FILES LIST_DIRECTORIES false
    ../3rdParty/easyloggingpp/src/*.cc
    src/cpp/*.cpp
    src/cpp/SDL2/*.cpp
)

file(GLOB HEADER_FILES LIST_DIRECTORIES false
    ../3rdParty/easyloggingpp/src/*.h
    src/include/tcelib/*.hpp
    src/include/tcelib/SDL2/*.hpp
)

add_library(tcelib STATIC ${SOURCE_FILES})
target_link_libraries(tcelib mingw32 SDL2_gfx SDL2_image SDL2_net SDL2_ttf SDL2main SDL2 setupapi imm32 winmm version)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (APPLE)
        # Incredibly, for both clang and g++, while a single compile-and-link invocation will create an
        # executable.dSYM/ dir with debug info, with separate compilation the final link does NOT create the
        # dSYM dir.
        #
        # The "dsymutil" program will create the dSYM dir for us. It takes in the executable and not the object
        # files even though it's the latter that contains the debug info. So, it will only work if the object files
        # built.
        find_program(DSYMUTIL_PROGRAM dsymutil)
        if (DSYMUTIL_PROGRAM)
            set(CMAKE_C_LINK_EXECUTABLE
                    "${CMAKE_C_LINK_EXECUTABLE}"
                    "${DSYMUTIL_PROGRAM} <TARGET>")
            set(CMAKE_C_CREATE_SHARED_LIBRARY
                    "${CMAKE_C_CREATE_SHARED_LIBRARY}"
                    "${DSYMUTIL_PROGRAM} <TARGET>")
            set(CMAKE_CXX_LINK_EXECUTABLE
                    "${CMAKE_CXX_LINK_EXECUTABLE}"
                    "${DSYMUTIL_PROGRAM} <TARGET>")
            set(CMAKE_CXX_CREATE_SHARED_LIBRARY
                    "${CMAKE_CXX_CREATE_SHARED_LIBRARY}"
                    "${DSYMUTIL_PROGRAM} <TARGET>")
        endif()

        target_compile_options(tcelib PUBLIC "-DDEBUG")
        target_link_libraries(tcelib backtrace)
    else()
        target_compile_options(tcelib PUBLIC "SHELL:-O0 -pg -fno-builtin -Wall -Wextra -static -m64 -DDEBUG")
        target_link_options(tcelib PUBLIC "SHELL:-O0 -pg -fno-builtin -Wall -Wextra -static -m64 -DDEBUG" "LINKER:-static,--disable-dynamicbase,--disable-reloc-section") #this works as well
        target_link_libraries(tcelib ${libbacktrace_BINARY_DIR}/libbacktrace.a)
    endif()
endif()

# TomC -- Unit Testing
enable_testing()

file(GLOB TEST_SOURCE_FILES LIST_DIRECTORIES false test/*.cpp)
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*main.cpp$")
add_executable(tcelib_test ${TEST_SOURCE_FILES} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(tcelib_test gtest_main)
target_link_libraries(tcelib_test mingw32 SDL2_gfx SDL2_image SDL2_net SDL2_ttf SDL2main SDL2 setupapi imm32 winmm version)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(tcelib_test ${libbacktrace_BINARY_DIR}/libbacktrace.a)
endif ()

include(GoogleTest)
gtest_discover_tests(tcelib_test)
