#include "FileParser.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<Tile> FileParser::ParseLine(std::string line) {
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
        }
    }
    return row;
}

std::vector<std::vector<Tile>> FileParser::ReadBoardFile(std::string path) {
    std::ifstream myfile (path);
    std::vector<std::vector<Tile>> board{};
    if (myfile) {
        std::string line;
        while (getline(myfile, line)) {
            std::vector<Tile> row = ParseLine(line);
            board.emplace_back(row);
        }
    }
    return board;
}