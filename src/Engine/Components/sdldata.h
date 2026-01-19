#pragma once

#include "AssetManager/SpriteSerializedData.h"

struct SDL_Texture;

namespace Muharrik
{
    struct SDLData
    {
        public:
        SpriteEnum mTextureID = SpriteEnum::NONE;

        ~SDLData()
        {
            mTextureID = SpriteEnum::NONE;
        }
    };
}