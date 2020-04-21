#include "Board.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

Board::Board(std::shared_ptr<Game> game) {
    _game = game;
}

bool Board::Init() {
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
                break;
            case 'O':
                row.emplace_back(Tile::Powerup);
                break;
            case 'P':
                _playerIniPos.x = colnum;
                _playerIniPos.y = rownum;
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

void Board::Render() {
    for (size_t y = 0; y < _rows; ++y) {
        for (size_t x = 0; x < _cols; ++x) {
            switch (_tiles[y][x]) {
                case Tile::Wall:
                    _game->_renderer->SetDrawColor(120, 120, 255, 255);
                    _game->_renderer->FillRect(_pos.x + x * _game->_tileWidth, _pos.y + y * _game->_tileHeight, _game->_tileWidth, _game->_tileHeight);
                    break;
                case Tile::Dot: {
                    Vector dotSize{2, 2};
                    _game->_renderer->SetDrawColor(255, 255, 255, 255);
                    _game->_renderer->FillRect(_pos.x + x * _game->_tileWidth + _game->_tileWidth / 2 - dotSize.x / 2, 
                        _pos.y + y * _game->_tileHeight + _game->_tileHeight / 2 - dotSize.y / 2, 
                        dotSize.x, dotSize.y);
                    break;
                }
                case Tile::Powerup: {
                    Vector powerupSize{4, 4};
                    _game->_renderer->SetDrawColor(255, 255, 255, 255);
                    _game->_renderer->FillRect(_pos.x + x * _game->_tileWidth + _game->_tileWidth / 2 - powerupSize.x / 2, 
                        _pos.y + y * _game->_tileHeight + _game->_tileHeight / 2 - powerupSize.y / 2, 
                        powerupSize.x, powerupSize.y);
                    break;
                }
                case Tile::Empty:
                    break;
            }
        }
    }
}