#pragma once

#include <entt/entt.hpp>
#include <string>
#include "Entities/entities.h"

namespace Muharrik
{
    class ECS
    {
        public:
        void InitECS();

        // Factory constructors for entities

        Sprite CreateSprite(std::string path, float x, float y, float rot);

        private:
        entt::registry mRegistry;
    };
}