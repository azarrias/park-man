#include "Animation.h"
#include "Texture.h"

#include <iostream>

Animation::Animation()
: _currentFrame(0), _counter(0)
{}

Animation::Animation(Texture texture)
: _texture(std::move(texture)), _currentFrame(0), _counter(0)
{}

bool Animation::LoadFromFile(std::string path) {
    return _texture.LoadFromFile(path);
}

void Animation::AddFrame(Frame f) {
    _frames.emplace_back(f);
}

void Animation::Update() {
    if (_frames.size() > 1) {
        if (_counter >= _frames[_currentFrame].duration) {
            ++_currentFrame;
            _counter = 0;
        }

        ++_counter;

        if (_currentFrame >= _frames.size()) {
            _currentFrame = 0;
        }
    }
}
