cmake_minimum_required(VERSION 3.0)

project(Game VERSION 0.0.1
                  DESCRIPTION "Game project using C++ and SDL2"
                  LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

file(COPY "${PROJECT_SOURCE_DIR}/assets" DESTINATION "${EXECUTABLE_OUTPUT_PATH}")

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

file(
  GLOB SRCS
  "${PROJECT_SOURCE_DIR}/src/*"
  "${PROJECT_SOURCE_DIR}/src/ECS/*"
  "${PROJECT_SOURCE_DIR}/game/*"
)

add_executable(game ${SRCS})

find_package(
  SDL2 REQUIRED
  SDL_image REQUIRED
)

target_link_libraries(game SDL2 SDL2_image)
target_compile_options(game PRIVATE -Wall -Wextra)
