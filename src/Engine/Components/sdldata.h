#pragma once

#include "AssetManager/SpriteSerializedData.h"

struct SDL_Texture;

namespace Muharrik
{
    struct SDLData
    {
        public:
        SDLData() : mTextureID(SpriteEnum::NONE) 
        {
        }
        SDLData(SpriteEnum value) : mTextureID(value) 
        {
        }

        ~SDLData()
        {
            mTextureID = SpriteEnum::NONE;
        }

        SpriteEnum mTextureID = SpriteEnum::NONE;

    };
}