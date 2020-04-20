#include <iostream>
#include "SDL2/SDL.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    constexpr unsigned short int screen_width{1280};
    constexpr unsigned short int screen_height{960};
    bool running = true;

    // Create window
    SDL_Window* window = SDL_CreateWindow("Park-Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                            screen_width, screen_height, SDL_WINDOW_SHOWN);
    if (nullptr == window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    while(running) {
        // Handle input
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (SDL_QUIT == e.type) {
                running = false;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}