#ifndef BOARD_H_
#define BOARD_H_

#include <memory>
#include <string>
#include <vector>
#include "Util.h"

class Game;

enum class Tile { House, Wall, Dot, Powerup, Empty };

class Board {
public:
    Board();
    Board(std::shared_ptr<Game> game);
    void EmptyTile(const Vector& coord);
    Tile GetTile(const Vector& coord) const;
    bool Init();
    std::vector<Tile> ParseLine(std::string line, unsigned short int rownum);
    bool LoadFromFile(std::string path);
    Vector PointToTile(int x, int y) const;
    void Render();

    // store starting position for game entities
    Vector _playerIniPos;
    std::vector<Vector> _enemiesIniPos;

    // tile set properties
    unsigned short int _rows;
    unsigned short int _cols;
    unsigned short int _dotsCounter;
    Vector _pos;
    Vector _size;

private:
    std::vector<std::vector<Tile>> _tiles;
    std::shared_ptr<Game> _game;
};

#endif