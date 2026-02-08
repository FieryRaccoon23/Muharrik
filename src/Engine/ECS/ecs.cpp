#include "ecs.h"

#include "Entities/sprite.h"
#include "Entities/camera2D.h"
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

    void ECS::CreateCamera2D(entt::entity e,
            float x, float y, float rot, float fov)
    {
        Camera2D::CreateCamera2DEntity(mRegistry, e, x, y, rot, fov);
    }

    void ECS::DestroyEntity(entt::entity e)
    {
        mRegistry.destroy(e);
    }
    
}