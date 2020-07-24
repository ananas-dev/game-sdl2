#pragma once
#include "Game.hpp"

class Map
{
    public:

        Map();
        ~Map();

        void LoadMap(int arr[20][25]);
        void DrawMap();

    private:

        SDL_Rect src_, dest_;

        SDL_Texture* floor1_;
        SDL_Texture* floor2_;
        SDL_Texture* floor3_;

        int map_[20][25];

};
