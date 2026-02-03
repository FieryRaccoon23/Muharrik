#pragma once

#include "Core/IGame.h"

namespace Muharrik
{
    class Engine;
}

namespace MuharrikGame
{
    class GameLoop : public Muharrik::IGame<MuharrikGame::GameLoop>
    {
        public:
        void InitImpl(Muharrik::Engine* engine);
        void StartImpl();
        void UpdateImpl(float dt);
        void EndImpl();
        void FinishImpl();

        private:
        Muharrik::Engine* mEngine;

    };
}