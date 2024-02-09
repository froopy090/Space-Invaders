#pragma once
#include "Entity.h"
#include "Bullet.h"

class Alien :
    public Entity
{
private:
    float speed;
    Bullet alienBullet;
    float moveX;
    float moveY;
    int positionXBullet;
    int positionYBullet;
    

public:
    bool isDead;

    Alien(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation, float speed, Bullet alienBullet, bool switchedDirection);
    Alien();

    //getters
    int getRectDestX();
    int getRectDestY();
    int getBulletY();
    int getBulletX();
    Bullet getAlienBullet();

    //setter
    void setBulletStatus(bool isShot);

    //game functions
    void resetBullet();
    void Event();
    void Update(bool* switchedFlag, bool* isHit);
    void Draw();
};

