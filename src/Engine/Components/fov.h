#pragma once

namespace Muharrik
{
    struct FoV
    {
        public:
        FoV() : mValue(0.0f) 
        {
        }
        FoV(float value) : mValue(value) 
        {
        }

        FoV& operator=(const FoV&) = default;
        FoV& operator=(FoV&&) noexcept = default;

        float mValue;
    };
}