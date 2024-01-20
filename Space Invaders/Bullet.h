#pragma once
#include "Entity.h"

class Bullet :
    public Entity
{
private:
    float speed;

public:
    bool isShot;
    Bullet(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation, float speed);

    void reset();

    int getRectDestX();
    int getRectDestY();

    void setShotBool(bool isShot);

    Bullet();
    void Update(int destRectX);
    void AlienUpdate(int destRectX, int destRecY);
};