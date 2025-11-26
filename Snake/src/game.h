#pragma once
#include "food.h"
#include "snake.h"
#include "utils.h"

class Game
{
public:
    Snake snake1;
    FOOD food1;
    bool running;
    int score;

    Sound eatSound;
    Sound wallSound;

    Game();
    ~Game();

    void Draw();
    void Update();
    void CheckCollisionWithFood();
    void CheckCollisionWithEdges();
    void GameOver();
    void CheckCollisionWithTail();
};