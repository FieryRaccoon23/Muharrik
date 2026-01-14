#pragma once

#include <glm/glm.hpp>

namespace Muharrik
{
    struct Position2D
    {
        public:
        Position2D() : mValue(0.0f, 0.0f) 
        {
        }
        Position2D(float x, float y) : mValue(x, y) 
        {
        }

        Position2D& operator=(const Position2D&) = default;
        Position2D& operator=(Position2D&&) noexcept = default;

        glm::vec2 mValue;
    };
}