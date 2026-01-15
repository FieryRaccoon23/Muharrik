#pragma once

#include <SDL3_image/SDL_image.h>

struct SDL_Texture;

namespace Muharrik
{
    struct SDLData
    {
        public:
        SDL_Texture* mTexture = nullptr;

        ~SDLData()
        {
            SDL_DestroyTexture(mTexture);
            mTexture = nullptr;
        }
    };
}