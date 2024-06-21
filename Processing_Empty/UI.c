#include "UI.h"

#include <stdio.h>
#include <time.h>
#include "Player.h"
#include "Enemy.h"
#include "Standard.h"

const float HpSize = 30.f;

void Text(char* text, float x, float y) 
{
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText(text, x, y);
}

void ShowPlayerHP() 
{
	if(player.isAlive)
	{
		CP_Settings_TextSize(HpSize);
		char str[100];
		sprintf_s(str, 50, "Player.HP : %5.2f", player.health);
		Text(str, 10, 30);
	}
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

	float phaseX = WindowWidthHalf - 200;
	float textSize = 200.f;
	if (currentTime - phaseStartTime < displayDuration) {
		CP_Settings_TextSize(textSize);
		if (enemy.phase == 2)
		{
			CP_Font_DrawText("Phase 2", phaseX, WindowHeightHalf);
		}
		else if (enemy.phase == 3)
		{
			CP_Font_DrawText("Phase 3", phaseX, WindowHeightHalf);
		}
		else if (enemy.phase == 4)
		{
			CP_Font_DrawText("The End", phaseX, WindowHeightHalf);
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
				enemy.health = (float)enemy.maxHP;
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
				enemy.health = (float)enemy.maxHP;
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
				enemy.health = (float)enemy.maxHP;
				isPhase3Full = false;
			}
		}
	}


	float enemyHP = enemy.health * (9.8f / enemy.phase);
	float enemyHP_X = WindowWidthHalf / 2.0f;
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRectAdvanced(enemyHP_X, 30, enemyHP, 30, 0.f, 10.f);
}

void UpdatePlayerHp()
{
	if(player.isAlive)
	{
		float playerHP = player.health;
		float playerHP_X = player.coord.x - (player.size / 2.0f);
		float playerHP_Y = player.coord.y - (player.size / 2.0f);
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawRectAdvanced(playerHP_X, playerHP_Y, playerHP, 10, 0.f, 10.f);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 0));
		CP_Graphics_DrawRect(playerHP_X, playerHP_Y, playerHP, 10.f);
	}
}