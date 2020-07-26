#include <Game.hpp>
#include <Collision.hpp>
#include <ECS/Components.hpp>
#include <LogCmd.hpp>
#include <Map.hpp>
#include <Vector2D.hpp>
#include <TextureManager.hpp>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto &player(manager.AddEntity());
auto &wall(manager.AddEntity());

Game::Game() {}
Game::~Game() {}

void Game::Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags=0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        logcmd::info("Subsystems Initialized!");
        window_ = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window_)
        {
            logcmd::info("Window Created!");
        }

        renderer = SDL_CreateRenderer(window_, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            logcmd::info("Renderer Created!");
        }

        isRunning_ = true;
    } else {
        isRunning_ = false;
    }

    map = new Map();

    /*  ECS implementation */

    player.AddComponent<TransformComponent>(2);
    player.AddComponent<SpriteComponent>("assets/adventurer/adventurer-idle-00.png");
    player.AddComponent<KeyboardController>();
    player.AddComponent<ColliderComponent>("player");

    wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.AddComponent<SpriteComponent>("assets/dongeon/wall_mid.png");
    wall.AddComponent<ColliderComponent>("wall");
}

/* Frame related stuff */

void Game::SetFps(const int FPS)
{
    frameDelay_ = 1000 / FPS;
}

// Runs at the start of the frame
void Game::StartFrame()
{
    if (frameDelay_)
    {
    frameStart_ = SDL_GetTicks();
    } else {
        logcmd::err("FPS is not set, set it with setFPS()");
        isRunning_ = false;
    }
}

// Runs at the end of the frame
void Game::EndFrame()
{
    if (frameStart_)
    {
        frameTime_ = SDL_GetTicks() - frameStart_;
        if (frameDelay_ > frameTime_)
        {
            SDL_Delay(frameDelay_ - frameTime_);
        }
    } else {
        logcmd::err("The frame is not initialized, use start()");
        isRunning_ = false;
    }
}

void Game::HandleEvent()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            isRunning_ = false;
            break;

        default:
            break;
    }
}

void Game::Update()
{
    manager.Refresh();
    manager.Update();

    if (Collision::AABB(player.GetComponent<ColliderComponent>().collider,
                        wall.GetComponent<ColliderComponent>().collider))
    {
        player.GetComponent<TransformComponent>().velocity * -1;
        logcmd::info("Collision !");
    }
}

void Game::Render()
{
    SDL_RenderClear(renderer);

    map->DrawMap();
    manager.Draw();

    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
