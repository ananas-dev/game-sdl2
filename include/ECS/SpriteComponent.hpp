#pragma once
#include <ECS/Components.hpp>
#include <TextureManager.hpp>
#include <SDL2/SDL.h>


class SpriteComponent : public Component
{
    private:
        TransformComponent *position_;
        SDL_Texture *texture_;
        SDL_Rect srcRect_, destRect_;

    public:
        SpriteComponent() = default;
        SpriteComponent(const char *path)
        {
            SetTexture(path);
        }

        void SetTexture(const char *path)
        {
            texture_ = TextureManager::LoadTexture(path);
        }

        void Init() override
        {
            position_ = &entity->GetComponent<TransformComponent>();
            srcRect_.x = srcRect_.y = 0;
            srcRect_.w = srcRect_.h = 32;
            destRect_.w = destRect_.h = 64;
        }

        void Update() override
        {
            destRect_.x = position_->X();
            destRect_.y = position_->Y();
        }

        void Draw() override
        {
            TextureManager::Draw(texture_, srcRect_, destRect_);
        }
};
