#include "Player.h"

int dashframeCount = 0;
const int dashframeLimit = 90;
bool isDash;
int DashCoolTime()
{
	if (++dashframeCount == dashframeLimit)
	{
		dashframeCount = 0;
		return 1;
	}
	return 0;
}

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
	player.shape = Circle;
	player.health = 100.f;
	player.moveSpeed = 0.5f;
	player.maxSpeed = 10.f;
	player.isAlive = 1;
	player.weapon = sword; // 1 > Sword // 2 > Arrow // 3 > Wand
}

void PlayerMove()
{
	if (DashCoolTime())
		isDash = true;
	//Up & Down
	if (CP_Input_KeyDown(KEY_W))
	{
		if (CP_Input_KeyTriggered(KEY_SPACE) && isDash)
		{
			isDash = false;
			player.accel.y = -player.dashAccel;
		}
		else
			player.accel.y = -player.moveSpeed;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		if (CP_Input_KeyTriggered(KEY_SPACE) && isDash)
		{
			isDash = false;
			player.accel.y = player.dashAccel;
		}
		else
			player.accel.y = player.moveSpeed;
	}
	else
	{
		player.accel.y = 0.0f;
	}

	//Right & Left
	if (CP_Input_KeyDown(KEY_D))
	{
		if (CP_Input_KeyTriggered(KEY_SPACE) && isDash)
		{
			isDash = false;
			player.accel.x = player.dashAccel;
		}
		else
			player.accel.x = player.moveSpeed;
	}
	else if (CP_Input_KeyDown(KEY_A))
	{
		if (CP_Input_KeyTriggered(KEY_SPACE) && isDash)
		{
			isDash = false;
			player.accel.x = -player.dashAccel;
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
	if (CP_Input_KeyTriggered(KEY_1))
		player.weapon.num = 1;
	else if (CP_Input_KeyTriggered(KEY_2))
		player.weapon.num = 2;
	else if (CP_Input_KeyTriggered(KEY_3))
		player.weapon.num = 3;
}