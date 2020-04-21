#include "Game.h"
#include "Player.h"

Player::Player(std::shared_ptr<Game> game) {
    _game = game;
}

bool Player::Init() {
    return true;
}

void Player::Render() {
    return;
}