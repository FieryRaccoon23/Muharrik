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

        void CreateSprite(entt::entity e, SpriteEnum se,
            float x, float y, float rot, float w, float h);

        void CreateCamera2D(entt::entity e,
            float x, float y, float rot, float fov);

        entt::entity CreateEmptyEntity();
        void DestroyEntity(entt::entity e);

        entt::registry& GetRegistry() { return mRegistry;}
        const entt::registry& GetRegistry() const { return mRegistry; }

        private:
        entt::registry mRegistry;
        SpriteAssetManager* mSpriteAssetManager = nullptr;
    };
}