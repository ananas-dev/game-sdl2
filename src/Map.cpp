#include <Map.hpp>
#include <Game.hpp>
#include <fstream>

Map::Map() {
}

Map::~Map() {
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    char tile;
    std::fstream mapFile;
    mapFile.open(path);

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            Game::AddTile(x * 32, y * 32, atoi(&tile));
            mapFile.ignore();
        }
    }

    mapFile.close();
}
