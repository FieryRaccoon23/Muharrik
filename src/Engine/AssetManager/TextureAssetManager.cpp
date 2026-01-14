#include "TextureAssetManager.h"

#include "Display/sdl.h"
#include <SDL3_image/SDL_image.h>

namespace Muharrik
{
    void TextureAssetManager::InitTextureAssetManager(const SDL* sdl)
    {
        mSDL = sdl;
    }

    int TextureAssetManager::CreateTexture(eastl::string path)
    {
        SDL_Texture* texture = mSDL->LoadPNGTexture(path.c_str());
        mRuntimeTextureData.push_back(texture);
        return mRuntimeTextureData.size() - 1;
    }

    TextureAssetManager::~TextureAssetManager()
    {
        for(auto t : mRuntimeTextureData)
        {
            SDL_DestroyTexture(t);
        }

        mRuntimeTextureData.clear();
    }
}