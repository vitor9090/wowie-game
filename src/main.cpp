#include <iostream>
#include "raylib.h"

void GameLoop();
void Draw();
void Update();

// Entity class
class Entity
{
    private:
        Texture2D texture;
        Vector2 origin;

    public:
        Vector2 position;

        // constructors
        Entity()
            : position(), origin()
        {}; 
       
        Entity(const Vector2 &POSITION)
            : position(POSITION)
        {};

        // getters
        const Vector2 GetOrigin() const
        {
            return origin;
        }

        const Texture2D GetTexture() const
        {
            return texture;
        }

        // setters
        void SetTexture(const char* TEX_PATH)
        {
            texture = LoadTexture(TEX_PATH);
        }

        void SetOrigin(const Vector2 ORIGIN)
        {
            origin.x = ORIGIN.x * GetTexture().width;
            origin.y = ORIGIN.y * GetTexture().width;
        }


        // base methods
        virtual void Update()
        {};

        void Draw()
        {
            if (texture.id != 0)
            {
                DrawTexturePro
                (
                texture,
                (Rectangle){0, 0, (float)GetTexture().width, (float)GetTexture().height},
                (Rectangle){position.x, position.y, (float)GetTexture().width, (float)GetTexture().height},
                GetOrigin(),
                0.0f,
                WHITE
                );
            }
        };
};

class Player : public Entity
{
    public:

    Player(const Vector2 &POSITION)
        : Entity(POSITION)
    {};
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
Player player((Vector2){100, 100});

// main func
int main(int argc, char* agrv[])
{
    InitWindow(ScreenInfo::width, ScreenInfo::height, "Hello, World!");

    // Set textures here
    player.SetOrigin((Vector2){0, 0});
    player.SetTexture("src/resources/textures/mike.png");

    std::cout << player.GetOrigin().x << '\n';

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