#pragma once

#include "IGame.h"
#include "Display/sdl.h"
#include "ECS/ecs.h"
#include "AssetManager/SpriteAssetManager.h"
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
        entt::entity OnCreateSpriteEntity(const eastl::string& path, 
            float x, float y, float rot, float w, float h);
        int OnAddEntitiesToSceneManager(EntitiesVec entities);

        private:
        Muharrik::SDL mSDL;
        SpriteAssetManager mSpriteAssetManager;
        Muharrik::ECS mECS;
        SceneManager mSceneManager;
    };
}