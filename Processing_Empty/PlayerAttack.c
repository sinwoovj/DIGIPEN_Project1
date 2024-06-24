#include "PlayerAttack.h"
#include "Weapon.h"
#include "cprocessing.h"
#include "Player.h"
#include "PlayerProjectile.h"
#include "Weapon.h"
#include "Enemy.h"
#include <math.h>
#include "Calculate.h"
#include "EnemyProjectile.h"
#include "Image.h"
#include "Sound.h"


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
		float r = enemy.size / 2.0f;
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
		float r = enemy.size / 2.0f;
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
		float r = enemy.size / 2.0f;
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
		float r = enemy.size / 2.0f;
		float x1 = player.coord.x - swordHand;
		float x2 = player.coord.x + player.size + swordHand;
		float y1 = player.coord.y + player.size + swordHeight;

		float distance1 = sqrtf(powf((enemy.coord.x - x1), 2) + powf((enemy.coord.y - y1), 2));
		float distance2 = sqrtf(powf((enemy.coord.x - x2), 2) + powf((enemy.coord.y - y1), 2));

		if (distance1 < r || distance2 < r)
			return true;
	}

	return false;
}
int frameCount = 0;
const int frameLimit = 10;

int swordFrame = 0;
float swordAnimationTime = 0.0f;
float swordDuration = 0.05f;
int CloseAttackCoolTime()
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
	float swordWidth = (sword.range * 2.0f);
	float swordHeight = (sword.range * 3 / 2.0f);
	float swordHand = (sword.range / 2.0f);

	swordAnimationTime += CP_System_GetDt();
	if (swordAnimationTime >= swordDuration)
	{
		swordAnimationTime = 0.0f;
		swordFrame++;
		if (swordFrame >= swordFrameNum)
		{
			swordFrame = 0;
		}
	}

	if (CP_Input_KeyDown(KEY_RIGHT) && player.isAlive)
	{
		if (CloseAttackCoolTime())
		{
			CP_Sound_PlayAdvanced(swordSound, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			int right = 0;
			if (isSwordReach(right, swordWidth, swordHeight, swordHand))
				SuccessAttack(player.weapon.num);
		}
		CP_Image_Draw(SwordImg[swordFrame], player.coord.x + (player.size * 2.0f), player.coord.y + (player.size /2.0f), 100, 150, 255);

	}
	else if (CP_Input_KeyDown(KEY_LEFT) && player.isAlive)
	{
		if (CloseAttackCoolTime())
		{
			CP_Sound_PlayAdvanced(swordSound, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			int left = 1;
			if (isSwordReach(left, swordWidth, swordHeight, swordHand))
				SuccessAttack(player.weapon.num);
		}
		CP_Image_Draw(SwordImg[swordFrame], player.coord.x - player.size, player.coord.y + (player.size / 2.0f), 100, 150, 255);
	}
	else if (CP_Input_KeyDown(KEY_UP) && player.isAlive)
	{
		if (CloseAttackCoolTime())
		{
			CP_Sound_PlayAdvanced(swordSound, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			int up = 2;
			if (isSwordReach(up, swordWidth, swordHeight, swordHand))
				SuccessAttack(player.weapon.num);
		}
		CP_Image_DrawAdvanced(SwordImg[swordFrame], player.coord.x + (player.size / 2.0f), player.coord.y - (player.size), 100, 150, 255, 90);
	}
	else if (CP_Input_KeyDown(KEY_DOWN) && player.isAlive)
	{
		if (CloseAttackCoolTime())
		{
			CP_Sound_PlayAdvanced(swordSound, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			int up = 3;
			if (isSwordReach(up, swordWidth, swordHeight, swordHand))
				SuccessAttack(player.weapon.num);
		}
		CP_Image_DrawAdvanced(SwordImg[swordFrame], player.coord.x + (player.size / 2.0f), player.coord.y + (player.size * 2.0f), 100, 150, 255, -90);
	}
}


/// <summary>
/// Long Range Attack
/// </summary>
bool isArrowReach(float* position_x, float* position_y, int* active)
{
	float distance = sqrtf(powf((enemy.coord.x - *position_x), 2.0f) + powf((enemy.coord.y - *position_y), 2.0f));
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
int thunderFrame = 0;
float thunderAnimationTime = 0.0f;
float thunderDuration = 0.1f;
void PlayerWandAttack()
{
	if ((CP_Input_KeyDown(KEY_RIGHT) || CP_Input_KeyDown(KEY_LEFT) || CP_Input_KeyDown(KEY_UP) || CP_Input_KeyDown(KEY_DOWN)) && player.isAlive)
	{
		float wand_x = CP_Random_RangeFloat(860, 1060);
		float wand_y = CP_Random_RangeFloat(440, 640);
		if (CloseAttackCoolTime())
		{
			CP_Sound_PlayAdvanced(wandSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			thunderFrame = 0;
			thunderAnimationTime = 0.0f;
			SuccessAttack(player.weapon.num);
		}

		thunderAnimationTime += CP_System_GetDt();
		if (thunderAnimationTime >= thunderDuration)
		{

			thunderAnimationTime = 0.0f;
			thunderFrame++;
			if (thunderFrame >= thunderFrameNum)
			{
				thunderFrame = 0;
			}
		}
		CP_Image_Draw(ThunderImg[thunderFrame], wand_x, wand_y, (float)CP_Random_RangeInt(40,100), (float)CP_Random_RangeInt(100, 250), 255);
	}
}