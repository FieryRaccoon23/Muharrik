#pragma once
#include "Config/MuharrikConfig.h"

#if MUHARRIK_ENABLE_RMLUI
#include <RmlUi/Core/SystemInterface.h>
#include <SDL3/SDL.h>

namespace Muharrik
{
    class RmlSystemInterface : public Rml::SystemInterface 
    {
        public:
        double GetElapsedTime() override { return SDL_GetTicks() / 1000.0;}
    };
}
#endif