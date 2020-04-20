#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <vector>
#include "FileParser.h"
#include "Renderer.h"

class Game {
public:
    Game();
    bool Init();
    bool Update();
    void Render();

private:
    std::unique_ptr<Renderer> _renderer;
    std::vector<std::vector<Tile>> _board;
};

#endif