#pragma once

#include <memory>
#include <EASTL/string.h>
#include <EASTL/fixed_hash_map.h>
#include <entt/entt.hpp>
#include <SDL3_image/SDL_image.h>
#include <EASTL/shared_ptr.h>
#include <EASTL/weak_ptr.h>

#include "SpriteSerializedData.h"

#define MAX_TEXTURE_ASSETS 50

struct SDL_Texture;

namespace Muharrik
{
    class SDL;

    using TextureHandle = eastl::shared_ptr<SDL_Texture>;
    using TextureWeak   = eastl::weak_ptr<SDL_Texture>;

    using SpriteMap = eastl::fixed_hash_map<
        entt::entity,
        TextureHandle,
        MAX_TEXTURE_ASSETS,
        MAX_TEXTURE_ASSETS * 2,
        false
    >;

    using TextureMap = eastl::fixed_hash_map<
        SpriteEnum,
        TextureWeak,
        MAX_TEXTURE_ASSETS,
        MAX_TEXTURE_ASSETS * 2,
        false
    >;

    struct SDLTextureDeleter 
    {
        void operator()(SDL_Texture* t) const noexcept 
        {
            if (t) 
            {
                SDL_DestroyTexture(t);
            }
            t = nullptr;
        }
    };

    class SpriteAssetManager
    {
        public:
        void InitSpriteAssetManager(const SDL* sdl);
        void CreateTexture(entt::entity e, SpriteEnum se);
        const SpriteMap& GetRuntimeSpriteAssets() const { return mRuntimeSpriteAssets;}

        void DestroyTextures(entt::registry& registry);
        void RemoveEntityFromRuntime(entt::entity e);

        private:
        SpriteMap mRuntimeSpriteAssets;
        TextureMap mRuntimeTextureCache;
        const SDL* mSDL = nullptr;

        TextureHandle MakeTextureHandle(SDL_Texture* raw) 
        {
            return TextureHandle(raw, SDLTextureDeleter{});
        }
    };
}