#pragma once
#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace Muharrik
{
    class SDL
    {
        public:
        int InitSDL();
        bool PollSDL();
        void QuitSDL();
        void DelaySDL(uint32_t ms);
        void LoadPNGTexture(const char* relativePath);
        void RenderTexture();

        private:
        SDL_Window* mWindow = nullptr;
        SDL_Renderer* mRenderer = nullptr;
        SDL_Texture* mTexture = nullptr;
    };
}