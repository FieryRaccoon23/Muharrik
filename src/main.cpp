#include "Engine/Core/engine.h"
#include "Game/GameLoop.h"

int main(int argc, char** argv)
{
    Muharrik::Engine engine;
    MuharrikGame::GameLoop gameLoop;

    engine.InitEngine();
    engine.MainLoop(gameLoop);
    engine.QuitEngine();

    return 0;
}
