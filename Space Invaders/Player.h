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
    Music playerBulletSound = LoadMusicStream("resources/sound/bulletSound.wav"); //bullet sound

public:
    bool isDead;

    Player(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation, float speed, Bullet *playerBullet);

    //getters
    int getBulletX();
    int getBulletY();
    Bullet getPlayerBullet();
    int getRecDestY();
    int getRecDestX();

    //helper
    void shoot();
    void kill();
    void revive();
    
    void Event();
    void Update();
    void Draw();
    void Reset();
};

