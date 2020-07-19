cmake_minimum_required(VERSION 3.0)

project(Game VERSION 0.0.1
                  DESCRIPTION "Game project using c++ and SDL2"
                  LANGUAGES CXX)

set(PROJECT_SOURCE_DIR "./src/")
set(GCC_COVERAGE_COMPILE_FLAGS "-lSDL2")

add_library(LogCmd STATIC "./src/LogCmd.cpp" "./include/LogCmd.hpp")
add_library(Game STATIC "./src/Game.cpp" "./include/Game.hpp")

add_executable(Game )

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

target_include_directories(GameExe PRIVATE ${Game_INCLUDE_DIRS})
