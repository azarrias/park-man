#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(std::shared_ptr<Game> game, Vector pos) 
: _game(game), _animation(Animation(Texture(game->_renderer)))
{
    // set initial position
    _pos.x = pos.x * _game->_tileWidth;
    _pos.y = pos.y * _game->_tileHeight;
}

bool Enemy::Init(std::string path) {
    if (!_animation.LoadFromFile(path))
        return false;

    // set animation
    _animation.AddFrame(Frame{ Rect{0, 0, 16, 16}, 10 });
    _animation.AddFrame(Frame{ Rect{16, 0, 16, 16}, 10 });

    return true;
}

void Enemy::Update() {
    _animation.Update();
}

void Enemy::Render() const {
    _animation._texture.Render(
        _game->_board._pos.x + _pos.x,
        _game->_board._pos.y + _pos.y,
        _animation._frames[_animation._currentFrame].quad.x,
        _animation._frames[_animation._currentFrame].quad.y,
        _animation._frames[_animation._currentFrame].quad.w,
        _animation._frames[_animation._currentFrame].quad.h
    );
}