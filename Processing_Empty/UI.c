#include "UI.h"
const float HpSize = 30.f;

const float windowX = 1920 / 2.0;
const float windowY = 1080 / 2.0;

void Text(char* text, float x, float y) 
{
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText(text, x, y);
}

void ShowPlayerHP() 
{
	CP_Settings_TextSize(HpSize);
	char str[100];
	sprintf_s(str, 50, "Player.HP : %5.2f", player.health);
	Text(str, 10, 30);
}

void ShowEnemyHP() 
{
	CP_Settings_TextSize(HpSize);
	char str[100];
	sprintf_s(str, 50, "Enemy.HP : %5.2f", enemy.health);
	Text(str, 1520, 30);
}

void ShowUI() 
{
	ShowPlayerHP();
	ShowEnemyHP();
}

float phaseStartTime = 0.0f;
int currentPhase = 0;
const float displayDuration = 2.0f;
void UpdatePhase()
{
	float currentTime = (float)clock() / CLOCKS_PER_SEC;
	if (enemy.phase != currentPhase) {
		currentPhase = enemy.phase;
		phaseStartTime = currentTime;
	}

	float phaseX = windowX - 200;
	float textSize = 200.f;
	if (currentTime - phaseStartTime < displayDuration) {
		CP_Settings_TextSize(textSize);
		if (enemy.phase == 2)
		{
			CP_Font_DrawText("Phase 2", phaseX, windowY);
		}
		else if (enemy.phase == 3)
		{
			CP_Font_DrawText("Phase 3", phaseX, windowY);
		}
		else if (enemy.phase == 4)
		{
			CP_Font_DrawText("The End", phaseX, windowY);
		}
	}
}

bool isPhase2Full = true;
bool isPhase3Full = true;
void UpdateEnemyHp()
{
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 0));
	CP_Graphics_DrawRect(1920 / 4.0, 30, 980, 30);

	if (enemy.phase == 1)
	{
		if (enemy.health != enemy.maxHP && enemy.isPhase1Full)
		{
			enemy.health += 10;
			if (enemy.health >= enemy.maxHP)
			{
				enemy.health = enemy.maxHP;
				enemy.isPhase1Full = false;
			}
		}
	}
	else if (enemy.phase == 2)
	{
		enemy.maxHP = enemy.phase * 100;
		if (enemy.health != enemy.maxHP && isPhase2Full)
		{
			enemy.health += 10;
			if (enemy.health >= enemy.maxHP)
			{
				enemy.health = enemy.maxHP;
				isPhase2Full = false;
			}
		}
		
	}
	else if (enemy.phase == 3)
	{
		enemy.maxHP = enemy.phase * 100;
		if (enemy.health != enemy.maxHP && isPhase3Full)
		{
			enemy.health += 10;
			if (enemy.health >= enemy.maxHP)
			{
				enemy.health = enemy.maxHP;
				isPhase3Full = false;
			}
		}
	}


	float enemyHP = enemy.health * (9.8f / enemy.phase);
	float enemyHP_X = windowX / 2.0;
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRectAdvanced(enemyHP_X, 30, enemyHP, 30, 0.f, 10.f);
}

void UpdatePlayerHp()
{
	float playerHP = player.health;
	float playerHP_X = player.coord.x - (player.size / 2.0);
	float playerHP_Y = player.coord.y - (player.size / 2.0);
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawRectAdvanced(playerHP_X, playerHP_Y, playerHP, 10, 0.f, 10.f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 0));
	CP_Graphics_DrawRect(playerHP_X, playerHP_Y, playerHP, 10.f);
}