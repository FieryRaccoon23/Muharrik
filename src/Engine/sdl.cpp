#include "sdl.h"

#include <cstdio>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#define SDL_MAIN_HANDLED 1

namespace Muharrik
{
    int SDL::InitSDL()
    {
        SDL_SetMainReady();

        if (!SDL_Init(SDL_INIT_VIDEO)) 
        {
            std::printf("SDL: SDL_Init failed: %s\n", SDL_GetError());
            return 1;
        }

        mWindow = SDL_CreateWindow("Muharrik", 800, 600, 0);
        if (!mWindow) 
        {
            std::printf("SDL: SDL_CreateWindow failed: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }

        return 0;
    }

    bool SDL::PollSDL()
    {
        bool result = true;
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT) 
            {
                result = false;
            }
        }

        return result;
    }

    void SDL::DelaySDL(uint32_t ms)
    {
        SDL_Delay(ms);
    }

    void SDL::QuitSDL()
    {
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }
    
}