#include "sdl.h"

#define SDL_MAIN_HANDLED 1

#include <cstdio>
#include <string>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

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


        mRenderer = SDL_CreateRenderer(mWindow, nullptr);
        if (!mRenderer) {
            std::printf("SDL: SDL_CreateRenderer failed: %s\n", SDL_GetError());
            return 1;
        }

        //std::printf("CWD: %s\n", SDL_GetBasePath());

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
        if(mWindow)
        {
            SDL_DestroyWindow(mWindow);
        }

        if(mRenderer)
        {
            SDL_DestroyRenderer(mRenderer);
        }

        SDL_Quit();
    }

    void SDL::LoadPNGTexture(const char* relativePath) 
    {
        std::string absolutePath = std::string(SDL_GetBasePath()) + relativePath;

        // Loads PNG into an SDL_Surface
        SDL_Surface* surf = IMG_Load(absolutePath.c_str());
        if (!surf) {
            std::printf("SDL: IMG_Load failed (%s): %s\n", absolutePath.c_str(), SDL_GetError());
            return;
        }

        // Convert surface into GPU texture
        mTexture = SDL_CreateTextureFromSurface(mRenderer, surf);
        SDL_DestroySurface(surf);

        if (!mTexture) 
        {
            std::printf("SDL: SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
            return;
        }
    }

    void SDL::RenderTexture()
    {
        if(!mTexture)
        {
            std::printf("SDL: No texture to render");
            return;
        }

        SDL_RenderClear(mRenderer);

        float w=0, h=0;
        SDL_GetTextureSize(mTexture, &w, &h);

        float scale = 0.5f; 
        SDL_FRect dst;
        dst.x = 0.0f;
        dst.y = 0.0f;
        dst.w = w * scale;
        dst.h = h * scale;

        SDL_RenderTexture(mRenderer, mTexture, nullptr, &dst);

        SDL_RenderPresent(mRenderer);
    }
    
}