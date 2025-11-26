#include <raylib.h>
#include <iostream>
#include "game.h"

int main()
{
    std::cout << "starting the game\n";
    InitWindow(2*offset + cellSize * cellCount,2*offset + cellSize * cellCount, "RetroSnake");
    SetTargetFPS(60);

    Game sgame;

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        if (EventTriggered(0.2))
        {
            sgame.Update();
        }

        if (IsKeyPressed(KEY_UP) && sgame.snake1.direction.y != 1)
        {
            sgame.snake1.direction = {0, -1};
            sgame.running = true;
        }
        if (IsKeyPressed(KEY_DOWN) && sgame.snake1.direction.y != -1)
        {
            sgame.snake1.direction = {0, 1};
            sgame.running = true;
        }
        if (IsKeyPressed(KEY_LEFT) && sgame.snake1.direction.x != 1)
        {
            sgame.snake1.direction = {-1, 0};
            sgame.running = true;
        }
        if (IsKeyPressed(KEY_RIGHT) && sgame.snake1.direction.x != -1)
        {
            sgame.snake1.direction = {1, 0};
            sgame.running = true;
        }

        // Drawing
        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize*cellCount + 10, (float)cellSize*cellCount + 10}, 5, darkgreen);
        DrawText("Retro Snake", offset - 5, 20, 40, darkgreen);
        DrawText(TextFormat("%i",sgame.score), offset-5, offset + cellSize*cellCount+10, 40, darkgreen);
        sgame.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}