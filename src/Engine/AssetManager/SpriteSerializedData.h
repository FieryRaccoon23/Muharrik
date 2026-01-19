#pragma once

#include <EASTL/fixed_hash_map.h>
#include <EASTL/string.h>
#include <entt/entt.hpp>

namespace Muharrik
{
    enum class SpriteEnum : int
    {
        NONE = -1,
        Test_Duck,
        Test_Pigeon,

        MAX_COUNT
    };

    inline static eastl::fixed_hash_map<
        int,
        eastl::string,
        (int)SpriteEnum::MAX_COUNT,
        (int)SpriteEnum::MAX_COUNT * 2,
        false
    > gSpriteAssets{
        { (int)SpriteEnum::Test_Duck,     eastl::string("content/engine/test.png") },
        { (int)SpriteEnum::Test_Pigeon,      eastl::string("content/engine/test2.png")  }
    };

}