#pragma once

#include "InputBindings.h"

#include <SDL3/SDL.h>

namespace Muharrik
{
    class InputHandler
    {
        public:
        void InitInputHandler();
        void UpdateInputHandler();

        bool IsActionPressed(InputAction action) const
        {
            SDL_Scancode code = gKeyBindings[action];
            return (mCurrentKeyStates[code] && !mPreviousKeyStates[code]);
        }

        bool IsActionDown(InputAction action) const
        {
            SDL_Scancode code = gKeyBindings[action];
            return mCurrentKeyStates[code];
        }

        bool IsActionReleased(InputAction action) const
        {
            SDL_Scancode code = gKeyBindings[action];
            return (!mCurrentKeyStates[code] && mPreviousKeyStates[code]);
        }

        private:
        const bool* mCurrentKeyStates;
        Uint8 mPreviousKeyStates[SDL_SCANCODE_COUNT];
    };
}