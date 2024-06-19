#include "PlayerAttack.h"

int frameCount = 0;
const int frameLimit = 10;
int AttackCoolTime() 
{
	if (++frameCount == frameLimit) 
	{
		frameCount = 0;
		return 1;
	}
	return 0;
}

void PlayerCloseAttack()
{
	if (CP_Input_KeyDown(KEY_RIGHT))
	{
		if (AttackCoolTime())
		{
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(player.coord.x + 25, player.coord.y, player.size, player.size + 25); //Draw trajectory
		}

	}
	else if (CP_Input_KeyDown(KEY_LEFT))
	{
		if (AttackCoolTime())
		{
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(player.coord.x - 25, player.coord.y, player.size, player.size + 25); //Draw trajectory
		}
	}
	else if (CP_Input_KeyDown(KEY_UP))
	{
		if (AttackCoolTime())
		{
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(player.coord.x, player.coord.y - 25, player.size + 25, player.size); //Draw trajectory
		}
	}
	else if (CP_Input_KeyDown(KEY_DOWN))
	{
		if (AttackCoolTime())
		{
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(player.coord.x, player.coord.y + 25, player.size + 25, player.size); //Draw trajectory
		}
	}
}

int LAframeCount = 0;
int LAframeLimit = 10;
int LongAttackCoolTime()
{
	if (LAframeCount >= LAframeLimit)
	{
		LAframeCount = 0;
		return 1;
	}
	LAframeCount++;
	return 0;
}

void PlayerLongAttack()
{
	float velocity = 10.0f;
	if (CP_Input_KeyDown(KEY_RIGHT))
	{
		if (LongAttackCoolTime())
		{
			Create_PlayerProjectile(player.coord.x + 20, player.coord.y + 20, velocity, 1);
		}
	}
	else if (CP_Input_KeyDown(KEY_LEFT))
	{
		if (LongAttackCoolTime())
		{
			Create_PlayerProjectile(player.coord.x + 20, player.coord.y + 20, velocity, 2);
		}
	}
	else if (CP_Input_KeyDown(KEY_UP))
	{
		if (LongAttackCoolTime())
		{
			Create_PlayerProjectile(player.coord.x + 20, player.coord.y + 20, velocity, 3);
		}
	}
	else if (CP_Input_KeyDown(KEY_DOWN))
	{
		if (LongAttackCoolTime())
		{
			Create_PlayerProjectile(player.coord.x + 20, player.coord.y + 20, velocity, 4);
		}
	}
}

void PlayerWandAttack()
{
	float wand_x = CP_Random_RangeFloat(860, 1060);
	float wand_y = CP_Random_RangeFloat(440, 640);
	if (CP_Input_KeyDown(KEY_RIGHT) || CP_Input_KeyDown(KEY_LEFT) || CP_Input_KeyDown(KEY_UP) || CP_Input_KeyDown(KEY_DOWN))
	{
		if (AttackCoolTime())
		{
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(wand_x, wand_y, player.size, player.size); //Draw Thunder
		}
	}
}