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
    Bullet();

    //helper
    void ResetPlayerBullet();
    void ResetAlienBullet();
    void CheckCollision(Bullet* b);

    //getters
    int getRectDestX();
    int getRectDestY();
    int getRectDectWidth();
    int getRectDestHeight();

    //setters
    void setDestRecY(int posY);
    void setShotBool(bool isShot);

    void Update(int destRectX);
    void AlienUpdate(int destRectX, int destRecY);
};