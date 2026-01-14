#pragma once

#include <entt/entt.hpp>
#include <EASTL/string.h>

namespace Muharrik
{
    class SpriteAssetManager;

    class ECS
    {
        public:
        void InitECS(SpriteAssetManager* value);

        // Factory constructors for entities

        entt::entity CreateSprite(const eastl::string& path, 
            float x, float y, float rot, float w, float h);

        entt::registry& GetRegistry() { return mRegistry;}

        private:
        entt::registry mRegistry;
        SpriteAssetManager* mSpriteAssetManager = nullptr;
    };
}