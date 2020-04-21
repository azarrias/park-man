#ifndef RENDERER_H_
#define RENDERER_H_

#include <memory>
#include <SDL2/SDL.h>

class Renderer {
public:
    Renderer();
    ~Renderer();
    bool Init();
    int Clear();
    int FillRect(int x, int y, int w, int h);
    int SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void UpdateScreen();
    static constexpr unsigned short int _screenWidth{1280};
    static constexpr unsigned short int _screenHeight{960};
    static constexpr unsigned short int _tileWidth{16};
    static constexpr unsigned short int _tileHeight{16};

private:
    static constexpr bool _vsync{true};
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _sdlWindow;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _sdlRenderer;
};

#endif