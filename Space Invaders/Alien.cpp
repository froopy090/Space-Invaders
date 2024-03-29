#include "Alien.h"

Alien::Alien(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation, float* speed, Bullet alienBullet, bool switchedDirection) 
	: Entity(texture, source, destination, position, rotation), speed(speed), alienBullet(alienBullet), moveX(12.0), moveY(20.0), isDead(false)
{
	
}

Alien::Alien()
	: speed(NULL), moveX(0.0), moveY(0.0), isDead(false)
{
	//default
}

//getters
int Alien::getRectDestX() {
	return destination.x;
}

int Alien::getRectDestY() {
	return destination.y;
}

int Alien::getBulletX() {
	return this->alienBullet.getRectDestX();
}

int Alien::getBulletY() {
	return this->alienBullet.getRectDestY();
}

Bullet* Alien::getAlienBullet() {
	return &alienBullet;
}


//setters
void Alien::setBulletStatus(bool isShot) {
	this->alienBullet.isShot = isShot;
}

//game functions
void Alien::Event() {
	if (!isDead) {
		//bullet event
		if (GetRandomValue(0, 5000) > 4990 && alienBullet.isShot == false) {
			alienBullet.isShot = true;
			positionXBullet = this->destination.x + 14;
			positionYBullet = this->destination.y + 14;
			alienBullet.setDestRecY(positionYBullet);
		}
	}
}

void Alien::Update(bool* switchedFlag, bool* isHit) {
	if (!isDead) {
		destination.x += GetFrameTime() * moveX; //moves alien to the right

		//move in the opposite direction if at the edge of the screen, or move in the opposite direction if another alien got to the edge first
		if ((destination.x >= GetScreenWidth() - destination.width - 50 || destination.x <= 50) || *switchedFlag) {
			destination.y += moveY; //moves down
			moveX *= -1; //switching direction
			*switchedFlag = true; //setting flag to true
		}

		//getting hit by player bullet
		if (*isHit) {
			isDead = true;
			*isHit = false;
		}
	}

	//bullet update even if alien is dead
	if (alienBullet.isShot) {
		alienBullet.AlienUpdate(positionXBullet, positionYBullet);
	}
}

void Alien::Draw() {
	if (!isDead) {
		DrawTexturePro(texture, source, destination, position, rotation, WHITE);
	}
	//bullet draw, even if alien is dead
	if (alienBullet.isShot) {
		alienBullet.Draw();
	}
}

void Alien::resetBullet() {
	this->alienBullet.ResetAlienBullet();
}

void Alien::UpdateSpeed() {
	if (moveX < 432 && moveX > -432) {
		moveX *= *speed; 
	}
	else {
		moveX *= 1.0; //once speeds reach |360| we move at this constant speed
	}
}

bool Alien::Wins() {
	if (destination.y + 35 >= 745) {
		return true; //aliens win -> game over
	}
	else {
		return false; //aliens haven't won
	}
}

void Alien::Reset() {
	isDead = false;
	this->destination = InitDest; //restores the initial position when game started
	this->alienBullet.ResetAlienBullet();
	if (moveX < 0) {
		moveX *= -1;
	}
	moveX = 12.0f;
}