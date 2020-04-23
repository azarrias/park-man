#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <memory>
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Texture {
public:
    Texture();
    Texture(std::shared_ptr<Renderer> renderer);
    bool LoadFromFile(std::string path);
    bool LoadFromText(TTF_Font* font, std::string text, SDL_Color color);
    void Render(int px, int py) const;
    void Render(int px, int py, int qx, int qy, int qw, int qh, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
    int Width() const { return _w; }
    int Height() const { return _h; }
private:
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _sdlTexture;
    std::shared_ptr<Renderer> _renderer;
    int _w;
    int _h;
};

#endif