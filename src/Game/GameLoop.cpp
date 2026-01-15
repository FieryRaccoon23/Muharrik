#include "GameLoop.h"

#include "Core/factory.h"

#include <entt/entt.hpp>
#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>

namespace MuharrikGame
{
    void GameLoop::Init()
    {
        //TEST
        const char* relativePath = "content/engine/test.png";
        entt::entity e = Muharrik::OnCreateSpriteEntityDelegate(relativePath, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f);
    }

    void GameLoop::Start()
    {
    }

    void GameLoop::Update(float dt)
    {
    }

    void GameLoop::End()
    {
    }

    void GameLoop::Finish()
    {
    }
    
}