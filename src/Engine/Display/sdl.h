#pragma once

#include <cstdint>

#include <EASTL/string.h>
#include <EASTL/span.h>

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
        SDL_Texture* LoadPNGTexture (const char* relativePath) const;
        void RenderTexture(eastl::span<SDL_Texture* const> textures);

        private:
        SDL_Window* mWindow = nullptr;
        SDL_Renderer* mRenderer = nullptr;
        eastl::string mBasePath;
    };
}