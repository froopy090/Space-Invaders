#include "Bullet.h"

Bullet::Bullet(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation, float speed)
	: Entity(texture, source, destination, position, rotation), speed(speed), isShot(false)
{

}

Bullet::Bullet() {
	isShot = false;
	speed = 0;
}

void Bullet::reset() {
	this->isShot = false;
	this->destination.y = GetScreenHeight() - 112;
}

int Bullet::getRectDestX() {
	return destination.x;
}

int Bullet::getRectDestY() {
	return destination.y;
}

void Bullet::setShotBool(bool isShot) {
	this->isShot = isShot;
}

void Bullet::Update(int destRecX) {
	this->destination.y -= GetFrameTime() * speed;
	this->destination.x = destRecX;
	if (this->destination.y <= 0) {
		isShot = false;
		this->destination.y = GetScreenHeight() - 112;
	}
}

void Bullet::AlienUpdate(int destRecX, int destRecY) {
	this->destination.y += GetFrameTime() * speed;
	this->destination.x = destRecX;
	if (this->destination.y >= GetScreenHeight()) {
		isShot = false;
		this->destination.y = destRecY;
	}
}