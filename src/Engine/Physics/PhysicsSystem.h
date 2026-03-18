#pragma once

#include <mujoco/mujoco.h>

namespace Muharrik
{
    class PhysicsSystem
    {
        public:
            void Init();
            void Step(float dt);
            void Quit();

        private:
            mjData*  mData  = nullptr;
            mjModel* mModel = nullptr;
            static constexpr const char* const mModelPath = "";
    };
}