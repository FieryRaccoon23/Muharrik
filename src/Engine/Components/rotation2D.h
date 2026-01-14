#pragma once

namespace Muharrik
{
    struct Rotation2D
    {
        public:
        Rotation2D() : mValue(0.0f) 
        {
        }
        Rotation2D(float value) : mValue(value) 
        {
        }

        Rotation2D& operator=(const Rotation2D&) = default;
        Rotation2D& operator=(Rotation2D&&) noexcept = default;

        float mValue;
    };
}