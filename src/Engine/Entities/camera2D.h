#pragma once

#include <entt/entt.hpp>

namespace Muharrik
{
    namespace Camera2D
    {
        void CreateCamera2DEntity(entt::registry& registry, entt::entity e,
        float x, float y, float rot, float fov);
    }

}