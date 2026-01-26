#pragma once

#define ENABLE_TRACY_PROFILING false

#include <cstring>

#if ENABLE_TRACY_PROFILING
#include <tracy/Tracy.hpp>
#endif

namespace Muharrik
{
    class TracyProfiler
    {
        public:
        static void Tracy_ZoneScopedNamed(const char* name)
        {
            #if ENABLE_TRACY_PROFILING
            ZoneScoped;
            ZoneName(name, std::strlen(name));
            #endif
        }

        static void Tracy_SetThreadName(const char* name)
        {
            #if ENABLE_TRACY_PROFILING
            tracy::SetThreadName(name);
            #endif
        }

        static void Tracy_FrameMark()
        {
            #if ENABLE_TRACY_PROFILING
            FrameMark;
            #endif
        }

        static void Tracy_TracyPlot(const char* name, float value)
        {
            #if ENABLE_TRACY_PROFILING
            TracyPlot(name, value);
            #endif
        }
    };
}