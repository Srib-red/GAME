#include <raylib.h>
#include "game.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    Color darkblu = {44, 44, 127, 255};
    InitWindow(300, 600, "tetris");
    SetTargetFPS(60);

    Game game1;

    while (WindowShouldClose() == false)
    {
        game1.Handleinput();
        if (EventTriggered(0.2))
        {
            game1.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkblu);
        game1.Draw();
        EndDrawing();
    }

    CloseWindow();
}