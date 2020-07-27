#include <TextureManager.hpp>

SDL_Texture* TextureManager::LoadTexture(std::string path) {
    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return texture;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
