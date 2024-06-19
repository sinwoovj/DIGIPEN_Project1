#include "UI.h"

void Text(char* text, float x, float y) {
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText(text, x, y);
}

void ShowPlayerHP() {
	char str[100];
	sprintf_s(str, 50, "Player.HP : %5.2f", player.health);
	Text(str, 10, 10);
}

void ShowPlayerEnemy() {
	char str[100];
	sprintf_s(str, 50, "Enemy.HP : %5.2f", enemy.health);
	Text(str, 1520, 10);
}

void ShowUI() {
	ShowPlayerHP();
	ShowPlayerEnemy();
}
