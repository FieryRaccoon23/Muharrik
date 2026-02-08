#include "camera2D.h"

#include "Components/position2D.h"
#include "Components/rotation2D.h"
#include "Components/fov.h"

namespace Muharrik
{
    namespace Camera2D
    {
        void CreateCamera2DEntity(entt::registry& registry, entt::entity e,
            float x, float y, float rot, float fov)
        {
            registry.emplace<Position2D>(e, x, y);
            registry.emplace<Rotation2D>(e, rot);
            registry.emplace<FoV>(e, fov);
        }
    }
}
