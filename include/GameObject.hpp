#pragma once
#include <Game.hpp>

class GameObject
{
    public:
        GameObject(const char* texturesheet, int x, int y);
        ~GameObject();

        void Update();
        void Render();

    private:
        int xpos_;
        int ypos_;

        SDL_Texture* objTexture_;
        SDL_Rect srcRect_, destRect_;
        SDL_Renderer* renderer_;
};
