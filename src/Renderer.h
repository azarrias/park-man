#ifndef RENDERER_H_
#define RENDERER_H_

#include <memory>
#include <SDL2/SDL.h>

class Game;

class Renderer {
public:
    Renderer();
    Renderer(std::shared_ptr<Game> game);
    ~Renderer();
    bool Init();
    int Clear();
    int FillRect(int x, int y, int w, int h);
    int SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    int SetVirtualResolution(int w, int h);
    void UpdateScreen();

private:
    static constexpr bool _vsync{true};
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _sdlWindow;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _sdlRenderer;
    std::shared_ptr<Game> _game;
};

#endif