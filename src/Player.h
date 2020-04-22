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
    Player(std::shared_ptr<Game> game);
    bool Init();
    void Update();
    void Render();

private:
    std::shared_ptr<Game> _game;
    Animation _animation;

    Vector _pos;
    Vector _size;

    // store starting position for game entities
    Vector _playerIniPos;
};

#endif