#include "Game.h"
#include "Settings.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitAudioDevice();
    Game game{ settings::screenWidth, settings::screenHeight, settings::fps, "Tetris Raylib" };
    SetExitKey(KEY_F1);
    while (!game.GameShouldClose())
    {
        game.Tick();
    }

    return 0;
}