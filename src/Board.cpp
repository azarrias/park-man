#include "Board.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

Board::Board()
{}

Board::Board(std::shared_ptr<Game> game) {
    _game = game;
}

void Board::EmptyTile(const Vector& coord)
{
    _tiles[coord.y][coord.x] = Tile::Empty;
}

// Get tile value given tile map coordinates
Tile Board::GetTile(const Vector& coord) const {
    return _tiles[coord.y][coord.x];
}

bool Board::Init() {
    _dotsCounter = 0;

    if(!LoadFromFile("../assets/map.dat")) {
        std::cerr << "Could not load board from file.\n";
        return false;
    }

    _rows = _tiles.size();
    _cols = _tiles[0].size();
    unsigned short int tileWidth = _game->_tileWidth;
    unsigned short int tileHeight = _game->_tileHeight;
    unsigned short int virtualWidth = _game->_virtualWidth;
    unsigned short int virtualHeight = _game->_virtualHeight;

    _pos.x = (virtualWidth - tileWidth * _cols) / 2;
    _pos.y = (virtualHeight - tileHeight * _rows) / 2;
    _size.x = _cols * tileWidth;
    _size.y = _rows * tileHeight;

    return true;
}

std::vector<Tile> Board::ParseLine(std::string line, unsigned short int rownum) {
    std::istringstream sline(line);
    char c;
    std::vector<Tile> row;
    unsigned short int colnum = 0;
    while (sline >> c) {
        switch (c) {
            case 'X':
                row.emplace_back(Tile::Wall);
                break;
            case 'o':
                row.emplace_back(Tile::Dot);
                ++_dotsCounter;
                break;
            case 'O':
                row.emplace_back(Tile::Powerup);
                ++_dotsCounter;
                break;
            case 'P':
                _playerIniPos = Vector{colnum, rownum};
                row.emplace_back(Tile::Empty);
                break;
            case 'E':
                _enemiesIniPos.emplace_back(Vector{ colnum, rownum });
            default:
                row.emplace_back(Tile::Empty);
        }

        ++colnum;
    }
    return row;
}

bool Board::LoadFromFile(std::string path) {
    std::ifstream myfile (path);
    std::vector<std::vector<Tile>> board{};
    if (myfile) {
        std::string line;
        unsigned short int rownum = 0;
        while (getline(myfile, line)) {
            std::vector<Tile> row = ParseLine(line, rownum);
            board.emplace_back(row);
            ++rownum;
        }
    }
    if (board.empty())
        return false;
    
    _tiles = board;
    return true;
}

// Translates point coordinates to tile map coordinates
Vector Board::PointToTile(int x, int y) const {
    // if the point is out of the board bounds, return tile coordinates (-1, -1)
    int coordx = x / _game->_tileWidth;
    int coordy = y / _game->_tileHeight;

    if (coordx < 0)
        coordx = _cols - 1;
    else if (coordx >= _cols)
        coordx = 0;

    if (coordy < 0)
        coordy = _rows - 1;
    else if (coordy >= _rows)
        coordy = 0;

    return Vector{coordx, coordy};
}

void Board::Render() {
    for (size_t y = 0; y < _rows; ++y) {
        for (size_t x = 0; x < _cols; ++x) {
            switch (_tiles[y][x]) {
                case Tile::Wall:
                    _game->_renderer->SetDrawColor(120, 120, 255, 255);
                    _game->_renderer->FillRect(_pos.x + x * _game->_tileWidth, _pos.y + y * _game->_tileHeight, _game->_tileWidth, _game->_tileHeight);
                    break;
                case Tile::Dot: {
                    _game->_renderer->SetDrawColor(255, 255, 255, 255);
                    _game->_renderer->FillRect(_pos.x + x * _game->_tileWidth + _game->_tileWidth / 2 - _game->_dotSize / 2, 
                        _pos.y + y * _game->_tileHeight + _game->_tileHeight / 2 - _game->_dotSize / 2,
                        _game->_dotSize, _game->_dotSize);
                    break;
                }
                case Tile::Powerup: {
                    _game->_renderer->SetDrawColor(255, 255, 255, 255);
                    _game->_renderer->FillRect(_pos.x + x * _game->_tileWidth + _game->_tileWidth / 2 - _game->_powerupSize / 2,
                        _pos.y + y * _game->_tileHeight + _game->_tileHeight / 2 - _game->_powerupSize / 2,
                        _game->_powerupSize, _game->_powerupSize);
                    break;
                }
                case Tile::Empty:
                    break;
            }
        }
    }
}