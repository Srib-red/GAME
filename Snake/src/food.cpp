#include "food.h"
#include "utils.h"

FOOD::FOOD(std::deque<Vector2> snakebody)
{
    Image image = LoadImage("Graphics/rengafood.jpg");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);

    position = GenerateRandomPos(snakebody);
}

FOOD::~FOOD()
{
    UnloadTexture(texture);
}

void FOOD::Draw()
{
    DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
}

Vector2 FOOD::GenerateRandomCell()
{
    float x = GetRandomValue(0, cellCount - 1);
    float y = GetRandomValue(0, cellCount - 1);
    return Vector2{x, y};
}

Vector2 FOOD::GenerateRandomPos(std::deque<Vector2> snakeBody)
{
    Vector2 position = GenerateRandomCell();
    while (ElementInDeque(position, snakeBody))
    {
        position = GenerateRandomCell();
    }
    return position;
}
