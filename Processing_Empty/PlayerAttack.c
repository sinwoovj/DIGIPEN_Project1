#include "PlayerAttack.h"
#include "Weapon.h"

void PlayerAttack(int num)
{
	if (num == 1)
		PlayerCloseAttack();
	else if (num == 2)
		PlayerLongAttack();
	else if (num == 3)
		PlayerWandAttack();

	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (isReach(&projectile[i].position_x, &projectile[i].position_y, &projectile[i].active))
		{
			SuccessAttack(player.weapon.num);
		}
	}
}
void SuccessAttack(int num)
{
	if (num == 2)
		enemy.health -= arrow.damage;
	else if (num == 3)
		enemy.health -= wand.damage;
}

/// <summary>
/// Short Range Attack
/// </summary>
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
		player.direction = 1;
		if (AttackCoolTime())
		{
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(player.coord.x + 25, player.coord.y, player.size, player.size + 25); //Draw trajectory
		}

	}
	else if (CP_Input_KeyDown(KEY_LEFT))
	{
		player.direction = 3;
		if (AttackCoolTime())
		{
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(player.coord.x - 25, player.coord.y, player.size, player.size + 25); //Draw trajectory
		}
	}
	else if (CP_Input_KeyDown(KEY_UP))
	{
		player.direction = 2;
		if (AttackCoolTime())
		{
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(player.coord.x, player.coord.y - 25, player.size + 25, player.size); //Draw trajectory
		}
	}
	else if (CP_Input_KeyDown(KEY_DOWN))
	{
		player.direction = 0;
		if (AttackCoolTime())
		{
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(player.coord.x, player.coord.y + 25, player.size + 25, player.size); //Draw trajectory
		}
	}
}

/// <summary>
/// Long Range Attack
/// </summary>
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

bool isReach(float* position_x, float* position_y, int* active)
{
	float distance = sqrtf(powf((enemy.coord.x - *position_x), 2.0) + powf((enemy.coord.y - *position_y), 2.0));
	if(distance <= (enemy.size / 2.0f))
	{
		*position_x = 0;
		*position_y = 0;
		*active = 0;
		return true;
	}
	else
		return false;
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


/// <summary>
/// Wand(Magical) Attack
/// </summary>
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
			SuccessAttack(player.weapon.num);
		}
	}
}