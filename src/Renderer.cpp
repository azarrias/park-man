#include <iostream>
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "Game.h"

Renderer::Renderer()
: _sdlRenderer(nullptr, SDL_DestroyRenderer), _sdlWindow(nullptr, SDL_DestroyWindow)
{}

Renderer::Renderer(std::shared_ptr<Game> game)
: _sdlRenderer(nullptr, SDL_DestroyRenderer), _sdlWindow(nullptr, SDL_DestroyWindow) {
    _game = game;
}

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
                                        _game->_screenWidth, _game->_screenHeight, SDL_WINDOW_SHOWN));
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

int Renderer::Clear() {
    return SDL_RenderClear(_sdlRenderer.get());
}

int Renderer::FillRect(int x, int y, int w, int h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return SDL_RenderFillRect(_sdlRenderer.get(), &rect);
}

int Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    return SDL_SetRenderDrawColor(_sdlRenderer.get(), r, g, b, a);
}

int Renderer::SetVirtualResolution(int w, int h) {
    return SDL_RenderSetLogicalSize(_sdlRenderer.get(), w, h);
}

void Renderer::UpdateScreen() {
    SDL_RenderPresent(_sdlRenderer.get());
}
