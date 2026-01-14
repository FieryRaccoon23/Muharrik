#pragma once

#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>
#include <entt/entt.hpp>

#define MAX_TEXTURE_ASSETS 50

struct SDL_Texture;

namespace Muharrik
{
    class SDL;

    using SpriteVec = eastl::fixed_vector<entt::entity, MAX_TEXTURE_ASSETS, false>;

    class SpriteAssetManager
    {
        public:
        void InitSpriteAssetManager(const SDL* sdl);
        int CreateTexture(entt::registry& registry, entt::entity e, const eastl::string& path);
        SpriteVec GetRuntimeSprites() const { return mRuntimeSpritesData;}

        void DestroySpriteAssetManager(entt::registry& registry);

        private:
        SpriteVec mRuntimeSpritesData;
        const SDL* mSDL = nullptr;
    };
}