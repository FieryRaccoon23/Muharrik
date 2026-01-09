#include "engine.h"

#include "sdl.h"
#include <cstdio>

#define FRAME_DELAY 16 // 60 fps

namespace Muharrik
{
    void Engine::MainLoop()
    {
        Muharrik::SDL sdl;

        int error = sdl.InitSDL();

        if(error > 0)
        {
            std::printf("MainLoop: SDL Init failed: %d\n", error);
            return;
        }

        bool running = true;
        while (running) 
        {
            running = sdl.PollSDL();
            sdl.DelaySDL(FRAME_DELAY);
        }

        sdl.QuitSDL();
    }
    
}