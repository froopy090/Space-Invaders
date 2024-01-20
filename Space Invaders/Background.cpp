#include "Background.h"

Background::Background(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation, float speed)
	: Entity(texture, source, destination, position, rotation), speed(speed)
{

}

void Background::Update() {
	this->destination.y += GetFrameTime() * speed;
	if (this->destination.y >= GetScreenHeight()) {
		this->destination.y = 0;
	}
}

void Background::Draw() {
	DrawTexturePro(texture, source, destination, position, rotation, WHITE);
	this->destination.y -= GetScreenHeight();
	DrawTexturePro(texture, source, destination, position, rotation, WHITE);
	this->destination.y += GetScreenHeight();
}