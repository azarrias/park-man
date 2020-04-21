#include <memory>
#include <iostream>
#include "Board.h"
#include "Game.h"

Game::Game() {
    _renderer = std::make_unique<Renderer>();
}

bool Game::Init() {
    _board = std::make_unique<Board>(get_shared_this());
    if(!_board->LoadFromFile("../assets/map.dat")) {
        std::cerr << "Could not load board from file.\n";
        return false;
    }
    return _renderer->Init();
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
    _renderer->SetDrawColor(0, 0, 0, 255);
    _renderer->Clear();
    _board->Render();
    _renderer->UpdateScreen();
}