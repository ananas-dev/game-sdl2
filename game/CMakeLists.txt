add_executable(game main.cpp)

target_link_libraries(game PRIVATE LogCmd Game TextureManager GameObject Map SDL2 SDL2_image)
