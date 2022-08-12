#pragma once

#include <raylib.h>

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
        const Vector2 GetOrigin() const;
        const Texture2D GetTexture() const;

        // setters
        void SetTexture(const char* TEX_PATH);
        void SetOrigin(const Vector2 ORIGIN);

        // base methods
        virtual void Update();
        void Draw();
};
