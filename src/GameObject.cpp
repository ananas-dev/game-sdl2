#include <GameObject.hpp>
#include <TextureManager.hpp>

GameObject::GameObject(const char* texturesheet, int xpos, int ypos)
{
    objTexture_ = TextureManager::LoadTexture(texturesheet);

    xpos_ = xpos;
    ypos_ = ypos;
}

void GameObject::Update()
{
    xpos_++;
    ypos_++;

    srcRect_.w = 50;
    srcRect_.h = 37;
    srcRect_.x = 0;
    srcRect_.y = 0;

    destRect_.x = xpos_;
    destRect_.y = ypos_;
    destRect_.w = srcRect_.w * 4;
    destRect_.h = srcRect_.h * 4;

}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture_, &srcRect_, &destRect_);
}
