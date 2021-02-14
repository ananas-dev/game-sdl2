#pragma once
#include <SDL2/SDL.h>

#include <ECS/ECS.hpp>
#include <ECS/TransformComponent.hpp>
#include <TextureManager.hpp>

class SpriteComponent : public Component {
 private:
  TransformComponent *mTransform;
  SDL_Texture *mTexture;
  SDL_Rect mSrcRect, mDestRect;

 public:
  SpriteComponent() = default;

  SpriteComponent(std::string path) { SetTexture(path); }

  ~SpriteComponent() { SDL_DestroyTexture(mTexture); }

  void SetTexture(std::string path) {
    mTexture = TextureManager::LoadTexture(path);
  }

  void Init() override {
    mTransform = &entity->GetComponent<TransformComponent>();
    mSrcRect.x = mSrcRect.y = 0;
    mSrcRect.w = mSrcRect.h = 32;
    mDestRect.w = mDestRect.h = 64;
  }

  void Update() override {
    mDestRect.x = static_cast<int>(mTransform->position.x);
    mDestRect.y = static_cast<int>(mTransform->position.y);
    mDestRect.w = mTransform->width * mTransform->scale;
    mDestRect.h = mTransform->height * mTransform->scale;
  }

  void Draw() override { TextureManager::Draw(mTexture, mSrcRect, mDestRect); }
};
