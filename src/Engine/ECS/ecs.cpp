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

    entt::entity ECS::CreateSprite(const eastl::string& path, 
        float x, float y, float rot, float w, float h)
    {
        entt::entity e = Sprite::CreateSpriteEntity(mRegistry, x, y, rot, w, h);

        int idx = mSpriteAssetManager->CreateTexture(mRegistry, e, path);

        return e;
    }
    
}