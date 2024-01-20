#pragma once
#include "Entity.h"
#include "Bullet.h"

class Player :
    public Entity
{
private:
    float speed;
    Bullet *playerBullet; //credit thenewchicken
    int positionXBullet;

public:
    Player(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation, float speed, Bullet *playerBullet);

    int getBulletX();
    int getBulletY();
    Bullet getPlayerBullet();

    void shoot();

    void Event();
    void Update();
    void Draw();
};

