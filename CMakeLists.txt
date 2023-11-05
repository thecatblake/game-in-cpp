cmake_minimum_required(VERSION 3.26)
project(game_in_cpp)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

add_library(game
        Vector2.cpp
        Vector2.h
        Game.cpp
        Game.h
)

target_link_libraries(game SDL2::SDL2)
add_executable(pong Pong.cpp)
target_link_libraries(pong game)