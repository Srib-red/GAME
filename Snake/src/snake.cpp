#include "snake.h"
#include "utils.h"
#include <raymath.h>

Snake::Snake()
{
    body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    direction = {1, 0};
    addSegment = false;
}

void Snake::Draw()
{
    for (unsigned int i = 0; i < body.size(); i++)
    {
        float x = body[i].x;
        float y = body[i].y;
        Rectangle segment = {offset + x * cellSize, offset + y * cellSize, (float)cellSize, (float)cellSize};
        DrawRectangleRounded(segment, 0.5, 6, darkgreen);
    }
}

void Snake::Update()
{
    body.push_front(Vector2Add(body[0], direction));
    if (addSegment == true)
    {
        // body.push_front(Vector2Add(body[0], direction));
        addSegment = false;
    }
    else
    {
        body.pop_back();
        // body.push_front(Vector2Add(body[0], direction));
    }
}

void Snake::Reset()
{
    this->body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    this->direction = {1, 0};
}
