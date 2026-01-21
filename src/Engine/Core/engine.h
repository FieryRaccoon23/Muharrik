#pragma once

#include "IGame.h"
#include "Display/sdl.h"
#include "ECS/ecs.h"
#include "AssetManager/SpriteAssetManager.h"
#include "AssetManager/SpriteSerializedData.h"
#include "Scene/SceneManager.h"
#include "Input/InputHandler.h"

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

        const InputHandler& GetInputHandler() const { return mInputHandler;}
        const Muharrik::SDL& GetSDL() const { return mSDL;}

        private:
        Muharrik::SDL mSDL;
        SpriteAssetManager mSpriteAssetManager;
        Muharrik::ECS mECS;
        SceneManager mSceneManager;
        InputHandler mInputHandler;
    };
}