#pragma once
#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;

namespace Muharrik
{
    class SDL
    {
        public:
        int InitSDL();
        bool PollSDL();
        void QuitSDL();
        void DelaySDL(uint32_t ms);
        void LoadPNGTexture(const char* path);

        private:
        SDL_Window* mWindow = nullptr;
        SDL_Renderer* mRenderer = nullptr;
    };
}