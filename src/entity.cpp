#include "entity.h"

// getters
const Vector2 Entity::GetOrigin() const
{
    return origin;
}

const Texture2D Entity::GetTexture() const
{
    return texture;
}

// setters
void Entity::SetTexture(const char* TEX_PATH)
{
    texture = LoadTexture(TEX_PATH);
}

void Entity::SetOrigin(const Vector2 ORIGIN)
{
    origin.x = ORIGIN.x * GetTexture().width;
    origin.y = ORIGIN.y * GetTexture().width;
}

// base methods
void Entity::Update() 
{};

void Entity::Draw()
{
    if (texture.id != 0)
    {
        DrawTexturePro
        (
        GetTexture(),
        (Rectangle){0, 0, (float)GetTexture().width, (float)GetTexture().height},
        (Rectangle){position.x, position.y, (float)GetTexture().width, (float)GetTexture().height},
        GetOrigin(),
        0.0f,
        WHITE
        );
    }
}