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
        break;

    case GameState::Win:
        if (_counter >= _winFrames) {
            _state = GameState::Start;
            _counter = 0;
            Reset();
        }
        else
            ++_counter;
        break;

    case GameState::Die:
        if (_counter >= _dieFrames) {
            _state = GameState::Start;
            _counter = 0;
            Reset();
        }
        else
            ++_counter;
    }

    return true;
}

void Game::Render() {
    _renderer->SetDrawColor(0, 0, 0, 255);
    _renderer->Clear();
    _board.Render();
    for (const Enemy& enemy : _enemies) {
        enemy.Render();
    }
    _player.Render();
    _gui.Render(*this);
    _renderer->UpdateScreen();
}

void Game::CheckWin() {
    if (_board._dotsCounter == 0) {
        _state = GameState::Win;
        _gui.EnableText();
        _gui.LoadTextureFromText("YOU WIN!", SDL_Color{ 255, 255, 150 });
    }
}

void Game::CheckDie() {
        _state = GameState::Die;
        _gui.EnableText();
        _gui.LoadTextureFromText("YOU DIE!", SDL_Color{ 255, 255, 150 });
}

bool Game::Reset() {
    _board._enemiesIniPos.clear();

    // restore board
    if (!_board.Init())
        return false;

    // reset player position
    _player._pos.x = _board._playerIniPos.x * _tileWidth;
    _player._pos.y = _board._playerIniPos.y * _tileHeight;

    // reset enemy position
    for (size_t i = 0; i < _board._enemiesIniPos.size(); ++i) {
        _enemies[i]._pos.x = _board._enemiesIniPos[i].x * _tileWidth;
        _enemies[i]._pos.y = _board._enemiesIniPos[i].y * _tileHeight;
        _enemies[i]._targetPosition = _enemies[i]._pos;
    }

    _gui.LoadTextureFromText("READY!", SDL_Color{ 255, 255, 150 });

    return true;
}
