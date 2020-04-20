#ifndef RENDERER_H_
#define RENDERER_H_

#include <memory>
#include <SDL2/SDL.h>

class Renderer {
public:
    Renderer();
    ~Renderer();
    bool Init();
    void ClearScreen(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void UpdateScreen();

private:
    static constexpr unsigned short int _screenWidth{1280};
    static constexpr unsigned short int _screenHeight{960};
    static constexpr bool _vsync{true};
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _sdlWindow;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _sdlRenderer;
};

#endif