#include "Game.h"
#include "Player.h"

Player::Player(std::shared_ptr<Game> game) {
    _game = game;
    _animation = Animation(Texture(game->_renderer));
}

bool Player::Init() {
    if (!_animation.LoadFromFile("../assets/pacman.png"))
        return false;
    return true;
}

void Player::Render() {
    _game->_board->_playerIniPos;
    _animation._texture.Render(_game->_board->_pos.x + _game->_board->_playerIniPos.x * _game->_tileWidth, 
        _game->_board->_pos.y + _game->_board->_playerIniPos.y * _game->_tileHeight, 
        0, 0, 16, 16);
    return;
}