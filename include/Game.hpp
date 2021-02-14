#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

class ColliderComponent;

class Game {
 public:
  Game();
  ~Game();

  void Init(const char *title, int xpos, int ypos, int width, int height,
            bool fullscreen);

  void SetFps(const int FPS);
  void StartFrame();
  void EndFrame();

  void HandleEvent();
  void Update();
  void Render();
  void Clean();
  bool Running();

  static void AddTile(int x, int y, int id);
  static SDL_Renderer *renderer;
  static SDL_Event event;
  static std::vector<ColliderComponent *> colliders;

 private:
  bool mIsRunning;
  SDL_Window *mWindow;
  int mFrameDelay;
  int mFrameTime;
  Uint32 mFrameStart;
  int mFrameCount;
};
