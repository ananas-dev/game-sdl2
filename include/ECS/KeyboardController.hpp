#pragma once

#include <ECS/ECS.hpp>
#include <ECS/TransformComponent.hpp>
#include <Game.hpp>
#include <SDL2/SDL.h>

class KeyboardController : public Component {
public:
    TransformComponent* transform;

    void Init() override {
        transform = &entity->GetComponent<TransformComponent>();
    }

    void Update() override {
        // When key is down
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
            case SDLK_q:
                transform->velocity.x = -1;
                break;
            case SDLK_d:
                transform->velocity.x = 1;
                break;
            case SDLK_z:
                transform->velocity.y = -1;
                break;
            case SDLK_s:
                transform->velocity.y = 1;
                break;
            default:
                break;
            }
        }
        // When key is up
        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
            case SDLK_q:
                transform->velocity.x = 0;
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                break;
            case SDLK_z:
                transform->velocity.y = 0;
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                break;
            default:
                break;
            }
        }
    }
};
