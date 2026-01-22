#include "SpriteAssetManager.h"

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
        auto it = mRuntimeTextureCache.find(se);

        if (it != mRuntimeTextureCache.end())
        {
            auto handle = it->second.lock();
            if (!handle)
            {
                const eastl::string& path = gSpriteAssets.at((int)se);
                SDL_Texture* raw = mSDL->LoadPNGTexture(path.c_str());
                handle = MakeTextureHandle(raw);
                it->second = handle;               
            }

            mRuntimeSpriteAssets[e] = handle;      
            return;
        }

        const eastl::string& path = gSpriteAssets.at((int)se);
        SDL_Texture* raw = mSDL->LoadPNGTexture(path.c_str());
        auto handle = MakeTextureHandle(raw);

        mRuntimeTextureCache.insert({ se, handle });
        mRuntimeSpriteAssets.insert({ e, handle }); 
    }

    void SpriteAssetManager::DestroyTextures(entt::registry& registry)
    {
        mRuntimeTextureCache.clear();
        mRuntimeSpriteAssets.clear();
    }

    void SpriteAssetManager::RemoveEntityFromRuntime(entt::entity e)
    {
        auto it = mRuntimeSpriteAssets.find(e);
        if (it != mRuntimeSpriteAssets.end())
        {
            mRuntimeSpriteAssets.erase(it);
        }
    }
}