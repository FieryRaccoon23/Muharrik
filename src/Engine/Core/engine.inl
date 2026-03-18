#include "Extern/TracyProfiler.h"

#include "LLM/LlamaInfer.h"
#include "Physics/PhysicsSystem.h"

namespace Muharrik
{
    template<class Derived>
    void Engine::MainLoop(IGame<Derived>& game)
    {
        bool running = true;

        game.Init(this);

#if MUHARRIK_ENABLE_LLAMA
        LlamaInfer infer;
        //infer.TestLlama();
#endif

        PhysicsSystem physicsSystem;

        while (running) 
        {
            TracyProfiler::Tracy_FrameMark();

            float dt = GetDeltaTimeSeconds();

            mInputHandler.UpdateInputHandler();

            running = mSDL.PollSDL();

            game.Update(dt);

            mSDL.RenderTexture(&mSpriteAssetManager, mECS.GetRegistry(), mCamera2DEntity);

            //mSDL.DelaySDL(FRAME_DELAY);
        }

        game.Finish();

    }
}