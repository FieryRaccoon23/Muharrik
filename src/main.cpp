#define SDL_MAIN_HANDLED 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <cstdio>
#include <iostream>
#include <vector>

#include "Engine/engine.h"

int main(int argc, char** argv)
{
    (void)argc; (void)argv;

    Muharrik::Engine engine;

    engine.MainLoop();

    SDL_SetMainReady();  // important when using SDL_MAIN_HANDLED

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Muharrik Test", 800, 600, 0);
    if (!window) {
        std::printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
        }
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    glm::vec2 v(1.0f, 2.0f);
    std::printf("%f %f\n", v.x, v.y);


    return 0;
}
