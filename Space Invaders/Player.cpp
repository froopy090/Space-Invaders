#include "Player.h"

Player::Player(Texture2D texture, Rectangle source, Rectangle destination, Vector2 position, float rotation, float speed, Bullet *playerBullet)
	: Entity(texture, source, destination, position, rotation), speed(speed), playerBullet(playerBullet), isDead(false)
{

}

//getters
int Player::getBulletX() {
	if (playerBullet->isShot) {
		return playerBullet->getRectDestX();
	}
	else {
		return -1;
	}
}

int Player::getBulletY() {
	if (playerBullet->isShot) {
		return playerBullet->getRectDestY();
	}
	else {
		return -1;
	}
}

Bullet Player::getPlayerBullet() {
	return *playerBullet;
}

int Player::getRecDestX() {
	return this->destination.x; //this was incorrect, thanks to thenewchicken for helping me debug this
}

int Player::getRecDestY() {
	return this->destination.y;
}


void Player::shoot() {
	playerBullet->isShot = true;
}

void Player::kill() {
	this->isDead = true;
}


void Player::Event() {
	if (!isDead) {
		//movement
		if (IsKeyDown(KEY_LEFT)) {
			this->source.x = 0;
			this->destination.x -= GetFrameTime() * speed;
			if (this->destination.x <= 0) {
				this->destination.x = 0;
			}
		}
		else if (IsKeyDown(KEY_RIGHT)) {
			this->source.x = 18;
			this->destination.x += GetFrameTime() * speed;
			if (this->destination.x >= GetScreenWidth() - this->destination.width) {
				this->destination.x = GetScreenWidth() - this->destination.width;
			}
		}
		else {
			this->source.x = 8;
		}

		//bullet event
		if (IsKeyPressed(KEY_SPACE) && playerBullet->isShot == false) {
			playerBullet->reset();
			playerBullet->isShot = true;
			positionXBullet = this->destination.x + 14;
		}
	}
	
}

void Player::Update() {
	if (playerBullet->isShot && !isDead) {
		playerBullet->Update(positionXBullet);
	}
}

void Player::Draw() {
	if (!isDead) {
		DrawTexturePro(texture, source, destination, position, rotation, WHITE);
		if (playerBullet->isShot) {
			playerBullet->Draw();
		}
	}
}