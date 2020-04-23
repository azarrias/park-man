#ifndef GUI_H_
#define GUI_H_

#include <memory>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Texture.h"

class GUI {
public:
	GUI();
	bool Init(Game& game, std::string ttfPath);
	bool LoadTextureFromText(std::string text, SDL_Color color);
	void Render(Game& game);
	void DisableText();
	void EnableText();

private:
	std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> _font;
	static constexpr unsigned short int _fontSize{ 28 };
	Texture _texture;
	bool _textEnabled;
};

#endif