#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class ColliderComponent;

class Game
{
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
        bool Running() { return isRunning_; }

        static SDL_Renderer *renderer;
        static SDL_Event event;
        static std::vector<ColliderComponent*> colliders;

    private:
        bool isRunning_;
        SDL_Window *window_;
        int frameDelay_;
        int frameTime_;
        Uint32 frameStart_;
        int frameCount_;
};
