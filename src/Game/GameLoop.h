#pragma once

#include "Core/IGame.h"

namespace MuharrikGame
{
    class GameLoop : public Muharrik::IGame
    {
        public:
        void Init() override;
        void Start() override;
        void Update(float dt) override;
        void End() override;
        void Finish() override;
    };
}