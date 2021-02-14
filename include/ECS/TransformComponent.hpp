#pragma once

#include <ECS/ECS.hpp>
#include <Vector2D.hpp>

class TransformComponent : public Component {
 public:
  Vector2D position;
  Vector2D velocity;

  int height = 32;
  int width = 32;
  int scale = 1;

  int speed = 3;

  TransformComponent() { position.Zero(); }

  TransformComponent(int sc) {
    position.Zero();
    scale = sc;
  }

  TransformComponent(float x, float y) {
    position.x = x;
    position.y = y;
  }

  TransformComponent(float x, float y, int h, int w, int sc) {
    position.x = x;
    position.y = y;
    height = h;
    width = w;
    scale = sc;
  }

  void Init() override { velocity.Zero(); }

  void Update() override {
    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
  }
};
