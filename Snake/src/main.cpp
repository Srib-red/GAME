#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>

using namespace std;

// Struct Color = {red, green, blue, alpha}
Color green = {173, 204, 96, 255};
Color darkgreen = {43, 51, 24, 255};

int cellSize = 40;
int cellCount = 25;
int offset = 75;

double lastUpdateTime = 0;

bool ElementInDeque(Vector2 element, deque<Vector2> deque1)
{
    for (unsigned int i = 0; i < deque1.size(); i++)
    {
        if (Vector2Equals(deque1[0], element))
        {
            return true;
        }
    }
    return false;
}

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

class Snake
{
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;

    void Draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = {x * cellSize, y * cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkgreen);
        }
    }

    void Update()
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

    void Reset()
    {
        this->body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        this->direction = {1, 0};
    }
};

class FOOD
{
public:
    Vector2 position;
    Texture2D texture;

    FOOD(deque<Vector2> snakebody)
    {
        Image image = LoadImage("Graphics/rengafood.jpg");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakebody);
    }

    ~FOOD()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

    Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
    {
        Vector2 position = GenerateRandomCell();
        while (ElementInDeque(position, snakeBody))
        {
            position = GenerateRandomCell();
        }
        return position;
    }
};

class Game
{
public:
    Snake snake1;
    FOOD food1 = FOOD(snake1.body);
    bool running = true;

    void Draw()
    {
        food1.Draw();
        snake1.Draw();
    }
    void Update()
    {
        if (running)
        {
            snake1.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    }
    void CheckCollisionWithFood()
    {
        if (Vector2Equals(snake1.body[0], food1.position))
        {
            food1.position = food1.GenerateRandomPos(snake1.body);
            snake1.addSegment = true;
        }
    }

    void CheckCollisionWithEdges()
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

    void GameOver()
    {
        snake1.Reset();
        food1.position = food1.GenerateRandomPos(snake1.body);
        running = false;
    }

    void CheckCollisionWithTail()
    {
        deque<Vector2> headlessBody = snake1.body;
        headlessBody.pop_front();
        if (ElementInDeque(snake1.body[0], headlessBody))
        {
            GameOver();
        }
    }
};

int main()
{
    cout << "starting the game\n";
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
        sgame.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}