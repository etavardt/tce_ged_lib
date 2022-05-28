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
#    ../3rdParty/easyloggingpp/src/*.cc
    src/cpp/*.cpp
)

file(GLOB HEADER_FILES LIST_DIRECTORIES false
    ../3rdParty/easyloggingpp/src/*.h
    src/include/*.hpp
    ../tcelib/src/include/tcelib/*.hpp
    ../tcelib/src/include/tcelib/SDL2/*.hpp
)

add_executable(ged ${SOURCE_FILES})
target_link_libraries(ged tcelib)
# target_link_libraries(ged mingw32)
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image SDL2::GFX SDL2::TTF)
#target_link_libraries(ged mingw32 SDL2_mixer SDL2_gfx SDL2_image SDL2_net SDL2_ttf SDL2main SDL2 setupapi imm32 winmm version harfbuzz)

#target_link_libraries(ged mingw32 SDL2_mixer SDL2_gfx SDL2_image SDL2_net SDL2_ttf SDL2main SDL2 setupapi imm32 winmm version jpeg png tiff webp harfbuzz)
# target_link_libraries(ged mingw32 SDL2_mixer SDL2_gfx SDL2_image SDL2_net SDL2_ttf SDL2main SDL2 setupapi imm32 winmm version harfbuzz)
# target_link_libraries(ged ${FREETYPE_LIBRARIES})
# target_link_libraries(ged ${SDL2} ${PNGLIB} ${JPEG} ${TIFF} ${WEBP} ${SDL2_IMAGE} ${LZ}) #SDL2_image dep libs

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
        target_link_libraries(ged backtrace)
    else()
        target_compile_options(ged PUBLIC "SHELL:-O0 -pg -fno-builtin -Wall -Wextra -static -m64 -DDEBUG")
        target_link_options(ged PUBLIC "SHELL:-O0 -pg -fno-builtin -Wall -Wextra -static -m64 -DDEBUG") #this works as well
        endif()
endif()

add_custom_command(
    TARGET ged POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/ged/resources/fonts ${CMAKE_BINARY_DIR}/fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/ged/resources/images ${CMAKE_BINARY_DIR}/images
    COMMENT "Copying recources" VERBATIM
)
#${CMAKE_SOURCE_DIR}/recources/fonts $<TARGET_FILE_DIR:ged>/fonts
#DEPENDS ${ASSETS}

# add_custom_command(
#     TARGET ged POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_SOURCE_DIR}/recources/Images $<TARGET_FILE_DIR:ged>/images
#     COMMENT "Copying recources" VERBATIM
#     #DEPENDS ${ASSETS}
# )


# TomC -- Unit Testing
enable_testing()

file(GLOB TEST_SOURCE_FILES LIST_DIRECTORIES false test/*.cpp)
#list(FILTER SOURCE_FILES EXCLUDE REGEX ".*main.cpp$")
add_executable(ged_test ${TEST_SOURCE_FILES} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(ged_test gtest_main tcelib)
# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     target_link_libraries(ged_test ${libbacktrace_BINARY_DIR}/libbacktrace.a)
# endif ()

include(GoogleTest)
gtest_discover_tests(ged_test)
