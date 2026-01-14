#include "SpriteAssetManager.h"

#include "Display/sdl.h"
#include "Components/sdldata.h"

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

    void SpriteAssetManager::DestroySpriteAssetManager(entt::registry& registry)
    {
        registry.clear<SDLData>();

        mRuntimeSpritesData.clear();
    }
}