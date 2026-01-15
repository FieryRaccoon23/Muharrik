#pragma once

#include <entt/signal/delegate.hpp>
#include <entt/entt.hpp>
#include <EASTL/string.h>

namespace Muharrik
{
    using CreateSpriteEntityDelegate = entt::delegate<
                                            entt::entity(
                                                const eastl::string&,
                                                float, float, float, float, float
                                                )
                                            >;

    using CreateEmptyEntityDelegate = entt::delegate<entt::entity(void)>;

    extern CreateEmptyEntityDelegate OnCreateEmptyEntityDelegate;

    extern CreateSpriteEntityDelegate OnCreateSpriteEntityDelegate;

}