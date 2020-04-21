#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include <string>
#include <vector>
#include "Vector.h"

class Game;

class Player {
public:
    Player(std::shared_ptr<Game> game);
    bool Init();
    void Render();

private:
    std::shared_ptr<Game> _game;

    Vector _pos;
    Vector _size;

    // store starting position for game entities
    Vector _playerIniPos;
};

#endif