#include "Controller.h"
#include "Player.h"
#include <SDL2/SDL.h>

bool Controller::HandleInput(Player& player) const {
    // Handle events on queue
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (SDL_QUIT == e.type) {
            return false;
        }
    }

    // Get key states
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    if (keyStates[SDL_SCANCODE_UP]) {
        player.MoveUp();
    }
    else if (keyStates[SDL_SCANCODE_DOWN]) {
        player.MoveDown();
    }
    else if (keyStates[SDL_SCANCODE_LEFT]) {
        player.MoveLeft();
    }
    else if (keyStates[SDL_SCANCODE_RIGHT]) {
        player.MoveRight();
    }

    return true;
}