#include "engine.h"

#include "Display/sdl.h"
#include "ECS/ecs.h"
#include <cstdio>

#define FRAME_DELAY 16 // 60 fps

namespace Muharrik
{
    void Engine::MainLoop()
    {
        Muharrik::ECS ecs;
        ecs.InitECS();

        Muharrik::SDL sdl;
        bool loadedImage = false;
        int error = sdl.InitSDL();
        if(error > 0)
        {
            std::printf("MainLoop: SDL Init failed: %d\n", error);
            return;
        }

        bool running = true;
        while (running) 
        {
            if(!loadedImage)
            {
                const char* relativePath = "content/engine/test.png";
                sdl.LoadPNGTexture(relativePath);
                loadedImage = true;

                sdl.RenderTexture();
            }
            running = sdl.PollSDL();
            sdl.DelaySDL(FRAME_DELAY);
        }

        sdl.QuitSDL();
    }
    
}