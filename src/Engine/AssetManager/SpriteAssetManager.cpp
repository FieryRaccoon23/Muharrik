#include "SpriteAssetManager.h"

#include "Display/renderer2D.h"
#include "Components/sdldata.h"
#include "Util/eastl_vector_util.h"

namespace Muharrik
{
    void SpriteAssetManager::InitSpriteAssetManager(const SDL* sdl)
    {
        mSDL = sdl;

        for(int i = 0; i < static_cast<int>(SpriteEnum::MAX_COUNT); ++i)
        {
            TextureEntityVector entityVec;
            mRuntimeBatchedSprites.push_back(entityVec);
        }
    }

    void SpriteAssetManager::CreateTexture(entt::entity e, SpriteEnum se)
    {
        // Add to dictionary if the texture not loaded yet
        auto it = mRuntimeTextureCache.find(se);

        SDL_Texture* texture = nullptr;

        if (it != mRuntimeTextureCache.end())
        {
            texture = it->second;
        }
        else
        {
            const eastl::string& path = gSpriteAssets.at((int)se);
            texture = mSDL->LoadPNGTexture(path.c_str());
            mRuntimeTextureCache.insert({ se, texture });
        }

        // Add to batch sprite
        int index = static_cast<int>(se);
        mRuntimeBatchedSprites[index].push_back(e);

        // Set sdl data
    }

    void SpriteAssetManager::DestroyTextures(entt::registry& registry)
    {
        // Clear texture dictionary
        for(auto it : mRuntimeTextureCache)
        {
            SDL_DestroyTexture(it.second);
        }
        mRuntimeTextureCache.clear();

        // Clear batch
        for(auto it : mRuntimeBatchedSprites)
        {
            it.clear();
        }
        mRuntimeBatchedSprites.clear();
    }

    void SpriteAssetManager::RemoveEntityFromRuntime(entt::entity e, entt::registry& registry)
    {
        if (!registry.any_of<SDLData>(e))
        {
            return;
        }

        // Remove from batch
        SDLData sdlData = registry.get<SDLData>(e);
        int index = static_cast<int>(sdlData.mTextureID);
        TextureEntityVector& entityVec = mRuntimeBatchedSprites[index];

        erase_unordered(entityVec, e);

        // If count goes to 0, release the texture
        if(entityVec.size() == 0)
        {
            SDL_DestroyTexture(mRuntimeTextureCache[sdlData.mTextureID]);
            mRuntimeTextureCache.erase(sdlData.mTextureID);
        }
    }
}