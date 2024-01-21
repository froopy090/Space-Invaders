#include "Alien.h"

Alien::Alien(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation, float speed, Bullet alienBullet, bool switchedDirection) 
	: Entity(texture, source, destination, position, rotation), speed(speed), alienBullet(alienBullet), moveX(10.0), moveY(10.0), isDead(false)
{
	
}

Alien::Alien()
	: speed(0.0), moveX(0.0), moveY(0.0), isDead(false)
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


void Alien::Event() {
	//bullet event
	if (GetRandomValue(0, 5000) > 4999) {
		alienBullet.isShot = true;
		positionXBullet = this->destination.x + 14;
		positionYBullet = this->destination.y + 14;
	}
}

void Alien::Update(bool* switchedFlag, bool* isHit) {
	if (!isDead) {
		destination.x += GetFrameTime() * moveX; //moves alien to the right

		//move in the opposite direction if at the edge of the screen, or move in the opposite direction if another alien got to the edge first
		if ((destination.x >= GetScreenWidth() - destination.width - 50 || destination.x <= 50) || *switchedFlag) {
			destination.y += moveY; //moves down
			moveX *= -1.2; //switches direction multiplier so it moves faster each time
			*switchedFlag = true; //setting flag to true
		}

		//getting hit by player bullet
		if (*isHit) {
			isDead = true;
			*isHit = false;
		}

		//bullet update
		if (alienBullet.isShot) {
			alienBullet.AlienUpdate(positionXBullet, positionYBullet);
		}
	}
	
}

void Alien::Draw() {
	if (!isDead) {
		DrawTexturePro(texture, source, destination, position, rotation, WHITE);
	}
	//bullet draw
	if (alienBullet.isShot) {
		alienBullet.Draw();
	}
}

