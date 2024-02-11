#include "Background.h"
#include "Player.h"
#include "Bullet.h"
#include "Alien.h"
#include "Shield.h"
#include "Heart.h"
#include "Timer.h"

//constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define TARGET_FPS 60

bool PAUSED = false;

int main() {
	//initializing window
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Invaders");
	SetTargetFPS(TARGET_FPS);

	//loading texture
	Texture2D backgroundTexture = LoadTexture("resources/texture/background.png");
	Texture2D shipTexture = LoadTexture("resources/texture/ships.png");
	Texture2D bulletTexture = LoadTexture("resources/texture/bullets.png");

	//background variables
	Rectangle backgroundRectSource = { 0,0,128,256 };
	Rectangle backgroundRectDest = { 0 ,0,WINDOW_WIDTH, WINDOW_HEIGHT };
	Vector2 position = { 0,0 };
	float rotation = 0.0; //using this for pretty much everything
	float speed = 400.0; //also going to use this for the player

	//player variables
	Rectangle playerSource = { 8,0,8,8 };
	Rectangle playerDest = { WINDOW_WIDTH / 2,WINDOW_HEIGHT - 100, 32, 32 };

	//player bullet variables
	Rectangle playerBulletSource = { 19,3,1,3 };
	Rectangle playerBulletDest = { playerDest.x + 14, playerDest.y - 12, 4,12 };
	float bulletSpeed = 400.0; 

	//alien variables
	const int row = 5;
	const int column = 11;

	bool switched = false;
	bool isMovingRight = true;
	bool isHit = false;
	float alienBulletSpeed = 200.0;

	Rectangle alienSource; //of ships texture
	Rectangle alienDest = { 100, 100, 35,35 };
	float alienSpeed = 200;

	//shield variables
	float offsetX = 0.0f;

	//alien bullet variables
	Rectangle alienBulletSource = { 11,4, 1, 2 };
	Rectangle alienBulletDest = { alienDest.x + 4, alienDest.y + 2, 4,12 };

	//Entities
	Background background(backgroundTexture, backgroundRectSource, backgroundRectDest, position, rotation, speed);

	Bullet *playerBullet = new Bullet(bulletTexture, playerBulletSource, playerBulletDest, position, rotation, bulletSpeed);
	Bullet alienBullet(bulletTexture, alienBulletSource, alienBulletDest, position, rotation, alienBulletSpeed);

	Player player(shipTexture, playerSource, playerDest, position, rotation, speed, playerBullet);

	Alien alienMatrix[row][column];

	Shield *shield1 = new Shield(offsetX); //these are pointers to avoid having too much stuff in stack, moving these to heap
	Shield *shield2 = new Shield(offsetX + 200);
	Shield *shield3 = new Shield(offsetX + 400);
	Shield *shield4 = new Shield(offsetX + 600);

	int playerDeathCount = 0; //counter for times the player dies, when it's 3, gameover 
	bool needsRevived = false;
	Heart* heart1 = new Heart(0.0f);
	Heart* heart2 = new Heart(40.0f);
	Heart* heart3 = new Heart(80.0f);

	//timer stuff
	Timer timer;
	float lifetime = 0.5f;

	Alien* alien;
	//initializing each alien
	for (int r = 0; r < row; r++) { 
		//switch to select the alien for the corrisponding row
		switch (r) {
		case 0:
			alienSource = { 34,2, 5, 5 }; //the alien in the top row
			break;
		case 1:
			alienSource = { 40, 2, 7, 6 }; //the alien for the next two rows
			break;
		case 3:
			alienSource = { 72, 25, 8, 6 }; //the alien for the bottom two rows
			break;
		}
		for (int c = 0; c < column; c++) {
			alienDest.x += 50; //moving the alien to the right 
			alien = new Alien(shipTexture, alienSource, alienDest, position, rotation, alienSpeed, alienBullet, switched);
			alienMatrix[r][c] = *alien;
			delete alien; //credit thenewchicken
		}

		alienDest.x = 100; //resetting the x position to prepare for a new row
		alienDest.y += 50; //moving down for the next row
	}
	alienDest.y = 100; //resetting the y position because idk


	while (!WindowShouldClose()) {
		//----events-------------------------------------
		player.Event();
		for (int r = 0; r < row; r++) { //alien events
			for (int c = 0; c < column; c++) {
				alienMatrix[r][c].Event();
			}
		}

		//game pauses while timer is running
		if (!timer.Finished()) {
			PAUSED = true;
		}
		else {
			PAUSED = false;
			if (needsRevived) {
				player.revive();
				needsRevived = false; //resetting flag
			}
		}
		//-------------------------------------------------
		

		//----update----------------------------------------
		if (!PAUSED) {
			background.Update();
			player.Update(); //I'm accidentally updating the player twice but it makes the bullet move nicely so im keeping it lol
			//updating all alien positions
			if (isMovingRight) {
				for (int r = row - 1; r >= 0; r--) {
					for (int c = column - 1; c >= 0; c--) {
						if ((player.getBulletY() <= alienMatrix[r][c].getRectDestY() + 35) && (player.getBulletY() >= alienMatrix[r][c].getRectDestY()) && ((player.getBulletX() >= alienMatrix[r][c].getRectDestX()) && (player.getBulletX() <= alienMatrix[r][c].getRectDestX() + 35)) && !alienMatrix[r][c].isDead) { //checking to see if alien got hit by player
							isHit = true;
							playerBullet->reset(); //removing the bullet after it hits the alien
						}
						alienMatrix[r][c].Update(&switched, &isHit);

						//checking if alien has hit player with bullet
						if ((alienMatrix[r][c].getBulletY() <= player.getRecDestY() + 32) && (alienMatrix[r][c].getBulletY() >= player.getRecDestY())) {
							if (alienMatrix[r][c].getBulletX() >= player.getRecDestX() && alienMatrix[r][c].getBulletX() <= player.getRecDestX() + 32) {
								player.isDead = true;
								timer.Start(lifetime);
								alienMatrix[r][c].resetBullet(); //removing bullet after it hits player
								playerDeathCount++; //increment the death count
							}

						}
					}
				}
				if (switched) {
					isMovingRight = false;
				}
			}
			else {
				for (int r = 0; r < row; r++) {
					for (int c = 0; c < column; c++) {
						if ((player.getBulletY() <= alienMatrix[r][c].getRectDestY() + 35) && (player.getBulletY() >= alienMatrix[r][c].getRectDestY()) && ((player.getBulletX() >= alienMatrix[r][c].getRectDestX()) && (player.getBulletX() <= alienMatrix[r][c].getRectDestX() + 35)) && !alienMatrix[r][c].isDead) { //checking to see if alien got hit by player
							isHit = true;
							playerBullet->reset(); //removing the bullet after it hits the alien
						}
						alienMatrix[r][c].Update(&switched, &isHit);

						//checking if alien has hit player with bullet
						if ((alienMatrix[r][c].getBulletY() <= player.getRecDestY() + 32) && (alienMatrix[r][c].getBulletY() >= player.getRecDestY())) {
							if (alienMatrix[r][c].getBulletX() >= player.getRecDestX() && alienMatrix[r][c].getBulletX() <= player.getRecDestX() + 32) {
								player.isDead = true;
								timer.Start(lifetime);
								alienMatrix[r][c].resetBullet(); //removing bullet after it hits player
								playerDeathCount++; //increment the death count
							}
						}
					}
				}
				if (switched) {
					isMovingRight = true;
				}
			}
			switched = false; //resetting switched flag for next iteration

			player.Update();

			shield1->playerUpdate(playerBullet); //player to shield collision update
			shield2->playerUpdate(playerBullet);
			shield3->playerUpdate(playerBullet);
			shield4->playerUpdate(playerBullet);

			for (int r = 0; r < row; r++) { //alien to shield collision update
				for (int c = 0; c < column; c++) {
					shield1->alienUpdate(&alienMatrix[r][c]);
					shield2->alienUpdate(&alienMatrix[r][c]);
					shield3->alienUpdate(&alienMatrix[r][c]);
					shield4->alienUpdate(&alienMatrix[r][c]);
				}
			}

			//hearts update
			switch (playerDeathCount)
			{
			case 1:
				heart3->Update();
				needsRevived = true; //player is revived
				break;
			case 2:
				heart2->Update();
				needsRevived = true; //player is revived
				break;
			case 3:
				heart1->Update();
				needsRevived = false; //player's last life
				player.kill();
				//and it is also GAMEOVER in this case so don't forget to add that later
				break;
			default:
				break;
			}
		}
		else {
			//timer update
			timer.Update();
		}
		//--------------------------------------------------	
		
		
		

		//----draw------------------------------------------
		BeginDrawing();
			ClearBackground(BLACK);
			

			background.Draw();
			DrawFPS(0, 0);

			DrawLine(0, 745, 800, 745, WHITE);
			heart1->Draw();
			heart2->Draw();
			heart3->Draw();
			
			player.Draw();
			

			shield1->Draw();
			shield2->Draw();
			shield3->Draw();
			shield4->Draw();

			//drawing all aliens
			for (int r = 0; r < row; r++) {
				for (int c = 0; c < column; c++) {
					alienMatrix[r][c].Draw();
				}
			}
			
		EndDrawing();
		//--------------------------------------------------
	}

	//deleting stuff to deallocate mem
	delete playerBullet; //credit thenewchicken

	delete shield1;
	delete shield2;
	delete shield3;
	delete shield4;

	delete heart1;
	delete heart2;
	delete heart3;

	//closing, unloading
	UnloadTexture(backgroundTexture);
	UnloadTexture(shipTexture);
	UnloadTexture(bulletTexture);
	CloseWindow();

	return 0;
}