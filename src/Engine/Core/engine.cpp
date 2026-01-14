#include "engine.h"

#include "Display/sdl.h"
#include "ECS/ecs.h"
#include "AssetManager/SpriteAssetManager.h"

#include <cstdio>

#define FRAME_DELAY 16 // 60 fps

namespace Muharrik
{
    void Engine::MainLoop()
    {
        // SDL
        Muharrik::SDL sdl;
        bool loadedImage = false;
        int error = sdl.InitSDL();
        if(error > 0)
        {
            std::printf("MainLoop: SDL Init failed: %d\n", error);
            return;
        }

        // SpriteAssetManager
        SpriteAssetManager spriteAssetManager;
        spriteAssetManager.InitSpriteAssetManager(&sdl);

        // EnTT
        Muharrik::ECS ecs;
        ecs.InitECS(&spriteAssetManager);

        //TEST
        const char* relativePath = "content/engine/test.png";
        entt::entity e = ecs.CreateSprite(relativePath, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
        std::printf("Entity: %d \n", e);

        bool running = true;
        while (running) 
        {
            sdl.RenderTexture({ spriteAssetManager.GetRuntimeSprites().data(), 
                spriteAssetManager.GetRuntimeSprites().size() }, ecs.GetRegistry());

            running = sdl.PollSDL();
            sdl.DelaySDL(FRAME_DELAY);
        }

        sdl.QuitSDL();
    }
    
}