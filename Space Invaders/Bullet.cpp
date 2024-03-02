#include "Bullet.h"

Bullet::Bullet(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation, float speed)
	: Entity(texture, source, destination, position, rotation), speed(speed), isShot(false)
{

}

Bullet::Bullet() {
	isShot = false;
	speed = 0;
}

void Bullet::ResetPlayerBullet() {
	this->isShot = false;
	this->destination.y = GetScreenHeight() - 112;
}

void Bullet::ResetAlienBullet() {
	this->isShot = false;
	this->destination.y = GetScreenHeight(); //placing the bullet at the bottom of the screen where the player cannot hit it
}

int Bullet::getRectDestX() {
	return destination.x;
}

int Bullet::getRectDestY() {
	return destination.y;
}

int Bullet::getRectDectWidth() {
	return destination.width;
}

int Bullet::getRectDestHeight() {
	return destination.height;
}

void Bullet::setShotBool(bool isShot) {
	this->isShot = isShot;
}

void Bullet::setDestRecY(int posY) {
	this->destination.y = posY;
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
	if (this->destination.y >= 745 - this->destination.height) { //doesn't go beyond the line at the bottom of the screen
		this->ResetAlienBullet();
	}
}

//checks collision with another bullet
void Bullet::CheckCollision(Bullet* b) {
	if (this->destination.y >= b->getRectDestY() && this->destination.y <= b->getRectDestY() + b->getRectDestHeight()) {
		if (this->destination.x >= b->getRectDestX() && this->destination.x <= b->getRectDestX() + b->getRectDectWidth()) {
			b->ResetPlayerBullet();
			this->ResetAlienBullet();
		}
	}
}