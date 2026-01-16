#pragma once

namespace Muharrik
{
    class Engine;
}

namespace MuharrikGame
{
    class GameScenes
    {
        public:
        void InitScenes(Muharrik::Engine* engine);
        void SetStartupScenes();
    };
}