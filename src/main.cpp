#include <iostream>
#include <vector>

#include <raylib.h>
#include "entity.h"

void GameLoop();
void Draw();
void Update();


class Player : public Entity
{

    private:
        std::vector<Vector2> queue = {
            (Vector2){1, 0},
            (Vector2){1, 0},
            (Vector2){1, 0},
            (Vector2){0, 1},
            (Vector2){0, 1},
            (Vector2){0, 1}
        };

    public:
        int speed = 19;
        bool queueIsEmpty = false;

        Player(const Vector2 &POSITION)
            : Entity(POSITION)
        {};

        // methods
        void CallQueue()
        {
            if (!queueIsEmpty)
            {
                for (u_short i = 0; i < queue.size(); i++)
                {
                    DoDirection(queue[i]);
                }   
            }

            queue.clear();
            queueIsEmpty = !queueIsEmpty;
            std::cout << "The queue has ended or is empty" << '\n';
        }

        // move methods
        void DoDirection(const Vector2 DIRECTION) 
        {
            std::cout << "[TEST]: Moved, x:" << DIRECTION.x << " y:" << DIRECTION.y << '\n';
            position.x += DIRECTION.x * speed;
            position.y += DIRECTION.y * speed;
        }

        // base methods
        void Update()
        {
            if (IsKeyDown('Q'))
                CallQueue();
        }
};

// Info about the windows
struct ScreenInfo
{
    static const u_short width = 800;
    static const u_short height = 600;
} ScreenInfo;

// define static vars
const u_short ScreenInfo::width;
const u_short ScreenInfo::height;

// Instantiate player class
Player player((Vector2){0, 0});

// main func
int main(int argc, char* agrv[])
{
    InitWindow(ScreenInfo::width, ScreenInfo::height, "Hello, World!");

    // Set textures here
    player.SetOrigin((Vector2){0, 0});
    player.SetTexture("src/resources/textures/mike.png");

    GameLoop();
    CloseWindow();

    return 0;
}

// The game loop happens here
void GameLoop()
{
    while (!WindowShouldClose())
    {
        Update();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Press Q to call queue", 0, 0, 19, WHITE);
        Draw();

        EndDrawing();
    }
}

// Draw function 
void Draw()
{
    player.Draw();
}

// Frame update
void Update()
{
    player.Update();
}