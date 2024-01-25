#include "Shield.h"

Shield::Shield() {
	//global offset
	offsetY = 200;

	//main rectangle
	recX = GetScreenWidth() / 2;
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
	cornerRightX = GetScreenWidth() / 2 + recWidth / 2;
	cornerRight = { cornerRightX, cornerY, cornerWidth, cornerHeight };
	cornerRightRotation = 45.0f;

	//left corner
	cornerLeftX = GetScreenWidth() / 2 - recWidth / 2;
	cornerLeft = { cornerLeftX, cornerY, cornerWidth, cornerHeight };
	cornerLeftRotation = -cornerRightRotation;

	//semi-circle
	center = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f + recHeight/2 + offsetY };
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