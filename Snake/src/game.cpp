#include "game.h"

Game::Game() : food1(snake1.body)
{
    running = true;
    score = 0;

    InitAudioDevice();
    eatSound = LoadSound("Sounds/eat.mp3");
    wallSound = LoadSound("Sounds/wall.mp3");
}

Game::~Game()
{
    UnloadSound(eatSound);
    UnloadSound(wallSound);
    CloseAudioDevice();
}

void Game::Draw()
{
    food1.Draw();
    snake1.Draw();
}

void Game::Update()
{
    if (running)
    {
        snake1.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }
}

void Game::CheckCollisionWithFood()
{
    if (Vector2Equals(snake1.body[0], food1.position))
    {
        food1.position = food1.GenerateRandomPos(snake1.body);
        snake1.addSegment = true;
        score += 1;
        PlaySound(eatSound);
    }
}

void Game::CheckCollisionWithEdges()
{
    if (snake1.body[0].x == cellCount || snake1.body[0].x == -1)
    {
        GameOver();
    }
    if (snake1.body[0].y == cellCount || snake1.body[0].y == -1)
    {
        GameOver();
    }
}

void Game::GameOver()
{
    snake1.Reset();
    food1.position = food1.GenerateRandomPos(snake1.body);
    running = false;
    score = 0;
    PlaySound(wallSound);
}

void Game::CheckCollisionWithTail()
{
    std::deque<Vector2> headlessBody = snake1.body;
    headlessBody.pop_front();
    if (ElementInDeque(snake1.body[0], headlessBody))
    {
        GameOver();
    }
}
