#include <iostream>
#include "SDL2/SDL.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    constexpr unsigned short int screen_width{1280};
    constexpr unsigned short int screen_height{960};
    bool running = true;

    SDL_Window* window = SDL_CreateWindow("Park-Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                            screen_width, screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
    }

    while(running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (SDL_QUIT == e.type) {
                running = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}