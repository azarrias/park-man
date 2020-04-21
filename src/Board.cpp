#include "Board.h"
#include "Game.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

Board::Board(std::shared_ptr<Game> game) {
    _game = game;
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
    unsigned short int numRows = _tiles.size();
    unsigned short int numCols = _tiles[0].size();
    unsigned short int tileWidth = _game->_renderer->_tileWidth;
    unsigned short int tileHeight = _game->_renderer->_tileHeight;
    unsigned short int screenWidth = _game->_renderer->_screenWidth;
    unsigned short int screenHeight = _game->_renderer->_screenHeight;

    unsigned short int xPos = (screenWidth - tileWidth * numCols) / 2;
    unsigned short int yPos = (screenHeight - tileHeight * numRows) / 2;

    _game->_renderer->SetDrawColor(0, 0, 255, 255);
    _game->_renderer->FillRect(xPos, yPos, tileWidth * numCols, tileHeight * numRows);
}