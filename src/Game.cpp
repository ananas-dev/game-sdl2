#include <Game.hpp>
#include <TextureManager.hpp>
#include <GameObject.hpp>
#include <Map.hpp>

GameObject* player;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

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

    player = new GameObject("assets/adventurer/adventurer-idle-00.png", 0, 0);
    map = new Map();
}

// Frame related stuff

void Game::SetFPS(const int FPS)
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
    SDL_Event event;
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
    player->Update();
}

void Game::Render()
{
    SDL_RenderClear(renderer);
    // Render stuff there
    map->DrawMap();
    player->Render();
    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
