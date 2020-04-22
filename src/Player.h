#ifndef PLAYER_H_
#define PLAYER_H_

#include "Animation.h"
#include <memory>
#include <string>
#include <vector>
#include "Util.h"

class Game;

class Player {
public:
    Player();
    Player(std::shared_ptr<Game> game);
    bool Init();
    void Update();
    void Render();

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

private:
    std::shared_ptr<Game> _game;
    Animation _animation;

    Vector _pos;
    Vector _size;
    static constexpr unsigned short int _speed{ 1 };

    // store starting position for game entities
    Vector _playerIniPos;
};

#endif