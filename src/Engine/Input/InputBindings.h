#pragma once

#include <SDL3/SDL.h>
#include <EASTL/fixed_hash_map.h>
#include <EASTL/utility.h>

namespace Muharrik
{
    enum class InputAction : int
    {
        NONE = -1,

        LAlt,
        RAlt,
        Enter,

        MAX_COUNT
    };


    using KeyBindingMap = eastl::fixed_hash_map<
    InputAction,
    SDL_Scancode,
    SDL_SCANCODE_COUNT,
    SDL_SCANCODE_COUNT * 2,
    false
    >;

    inline static KeyBindingMap gKeyBindings{
        { InputAction::LAlt, SDL_Scancode::SDL_SCANCODE_LALT },
        { InputAction::RAlt, SDL_Scancode::SDL_SCANCODE_RALT },
        { InputAction::Enter, SDL_Scancode::SDL_SCANCODE_RETURN }
    };

}