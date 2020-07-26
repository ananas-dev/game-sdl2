#pragma once
#include <Game.hpp>

class TextureManager
{
    public:
        static SDL_Texture* LoadTexture(std::string path);
        static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};
