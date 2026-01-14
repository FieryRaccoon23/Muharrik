#include "engine.h"

#include "Display/sdl.h"
#include "ECS/ecs.h"
#include "AssetManager/TextureAssetManager.h"

#include <cstdio>

#define FRAME_DELAY 16 // 60 fps

namespace Muharrik
{
    void Engine::MainLoop()
    {
        // EnTT
        Muharrik::ECS ecs;
        ecs.InitECS();

        // SDL
        Muharrik::SDL sdl;
        bool loadedImage = false;
        int error = sdl.InitSDL();
        if(error > 0)
        {
            std::printf("MainLoop: SDL Init failed: %d\n", error);
            return;
        }

        // TextureAssetManager
        TextureAssetManager textureAssetManager;
        textureAssetManager.InitTextureAssetManager(&sdl);

        //TEST
        const char* relativePath = "content/engine/test.png";
        textureAssetManager.CreateTexture(relativePath);

        bool running = true;
        while (running) 
        {
            sdl.RenderTexture({ textureAssetManager.GetRuntimeTextures().data(), 
                textureAssetManager.GetRuntimeTextures().size() });

            running = sdl.PollSDL();
            sdl.DelaySDL(FRAME_DELAY);
        }

        sdl.QuitSDL();
    }
    
}