#pragma once
#include "Entity.h"
#include "Timer.h"
#include "Bullet.h"

class BonusAlien :
    public Entity
{
public:
    BonusAlien(Texture2D texture, Vector2 position, Rectangle source, Rectangle dest);
    void Update();
    void Event();
    void Draw();
    void checkBulletCollision(Bullet* playerBullet, int* playerScore);
    void Reset();

private:
    bool isDead;
    float speed;
    int direction;

    Timer timer;
};

