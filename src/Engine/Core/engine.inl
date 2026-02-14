#include "Extern/TracyProfiler.h"

#include "LLM/LlamaInfer.h"

namespace Muharrik
{
    template<class Derived>
    void Engine::MainLoop(IGame<Derived>& game)
    {
        bool running = true;

        game.Init(this);

        LlamaInfer infer;
        //infer.TestLlama();

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