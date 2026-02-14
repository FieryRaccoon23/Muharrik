#include "SpriteAssetManager.h"

#include "Display/renderer2D.h"
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

        // Add to batch
        auto batchIt = mRuntimeBatchedTextures.find(se);
        if (batchIt != mRuntimeBatchedTextures.end())
        {
            TextureEntitySet& currSet = batchIt->second;
            currSet.insert(e);
        }
        else
        {
            TextureEntitySet newSet;
            newSet.insert(e);
            mRuntimeBatchedTextures.insert({se, newSet});
        }
    }

    void SpriteAssetManager::DestroyTextures(entt::registry& registry)
    {
        mRuntimeTextureCache.clear();
        mRuntimeSpriteAssets.clear();

        // Clear batch
        for(auto it : mRuntimeBatchedTextures)
        {
            it.second.clear();
        }
        mRuntimeBatchedTextures.clear();
    }

    void SpriteAssetManager::RemoveEntityFromRuntime(entt::entity e, entt::registry& registry)
    {
        if (!registry.any_of<SDLData>(e))
        {
            return;
        }

        // Remove from batch
        SDLData sdlData = registry.get<SDLData>(e);
        TextureEntitySet& textureSet = mRuntimeBatchedTextures[sdlData.mTextureID];
        textureSet.erase(e);
        if(textureSet.size() == 0)
        {
            mRuntimeBatchedTextures.erase(sdlData.mTextureID);
        }

        // Remove reference
        auto it = mRuntimeSpriteAssets.find(e);
        if (it != mRuntimeSpriteAssets.end())
        {
            mRuntimeSpriteAssets.erase(it);
        }
    }
}