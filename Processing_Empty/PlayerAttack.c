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
		if (isArrowReach(&projectile[i].position_x, &projectile[i].position_y, &projectile[i].active))
		{
			SuccessAttack(player.weapon.num);
		}
	}
}
void SuccessAttack(int num)
{
	if (num == 1)
		enemy.health -= sword.damage;
	else if (num == 2)
		enemy.health -= arrow.damage;
	else if (num == 3)
		enemy.health -= wand.damage;

	CP_Sound_PlayAdvanced(bossHurt, 0.2f, 1.0f, FALSE, CP_SOUND_GROUP_1);
}

/// <summary>
/// Short Range Attack
/// </summary>
bool isSwordReach(int direction, float swordWidth, float swordHeight, float swordHand)
{
	if (direction == 0) //right
	{
		float r = enemy.size / 2.0;
		float x1 = player.coord.x + player.size + swordHeight;
		float y1 = player.coord.y - swordHand;
		float y2 = player.coord.y + player.size + swordHand;

		float distance1 = sqrtf(powf((enemy.coord.x - x1), 2) + powf((enemy.coord.y - y1), 2));
		float distance2 = sqrtf(powf((enemy.coord.x - x1), 2) + powf((enemy.coord.y - y2), 2));

		if (distance1 < r || distance2 < r)
			return true;
	}
	else if (direction == 1) //left
	{
		float r = enemy.size / 2.0;
		float x1 = player.coord.x - swordHeight;
		float y1 = player.coord.y - swordHand;
		float y2 = player.coord.y - swordHand + swordWidth;

		float distance1 = sqrtf(powf((enemy.coord.x - x1), 2) + powf((enemy.coord.y - y1), 2));
		float distance2 = sqrtf(powf((enemy.coord.x - x1), 2) + powf((enemy.coord.y - y2), 2));

		if (distance1 < r || distance2 < r)
			return true;
	}
	else if (direction == 2) //up
	{
		float r = enemy.size / 2.0;
		float x1 = player.coord.x - swordHand;
		float x2 = player.coord.x + player.size + swordHand;
		float y1 = player.coord.y - swordHeight;

		float distance1 = sqrtf(powf((enemy.coord.x - x1), 2) + powf((enemy.coord.y - y1), 2));
		float distance2 = sqrtf(powf((enemy.coord.x - x2), 2) + powf((enemy.coord.y - y1), 2));

		if (distance1 < r || distance2 < r)
			return true;
	}
	else if (direction == 3)
	{
		float r = enemy.size / 2.0;
		float x1 = player.coord.x - swordHand;
		float x2 = player.coord.x + player.size + swordHand;
		float y1 = player.coord.y + player.size + swordHeight;

		float distance1 = sqrtf(powf((enemy.coord.x - x1), 2) + powf((enemy.coord.y - y1), 2));
		float distance2 = sqrtf(powf((enemy.coord.x - x2), 2) + powf((enemy.coord.y - y1), 2));

		if (distance1 < r || distance2 < r)
			return true;
	}
}
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
	float swordWidth = (sword.range * 2.0);
	float swordHeight = (sword.range * 3 / 2.0);
	float swordHand = (sword.range / 2.0);
	if (CP_Input_KeyDown(KEY_RIGHT) && player.isAlive)
	{
		player.direction = 1;
		if (AttackCoolTime())
		{
			CP_Sound_PlayAdvanced(swordSound, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(player.coord.x + player.size, player.coord.y - swordHand, swordHeight, swordWidth); //Draw trajectory
			int right = 0;
			if (isSwordReach(right, swordWidth, swordHeight, swordHand))
				SuccessAttack(player.weapon.num);
		}

	}
	else if (CP_Input_KeyDown(KEY_LEFT) && player.isAlive)
	{
		player.direction = 3;
		if (AttackCoolTime())
		{
			CP_Sound_PlayAdvanced(swordSound, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(player.coord.x - swordHeight, player.coord.y - swordHand, swordHeight, swordWidth); //Draw trajectory
			int left = 1;
			if (isSwordReach(left, swordWidth, swordHeight, swordHand))
				SuccessAttack(player.weapon.num);
		}
	}
	else if (CP_Input_KeyDown(KEY_UP) && player.isAlive)
	{
		player.direction = 2;
		if (AttackCoolTime())
		{
			CP_Sound_PlayAdvanced(swordSound, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(player.coord.x - swordHand, player.coord.y - swordHeight, swordWidth, swordHeight); //Draw trajectory
			int up = 2;
			if (isSwordReach(up, swordWidth, swordHeight, swordHand))
				SuccessAttack(player.weapon.num);
		}
	}
	else if (CP_Input_KeyDown(KEY_DOWN) && player.isAlive)
	{
		player.direction = 0;
		if (AttackCoolTime())
		{
			CP_Sound_PlayAdvanced(swordSound, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(player.coord.x - swordHand, player.coord.y + sword.range, swordWidth, swordHeight); //Draw trajectory
			int up = 3;
			if (isSwordReach(up, swordWidth, swordHeight, swordHand))
				SuccessAttack(player.weapon.num);
		}
	}
}


/// <summary>
/// Long Range Attack
/// </summary>
bool isArrowReach(float* position_x, float* position_y, int* active)
{
	float distance = sqrtf(powf((enemy.coord.x - *position_x), 2.0) + powf((enemy.coord.y - *position_y), 2.0));
	if (distance <= (enemy.size / 2.0f))
	{
		*position_x = 0;
		*position_y = 0;
		*active = 0;
		return true;
	}
	else
		return false;
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
	if (CP_Input_KeyDown(KEY_RIGHT) && player.isAlive)
	{
		if (LongAttackCoolTime())
		{
			Create_PlayerProjectile(player.coord.x + 20, player.coord.y + 20, velocity, 1);
			CP_Sound_PlayAdvanced(arrowSound, 0.3f, 0.8f, FALSE, CP_SOUND_GROUP_1);
		}
	}
	else if (CP_Input_KeyDown(KEY_LEFT) && player.isAlive)
	{
		if (LongAttackCoolTime())
		{
			Create_PlayerProjectile(player.coord.x + 20, player.coord.y + 20, velocity, 2);
			CP_Sound_PlayAdvanced(arrowSound, 0.3f, 0.8f, FALSE, CP_SOUND_GROUP_1);
		}
	}
	else if (CP_Input_KeyDown(KEY_UP) && player.isAlive)
	{
		if (LongAttackCoolTime())
		{
			Create_PlayerProjectile(player.coord.x + 20, player.coord.y + 20, velocity, 3);
			CP_Sound_PlayAdvanced(arrowSound, 0.3f, 0.8f, FALSE, CP_SOUND_GROUP_1);
		}
	}
	else if (CP_Input_KeyDown(KEY_DOWN) && player.isAlive)
	{
		if (LongAttackCoolTime())
		{
			Create_PlayerProjectile(player.coord.x + 20, player.coord.y + 20, velocity, 4);
			CP_Sound_PlayAdvanced(arrowSound, 0.3f, 0.8f, FALSE, CP_SOUND_GROUP_1);
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
	if ((CP_Input_KeyDown(KEY_RIGHT) || CP_Input_KeyDown(KEY_LEFT) || CP_Input_KeyDown(KEY_UP) || CP_Input_KeyDown(KEY_DOWN)) && player.isAlive)
	{
		if (AttackCoolTime())
		{
			CP_Sound_PlayAdvanced(wandSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(wand_x, wand_y, player.size, player.size); //Draw Thunder
			SuccessAttack(player.weapon.num);
		}
	}
}