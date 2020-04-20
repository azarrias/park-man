#include <iostream>
#include "SDL2/SDL.h"
#include "Renderer.h"

Renderer::Renderer()
: _sdlWindow(nullptr, SDL_DestroyWindow), _sdlRenderer(nullptr, SDL_DestroyRenderer)
{}

Renderer::~Renderer()
{
    SDL_Quit();
}

bool Renderer::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create window
    _sdlWindow.reset(SDL_CreateWindow("Park-Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                        _screenWidth, _screenHeight, SDL_WINDOW_SHOWN));
    if (nullptr == _sdlWindow) {
        std::cerr << "Window could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create renderer
    _sdlRenderer.reset(SDL_CreateRenderer(_sdlWindow.get(), -1, SDL_RENDERER_ACCELERATED));
    if (nullptr == _sdlRenderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    return true;
}

void Renderer::ClearScreen(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(_sdlRenderer.get(), r, g, b, a);
    SDL_RenderClear(_sdlRenderer.get());
}

void Renderer::UpdateScreen() {
    SDL_RenderPresent(_sdlRenderer.get());
}
