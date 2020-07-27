#pragma once

#include <ECS/ECS.hpp>
#include <ECS/TransformComponent.hpp>
#include <ECS/SpriteComponent.hpp>
#include <SDL2/SDL.h>

class TileComponent : public Component {
public:
    TransformComponent* transform;
    SpriteComponent* sprite;

    SDL_Rect tileRect;
    int tileId;
    std::string path;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id) {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileId = id;

        switch (tileId) {
        case 0:
            path = "assets/dongeon/floor_1.png";
            break;
        case 1:
            path = "assets/dongeon/floor_3.png";
            break;
        case 2:
            path = "assets/dongeon/wall_mid.png";
            break;
        default:
            break;
        }
    }

    void Init() override {
        entity->AddComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
        transform = &entity->GetComponent<TransformComponent>();

        entity->AddComponent<SpriteComponent>(path);
        sprite = &entity->GetComponent<SpriteComponent>();
    }
};
