#include <iostream> 
#include <SDL2/SDL_image.h>
#include "Texture.h"

Texture::Texture()
: _sdlTexture(nullptr, SDL_DestroyTexture)
{}

Texture::Texture(std::shared_ptr<Renderer> renderer) 
: _sdlTexture(nullptr, SDL_DestroyTexture)
{
    _renderer = renderer;
}

bool Texture::LoadFromFile(std::string path) {
    // Load image into temporary surface
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL) {
        std::cerr << "Could not load surface from file\n";
        std::cerr << "IMG_Error: " << IMG_GetError() << "\n";
        return false;
    }

    _sdlTexture.reset(SDL_CreateTextureFromSurface(_renderer->_sdlRenderer.get(), surface));
    if (_sdlTexture == nullptr) {
        std::cerr << "Could not create texture from surface\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    _w = surface->w;
    _h = surface->h;

    SDL_FreeSurface(surface);
    return true;
}

void Texture::Render(int posx, int posy) {
    Render(posx, posy, 0, 0, _w, _h);
}

void Texture::Render(int px, int py, int qx, int qy, int qw, int qh) {
    SDL_Rect quad{qx, qy, qw, qh};
    SDL_Rect coord{px, py, qw, qh};
    SDL_RenderCopy(_renderer->_sdlRenderer.get(), _sdlTexture.get(), &quad, &coord);
}