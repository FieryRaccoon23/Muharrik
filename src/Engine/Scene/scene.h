#pragma once

#include <entt/entt.hpp>
#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>

#define MAX_ENTITIES 50

namespace Muharrik
{
    using EntitiesVec = eastl::fixed_vector<entt::entity, MAX_ENTITIES, false>;

    class Scene
    {
        public:
        Scene(){}
        ~Scene(){}
        void AddEntities(const EntitiesVec& entities);

        private:
        EntitiesVec mEntitiesVector;
        int mID = -1;
    };

}