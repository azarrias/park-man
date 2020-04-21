#ifndef BOARD_H_
#define BOARD_H_

#include <memory>
#include <string>
#include <vector>

class Game;

enum class Tile { Wall, Dot, Powerup, Empty };

class Board {
public:
    Board(std::shared_ptr<Game> game);
    bool Init();
    std::vector<Tile> ParseLine(std::string line);
    bool LoadFromFile(std::string path);
    void Render();

private:
    std::vector<std::vector<Tile>> _tiles;
    std::shared_ptr<Game> _game;
    unsigned short int _rows;
    unsigned short int _cols;
    unsigned short int _x;
    unsigned short int _y;
    unsigned short int _w;
    unsigned short int _h;
};

#endif