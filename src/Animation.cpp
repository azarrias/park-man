#include "Animation.h"
#include "Texture.h"

#include <iostream>

Animation::Animation()
{}

Animation::Animation(Texture texture)
: _texture(std::move(texture))
{}

bool Animation::LoadFromFile(std::string path) {
    return _texture.LoadFromFile(path);
}

void Animation::AddFrame(Rect r) {
    _clips.emplace_back(r);
}

void Animation::Render() {

}