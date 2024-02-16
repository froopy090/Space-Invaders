#include "BonusAlien.h"
#include "Timer.h"
BonusAlien::BonusAlien(Texture2D texture, Vector2 position, Rectangle source, Rectangle dest) 
	: Entity(texture, source, dest, position, 0.0f), speed(0.0f), isDead(false), direction(1)
{
	timer.Start(30.0f); //every 30 sec, this alien shows up
}

void BonusAlien::Update() {
	if (!isDead){
		destination.x += GetFrameTime() * speed * direction;
		timer.Update();

		if (destination.x >= GetScreenWidth()) {
			speed = 0.0f;
			direction = -1; //next time it moves it will go left
		}

		if (destination.x + destination.width <= 0) {
			speed = 0.0f;
			direction = 1; //next time it moves it will go right
		}
	}
}

void BonusAlien::Event() {
	if (!isDead && timer.Finished()) {
		speed = 150.0f;
		timer.Start(35.0f); //resetting the timer, add 5 seconds to it because it takes 5 seconds to cross the screen
	}
}

void BonusAlien::Draw() {
	if (!isDead && speed != 0.0f) {
		DrawTexturePro(texture, source, destination, position, rotation, WHITE);
	}
}

void BonusAlien::checkBulletCollision(Bullet* playerBullet, int* playerScore) {
	if (!isDead && playerBullet->getRectDestY() <= destination.y && playerBullet->getRectDestX() >= destination.x && playerBullet->getRectDestX() <= destination.x + destination.width) {
		isDead = true;
		*playerScore += 100;
	}
}

void BonusAlien::Reset() {
	isDead = false;
}