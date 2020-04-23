#include <memory>
#include <iostream>
#include "Board.h"
#include "Game.h"

bool Game::Init() {
    _renderer = std::make_shared<Renderer>(get_shared_this());
    if (!_renderer->Init())
        return false;

    _renderer->SetVirtualResolution(640, 480);

    _board = Board(get_shared_this());
    if (!_board.Init())
        return false;

    _player = Player(get_shared_this());
    if (!_player.Init())
        return false;

    for (const Vector& enemyPos : _board._enemiesIniPos) {
        _enemies.emplace_back(Enemy(get_shared_this(), enemyPos));
    }

    // init enemies with corresponding textures
    if (!_enemies[0].Init("../assets/cartman.png")) return false;
    if (!_enemies[1].Init("../assets/kenny.png")) return false;
    if (!_enemies[2].Init("../assets/kyle.png")) return false;
    if (!_enemies[3].Init("../assets/stan.png")) return false;

    if (!_gui.Init(*this, "../assets/font.ttf"))
        return false;

    if (!_gui.LoadTextureFromText("READY!", SDL_Color{ 255, 255, 150 }))
        return false;

    _state = GameState::Start;

    return true;
}

bool Game::Update() {
    switch (_state) {
    case GameState::Start:
        if (_counter >= _startFrames) {
            _state = GameState::Play;
            _gui.DisableText();
            _counter = 0;
        }
        else
            ++_counter;
        break;

    case GameState::Play:
        if (!_controller.HandleInput(_player))
            return false;
        for (Enemy& enemy : _enemies) {
            enemy.Update();
        }
        _player.Update();
    }

    return true;
}

void Game::Render() {
    _renderer->SetDrawColor(0, 0, 0, 255);
    _renderer->Clear();
    _board.Render();
    _gui.Render(*this);
    for (const Enemy& enemy : _enemies) {
        enemy.Render();
    }
    _player.Render();
    _renderer->UpdateScreen();
}