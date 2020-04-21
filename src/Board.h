#ifndef BOARD_H_
#define BOARD_H_

#include <memory>
#include <string>
#include <vector>
#include "Vector.h"

class Game;

enum class Tile { Wall, Dot, Powerup, Empty };

class Board {
public:
    Board(std::shared_ptr<Game> game);
    bool Init();
    std::vector<Tile> ParseLine(std::string line, unsigned short int rownum);
    bool LoadFromFile(std::string path);
    void Render();

private:
    std::vector<std::vector<Tile>> _tiles;
    std::shared_ptr<Game> _game;

    // tile set properties
    unsigned short int _rows;
    unsigned short int _cols;
    Vector _pos;
    Vector _size;

    // store starting position for game entities
    Vector _playerIniPos;
};

#endif