#include "Game.h"
#include "GUI.h"
#include <iostream>
#include <SDL2/SDL_image.h>

GUI::GUI()
: _font(nullptr, TTF_CloseFont), _textEnabled(true)
{}

bool GUI::Init(Game& game, std::string ttfPath) {
    _texture = Texture(game._renderer);

    // initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Could not initialize SDL_ttf!\n";
        std::cerr << "SDL_Error: " << TTF_GetError() << "\n";
        return false;
    }

    // load ttf font from file
	_font.reset(TTF_OpenFont(ttfPath.c_str(), _fontSize));
    if (_font == nullptr) {
        std::cerr << "Could not create TTF font from file\n";
        std::cerr << "SDL_Error: " << TTF_GetError() << "\n";
        return false;
    }

	return true;
}

bool GUI::LoadTextureFromText(std::string text, SDL_Color color) {
    // load textures from text
    if (!_texture.LoadFromText(_font.get(), text, color)) {
        std::cerr << "Could not render text texture\n";
        return false;
    }
    return true;
}

void GUI::Render(Game& game) {
    if (_textEnabled)
        _texture.Render((game._virtualWidth - _texture.Width()) / 2, (game._virtualHeight - _texture.Height()) * 0.57);
}

void GUI::DisableText()
{
    _textEnabled = false;
}

void GUI::EnableText()
{
    _textEnabled = true;
}
