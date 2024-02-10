#include "Heart.h"

Heart::Heart(float offset)
	:xPos(X + offset), playerDied(false)
{
	top1 = { xPos, Y, 9,4 };
	top2 = { xPos + 15, Y, 9, 4 };
	body = { xPos - 4, Y + 4, 32, 8 };
	bottom1 = { xPos, Y + 12, 24, 4 };
	bottom2 = { xPos + 4, Y + 16, 16, 4 };
	bottom3 = { xPos + 8, Y + 20, 8, 4 };
}

void Heart::Draw() {
	if (!playerDied) {
		DrawRectangleRec(top1, WHITE);
		DrawRectangleRec(top2, WHITE);
		DrawRectangleRec(body, WHITE);
		DrawRectangleRec(bottom1, WHITE);
		DrawRectangleRec(bottom2, WHITE);
		DrawRectangleRec(bottom3, WHITE);
	}
}

void Heart::Update() {
	playerDied = true;
}