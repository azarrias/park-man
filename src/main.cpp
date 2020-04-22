#include <iostream>
#include "SDL2/SDL.h"
#include "Game.h"

int main(int argc, char* argv[]) {
    std::shared_ptr<Game> game = std::make_shared<Game>();
    if (!game->Init()) 
        return EXIT_FAILURE;

    while (game->Update()) {
        game->Render();
    }

    return EXIT_SUCCESS;
}
