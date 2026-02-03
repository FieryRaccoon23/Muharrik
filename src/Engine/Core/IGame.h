#pragma once

namespace Muharrik
{
    class Engine;

    template<class Derived>
    class IGame
    {
        public:
        void Init(Engine* engine)
        {
            static_cast<Derived*>(this)->InitImpl(engine); 
        }

        void Start()
        {
            static_cast<Derived*>(this)->StartImpl(); 
        }

        void Update(float dt)
        {
            static_cast<Derived*>(this)->UpdateImpl(dt); 
        }

        void End()
        {
            static_cast<Derived*>(this)->EndImpl(); 
        }

        void Finish()
        {
            static_cast<Derived*>(this)->FinishImpl(); 
        }

        protected:
        IGame() = default;
        ~IGame() = default;
    };
}