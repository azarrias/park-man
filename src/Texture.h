#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <memory>
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <string>

class Texture {
public:
    Texture();
    Texture(std::shared_ptr<Renderer> renderer);
    bool LoadFromFile(std::string path);
    void Render(int px, int py);
    void Render(int px, int py, int qx, int qy, int qw, int qh);
private:
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _sdlTexture;
    std::shared_ptr<Renderer> _renderer;
    int _w;
    int _h;
};

#endif