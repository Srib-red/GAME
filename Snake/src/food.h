#pragma once
#include <raylib.h>
#include <deque>

class FOOD
{
public:
    Vector2 position;
    Texture2D texture;

    FOOD(std::deque<Vector2> snakebody);
    ~FOOD();

    void Draw();
    Vector2 GenerateRandomCell();
    Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody);
};