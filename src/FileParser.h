#ifndef FILE_PARSER_H_
#define FILE_PARSER_H_

#include <string>
#include <vector>

enum class Tile { Wall, Dot, Powerup };

namespace FileParser {

std::vector<Tile> ParseLine(std::string line);
std::vector<std::vector<Tile>> ReadBoardFile(std::string path);

};

#endif