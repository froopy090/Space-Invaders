#include "Background.h"
#include "Player.h"
#include "Bullet.h"
#include "Alien.h"
#include "Shield.h"
#include "Heart.h"
#include "Timer.h"
#include "BonusAlien.h"
#include "iostream"
#include <fstream>
#include "string"
#include "algorithm"

//constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define TARGET_FPS 60
#define MAX_INPUT_CHARS 3

//some definitions
bool PAUSED = false;
typedef enum Gamescreen {LOGO = 0, TITLE, GAMEPLAY, GAMEOVER, WIN, HIGHSCORES};
struct highscore {
	char name[MAX_INPUT_CHARS + 1]; //3 chars for name + 1 for terminating char
	int score = 0;
};

//helper functions

//compares two highscore structs by their score value and returns 1 if the first is greater than the second highscore
bool compareHighScores(highscore& a, highscore& b) {
	return a.score > b.score;
}

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
	float alienSpeed = 1.05f;
	//float speedIncrement = .01f;

	bool alienGotShot = false;
	int alienDeathCounter = 0;


	//bonus alien variables
	Rectangle bonusAlienSource = {41, 10, 6, 4};
	Rectangle bonusAlienDest = {0, 50, 35, 35};


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
	BonusAlien bonusAlien(shipTexture, position, bonusAlienSource, bonusAlienDest);

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
	
	Timer logoTimer;
	logoTimer.Start(2.0f);

	//scores
	int player1Score = 0;

	int alien1Point = 10; //points for 4th and 5th row aliens
	int alien2Point = 20; //points for 2nd and 3rd row aliens
	int alien3Point = 30; //points for top row alien

	//screen
	Gamescreen currentScreen = LOGO;

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
			alien = new Alien(shipTexture, alienSource, alienDest, position, rotation, &alienSpeed, alienBullet, switched);
			alienMatrix[r][c] = *alien;
			alienMatrix[r][c].InitDest = alienDest;
			delete alien; //credit thenewchicken
		}

		alienDest.x = 100; //resetting the x position to prepare for a new row
		alienDest.y += 50; //moving down for the next row
	}
	alienDest.y = 100; //resetting the y position because idk

	//highscore variables
	highscore playerHighscore;
	char playerName[MAX_INPUT_CHARS + 1];
	int letterCount = 0;
	int key = 0;
	Rectangle textBox = {GetScreenWidth()/2 - 50, GetScreenHeight()/2 - 25, 100, 50};

	std::ofstream fileOut;
	std::ifstream fileIn;
	highscore readScore[100]; //array of scores to then be shown on screen
	bool saved = false;

	int adj = 0;
	int scoreY = 0;
	int maxScoreCount = 0; //there should be max 19 scores shown on the leaderboard, the others are still saved just not shown


	while (!WindowShouldClose()) {
		//game pauses while timer is running--------------
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




		//game screen update-----------------------------
		//-----------------------------------------------
		switch (currentScreen)
		{
		case LOGO:
			logoTimer.Update();
			if (logoTimer.Finished()) { //go to title screen after timer is done
				currentScreen = TITLE;
			}
			break;
		case TITLE:
			if (IsKeyPressed(KEY_ENTER)) { //press enter to start the game
				currentScreen = GAMEPLAY;
			}

			saved = false; //now I can save a new score on file
			break;
		case GAMEPLAY:
			if (!PAUSED) {
				//----events-------------------------------------
				player.Event();
				bonusAlien.Event();
				for (int r = 0; r < row; r++) { //alien events
					for (int c = 0; c < column; c++) {
						alienMatrix[r][c].Event();
					}
				}
				//-------------------------------------------------

				//----update----------------------------------------
				background.Update();
				player.Update(); //I'm accidentally updating the player twice but it makes the bullet move nicely so im keeping it lol
				bonusAlien.checkBulletCollision(playerBullet, &player1Score);
				bonusAlien.Update();
				//updating all alien positions
				if (isMovingRight) {
					for (int r = row - 1; r >= 0; r--) {
						for (int c = column - 1; c >= 0; c--) {
							if ((player.getBulletY() <= alienMatrix[r][c].getRectDestY() + 35) && (player.getBulletY() >= alienMatrix[r][c].getRectDestY()) && ((player.getBulletX() >= alienMatrix[r][c].getRectDestX()) && (player.getBulletX() <= alienMatrix[r][c].getRectDestX() + 35)) && !alienMatrix[r][c].isDead) { //checking to see if alien got hit by player
								isHit = true;
								alienGotShot = true;
								alienDeathCounter++;
								//alienSpeed += speedIncrement;
								playerBullet->ResetPlayerBullet(); //removing the bullet after it hits the alien
								switch (r) //updating the score
								{
								case 0:
									player1Score += alien3Point;
									break;
								case 1:
									player1Score += alien2Point;
									break;
								case 2:
									player1Score += alien2Point;
									break;
								case 3:
									player1Score += alien1Point;
									break;
								case 4:
									player1Score += alien1Point;
									break;
								default:
									break;
								}
							}
							alienMatrix[r][c].Update(&switched, &isHit);
							alienMatrix[r][c].getAlienBullet()->CheckCollision(playerBullet); //checking if player bullet hits alien bullet

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
								alienGotShot = true;
								alienDeathCounter++;
								//alienSpeed += speedIncrement;
								playerBullet->ResetPlayerBullet(); //removing the bullet after it hits the alien
								switch (r) //updating the score
								{
								case 0:
									player1Score += alien3Point;
									break;
								case 1:
									player1Score += alien2Point;
									break;
								case 2:
									player1Score += alien2Point;
									break;
								case 3:
									player1Score += alien1Point;
									break;
								case 4:
									player1Score += alien1Point;
									break;
								default:
									break;
								}
							}
							alienMatrix[r][c].Update(&switched, &isHit);
							alienMatrix[r][c].getAlienBullet()->CheckCollision(playerBullet); //checking if player bullet hits alien bullet

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

						//updating alien speeds
						if (alienGotShot) {
							alienMatrix[r][c].UpdateSpeed(); //updating all speeds only when an alien has been shot
						}

						//checking if aliens reached the bottom of screen
						if (alienMatrix[r][c].Wins()) {
							currentScreen = GAMEOVER;
						}
					}
				}
				alienGotShot = false;

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
					currentScreen = GAMEOVER; //its game over :(
					break;
				default:
					break;
				}
			}
			else {
				//timer update
				timer.Update();
			}

			if (alienDeathCounter == (row * column)) { //if all aliens are dead, player wins
				currentScreen = WIN;
			}


			//cheat code: insta-wins the game
			/*if (IsKeyPressed(KEY_COMMA)) {
				currentScreen = WIN;
			}*/

			//saving score
			playerHighscore.score = player1Score;
			//--------------------------------------------------	
			break;
		case GAMEOVER:
			//resetting entities
			for (int r = 0; r < row; r++) {
				for (int c = 0; c < column; c++) {
					alienMatrix[r][c].Reset();
					alienDeathCounter = 0;
				}
			}

			bonusAlien.Reset();

			heart1->Reset();
			heart2->Reset();
			heart3->Reset();

			player.Reset();
			playerDeathCount = 0;
			player1Score = 0;

			shield1->Reset();
			shield2->Reset();
			shield3->Reset();
			shield4->Reset();

			//user input for username
			key = GetCharPressed();

			//check if more characters have been pressed on the same frame
			while (key > 0) {
				//only keys in range [32, 125]
				if ((key >= 32) && (key <= 125) && letterCount < MAX_INPUT_CHARS) {
					playerName[letterCount] = (char)key;
					playerName[letterCount + 1] = '\0'; //add null terminator at the end of the string
					letterCount++;
				}
				key = GetCharPressed(); //checking for next character
			}

			//checking if user deletes letters
			if (IsKeyPressed(KEY_BACKSPACE)) {
				letterCount--;
				if (letterCount < 0) letterCount = 0;
				playerName[letterCount] = '\0';
			}

			//saving the name in struct
			if (IsKeyPressed(KEY_ENTER)) {
				strcpy_s(playerHighscore.name, playerName);
				currentScreen = HIGHSCORES;
			}
			break;
		case HIGHSCORES:
			if (IsKeyPressed(KEY_ENTER)) currentScreen = TITLE; //enter to return to title screen


			//reading/writing to file
			if (!saved) { //I only want to read/write ONCE, this should not repeat every iteration
				//writing to file
				fileOut.open("resources/Highscores.bin", std::ios::binary | std::ios::app);
				if (fileOut.is_open()) {
					fileOut.write(reinterpret_cast<char*>(&playerHighscore), sizeof(highscore));

					std::cout << "success writing in fileOut!" << std::endl;

					fileOut.close();
				}
				else {
					std::cerr << "error opening the fileOut for writing" << std::endl;
				}

				//reading from the file
				fileIn.open("resources/Highscores.bin", std::ios::binary);
				if (fileIn.is_open()) {
					fileIn.read(reinterpret_cast<char*>(&readScore), 100 * sizeof(highscore));

					std::cout << "success reading fileIn!" << std::endl;

					fileIn.close();
				}
				else {
					std::cerr << "error opening the fileIn for reading" << std::endl;
				}
				saved = true;

				//ordering readScore in descending order
				std::sort(readScore, readScore + 100, compareHighScores);
			}
			break;
		case WIN:
			if (IsKeyPressed(KEY_ENTER)) { //press enter to keep playing
				currentScreen = GAMEPLAY;
			}
			//resetting entities, but not resetting the hearts
			for (int r = 0; r < row; r++) {
				for (int c = 0; c < column; c++) {
					alienMatrix[r][c].Reset();
					alienDeathCounter = 0;
				}
			}

			bonusAlien.Reset();

			player.Reset();

			shield1->Reset();
			shield2->Reset();
			shield3->Reset();
			shield4->Reset();
			break;
		default:
			break;
		}
		//-----------------------------------------------
		//-----------------------------------------------
		
		

		//----draw------------------------------------------
		BeginDrawing();
			ClearBackground(BLACK);
			
			switch (currentScreen)
			{
			case LOGO:
				DrawText("FROOPY GAMES", 100, 300, 50, YELLOW);
				break;
			case TITLE:
				DrawText("SPACE INVADERS", 100, 50, 70, WHITE);
				DrawText("Press ENTER to start", 100, 150, 50, WHITE);
				break;
			case GAMEPLAY:
				background.Draw();
				DrawText("SCORE < 1 >", 10, 10, 21, WHITE);
				DrawText(TextFormat("%i", player1Score), 40, 30, 19, WHITE);
				DrawText("HI-SCORE", 150, 10, 21, WHITE);
				//DrawFPS(0, 0);

				DrawLine(0, 745, 800, 745, WHITE);
				heart1->Draw();
				heart2->Draw();
				heart3->Draw();

				player.Draw();
				bonusAlien.Draw();

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
				break;
			case GAMEOVER:
				DrawText("GAMEOVER :(", 100, 100, 70, WHITE);
				DrawText(TextFormat("Final Score: %i", playerHighscore.score), 100, 170, 60, WHITE);
				DrawText("Type your name :>", textBox.x - 150, textBox.y - 70, 50, WHITE);
				DrawRectangleRec(textBox, GRAY);
				if(letterCount > 0) DrawText(playerName, (int)textBox.x + 5, (int)textBox.y + 8, 40, WHITE);
				break;
			case HIGHSCORES:
				DrawText("TOP 20 HIGHSCORES", 75, 20, 60, YELLOW);

				//character array to hold the combined string
				char combinedArray[20];

				//printing scores on screen
				scoreY = 150;
				for (int i = 0; i < 20; i++) { //only showing top 20 highscores
					if (readScore[i].score > 0 && readScore[i].score < 1000000) {
						//copying the characters of player name into array
						strcpy_s(combinedArray, readScore[i].name);

						//appending the score
						strcat_s(combinedArray, " - ");
						char scoreStr[5]; //buffer to hold the score as string
						sprintf_s(scoreStr, "%d", readScore[i].score);
						strcat_s(combinedArray, scoreStr);
						strcat_s(combinedArray, "\n"); //at this point I have "name - score\n"

						DrawText(combinedArray, 345, scoreY, 22, WHITE);

						//adjusting positioning
						scoreY += 30;
					}
				}
				break;
			case WIN:
				//drawing game
				background.Draw();
				DrawText("SCORE < 1 >", 10, 10, 21, WHITE);
				DrawText(TextFormat("%i", player1Score), 40, 30, 19, WHITE);
				DrawText("HI-SCORE", 150, 10, 21, WHITE);
				//DrawFPS(0, 0);

				DrawLine(0, 745, 800, 745, WHITE);
				heart1->Draw();
				heart2->Draw();
				heart3->Draw();

				player.Draw();
				bonusAlien.Draw();

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

				DrawText("CLEAR !", 300, 400, 70, YELLOW);
				DrawText("Press ENTER to keep going!", 50, 500, 30, YELLOW);
				break;
			default:
				break;
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