#pragma once

#include <entt/entt.hpp>
#include <EASTL/string.h>

#include "AssetManager/SpriteSerializedData.h"

namespace Muharrik
{
    class SpriteAssetManager;

    class ECS
    {
        public:
        void InitECS(SpriteAssetManager* value);

        // Factory constructors for entities

        entt::entity CreateSprite(SpriteEnum se,
            float x, float y, float rot, float w, float h);

        entt::entity CreateCamera2D(float x, float y, float rot, float fov);

        entt::entity CreateEmptyEntity();
        void DestroyEntity(entt::entity e);

        entt::registry& GetRegistry() { return mRegistry;}
        const entt::registry& GetRegistry() const { return mRegistry; }

        private:
        entt::registry mRegistry;
        SpriteAssetManager* mSpriteAssetManager = nullptr;
    };
}