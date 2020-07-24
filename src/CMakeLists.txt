add_library(
  LogCmd
  LogCmd.cpp
  LogCmd.hpp
  )

add_library(
  Game
  LogCmd
  Game.cpp
  Game.hpp
  )

add_library(
  TextureManager
  Game
  TextureManager.cpp
  TextureManager.hpp
  )


add_library(
  GameObject
  Game
  TextureManager
  GameObject.cpp
  GameObject.hpp
  )

add_library(
  Map
  Game
  TextureManager
  Map.cpp
  Map.hpp
  )

target_include_directories(LogCmd PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(Game PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(TextureManager PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(GameObject PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(Map PUBLIC "${PROJECT_SOURCE_DIR}/src")
