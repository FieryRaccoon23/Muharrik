#pragma once

namespace Muharrik
{
    class IGame
    {
        public:
        virtual ~IGame() = default;
        virtual void Init() = 0;
        virtual void Start() = 0;
        virtual void Update(float dt) = 0;
        virtual void End() = 0;
        virtual void Finish() = 0;
    };
}