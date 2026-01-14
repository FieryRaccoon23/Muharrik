#pragma once

#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>

#define MAX_TEXTURE_ASSETS 50

struct SDL_Texture;

namespace Muharrik
{
    class SDL;

    using TexturePtrVec = eastl::fixed_vector<SDL_Texture*, MAX_TEXTURE_ASSETS, false>;

    class TextureAssetManager
    {
        public:
        void InitTextureAssetManager(const SDL* sdl);
        int CreateTexture(eastl::string path);
        const TexturePtrVec GetRuntimeTextures() const { return mRuntimeTextureData;}

        ~TextureAssetManager();

        private:
        TexturePtrVec mRuntimeTextureData;
        const SDL* mSDL = nullptr;
    };
}