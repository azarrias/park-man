#include <memory>
#include <iostream>
#include "FileParser.h"
#include "Game.h"

Game::Game() {
    _renderer = std::make_unique<Renderer>();
}

bool Game::Init() {
    _board = FileParser::ReadBoardFile("../assets/map.dat");
    if (_board.empty()) {
        std::cerr << "FileParser could not read board from file.\n";
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
    _renderer->ClearScreen(0, 0, 0, 255);
    _renderer->UpdateScreen();
}