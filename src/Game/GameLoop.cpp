#include "GameLoop.h"

#include "Core/engine.h"
#include "Input/InputHandler.h"

#include "GameScenes.h"

#include <entt/entt.hpp>
#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>
#include <cstdio>

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
        static int i = 0;

        if(i == 100)
        {
            mEngine->OnRemoveSceneFromSceneManager(0);
            GameScenes gameScene;
            gameScene.AnotherScene(mEngine);
        }
        ++i;

        // Add in player input
        if ((mEngine->GetInputHandler().IsActionDown(Muharrik::InputAction::LAlt) ||
            mEngine->GetInputHandler().IsActionDown(Muharrik::InputAction::RAlt)) &&
            mEngine->GetInputHandler().IsActionPressed(Muharrik::InputAction::Enter))
        {
            mEngine->GetSDL().ToggleFullScreen();
        }   
    }

    void GameLoop::End()
    {
    }

    void GameLoop::Finish()
    {
    }
    
}