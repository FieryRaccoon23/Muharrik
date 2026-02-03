#include "Extern/TracyProfiler.h"

namespace Muharrik
{
    template<class Derived>
    void Engine::MainLoop(IGame<Derived>& game)
    {
        bool running = true;

        game.Init(this);

        while (running) 
        {
            TracyProfiler::Tracy_FrameMark();

            mInputHandler.UpdateInputHandler();

            running = mSDL.PollSDL();

            // NOTE: Pass correct frame rate
            game.Update(0.0f);

            mSDL.RenderTexture(&mSpriteAssetManager, mECS.GetRegistry());

            //mSDL.DelaySDL(FRAME_DELAY);
        }

        game.Finish();

    }
}