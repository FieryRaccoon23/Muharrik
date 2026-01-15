#include "ecs.h"

#include "Entities/sprite.h"
#include "AssetManager/SpriteAssetManager.h"

// #include <taskflow/taskflow.hpp>

namespace Muharrik
{
    void ECS::InitECS(SpriteAssetManager* value)
    {
        mSpriteAssetManager = value;
    }

    entt::entity ECS::CreateEmptyEntity()
    {
        entt::entity e = mRegistry.create();
        return e;
    }

    void ECS::CreateSprite(entt::entity e, const eastl::string& path, 
            float x, float y, float rot, float w, float h)
    {
        Sprite::CreateSpriteEntity(mRegistry, e, x, y, rot, w, h);

        int idx = mSpriteAssetManager->CreateTexture(mRegistry, e, path);
    }
    
}