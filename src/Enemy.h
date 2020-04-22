#ifndef ENEMY_H_
#define ENEMY_H_

#include "Animation.h"
#include "Util.h"

class Game;

class Enemy {
public:
    Enemy(std::shared_ptr<Game> game, Vector pos);
    bool Init(std::string path);
    void Update();
    void Render() const;

private:
    std::shared_ptr<Game> _game;
    Animation _animation;

    Vector _pos;
    Vector _size;
    static constexpr unsigned short int _speed{ 1 };
};

#endif