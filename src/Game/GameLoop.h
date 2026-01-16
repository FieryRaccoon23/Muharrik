#pragma once

#include "Core/IGame.h"

namespace Muharrik
{
    class Engine;
}

namespace MuharrikGame
{
    class GameLoop : public Muharrik::IGame
    {
        public:
        void Init(Muharrik::Engine* engine) override;
        void Start() override;
        void Update(float dt) override;
        void End() override;
        void Finish() override;

        private:
        Muharrik::Engine* mEngine;

    };
}