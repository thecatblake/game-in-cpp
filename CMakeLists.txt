cmake_minimum_required(VERSION 3.26)
project(game_in_cpp)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED SDL2_image)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_library(game
        Vector2.cpp
        Vector2.h
        Game.cpp
        Game.h
        Math.cpp
        Math.h
        Actor.cpp
        Actor.h
        Component.cpp
        Component.h
        SpriteComponent.cpp
        SpriteComponent.h
)

target_link_libraries(game SDL2::SDL2 SDL2_image::SDL2_image)
add_executable(pong Pong.cpp)
target_link_libraries(pong game)
add_executable(spaceship Spaceship.cpp)
target_link_libraries(spaceship game)