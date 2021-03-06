#pragma once
#include <SDL2/SDL.h>

#include <ECS/ECS.hpp>
#include <ECS/TransformComponent.hpp>
#include <Game.hpp>
#include <string>

class ColliderComponent : public Component {
 public:
  SDL_Rect collider;
  std::string tag;

  TransformComponent* transform;

  ColliderComponent(std::string t) { tag = t; }

  void Init() override {
    if (!entity->HasComponent<TransformComponent>()) {
      entity->AddComponent<TransformComponent>();
    }
    transform = &entity->GetComponent<TransformComponent>();

    Game::colliders.push_back(this);
  }

  void Update() override {
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;
  }
};
