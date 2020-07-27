#include <iostream>
#include <Game.hpp>
#include <LogCmd.hpp>

Game *game = nullptr;

int main(/*int argc, char *argv[]*/) {
    game = new Game();

    game->Init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
    game->SetFps(60);

    while (game->Running()) {
        game->StartFrame();

        game->HandleEvent();
        game->Update();
        game->Render();

        game->EndFrame();
    }

    game->Clean();
    logcmd::warn("Execution has stopped, cleaning...");

    return 0;
}
