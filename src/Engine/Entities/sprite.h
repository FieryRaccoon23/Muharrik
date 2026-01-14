#pragma once

#include <entt/entt.hpp>
#include <EASTL/string.h>

namespace Muharrik
{
    namespace Sprite
    {
        entt::entity CreateSpriteEntity(entt::registry& registry, 
        float x, float y, float rot, float w, float h);
    }

}