#pragma once

#include <entt/entt.hpp>
#include <SDL3_image/SDL_image.h>
#include <EASTL/string.h>
#include <EASTL/fixed_hash_map.h>
#include <EASTL/fixed_vector.h>

#include "SpriteSerializedData.h"

#define MAX_TEXTURE_ASSETS 50
#define MAX_ENTITIES_PER_TEXTURE 100

struct SDL_Texture;

namespace Muharrik
{
    class SDL;

    // Dictionary to convert sprite enum to sdl texture
    using TextureMap = eastl::fixed_hash_map<
        SpriteEnum,
        SDL_Texture*,
        MAX_TEXTURE_ASSETS,
        MAX_TEXTURE_ASSETS * 2,
        false
    >;

    using TextureEntityVector = eastl::fixed_vector<
        entt::entity,
        MAX_ENTITIES_PER_TEXTURE,
        false
    >;

    // Vector to hold all entities using the same texture
    using BatchedSpriteAssets = eastl::fixed_vector<
        TextureEntityVector,
        MAX_TEXTURE_ASSETS,
        false
    >;

    class SpriteAssetManager
    {
        public:
        void InitSpriteAssetManager(const SDL* sdl);
        void CreateTexture(entt::entity e, SpriteEnum se);
        const TextureMap& GetRuntimeTextureAssets() const { return mRuntimeTextureCache;}
        const BatchedSpriteAssets& GetRuntimeBatchedSpriteAssets() const { return mRuntimeBatchedSprites;}

        void DestroyTextures(entt::registry& registry);
        void RemoveEntityFromRuntime(entt::entity e, entt::registry& registry);

        private:
        TextureMap mRuntimeTextureCache;
        BatchedSpriteAssets mRuntimeBatchedSprites;
        const SDL* mSDL = nullptr;

    };
}