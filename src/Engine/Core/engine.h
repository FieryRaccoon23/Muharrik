#pragma once

#include "IGame.h"
#include "Display/sdl.h"
#include "ECS/ecs.h"
#include "AssetManager/SpriteAssetManager.h"
#include "AssetManager/SpriteSerializedData.h"
#include "Scene/SceneManager.h"

namespace Muharrik
{
    class Engine
    {
        public:
        void InitEngine();
        void MainLoop(IGame& game);
        void QuitEngine();

        entt::entity OnCreateEmptyEntity();
        entt::entity OnCreateSpriteEntity(SpriteEnum se, 
            float x, float y, float rot, float w, float h);
        void OnDestroyEntities(const EntitiesVec& entities);
        int OnAddEntitiesToSceneManager(const EntitiesVec& entities);
        void OnRemoveSceneFromSceneManager(int i);

        private:
        Muharrik::SDL mSDL;
        SpriteAssetManager mSpriteAssetManager;
        Muharrik::ECS mECS;
        SceneManager mSceneManager;
    };
}