#ifndef __GAME_H_
#define __GAME_H_
#include <SDL2/SDL.h>
#include <iostream>
#include "LogCmd.hpp"

class Game {

public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height,
              bool fullscreen);

    void handleEvent();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; }

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif // __GAME_H_
