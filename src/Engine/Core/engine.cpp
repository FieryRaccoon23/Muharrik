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

        // Delegates
        //OnCreateEmptyEntityDelegate.connect<&Engine::OnCreateEmptyEntity>(this);
        //OnCreateSpriteEntityDelegate.connect<&Engine::OnCreateSpriteEntity>(this);
    }

    void Engine::MainLoop(IGame& game)
    {
        bool running = true;

        game.Init(this);

        while (running) 
        {
            mSDL.RenderTexture({ mSpriteAssetManager.GetRuntimeSprites().data(), 
                mSpriteAssetManager.GetRuntimeSprites().size() }, mECS.GetRegistry());

            running = mSDL.PollSDL();

            // NOTE: Pass correct frame rate
            game.Update(0.0f);

            mSDL.DelaySDL(FRAME_DELAY);
        }

        game.Finish();

    }

    void Engine::QuitEngine()
    {
        mSDL.QuitSDL();
        mSpriteAssetManager.DestroySpriteAssetManager(mECS.GetRegistry());
        mSceneManager.QuiteSceneManager();
    }

    int Engine::OnAddEntitiesToSceneManager(EntitiesVec entities)
    {
        return mSceneManager.AddScene(entities);
    }

    entt::entity Engine::OnCreateEmptyEntity()
    {
        return mECS.CreateEmptyEntity();
    }
    
    entt::entity Engine::OnCreateSpriteEntity(const eastl::string& path, 
            float x, float y, float rot, float w, float h)
    {
        entt::entity e = mECS.CreateEmptyEntity();
        mECS.CreateSprite(e, path, x, y, rot, w, h);

        return e;
    }
}