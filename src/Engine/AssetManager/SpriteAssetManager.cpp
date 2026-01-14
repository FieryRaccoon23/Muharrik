#include "SpriteAssetManager.h"

#include "Display/sdl.h"
#include "Components/sdldata.h"
#include <SDL3_image/SDL_image.h>

namespace Muharrik
{
    void SpriteAssetManager::InitSpriteAssetManager(const SDL* sdl)
    {
        mSDL = sdl;
    }

    int SpriteAssetManager::CreateTexture(entt::registry& registry, entt::entity e, const eastl::string& path)
    {
        SDL_Texture* texture = mSDL->LoadPNGTexture(path.c_str());
        SDLData& sdlData = registry.get<SDLData>(e);
        sdlData.mTexture = texture;
        mRuntimeSpritesData.push_back(e);
        return mRuntimeSpritesData.size() - 1;
    }

    SpriteAssetManager::~SpriteAssetManager()
    {
        // NOTE: Leaking Memory here !!!!!
        for(auto t : mRuntimeSpritesData)
        {
            //SDL_DestroyTexture(t);
        }

        mRuntimeSpritesData.clear();
    }
}