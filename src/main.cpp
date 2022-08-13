#include <iostream>
#include <vector>

#include <raylib.h>
#include <raymath.h>
#include "entity.h"

void GameLoop();
void Draw();
void Update();


class Player : public Entity
{
    private:
        Vector2 input_vector;

        float queueCooldown = 0;

        bool canAddToQueue = true;
        bool playingQueue = false;

        u_short currentQueueValue = 0;        

        float animTimer = 0;

    public:
        std::vector<Vector2> queue = {};
        Vector2 startPosition = { 16, 16 };

        int speed_multiplier = 5;
        int speed = 16 * speed_multiplier;

        bool queueIsEmpty = true;
        float queueCooldownMax = 0.5f;
        float animTimerMax = 1.0f / speed_multiplier;

        Player(const Vector2 &POSITION)
            : Entity(POSITION)
        {};

        // methods
        void CallQueue()
        {
            for (u_short i = 0; i < queue.size(); i++)
            {
                DoDirection(queue[i]);
            }   

            queue.clear();
            std::cout << "The queue has ended or is empty" << '\n';
            queueIsEmpty = !queueIsEmpty;
        }

        // move methods
        void DoDirection(const Vector2 DIRECTION) 
        {
            std::cout << "[TEST]: Moved, x: " << DIRECTION.x << " y: " << DIRECTION.y << '\n';
            position.x += DIRECTION.x * speed;
            position.y += DIRECTION.y * speed;
        }

        // base methods
        void Update()
        {
            Vector2 input_vector =
            {
                (float)IsKeyDown(KEY_RIGHT) - (float)IsKeyDown(KEY_LEFT),
                (float)IsKeyDown(KEY_DOWN) - (float)IsKeyDown(KEY_UP)
            };

            if (IsKeyDown(KEY_R))
            {
                position = startPosition;
                canAddToQueue = true;
                animTimer = 0;
                playingQueue = false;
                currentQueueValue = 0;
                queue.clear();
            }

            if (!queueIsEmpty)
                if (IsKeyDown(KEY_Q) && !playingQueue)
                {
                    playingQueue = true;
                    canAddToQueue = false;
                }

            if (playingQueue)
            {
                canAddToQueue = false;
                animTimer += GetFrameTime();
                if (currentQueueValue < queue.size())
                {
                    if (animTimer < animTimerMax)
                    {
                        position.x += queue[currentQueueValue].x * speed * GetFrameTime();
                        position.y += queue[currentQueueValue].y * speed * GetFrameTime();

                        position.x = Clamp(position.x, 16, 175 - 16);
                        position.y = Clamp(position.y, 16, 175 - 16);
                    } else {
                        currentQueueValue++;
                        animTimer = 0;
                    }
                } else {
                    currentQueueValue = 0;
                }
            }

            if (canAddToQueue)
            {
                if ((input_vector.x != 0 || input_vector.y != 0))
                    {
                        std::cout << "[INFO]: Added to queue, move x: " << input_vector.x << " y:" << input_vector.y << '\n'; 
                        queue.insert(queue.end(), input_vector);
                        canAddToQueue = false;
                        if (queueIsEmpty)
                        {
                            queueIsEmpty = false;
                        }
                    }
            } else
            {
                if (!playingQueue)
                {
                    if (queueCooldown < queueCooldownMax)
                    {
                        queueCooldown += GetFrameTime();
                    } else
                    {
                        canAddToQueue = true;
                        queueCooldown = 0;
                    }
                } else {
                    queueCooldown = 0;
                }
            }
        }
};

// Info about the windows
struct ScreenInfo
{
    static const u_short WIDTH  = 600;
    static const u_short HEIGHT = 386;

    static const u_short VIRTUAL_WIDTH  = 300;
    static const u_short VIRTUAL_HEIGHT = 193;

    static constexpr float VIRTUAL_RATIO = (float)WIDTH/(float)VIRTUAL_WIDTH;

} ScreenInfo;

// define static vars
const u_short ScreenInfo::WIDTH;
const u_short ScreenInfo::HEIGHT;

const u_short ScreenInfo::VIRTUAL_HEIGHT;
const u_short ScreenInfo::VIRTUAL_WIDTH;

constexpr float ScreenInfo::VIRTUAL_RATIO;

// vars
const Rectangle VIRTUAL_PLAY_AREA = { 16, 16, 175, 175 };
const Rectangle SCREEN_PLAY_AREA  = { VIRTUAL_PLAY_AREA.x * 2, VIRTUAL_PLAY_AREA.y * 2, VIRTUAL_PLAY_AREA.width * 2, VIRTUAL_PLAY_AREA.height * 2 };


// Instantiate player class
Player player((Vector2){16, 16});

// cameras
Camera2D worldSpaceCamera = { 0 };

Camera2D screenSpaceCamera = { 0 };


// main func
int main(int argc, char* agrv[])
{
    InitWindow(ScreenInfo::WIDTH, ScreenInfo::HEIGHT, "Hello, World!");

    // Set textures here
    player.SetOrigin((Vector2){0, 0});
    player.SetTexture("src/resources/textures/mike.png");

    screenSpaceCamera.target   = (Vector2){0, 0};
    screenSpaceCamera.zoom     = 1.0f;

    worldSpaceCamera.target   = (Vector2){0, 0};
    worldSpaceCamera.zoom     =   1.0f;
    GameLoop();

    return 0;
}

// The game loop happens here
void GameLoop()
{
    const Texture2D BORDER_TEX = LoadTexture("src/resources/textures/border.png");
    RenderTexture2D target = LoadRenderTexture(ScreenInfo::VIRTUAL_WIDTH, ScreenInfo::VIRTUAL_HEIGHT);

    Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
    Rectangle destRec = { -ScreenInfo::VIRTUAL_RATIO, -ScreenInfo::VIRTUAL_RATIO, ScreenInfo::WIDTH + (ScreenInfo::VIRTUAL_RATIO*2), ScreenInfo::HEIGHT + (ScreenInfo::VIRTUAL_RATIO*2) };

    const Vector2 ORIGIN = { 0.0f, 0.0f };

    while (!WindowShouldClose())
    {
        Update();

        BeginTextureMode(target);
            ClearBackground(WHITE);

            BeginMode2D(worldSpaceCamera);

                Draw();
                DrawTexture(BORDER_TEX, 0, 0, WHITE);

            EndMode2D();

        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(screenSpaceCamera);
                DrawTexturePro(target.texture, sourceRec, destRec, ORIGIN, 0.0f, WHITE);
            EndMode2D();

            DrawText("QUEUE", (ScreenInfo.WIDTH / 2 + VIRTUAL_PLAY_AREA.width) - (6 * 32) / 4, VIRTUAL_PLAY_AREA.y + 16, 32, WHITE);
            for (u_short i = 1; i < player.queue.size() + 1; i++)
            {
                DrawText((TextFormat)("Vec{ %i , %i };", (int)player.queue[i - 1].x, (int)player.queue[i - 1].y), (ScreenInfo.WIDTH / 2 + VIRTUAL_PLAY_AREA.width) - 80, (VIRTUAL_PLAY_AREA.y + 32) + i * 32, 14, WHITE);
            }
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();
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