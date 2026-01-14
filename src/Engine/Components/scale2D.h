#pragma once

#include <glm/glm.hpp>

namespace Muharrik
{
    struct Scale2D
    {
        public:
        Scale2D() : mValue(1.0f, 1.0f) 
        {
        }
        Scale2D(float x, float y) : mValue(x, y) 
        {
        }

        Scale2D& operator=(const Scale2D&) = default;
        Scale2D& operator=(Scale2D&&) noexcept = default;

        glm::vec2 mValue;
    };
}