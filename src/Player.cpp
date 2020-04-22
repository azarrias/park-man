#include "Game.h"
#include "Player.h"

Player::Player(std::shared_ptr<Game> game) {
    _game = game;
    _animation = Animation(Texture(game->_renderer));
}

bool Player::Init() {
    if (!_animation.LoadFromFile("../assets/pacman.png"))
        return false;
    
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
        _game->_board->_pos.x + _game->_board->_playerIniPos.x * _game->_tileWidth, 
        _game->_board->_pos.y + _game->_board->_playerIniPos.y * _game->_tileHeight, 
        _animation._frames[_animation._currentFrame].quad.x,
        _animation._frames[_animation._currentFrame].quad.y,
        _animation._frames[_animation._currentFrame].quad.w,
        _animation._frames[_animation._currentFrame].quad.h
    );
}