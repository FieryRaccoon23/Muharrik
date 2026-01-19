#include "SpriteAssetManager.h"

#include <SDL3_image/SDL_image.h>

#include "Display/sdl.h"
#include "Components/sdldata.h"

namespace Muharrik
{
    void SpriteAssetManager::InitSpriteAssetManager(const SDL* sdl)
    {
        mSDL = sdl;
    }

    void SpriteAssetManager::CreateTexture(entt::entity e, SpriteEnum se)
    {
        SDL_Texture* texture = nullptr;

        if(mRuntimeTextureCache.contains(se))
        {
            texture = mRuntimeTextureCache[se];
        }
        else
        {
            const eastl::string& path = gSpriteAssets.at((int)se);
            texture = mSDL->LoadPNGTexture(path.c_str());
            mRuntimeTextureCache.insert({se, texture});
        }

        mRuntimeSpriteAssets.insert({e, texture});
    }

    void SpriteAssetManager::DestroySpriteAssetManager(entt::registry& registry)
    {
        for (auto kv : mRuntimeTextureCache)
        {
            SDL_Texture* value = kv.second;
            SDL_DestroyTexture(value);
            value = nullptr;
        }

        mRuntimeTextureCache.clear();
        mRuntimeSpriteAssets.clear();

        registry.clear<SDLData>();
    }
}