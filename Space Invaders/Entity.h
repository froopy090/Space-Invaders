#pragma once
#include <raylib.h>
class Entity
{
protected:
	Texture2D texture;
	Rectangle source;
	Rectangle destination;
	Vector2 position;
	float rotation;

public:
	Entity(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation);
	Entity();
	void Event();
	void Update();
	void Draw();
};

