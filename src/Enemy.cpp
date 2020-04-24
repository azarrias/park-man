#include "Enemy.h"
#include "Game.h"
#include "Util.h"

Enemy::Enemy(std::shared_ptr<Game> game, Vector pos) 
: _size{ 16, 16 }, _game(game), _animation(Animation(Texture(game->_renderer))),
  _orientation(Orientation::Down)
{
    // set initial position
    _pos.x = pos.x * _game->_tileWidth;
    _pos.y = pos.y * _game->_tileHeight;
    _targetPosition = _pos;
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
    // when reaching destination, randomize between available paths
    if (ReachedDestination()) {
        SetTargetDestination();
    }
    Move();
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

// to be improved (should check if we are past destination as well)
bool Enemy::ReachedDestination() const {
    return _pos.x == _targetPosition.x && _pos.y == _targetPosition.y;
}

void Enemy::SetTargetDestination() {
    // check adjacent tiles 
    Vector currentTile = _game->_board.PointToTile(_pos.x, _pos.y);
    Vector upTile{ currentTile.x, currentTile.y - 1 };
    Vector leftTile{ currentTile.x - 1, currentTile.y };
    Vector rightTile{ currentTile.x + 1, currentTile.y };
    Vector bottomTile{ currentTile.x, currentTile.y + 1 };

    // avoid walls, and going back to the ghost house
    std::vector<Vector> availablePaths;
    std::vector<Orientation> orientations;
    if (upTile.y >= 0 && Tile::Wall != _game->_board.GetTile(upTile)) {
        if (Tile::House != _game->_board.GetTile(upTile) ||
            Tile::House == _game->_board.GetTile(currentTile)) {
            availablePaths.emplace_back(upTile);
            orientations.emplace_back(Orientation::Up);
        }
    }
    if (leftTile.x >= 0 && Tile::Wall != _game->_board.GetTile(leftTile)) {
        if (Tile::House != _game->_board.GetTile(leftTile) ||
            Tile::House == _game->_board.GetTile(currentTile)) {
            availablePaths.emplace_back(leftTile);
            orientations.emplace_back(Orientation::Left);
        }
    }
    if (rightTile.x < _game->_board._cols && 
        Tile::Wall != _game->_board.GetTile(rightTile)) {
        if (Tile::House != _game->_board.GetTile(rightTile) ||
            Tile::House == _game->_board.GetTile(currentTile)) {
            availablePaths.emplace_back(rightTile);
            orientations.emplace_back(Orientation::Right);
        }
    }
    if (bottomTile.y < _game->_board._rows &&
        Tile::Wall != _game->_board.GetTile(bottomTile)) {
        if (Tile::House != _game->_board.GetTile(bottomTile) ||
            Tile::House == _game->_board.GetTile(currentTile)) {
            availablePaths.emplace_back(bottomTile);
            orientations.emplace_back(Orientation::Down);
        }
    }

    // randomize next target position
    std::random_device randomDevice;
    std::mt19937 engine{ randomDevice() };
    std::uniform_int_distribution<int> distribution(0, availablePaths.size() - 1);
    int index = distribution(engine);
    Vector targetTile = availablePaths[index];
    _targetPosition.x = targetTile.x * _game->_tileWidth;
    _targetPosition.y = targetTile.y * _game->_tileHeight;
    _orientation = orientations[index];
}

void Enemy::Move() {
    switch (_orientation) {
        case Orientation::Down:
            _pos.y += _speed;
            break;
        case Orientation::Left:
            _pos.x -= _speed;
            break;
        case Orientation::Right:
            _pos.x += _speed;
            break;
        case Orientation::Up:
            _pos.y -= _speed;
            break;
    }
}