#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <vector>
#include "Board.h"
#include "Controller.h"
#include "Enemy.h"
#include "Player.h"
#include "Renderer.h"

class Game : public std::enable_shared_from_this<Game> {
public:
    bool Init();
    bool Update();
    void Render();
    std::shared_ptr<Game> get_shared_this() { return shared_from_this(); }
    std::shared_ptr<Renderer> _renderer;
    Board _board;
    Player _player;
    std::vector<Enemy> _enemies;

    static constexpr unsigned short int _screenWidth{1280};
    static constexpr unsigned short int _screenHeight{960};
    static constexpr unsigned short int _virtualWidth{640};
    static constexpr unsigned short int _virtualHeight{480};
    static constexpr unsigned short int _tileWidth{16};
    static constexpr unsigned short int _tileHeight{16};
    static constexpr unsigned short int _dotSize{2};
    static constexpr unsigned short int _powerupSize{4};

private:
    Controller _controller;
};

#endif