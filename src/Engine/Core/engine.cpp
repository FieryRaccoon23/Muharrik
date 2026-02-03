#include "engine.h"

#include "factory.h"

#include <cstdio>

#define FRAME_DELAY 16 // 60 fps

namespace Muharrik
{
    void Engine::InitEngine()
    {
        // SDL
        bool loadedImage = false;
        int error = mSDL.InitSDL();
        if(error > 0)
        {
            std::printf("MainLoop: SDL Init failed: %d\n", error);
            return;
        }

        // SpriteAssetManager
        mSpriteAssetManager.InitSpriteAssetManager(&mSDL);

        // EnTT
        mECS.InitECS(&mSpriteAssetManager);

        // Scenes
        mSceneManager.InitSceneManager();

        //Input
        mInputHandler.InitInputHandler();

        // Delegates
        //OnCreateEmptyEntityDelegate.connect<&Engine::OnCreateEmptyEntity>(this);
        //OnCreateSpriteEntityDelegate.connect<&Engine::OnCreateSpriteEntity>(this);
    }

    void Engine::QuitEngine()
    {
        mSDL.QuitSDL();
        mSpriteAssetManager.DestroyTextures(mECS.GetRegistry());
        mSceneManager.ClearScenes();
    }

    entt::entity Engine::OnCreateEmptyEntity()
    {
        return mECS.CreateEmptyEntity();
    }
    
    entt::entity Engine::OnCreateSpriteEntity(SpriteEnum se, 
            float x, float y, float rot, float w, float h)
    {
        entt::entity e = mECS.CreateEmptyEntity();
        mECS.CreateSprite(e, se, x, y, rot, w, h);

        return e;
    }

    void Engine::OnDestroyEntities(const EntitiesVec& entities)
    {
        TracyProfiler::Tracy_ZoneScopedNamed("Engine::OnDestroyEntities");

        for (entt::entity e : entities)
        {
            mSpriteAssetManager.RemoveEntityFromRuntime(e, mECS.GetRegistry());
            mECS.DestroyEntity(e);
        }
    }

    int Engine::OnAddEntitiesToSceneManager(const EntitiesVec& entities)
    {
        return mSceneManager.AddScene(entities);
    }

    void Engine::OnRemoveSceneFromSceneManager(int i)
    {
        OnDestroyEntities(mSceneManager.GetEntitiesOfScene(i));
        mSceneManager.RemoveScene(i);
    }
}