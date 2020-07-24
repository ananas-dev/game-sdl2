cmake_minimum_required(VERSION 3.0)

project(Game VERSION 0.0.1
                  DESCRIPTION "Game project using C++ and SDL2"
                  LANGUAGES CXX)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
)

file(
  GLOB SRCS
  "${PROJECT_SOURCE_DIR}/include/*"
  "${PROJECT_SOURCE_DIR}/src/*"
  "${PROJECT_SOURCE_DIR}/game/*"
)

add_executable(Game ${SRCS})

find_package(
  SDL2 REQUIRED
  SDL_image REQUIRED
)

target_link_libraries(Game SDL2 SDL2_image)
