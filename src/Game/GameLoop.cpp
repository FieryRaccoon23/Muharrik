#include "GameLoop.h"

#include "Core/engine.h"
//#include "Core/factory.h"

#include "GameScenes.h"

#include <entt/entt.hpp>
#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>

namespace MuharrikGame
{
    void GameLoop::Init(Muharrik::Engine* engine)
    {
        GameScenes gameScene;
        mEngine = engine;
        gameScene.InitScenes(mEngine);
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