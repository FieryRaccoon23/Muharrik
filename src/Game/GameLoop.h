#pragma once

#include <entt/entt.hpp>
#include "Core/IGame.h"
#include "Components/position2D.h"

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
        entt::entity mCamera2DEntity;
        Muharrik::Position2D* mCameraPos;
    };
}