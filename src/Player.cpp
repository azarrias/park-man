#include "Game.h"
#include "Player.h"

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
    Vector source_pos = _pos;
    _pos.y -= _speed;
    if (_pos.y < -8)
        _pos.y = _game->_board._size.y - 8;
    Vector tileLeftUp = _game->_board.PointToTile(_pos.x + 2, _pos.y + 2);
    Vector tileRightUp = _game->_board.PointToTile(_pos.x + 14, _pos.y + 2);
    if (Tile::Wall == _game->_board.GetTile(tileLeftUp) ||
        Tile::Wall == _game->_board.GetTile(tileRightUp))
        _pos = source_pos;
}

void Player::MoveDown() {
    Vector source_pos = _pos;
    _pos.y += _speed;
    if (_pos.y > _game->_board._size.y - 8)
        _pos.y = -8;
    Vector tileLeftDown = _game->_board.PointToTile(_pos.x + 2, _pos.y + 14);
    Vector tileRightDown = _game->_board.PointToTile(_pos.x + 14, _pos.y + 14);
    if (Tile::Wall == _game->_board.GetTile(tileLeftDown) ||
        Tile::Wall == _game->_board.GetTile(tileRightDown))
        _pos = source_pos;
}

void Player::MoveLeft() {
    Vector source_pos = _pos;
    _pos.x -= _speed;
    if (_pos.x < -8)
        _pos.x = _game->_board._size.x - 8;
    Vector tileLeftUp = _game->_board.PointToTile(_pos.x + 2, _pos.y + 2);
    Vector tileLeftDown = _game->_board.PointToTile(_pos.x + 2, _pos.y + 14);
    if (Tile::Wall == _game->_board.GetTile(tileLeftUp) ||
        Tile::Wall == _game->_board.GetTile(tileLeftDown))
        _pos = source_pos;
}

void Player::MoveRight() {
    Vector source_pos = _pos;
    _pos.x += _speed;
    if (_pos.x > _game->_board._size.x - 8)
        _pos.x = -8;
    Vector tileRightUp = _game->_board.PointToTile(_pos.x + 14, _pos.y + 2);
    Vector tileRightDown = _game->_board.PointToTile(_pos.x + 14, _pos.y + 14);
    if (Tile::Wall == _game->_board.GetTile(tileRightUp) ||
        Tile::Wall == _game->_board.GetTile(tileRightDown))
        _pos = source_pos;
}
