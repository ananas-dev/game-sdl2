#include <Map.hpp>
#include <TextureManager.hpp>

int lvl1[20][25] = {
{ 1,0,0,1,2,0,0,2,1,0,0,0,2,0,0,2,0,0,1,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,0,1,0,0,0,0,0 },
{ 0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
{ 0,0,0,2,0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0 },
{ 0,0,0,0,0,0,0,1,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0 },
{ 0,0,1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,1,0,0,2,0,0 },
{ 0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1 },
{ 0,0,0,2,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0 },
{ 0,0,0,2,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0 }
};

Map::Map()
{
    floor1_ = TextureManager::LoadTexture("assets/dongeon/floor_1.png");
    floor2_ = TextureManager::LoadTexture("assets/dongeon/floor_2.png");
    floor3_ = TextureManager::LoadTexture("assets/dongeon/floor_3.png");

    LoadMap(lvl1);

    src_.x = src_.y = 0;
    src_.w = dest_.w = 32;
    src_.h = dest_.h = 32;
}

Map::~Map()
{
    SDL_DestroyTexture(floor1_);
    SDL_DestroyTexture(floor2_);
    SDL_DestroyTexture(floor3_);
}

void Map::LoadMap(int arr[20][25])
{
    for (int row = 0; row < 20; row++)
    {
        for (int column = 0; column < 25; column++)
        {
            map_[row][column] = arr[row][column];
        }
    }
}

void Map::DrawMap()
{
    int type = 0;

    for (int row = 0; row < 20; row++)
    {
        for (int column = 0; column < 25; column++)
        {
            type = map_[row][column];

            dest_.x = column * 32;
            dest_.y = row * 32;

            switch (type)
            {
                case 0:
                    TextureManager::Draw(floor1_, src_, dest_);
                    break;
                case 1:
                    TextureManager::Draw(floor2_, src_, dest_);
                    break;
                case 2:
                    TextureManager::Draw(floor3_, src_, dest_);
                    break;
                default:
                    break;
            }
        }
    }
}
