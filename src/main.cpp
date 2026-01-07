#define SDL_MAIN_HANDLED 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <cstdio>

int main(int argc, char** argv)
{
    (void)argc; (void)argv;

    SDL_SetMainReady();  // important when using SDL_MAIN_HANDLED

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL3 Test", 800, 600, 0);
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
    return 0;
}
