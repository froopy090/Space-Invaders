#pragma once
#include "raylib.h"

#define X 10
#define Y 10

class Heart
{
public:
	Heart(float offsetX);
	void Draw();
	void Update();

private:
	float xPos;

	//top two rectangles
	Rectangle top1;
	Rectangle top2;

	//main body
	Rectangle body;

	//bottom 3 rectangles
	Rectangle bottom1;
	Rectangle bottom2;
	Rectangle bottom3;
};