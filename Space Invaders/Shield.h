#pragma once
#include "raylib.h"
#include "Bullet.h"
#include "Alien.h"

#define MAX_WIDTH 100
#define MAX_HEIGHT 70
#define PIXEL_SIZE 2 //the shield is being drawn by 2x2 rectangle or "pixels"
#define X_POS 50
#define Y_POS 600

class Shield
{
public:
	Shield(float offsetX);
	void Draw();
	void playerUpdate(Bullet *playerBullet);
	void alienUpdate(Alien *alien);

private:
	float offsetX; //decides where the entire shield will be drawn

	Rectangle pixelRec[MAX_HEIGHT / PIXEL_SIZE][MAX_WIDTH / PIXEL_SIZE];
	float xPos;
	float yPos;
	Color pixelColor[MAX_HEIGHT / PIXEL_SIZE][MAX_WIDTH / PIXEL_SIZE];
};