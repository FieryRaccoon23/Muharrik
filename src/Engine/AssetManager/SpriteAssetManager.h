#pragma once

#include <EASTL/string.h>
#include <EASTL/fixed_hash_map.h>
#include <entt/entt.hpp>

#include "SpriteSerializedData.h"

#define MAX_TEXTURE_ASSETS 50

struct SDL_Texture;

namespace Muharrik
{
    class SDL;

    using SpriteMap = eastl::fixed_hash_map<
        entt::entity,
        SDL_Texture*,
        MAX_TEXTURE_ASSETS,
        MAX_TEXTURE_ASSETS * 2,
        false
    >;

    using TextureMap = eastl::fixed_hash_map<
        SpriteEnum,
        SDL_Texture*,
        MAX_TEXTURE_ASSETS,
        MAX_TEXTURE_ASSETS * 2,
        false
    >;

    class SpriteAssetManager
    {
        public:
        void InitSpriteAssetManager(const SDL* sdl);
        void CreateTexture(entt::entity e, SpriteEnum se);
        const SpriteMap& GetRuntimeSpriteAssets() const { return mRuntimeSpriteAssets;}

        void DestroySpriteAssetManager(entt::registry& registry);

        private:
        SpriteMap mRuntimeSpriteAssets;
        TextureMap mRuntimeTextureCache;
        const SDL* mSDL = nullptr;
    };
}