#pragma once
#include "Entity.h"
class Background :
    public Entity
{
private:
    float speed;

public:
    Background(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation, float speed);
    void Update();
    void Draw();
};

