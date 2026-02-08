#include "GameLoop.h"

#include "Core/engine.h"
#include "Input/InputHandler.h"

#include "GameScenes.h"

#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>
#include <cstdio>

namespace MuharrikGame
{
    void GameLoop::InitImpl(Muharrik::Engine* engine)
    {
        GameScenes gameScene;
        mEngine = engine;
        gameScene.InitScenes(mEngine);

        mCamera2DEntity = mEngine->GetCamera2DEntity();
        mCameraPos = &mEngine->GetECS().GetRegistry().get<Muharrik::Position2D>(mCamera2DEntity);
    }

    void GameLoop::StartImpl()
    {
    }

    void GameLoop::UpdateImpl(float dt)
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
        
        static float cameraSpeed = 1.0f;
        if (mEngine->GetInputHandler().IsActionDown(Muharrik::InputAction::Up))
        {
            mCameraPos->mValue.y += cameraSpeed;
        }
        else if (mEngine->GetInputHandler().IsActionDown(Muharrik::InputAction::Down))
        {
            mCameraPos->mValue.y -= cameraSpeed;
        }

        if (mEngine->GetInputHandler().IsActionDown(Muharrik::InputAction::Right))
        {
            mCameraPos->mValue.x -= cameraSpeed;
        }
        else if (mEngine->GetInputHandler().IsActionDown(Muharrik::InputAction::Left))
        {
            mCameraPos->mValue.x += cameraSpeed;
        }
    }

    void GameLoop::EndImpl()
    {
    }

    void GameLoop::FinishImpl()
    {
    }
    
}