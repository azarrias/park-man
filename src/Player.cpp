#include "Game.h"
#include "Player.h"

Player::Player()
: _pos{0, 0}, _size{0, 0}
{}

Player::Player(std::shared_ptr<Game> game)
: _size{ 16, 16 } {
    _game = game;
    _animation = Animation(Texture(game->_renderer));
    _collider = Collider(Vector{ _size.x / 2, _size.y / 2 }, Vector{ 12, 12 });
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
    // keep previous position and calculate the new one
    Vector source_pos = _pos;
    _pos.y -= _speed;

    // warp to the opposite side of the board
    if (_pos.y < -8)
        _pos.y = _game->_board._size.y - 8;

    // get board coordinates of the relevant tiles
    Vector tileLeftUp = _game->_board.PointToTile(_pos.x + 2, _pos.y + 2);
    Vector tileRightUp = _game->_board.PointToTile(_pos.x + 14, _pos.y + 2);

    // if there is a wall, undo movement
    if (Tile::Wall == _game->_board.GetTile(tileLeftUp) ||
        Tile::Wall == _game->_board.GetTile(tileRightUp))
        _pos = source_pos;
    else {
        // if there is a collectible, check if the player collides with it
        HandleCollectibleCollisions(tileLeftUp);
        if (tileRightUp.x != tileLeftUp.x)
            HandleCollectibleCollisions(tileRightUp);
    }
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
    else {
        // if there is a collectible, check if the player collides with it
        HandleCollectibleCollisions(tileLeftDown);
        if (tileRightDown.x != tileLeftDown.x)
            HandleCollectibleCollisions(tileRightDown);
    }
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
    else {
        // if there is a collectible, check if the player collides with it
        HandleCollectibleCollisions(tileLeftUp);
        if (tileLeftDown.y != tileLeftUp.y)
            HandleCollectibleCollisions(tileLeftDown);
    }
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
    else {
        // if there is a collectible, check if the player collides with it
        HandleCollectibleCollisions(tileRightUp);
        if (tileRightDown.y != tileRightUp.y)
            HandleCollectibleCollisions(tileRightDown);
    }
}

void Player::HandleCollectibleCollisions(const Vector& tileCoord)
{
    int collectibleSize = 0;

    if (Tile::Dot == _game->_board.GetTile(tileCoord))
        collectibleSize = _game->_dotSize;
    else if (Tile::Powerup == _game->_board.GetTile(tileCoord))
        collectibleSize = _game->_powerupSize;
    else
        return;

    Rect collectibleCollider{ tileCoord.x * _game->_tileWidth + _game->_tileWidth / 2 - collectibleSize / 2,
        tileCoord.y * _game->_tileHeight + _game->_tileHeight / 2 - collectibleSize / 2,
        collectibleSize, collectibleSize };

    if (_collider.IsColliding(*this, collectibleCollider)) {
        _game->_board.EmptyTile(tileCoord);
        --_game->_board._dotsCounter;
    }
}
