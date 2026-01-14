#pragma once

#include <entt/entt.hpp>
#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>

#define MAX_ENTITIES 50

namespace Muharrik
{
    class Scene
    {
        using EntitiesVec = eastl::fixed_vector<int, MAX_ENTITIES, false>;

        public:
        Scene(){}
        ~Scene(){}

        private:
        EntitiesVec mEntitiesVector;
        int mID = -1;
    };

}