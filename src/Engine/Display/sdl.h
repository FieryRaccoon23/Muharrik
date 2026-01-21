#pragma once

#include <cstdint>

#include <EASTL/string.h>
#include <EASTL/span.h>
#include <entt/entt.hpp>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace Muharrik
{
    class SpriteAssetManager;
    
    class SDL
    {
        public:
        int InitSDL();
        bool PollSDL();
        void QuitSDL();
        void DelaySDL(uint32_t ms);
        SDL_Texture* LoadPNGTexture (const char* relativePath) const;
        void RenderTexture(const SpriteAssetManager* spriteAssetManager, entt::registry& registry);
        void ToggleFullScreen() const;

        private:
        SDL_Window* mWindow = nullptr;
        SDL_Renderer* mRenderer = nullptr;
        eastl::string mBasePath;
    };
}