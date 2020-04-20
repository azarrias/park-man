#include <iostream>
#include "SDL2/SDL.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}