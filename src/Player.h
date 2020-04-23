#ifndef PLAYER_H_
#define PLAYER_H_

#include "Animation.h"
#include "Collider.h"
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

    void HandleCollectibleCollisions(const Vector& tileCoord);

    Vector _pos;
    Vector _size;

private:
    std::shared_ptr<Game> _game;
    Animation _animation;
    Collider _collider;

    static constexpr unsigned short int _speed{ 3 };
};

#endif