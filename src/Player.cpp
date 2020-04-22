#include "Game.h"
#include "Player.h"

#include <iostream>

Player::Player()
{}

Player::Player(std::shared_ptr<Game> game) {
    _game = game;
    _animation = Animation(Texture(game->_renderer));
}

bool Player::Init() {
    if (!_animation.LoadFromFile("../assets/pacman.png"))
        return false;

    // set initial position
    _pos.x = _game->_board._playerIniPos.x * _game->_tileWidth;
    _pos.y = _game->_board._playerIniPos.y * _game->_tileHeight;
    
    // set animation
    _animation.AddFrame(Frame{Rect{0, 0, 16, 16}, 10});
    _animation.AddFrame(Frame{Rect{16, 0, 16, 16}, 10});
    _animation.AddFrame(Frame{Rect{32, 0, 16, 16}, 10});
    _animation.AddFrame(Frame{Rect{16, 0, 16, 16}, 10});

    return true;
}

void Player::Update() {
    _animation.Update();
}

void Player::Render() {
    _animation._texture.Render(
        _game->_board._pos.x + _pos.x, 
        _game->_board._pos.y + _pos.y, 
        _animation._frames[_animation._currentFrame].quad.x,
        _animation._frames[_animation._currentFrame].quad.y,
        _animation._frames[_animation._currentFrame].quad.w,
        _animation._frames[_animation._currentFrame].quad.h
    );
}

void Player::MoveUp() {
    _pos.y -= _speed;
}

void Player::MoveDown() {
    _pos.y += _speed;
}

void Player::MoveLeft() {
    _pos.x -= _speed;
}

void Player::MoveRight() {
    _pos.x += _speed;
}