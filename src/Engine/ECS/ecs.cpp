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

    entt::entity ECS::CreateSprite(SpriteEnum se, 
            float x, float y, float rot, float w, float h)
    {
        entt::entity e = CreateEmptyEntity();
        Sprite::CreateSpriteEntity(mRegistry, e, x, y, rot, w, h, se);
        mSpriteAssetManager->CreateTexture(e, se);

        return e;
    }

    entt::entity ECS::CreateCamera2D(float x, float y, float rot, float fov)
    {
        entt::entity e = CreateEmptyEntity();
        Camera2D::CreateCamera2DEntity(mRegistry, e, x, y, rot, fov);
        return e;
    }

    void ECS::DestroyEntity(entt::entity e)
    {
        mRegistry.destroy(e);
    }
    
}