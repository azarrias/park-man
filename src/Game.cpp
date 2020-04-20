#include <memory>
#include "Game.h"

Game::Game() {
    renderer = std::make_unique<Renderer>();
}

bool Game::Init() {
    return renderer->Init();
}

bool Game::Update() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (SDL_QUIT == e.type) {
            return false;
        }
    }
    return true;
}

void Game::Render() {
    renderer->ClearScreen(0, 0, 0, 255);
    renderer->UpdateScreen();
}