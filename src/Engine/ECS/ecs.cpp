#include "ecs.h"

#include "Components/position2D.h"
#include "Components/rotation2D.h"

// #include <taskflow/taskflow.hpp>

namespace Muharrik
{
    // void ECS::TestEntity()
    // {
    //     // entt::registry reg;
    //     // entt::entity ent = reg.create();
    //     // reg.emplace<Position2D>(ent, 1.0f, 2.0f);
    //     // reg.emplace<Rotation2D>(ent, 1.0f);

    //     // Position2D& pos = reg.get<Position2D>(ent);
    //     // pos = Position2D(5.0f, 6.0f);

    //     // Rotation2D& rot = reg.get<Rotation2D>(ent);
    //     // rot = Rotation2D(5.0f);
    // }

    void ECS::InitECS()
    {

    }

    Sprite ECS::CreateSprite(std::string path, float x, float y, float rot)
    {
        Sprite s = mRegistry.create();
        mRegistry.emplace<Position2D>(s, x, y);
        mRegistry.emplace<Rotation2D>(s, rot);
        return s;
    }
    
}