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

        void CreateSprite(entt::entity e, const eastl::string& path, 
            float x, float y, float rot, float w, float h);

        entt::entity CreateEmptyEntity();

        entt::registry& GetRegistry() { return mRegistry;}
        const entt::registry& GetRegistry() const { return mRegistry; }

        private:
        entt::registry mRegistry;
        SpriteAssetManager* mSpriteAssetManager = nullptr;
    };
}