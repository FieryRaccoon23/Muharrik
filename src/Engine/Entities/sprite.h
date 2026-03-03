#pragma once

#include <entt/entt.hpp>
#include <EASTL/string.h>

namespace Muharrik
{
    enum class SpriteEnum : int;
    
    namespace Sprite
    {
        void CreateSpriteEntity(entt::registry& registry, entt::entity e,
        float x, float y, float rot, float w, float h, SpriteEnum se);
    }

}