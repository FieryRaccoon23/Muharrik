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

    void ECS::CreateSprite(entt::entity e, SpriteEnum se, 
            float x, float y, float rot, float w, float h)
    {
        Sprite::CreateSpriteEntity(mRegistry, e, x, y, rot, w, h);

        mSpriteAssetManager->CreateTexture(e, se);
    }

    void ECS::DestroyEntity(entt::entity e)
    {
        mRegistry.destroy(e);
    }
    
}