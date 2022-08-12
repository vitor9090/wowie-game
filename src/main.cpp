#include <iostream>
#include "raylib.h"

void GameLoop();
void Draw();
void Update();

// Entity class
class Entity
{
    public:
        Vector2 position;

        // constructors
        Entity()
            : position()
        {}; 
       
        Entity(const Vector2 &POSITION)
            : position(POSITION) // this line here
        {};

        // base methods
        virtual void Update()
        {};

        void Draw()
        {
            DrawCircle
            (
                position.x,
                position.y,
                100,
                WHITE
            );
        };
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

// Instantiate entity class
Entity player((Vector2){100, 100});

// main func
int main(int argc, char* agrv[])
{
    InitWindow(ScreenInfo::width, ScreenInfo::height, "Hello, World!");

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
{}