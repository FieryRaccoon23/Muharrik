#include "sdl.h"

#define SDL_MAIN_HANDLED 1

#include <cstdio>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <EASTL/fixed_hash_map.h>
#include <EASTL/shared_ptr.h>

#include "AssetManager/SpriteAssetManager.h"
#include "Components/position2D.h"
#include "Components/rotation2D.h"
#include "Components/scale2D.h"
#include "Components/sdldata.h"

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
        if (!mRenderer) 
        {
            std::printf("SDL: SDL_CreateRenderer failed: %s\n", SDL_GetError());
            return 1;
        }

        //std::printf("CWD: %s\n", SDL_GetBasePath());

        const char* sdlPath = SDL_GetBasePath();
        mBasePath = sdlPath;

        // const char* name = SDL_GetRendererName(mRenderer);
        // if (!name) 
        // {
        //     std::printf("SDL_GetRendererName failed: %s\n", SDL_GetError());
        // } else 
        // {
        //     const bool isSoftware = (std::strcmp(name, "software") == 0);
        //     std::printf("SDL renderer name: %s\n", name);
        //     std::printf("Rendering path: %s\n", isSoftware ? "CPU (software)" : "GPU (accelerated)");
        // }

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

    SDL_Texture* SDL::LoadPNGTexture(const char* relativePath) const
    {
        eastl::string absolutePath = mBasePath + relativePath;

        // Loads PNG into an SDL_Surface
        SDL_Surface* surf = IMG_Load(absolutePath.c_str());
        if (!surf) 
        {
            std::printf("SDL: IMG_Load failed (%s): %s\n", absolutePath.c_str(), SDL_GetError());
            return nullptr;
        }

        // Convert surface into GPU texture
        SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surf);
        SDL_DestroySurface(surf);

        if (!texture) 
        {
            std::printf("SDL: SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
            return nullptr;
        }

        return texture;
    }

    void SDL::RenderTexture(const SpriteAssetManager* spriteAssetManager, entt::registry& registry)
    {
        SDL_RenderClear(mRenderer);

        const auto& textureMap = spriteAssetManager->GetRuntimeTextureAssets();

        const auto& spriteMap = spriteAssetManager->GetRuntimeBatchedSpriteAssets();
        for(auto spriteIt = spriteMap.begin(); spriteIt != spriteMap.end(); ++spriteIt)
        {
            SpriteEnum se = spriteIt->first;
            auto textureIt = textureMap.find(se);
            const TextureWeak text = textureIt->second;

            SDL_Texture* t = nullptr;
            if (auto texShared = textureIt->second.lock()) 
            {
                t = texShared.get();
            }

            if(t == nullptr)
            {
                std::printf("SDL: RenderTexture failed: Texture t is null");
                continue;
            }

            for(auto e : spriteIt->second)
            {
                Position2D& pos = registry.get<Position2D>(e);
                Scale2D& scale = registry.get<Scale2D>(e);

                float w=0, h=0;
                SDL_GetTextureSize(t, &w, &h);
                SDL_FRect dst;
                dst.x = pos.mValue.x;
                dst.y = pos.mValue.y;
                dst.w = scale.mValue.x * w;
                dst.h = scale.mValue.y * h;

                SDL_RenderTexture(mRenderer, t, nullptr, &dst);
            }
        }

        SDL_RenderPresent(mRenderer);
    }

    void SDL::ToggleFullScreen() const
    {
        Uint32 flags = SDL_GetWindowFlags(mWindow);
        if (flags & SDL_WINDOW_FULLSCREEN) 
        {
            SDL_SetWindowFullscreen(mWindow, false);
        } 
        else 
        {
            SDL_SetWindowFullscreen(mWindow, true); 
        }
    }
    
}