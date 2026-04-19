cmake_minimum_required(VERSION 3.20)
project(SDLGames C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)

add_executable(SDLGames main.c
)
target_link_libraries(SDLGames SDL2::SDL2)
