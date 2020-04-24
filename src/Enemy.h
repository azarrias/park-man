#ifndef ENEMY_H_
#define ENEMY_H_

#include "Animation.h"
#include <random>
#include "Util.h"

class Game;

class Enemy {
public:
    Enemy(std::shared_ptr<Game> game, Vector pos);
    bool Init(std::string path);
    void Update();
    void Render() const;

    Vector _pos;
    Vector _size;
    Vector _targetPosition;

private:
    bool ReachedDestination() const;
    void SetTargetDestination();
    void Move();

    std::shared_ptr<Game> _game;
    Animation _animation;
    Orientation _orientation;

    static constexpr unsigned short int _speed{ 1 };
};

#endif