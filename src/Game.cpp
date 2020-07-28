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

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.AddEntity());
//auto& wall(manager.AddEntity());

enum groupLabels : std::size_t {
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

auto& tiles(manager.GetGroup(groupMap));
auto& players(manager.GetGroup(groupPlayers));
auto& enemies(manager.GetGroup(groupEnemies));

Game::Game() {}
Game::~Game() {}

void Game::Init(const char *title, int xpos, int ypos, int width, int height,
                bool fullscreen) {
    int flags=0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        logcmd::info("Subsystems Initialized!");
        mWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (mWindow) {
            logcmd::info("Window Created!");
        }

        renderer = SDL_CreateRenderer(mWindow, -1, 0);

        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            logcmd::info("Renderer Created!");
        }
        mIsRunning = true;
    } else {
        mIsRunning = false;
    }

    //////////////////////////
    /// ECS IMPLEMENTATION ///
    //////////////////////////

    // Map
    Map::LoadMap("assets/maps/map.txt", 25, 20);

    // Player
    player.AddComponent<TransformComponent>(2);
    player.AddComponent<SpriteComponent>("assets/adventurer/adventurer-idle-00.png");
    player.AddComponent<KeyboardController>();
    player.AddComponent<ColliderComponent>("player");
    player.AddGroup(groupPlayers);

    // Wall
    //wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    //wall.AddComponent<SpriteComponent>("assets/dongeon/wall_mid.png");
    //wall.AddComponent<ColliderComponent>("wall");
    //wall.AddGroup(groupMap);
}

/////////////////////
/// FRAME RELATED ///
/////////////////////

void Game::SetFps(const int FPS) {
    mFrameDelay = 1000 / FPS;
}

// Runs at the start of the frame
void Game::StartFrame() {
    if (mFrameDelay)
    {
    mFrameStart = SDL_GetTicks();
    } else {
        logcmd::err("FPS is not set, set it with setFPS()");
        mIsRunning = false;
    }
}

// Runs at the end of the frame
void Game::EndFrame() {
    if (mFrameStart) {
        mFrameTime = SDL_GetTicks() - mFrameStart;
        if (mFrameDelay > mFrameTime) {
            SDL_Delay(mFrameDelay - mFrameTime);
        }
    } else {
        logcmd::err("The frame is not initialized, use start()");
        mIsRunning = false;
    }
}

////////////////////////
/// RUNS EVERY FRAME ///
////////////////////////

void Game::HandleEvent() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            mIsRunning = false;
            break;

        default:
            break;
    }
}

void Game::Update() {
    manager.Refresh();
    manager.Update();

    for (auto collider: colliders) {
        Collision::AABB(player.GetComponent<ColliderComponent>(), *collider);
    }
}

void Game::Render() {
    SDL_RenderClear(renderer);
    // Begin
    for (auto& tile : tiles) {
        tile->Draw();
    }
    for (auto& player : players) {
        player->Draw();
    }
    for (auto& enemy : enemies) {
        enemy->Draw();
    }
    // End
    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::Running() {
    return mIsRunning;
}

/////////////
/// TILES ///
/////////////

void Game::AddTile(int x, int y, int id) {
    auto& tile(manager.AddEntity());
    tile.AddComponent<TileComponent>(x, y, 32, 32, id);
    tile.AddGroup(groupMap);
}

