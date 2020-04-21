#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <vector>
#include "Board.h"
#include "Renderer.h"

class Game : public std::enable_shared_from_this<Game> {
public:
    Game();
    bool Init();
    bool Update();
    void Render();
    std::shared_ptr<Game> get_shared_this() { return shared_from_this(); }
    std::unique_ptr<Renderer> _renderer;
    std::unique_ptr<Board> _board;
};

#endif