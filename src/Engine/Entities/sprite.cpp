#include "sprite.h"

#include "Components/position2D.h"
#include "Components/rotation2D.h"
#include "Components/scale2D.h"
#include "Components/sdldata.h"

namespace Muharrik
{
    namespace Sprite
    {
        void CreateSpriteEntity(entt::registry& registry, entt::entity e,
            float x, float y, float rot, float w, float h)
        {
            registry.emplace<Position2D>(e, x, y);
            registry.emplace<Rotation2D>(e, rot);
            registry.emplace<Scale2D>(e, w, h);
            registry.emplace<SDLData>(e);
        }
    }
}
