#include "InputHandler.h"

#include <cstring> 

namespace Muharrik
{
    void InputHandler::InitInputHandler()
    {
        mCurrentKeyStates = SDL_GetKeyboardState(NULL);
        std::memset(mPreviousKeyStates, 0, sizeof(mPreviousKeyStates));
    }

    void InputHandler::UpdateInputHandler()
    {
        std::memcpy(mPreviousKeyStates, mCurrentKeyStates, sizeof(mPreviousKeyStates));
    }
}