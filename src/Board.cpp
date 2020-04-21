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

    _x = (virtualWidth - tileWidth * _cols) / 2;
    _y = (virtualHeight - tileHeight * _rows) / 2;
    _w = _cols * tileWidth;
    _h = _rows * tileHeight;

    return true;
}

std::vector<Tile> Board::ParseLine(std::string line) {
    std::istringstream sline(line);
    char c;
    std::vector<Tile> row;
    while (sline >> c) {
        if (c == 'X') {
            row.emplace_back(Tile::Wall);
        } else if (c == 'o') {
            row.emplace_back(Tile::Dot);
        } else if (c == 'O') {
            row.emplace_back(Tile::Powerup);
        } else {
            row.emplace_back(Tile::Empty);
        }
    }
    return row;
}

bool Board::LoadFromFile(std::string path) {
    std::ifstream myfile (path);
    std::vector<std::vector<Tile>> board{};
    if (myfile) {
        std::string line;
        while (getline(myfile, line)) {
            std::vector<Tile> row = ParseLine(line);
            board.emplace_back(row);
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
                    _game->_renderer->FillRect(_x + x * _game->_tileWidth, _y + y * _game->_tileHeight, _game->_tileWidth, _game->_tileHeight);
                    break;
                case Tile::Dot:
                    _game->_renderer->SetDrawColor(255, 255, 255, 255);
                    _game->_renderer->FillRect(_x + x * _game->_tileWidth + _game->_tileWidth / 2 - 2 / 2, 
                        _y + y * _game->_tileHeight + _game->_tileHeight / 2 - 2 / 2, 
                        2, 2);
                    break;
                case Tile::Powerup:
                    _game->_renderer->SetDrawColor(255, 255, 255, 255);
                    _game->_renderer->FillRect(_x + x * _game->_tileWidth + _game->_tileWidth / 2 - 4 / 2, 
                        _y + y * _game->_tileHeight + _game->_tileHeight / 2 - 4 / 2, 
                        4, 4);
                    break;
                case Tile::Empty:
                    break;
            }
        }
    }
}