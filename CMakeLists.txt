cmake_minimum_required(VERSION 3.0)

project(Game VERSION 0.0.1
                  DESCRIPTION "Game project using c++ and SDL2"
                  LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(libs/SDL2)
add_subdirectory(game)
