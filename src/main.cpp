#include <iostream>
#include "SDL2/SDL.h"
#include "Game.h"

int main() {
    Game game;
    if (!game.Init()) 
        return EXIT_FAILURE;

    while (game.Update()) {
        game.Render();
    }

    return EXIT_SUCCESS;
}