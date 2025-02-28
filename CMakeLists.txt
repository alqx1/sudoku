cmake_minimum_required(VERSION 3.28)
project(sudoku LANGUAGES C)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

find_package(raylib)
if (NOT raylib_FOUND)
    FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SDL2)
endif()

set(libs ${libs} raylib glfw m)

FILE(GLOB_RECURSE CSOURCES ./src/*.c)
add_executable(sudoku ${CSOURCES})

add_custom_command(
        TARGET sudoku POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/config.txt
                ${CMAKE_CURRENT_BINARY_DIR}/config.txt)
add_custom_command(
        TARGET sudoku POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/sudoku.txt
                ${CMAKE_CURRENT_BINARY_DIR}/sudoku.txt)


target_link_libraries(sudoku PRIVATE
    ${libs}
)
