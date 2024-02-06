#include "Shield.h"

Shield::Shield(float offsetX)
	: offsetX(offsetX), xPos(X_POS + offsetX), yPos(Y_POS)
{
	for (int row = 0; row < MAX_HEIGHT / PIXEL_SIZE; row++) {
		for (int column = 0; column < MAX_WIDTH / PIXEL_SIZE; column++) {
			pixelRec[row][column] = { xPos, yPos, PIXEL_SIZE, PIXEL_SIZE, };
			xPos += PIXEL_SIZE;
			pixelColor[row][column] = WHITE;
		}
		xPos = X_POS + offsetX;
		yPos += PIXEL_SIZE;
	}
	yPos = Y_POS;
}

void Shield::Draw() {
	for (int row = 0; row < MAX_HEIGHT / PIXEL_SIZE; row++) {
		for (int column = 0; column < MAX_WIDTH / PIXEL_SIZE; column++) {
			//first row 'deleted' pixels
			if (row == 0 && (column == 0 || column == 1 || column == 2 || column == 3 
				|| column == MAX_WIDTH / PIXEL_SIZE - 4 || column == MAX_WIDTH / PIXEL_SIZE - 3
				|| column == MAX_WIDTH / PIXEL_SIZE - 2 || column == MAX_WIDTH / PIXEL_SIZE - 1)) {
				pixelColor[row][column] = BLANK;
				DrawRectangleRec(pixelRec[row][column], pixelColor[row][column]);
			}
			//second row 'deleted' pixels
			else if (row == 1 && (column == 0 || column == 1 || column == 2
				|| column == MAX_WIDTH / PIXEL_SIZE - 3
				|| column == MAX_WIDTH / PIXEL_SIZE - 2 || column == MAX_WIDTH / PIXEL_SIZE - 1)) {
				pixelColor[row][column] = BLANK;
				DrawRectangleRec(pixelRec[row][column], pixelColor[row][column]);
			}
			//third row 'deleted' pixels
			else if (row == 2 && (column == 0 || column == 1
				|| column == MAX_WIDTH / PIXEL_SIZE - 2 || column == MAX_WIDTH / PIXEL_SIZE - 1)) {
				pixelColor[row][column] = BLANK;
				DrawRectangleRec(pixelRec[row][column], pixelColor[row][column]);
			}
			//fourth row 'deleted' pixels
			else if (row == 3 && (column == 0
				|| column == MAX_WIDTH / PIXEL_SIZE - 1)) {
				pixelColor[row][column] = BLANK;
				DrawRectangleRec(pixelRec[row][column], pixelColor[row][column]);
			}
			//last row and 2nd to last row 'deleted' pixels
			else if ((row == MAX_HEIGHT / PIXEL_SIZE - 1 || row == MAX_HEIGHT / PIXEL_SIZE - 2) 
				&& (column >= 4 && column <= MAX_WIDTH / PIXEL_SIZE - 5)) {
				pixelColor[row][column] = BLANK;
				DrawRectangleRec(pixelRec[row][column], pixelColor[row][column]);
			}
			//3rd to last row 'deleted' pixels
			else if ((row == MAX_HEIGHT / PIXEL_SIZE - 3 || row == MAX_HEIGHT / PIXEL_SIZE - 4)
				&& (column >= 5 && column <= MAX_WIDTH / PIXEL_SIZE - 6)) {
				pixelColor[row][column] = BLANK;
				DrawRectangleRec(pixelRec[row][column], pixelColor[row][column]);
			}
			//next 2 rows
			else if ((row == MAX_HEIGHT / PIXEL_SIZE - 5 || row == MAX_HEIGHT / PIXEL_SIZE - 6)
				&& (column >= 6 && column <= MAX_WIDTH / PIXEL_SIZE - 7)) {
				pixelColor[row][column] = BLANK;
				DrawRectangleRec(pixelRec[row][column], pixelColor[row][column]);
			}
			//next 2 rows
			else if ((row == MAX_HEIGHT / PIXEL_SIZE - 7 || row == MAX_HEIGHT / PIXEL_SIZE - 8)
				&& (column >= 7 && column <= MAX_WIDTH / PIXEL_SIZE - 8)) {
				pixelColor[row][column] = BLANK;
				DrawRectangleRec(pixelRec[row][column], pixelColor[row][column]);
			}
			else {
				DrawRectangleRec(pixelRec[row][column], pixelColor[row][column]);
			}
		}
	}
}

void Shield::alienUpdate(Alien *alien) {
	Color whiteColor = WHITE;
	//alien bullet collision
	for (int row = 0; row < MAX_HEIGHT / PIXEL_SIZE; row++) {
		for (int column = 0; column < MAX_WIDTH / PIXEL_SIZE; column++) {
			if (alien->getBulletX() >= pixelRec[row][column].x && alien->getBulletX() <= pixelRec[row][column].x + PIXEL_SIZE && *(int*)&pixelColor[row][column] == *(int*)&whiteColor) {
				if (alien->getBulletY() >= pixelRec[row][column].y && alien->getBulletY() <= pixelRec[row][column].y + PIXEL_SIZE && *(int*)&pixelColor[row][column] == *(int*)&whiteColor) {
					alien->setBulletStatus(false);
					pixelColor[row][column] = BLANK;
				}
			}
		}
	}
}

void Shield::playerUpdate(Bullet *playerBullet) {
	Color whiteColor = WHITE;
	//player bullet collision
	for (int row = 0; row < MAX_HEIGHT / PIXEL_SIZE; row++) {
		for (int column = 0; column < MAX_WIDTH / PIXEL_SIZE; column++) {
			if (playerBullet->getRectDestX() >= pixelRec[row][column].x && playerBullet->getRectDestX() <= pixelRec[row][column].x + PIXEL_SIZE && *(int*)&pixelColor[row][column] == *(int*)&whiteColor) {
				if (playerBullet->getRectDestY() >= pixelRec[row][column].y && playerBullet->getRectDestY() <= pixelRec[row][column].y + PIXEL_SIZE && *(int*)&pixelColor[row][column] == *(int*)&whiteColor) {
					playerBullet->reset();
					pixelColor[row][column] = BLANK;
				}
			}
		}
	}
}