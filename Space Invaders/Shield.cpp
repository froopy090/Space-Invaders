#include "Shield.h"

Shield::Shield(float offsetX, Bullet *playerBullet, Bullet *alienBullet)
	: playerBullet(playerBullet), alienBullet(alienBullet)
{
	//global offset
	offsetX = offsetX;
	offsetY = 200.0f;

	//main rectangle
	recX = GetScreenWidth() / 2 + offsetX;
	recY = GetScreenHeight() / 2 + offsetY;
	recWidth = 100;
	recHeight = 70;
	rec = { recX, recY, recWidth, recHeight };
	recOrigin = { recWidth / 2, recHeight / 2 };
	rotation = 0.0f;
	recColor = WHITE;

	//shared corner variables
	cornerY = GetScreenHeight() / 2 - recHeight/2 + offsetY;
	cornerWidth = 20;
	cornerHeight = 20;
	cornerOrigin = { cornerWidth / 2, cornerHeight / 2 };
	cornerColor = BLACK;

	//right corner
	cornerRightX = GetScreenWidth() / 2 + recWidth / 2 + offsetX;
	cornerRight = { cornerRightX, cornerY, cornerWidth, cornerHeight };
	cornerRightRotation = 45.0f;

	//left corner
	cornerLeftX = GetScreenWidth() / 2 - recWidth / 2 + offsetX;
	cornerLeft = { cornerLeftX, cornerY, cornerWidth, cornerHeight };
	cornerLeftRotation = -cornerRightRotation;

	//semi-circle
	center = { GetScreenWidth() / 2.0f + offsetX, GetScreenHeight() / 2.0f + recHeight/2 + offsetY };
	radius = 25.0f;
	startAngle = 90.0f;
	endAngle = 270.0f;
	segments = 1;
	circleColor = BLACK;
}

void Shield::Draw() {
	DrawRectanglePro(rec, recOrigin, rotation, recColor);
	DrawRectanglePro(cornerRight, cornerOrigin, cornerRightRotation, cornerColor);
	DrawRectanglePro(cornerLeft, cornerOrigin, cornerLeftRotation, cornerColor);
	DrawCircleSector(center, radius, startAngle, endAngle, segments, circleColor);
}

void Shield::Update() {
	//player bullet collision
	if (playerBullet->getRectDestX() >= recX - recOrigin.x && playerBullet->getRectDestX() <= recX + recOrigin.x) {
		if (playerBullet->getRectDestY() >= recY - recOrigin.y && playerBullet->getRectDestY() <= recY + recOrigin.y) {
			playerBullet->reset();
		}
	}

	//alien bullet collision
	/*if (alienBullet->getRectDestX() >= recX - recOrigin.x && alienBullet->getRectDestX() <= recX + recOrigin.x) {
		if (alienBullet->getRectDestY() >= recY - recOrigin.y && alienBullet->getRectDestY() <= recY + recOrigin.y) {
			alienBullet->reset();
		}
	}*/
}