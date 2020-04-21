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

    unsigned short int numRows = _tiles.size();
    unsigned short int numCols = _tiles[0].size();
    unsigned short int tileWidth = _game->_tileWidth;
    unsigned short int tileHeight = _game->_tileHeight;
    unsigned short int virtualWidth = _game->_virtualWidth;
    unsigned short int virtualHeight = _game->_virtualHeight;

    _x = (virtualWidth - tileWidth * numCols) / 2;
    _y = (virtualHeight - tileHeight * numRows) / 2;
    _w = numCols * tileWidth;
    _h = numRows * tileHeight;

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
    _game->_renderer->SetDrawColor(0, 0, 255, 255);
    _game->_renderer->FillRect(_x, _y, _w, _h);
}