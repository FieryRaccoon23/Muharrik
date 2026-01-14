#include "sprite.h"

#include "Components/position2D.h"
#include "Components/rotation2D.h"
#include "Components/scale2D.h"
#include "Components/sdldata.h"

namespace Muharrik
{
    namespace Sprite
    {
        entt::entity CreateSpriteEntity(entt::registry& registry, 
            float x, float y, float rot, float w, float h)
        {
            entt::entity e = registry.create();
            registry.emplace<Position2D>(e, x, y);
            registry.emplace<Rotation2D>(e, rot);
            registry.emplace<Scale2D>(e, w, h);
            registry.emplace<SDLData>(e);
            return e;
        }
    }
}
