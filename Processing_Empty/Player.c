#include <time.h>
#include "Player.h"
#include "Roughly.h"
#include "Image.h"
#include "Enemy.h"
#include "Sound.h"

void PlayerInit()
{
	//Player size setting
	player.coord.x = 100.f;
	player.coord.y = 100.f;
	player.size = 50.f;
	player.accel.x = 0;
	player.accel.y = 0;
	player.velocity.x = 0;
	player.velocity.y = 0;
	player.dashAccel = 100.f;
	player.dashCoolTimeLimit = 3.f;
	player.shape = Circle;
	player.health = 100.f;
	player.moveSpeed = 0.5f;
	player.maxSpeed = 10.f;
	player.isAlive = 1;
	player.weapon = sword; // 1 > Sword // 2 > Arrow // 3 > Wand
	player.direction = 0;
}
void PlayerDraw()
{
	if (CP_Input_KeyDown(KEY_RIGHT) && player.isAlive)
		player.direction = 1;
	else if (CP_Input_KeyDown(KEY_LEFT) && player.isAlive)
		player.direction = 3;
	else if (CP_Input_KeyDown(KEY_UP) && player.isAlive)
		player.direction = 2;
	else if (CP_Input_KeyDown(KEY_DOWN) && player.isAlive)
		player.direction = 0;
	CP_Image_Draw(PlayerDir[player.direction], player.coord.x + player.size / 2, player.coord.y + player.size / 2, player.size, player.size, 255); //Draw BG
}

bool isDash;
time_t dashStartTime;
int DashCoolTime()
{
	time_t currentTime = clock();
	player.dashCoolTime = (float)(currentTime - dashStartTime) / CLOCKS_PER_SEC;

	if (player.dashCoolTime >= player.dashCoolTimeLimit)
	{
		return 1;
	}
	return 0;
}
void PlayerMove()
{
	if (!isDash && DashCoolTime())
	{
		isDash = true;
	}
	//Up & Down
	if (CP_Input_KeyDown(KEY_W) && player.isAlive)
	{
		if (CP_Input_KeyTriggered(KEY_SPACE) && isDash)
		{
			CP_Sound_PlayAdvanced(dashSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			isDash = false;
			player.accel.y = -player.dashAccel;
			dashStartTime = clock();
		}
		else
			player.accel.y = -player.moveSpeed;
	}
	else if (CP_Input_KeyDown(KEY_S) && player.isAlive)
	{
		if (CP_Input_KeyTriggered(KEY_SPACE) && isDash)
		{
			CP_Sound_PlayAdvanced(dashSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			isDash = false;
			player.accel.y = player.dashAccel;
			dashStartTime = clock();
		}
		else
			player.accel.y = player.moveSpeed;
	}
	else
	{
		player.accel.y = 0.0f;
	}

	//Right & Left
	if (CP_Input_KeyDown(KEY_D) && player.isAlive)
	{
		if (CP_Input_KeyTriggered(KEY_SPACE) && isDash)
		{
			CP_Sound_PlayAdvanced(dashSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			isDash = false;
			player.accel.x = player.dashAccel;
			dashStartTime = clock();
		}
		else
			player.accel.x = player.moveSpeed;
	}
	else if (CP_Input_KeyDown(KEY_A) && player.isAlive)
	{
		if (CP_Input_KeyTriggered(KEY_SPACE) && isDash)
		{
			CP_Sound_PlayAdvanced(dashSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			isDash = false;
			player.accel.x = -player.dashAccel;
			dashStartTime = clock();
		}
		else
			player.accel.x = -player.moveSpeed;
	}
	else
	{
		player.accel.x = 0.0f;
	}

	CheckWallCollision();
}


void PlayerCheck()
{
	float dieX = (1920 / 2.0) - 300;
	float dieY = 1080 / 2.0;
	float restartX = 1920 / 2.0 - 300;
	float restartY = 1080 / 2.0 + 200;
	if (player.health <= 0)
	{
		//여러번 울리는 상황 해결
		//CP_Sound_PlayAdvanced(gameOver, 0.1f, 1.0f, FALSE, CP_SOUND_GROUP_1);
		player.isAlive = 0;
		CP_Settings_TextSize(200.f);
		CP_Font_DrawText("You Died", dieX, dieY);

		CP_Settings_TextSize(100.f);
		CP_Font_DrawText("Press R to Restart", restartX, restartY);

	}
}

float friction = 0.95f;
void PlayerUpdatePosition()
{
	//속도에 가속도를 더함
	player.velocity.x += player.accel.x;
	player.velocity.y += player.accel.y;

	//마찰력 적용
	player.velocity.x *= friction;
	player.velocity.y *= friction;

	//속도에 위치를 더함
	player.coord.x += player.velocity.x;
	player.coord.y += player.velocity.y;

	//최대 속도 제한
	
	if (player.velocity.x > player.maxSpeed) player.velocity.x = player.maxSpeed;
	if (player.velocity.x < -player.maxSpeed) player.velocity.x = -player.maxSpeed;
	if (player.velocity.y > player.maxSpeed) player.velocity.y = player.maxSpeed;
	if (player.velocity.y < -player.maxSpeed) player.velocity.y = -player.maxSpeed;
}
void CheckWallCollision()
{
	if (player.coord.x <= 0)
	{
		player.coord.x = 0.0f;
		player.velocity.x = -player.velocity.x * player.moveSpeed;
		player.accel.x = 0;
	}
	else if (player.coord.x + player.size >= CP_System_GetWindowWidth())
	{
		player.coord.x = CP_System_GetWindowWidth() - player.size;
		player.velocity.x = -player.velocity.x * player.moveSpeed;
		player.accel.x = 0;
	}

	if (player.coord.y <= 0)
	{
		player.coord.y = 0;
		player.velocity.y = -player.velocity.y * player.moveSpeed;
		player.accel.y = 0;
	}
	else if (player.coord.y + player.size >= CP_System_GetWindowHeight())
	{
		player.coord.y = CP_System_GetWindowHeight() - player.size;
		player.velocity.y = -player.velocity.y * player.moveSpeed;
		player.accel.y = 0;
	}
}
void SelectWeapon()
{
	if (enemy.phase == 1)
	{
		if (CP_Input_KeyTriggered(KEY_1))
			player.weapon.num = 1;
	}
	else if (enemy.phase == 2)
	{
		if (CP_Input_KeyTriggered(KEY_1))
			player.weapon.num = 1;
		else if (CP_Input_KeyTriggered(KEY_2))
			player.weapon.num = 2;
	}
	else if (enemy.phase == 3)
	{
		if (CP_Input_KeyTriggered(KEY_1))
			player.weapon.num = 1;
		else if (CP_Input_KeyTriggered(KEY_2))
			player.weapon.num = 2;
		else if (CP_Input_KeyTriggered(KEY_3))
			player.weapon.num = 3;
	}

	if (CP_Input_KeyTriggered(KEY_1) && CP_Input_KeyDown(KEY_LEFT_SHIFT))
		player.weapon.num = 1;
	else if (CP_Input_KeyTriggered(KEY_2) && CP_Input_KeyDown(KEY_LEFT_SHIFT))
		player.weapon.num = 2;
	else if (CP_Input_KeyTriggered(KEY_3) && CP_Input_KeyDown(KEY_LEFT_SHIFT))
		player.weapon.num = 3;
}