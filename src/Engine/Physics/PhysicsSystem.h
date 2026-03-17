#pragma once

#include <mujoco/mujoco.h>

namespace Muharrik
{
    class PhysicsSystem
    {
        public:
            void Init(const char* modelPath);
            void Step(float dt);
            void Quit();

        private:
            mjData*  mData  = nullptr;
            mjModel* mModel = nullptr;
    };
}