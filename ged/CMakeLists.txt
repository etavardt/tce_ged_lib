project(ged LANGUAGES CXX C)
include(CMakePrintHelpers)
#Example usage: cmake_print_variables(SOURCE_FILES)
# cmake_print_variables(CMAKE_CPP_LINKER_LAUNCHER)
cmake_print_variables(libbacktrace_SOURCE_DIR)
include_directories(
    src/include/
    ../tcelib/src/include/tcelib/
    ../tcelib/src/include/tcelib/SDL2
    ../3rdParty/easyloggingpp/src/
    ${libbacktrace_SOURCE_DIR}/src/
    ${libbacktrace_BINARY_DIR}/gen
)

file(GLOB SOURCE_FILES LIST_DIRECTORIES false
    ../3rdParty/easyloggingpp/src/*.cc
    src/cpp/*.cpp
)

file(GLOB HEADER_FILES LIST_DIRECTORIES false
    ../3rdParty/easyloggingpp/src/*.h
    src/include/*.hpp
    ../tcelib/src/include/tcelib/*.hpp
    ../tcelib/src/include/tcelib/SDL2/*.hpp
)

add_executable(ged ${SOURCE_FILES})
target_link_libraries(ged SDL2 SDL2main setupapi imm32 winmm version)
#target_include_directories(ged PUBLIC 3rdParty/easyloggingpp)
#target_link_directories(ged build/tcelib)

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

        target_compile_options(ged PUBLIC "-DDEBUG")
#        target_link_libraries(ged SDL2 SDL2main setupapi imm32 winmm version)
        target_link_libraries(ged backtrace tcelib)
    else()
        target_compile_options(ged PUBLIC "SHELL:-O0 -pg -fno-builtin -Wall -Wextra -static -m64 -DDEBUG")
#        target_link_options(ged PUBLIC "SHELL:-O0 -pg -fno-builtin -Wall -Wextra -static -m64 -DDEBUG" "LINKER:-static,--disable-dynamicbase,--disable-reloc-section") #this works as well
        target_link_options(ged PUBLIC "SHELL:-O0 -pg -fno-builtin -Wall -Wextra -static -m64 -DDEBUG" ) #this works as well
#        target_link_libraries(ged SDL2 SDL2main ${libbacktrace_BINARY_DIR}/libbacktrace.a tcelib)
#        target_link_libraries(ged SDL2 SDL2main setupapi imm32 winmm version)
        target_link_libraries(ged tcelib)
#        target_link_libraries(ged ${SDL2_LIBRARY})
        endif()
endif()

# TomC -- Unit Testing
enable_testing()

file(GLOB TEST_SOURCE_FILES LIST_DIRECTORIES false test/*.cpp)
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*main.cpp$")
add_executable(ged_test ${TEST_SOURCE_FILES} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(ged_test SDL2 SDL2main setupapi imm32 winmm version)
target_link_libraries(ged_test gtest_main tcelib)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(ged_test ${libbacktrace_BINARY_DIR}/libbacktrace.a)
endif ()

include(GoogleTest)
gtest_discover_tests(ged_test)
