#pragma once
#include <cstdint>

struct SDL_Window;

namespace Muharrik
{
    class SDL
    {
        public:
        int InitSDL();
        bool PollSDL();
        void QuitSDL();
        void DelaySDL(uint32_t ms);

        private:
        SDL_Window* mWindow = nullptr;
    };
}