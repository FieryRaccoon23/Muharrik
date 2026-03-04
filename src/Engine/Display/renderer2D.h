#pragma once

#include <cstdint>

#include <EASTL/string.h>
#include <EASTL/span.h>
#include <entt/entt.hpp>
#include <RmlUi/Core.h>

#include "RmlSystemInterface.h"
#include "ThirdParty/rmlui/Backends/RmlUi_Renderer_SDL.h"

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
        void RenderTexture(const SpriteAssetManager* spriteAssetManager, 
            entt::registry& registry, const entt::entity camera2DEntity);
        void ToggleFullScreen() const;

        private:
        void InitRML();

        SDL_Window* mWindow = nullptr;
        SDL_Renderer* mRenderer = nullptr;
        eastl::string mBasePath;

        RmlSystemInterface mRmlSystem;
        std::optional<RenderInterface_SDL> mRmlRenderer;
        Rml::Context* mRmlContext = nullptr;
    };
}