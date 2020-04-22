#include <memory>
#include <iostream>
#include "Board.h"
#include "Game.h"

bool Game::Init() {
    _renderer = std::make_shared<Renderer>(get_shared_this());
    if (!_renderer->Init())
        return false;

    _renderer->SetVirtualResolution(640, 480);

    _board = std::make_unique<Board>(get_shared_this());
    if (!_board->Init())
        return false;

    _player = std::make_unique<Player>(get_shared_this());
    if (!_player->Init())
        return false;

    return true;    
}

bool Game::Update() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (SDL_QUIT == e.type) {
            return false;
        }
    }
    _player->Update();
    return true;
}

void Game::Render() {
    _renderer->SetDrawColor(0, 0, 0, 255);
    _renderer->Clear();
    _board->Render();
    _player->Render();
    _renderer->UpdateScreen();
}