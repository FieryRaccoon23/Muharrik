#include "ecs.h"

#include <entt/entt.hpp>
#include <cstdio>
#include <iostream>

namespace Muharrik
{
    struct Position { float x{}, y{}; };
    struct Velocity { float dx{}, dy{}; };

    void ECS::TestEntity()
    {
        entt::registry reg;

        // Create an entity and attach components
        auto e = reg.create();
        reg.emplace<Position>(e, 1.0f, 2.0f);
        reg.emplace<Velocity>(e, 0.5f, -0.25f);

    }
    
}