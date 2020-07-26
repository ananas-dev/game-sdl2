#pragma once
#include <ECS/Components.hpp>
#include <TextureManager.hpp>
#include <SDL2/SDL.h>


class SpriteComponent : public Component
{
    private:
        TransformComponent *transform_;
        SDL_Texture *texture_;
        SDL_Rect srcRect_, destRect_;

    public:
        SpriteComponent() = default;
        SpriteComponent(const char *path)
        {
            SetTexture(path);
        }

        ~SpriteComponent()
        {
            SDL_DestroyTexture(texture_);
        }

        void SetTexture(const char *path)
        {
            texture_ = TextureManager::LoadTexture(path);
        }

        void Init() override
        {
            transform_ = &entity->GetComponent<TransformComponent>();
            srcRect_.x = srcRect_.y = 0;
            srcRect_.w = srcRect_.h = 32;
            destRect_.w = destRect_.h = 64;
        }

        void Update() override
        {
            destRect_.x = (int)transform_->position.x;
            destRect_.y = (int)transform_->position.y;
            destRect_.w = transform_->height = transform_->scale;
            destRect_.h = transform_->width = transform_->scale;
        }

        void Draw() override
        {
            TextureManager::Draw(texture_, srcRect_, destRect_);
        }
};
