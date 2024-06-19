#include "Player.h"

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
	player.health = 100.f;
	player.moveSpeed = 0.5f;
	player.maxSpeed = 10.f;
	bool isAlive;
	Weapon weapon;
}

void PlayerMove()
{
	//Up & Down
	if (CP_Input_KeyDown(KEY_W))
	{
		player.accel.y = -0.5f;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		player.accel.y = 0.5f;
	}
	else
	{
		player.accel.y = 0.0f;
	}

	//Right & Left
	if (CP_Input_KeyDown(KEY_D))
	{
		player.accel.x = 0.5f;
	}
	else if (CP_Input_KeyDown(KEY_A))
	{
		player.accel.x = -0.5f;
	}
	else
	{
		player.accel.x = 0.0f;
	}

	CheckWallCollision();
}

float friction = 0.95f;
float max_speed = 10.0f;
void PlayerUpdatePosition()
{
	//�ӵ��� ���ӵ��� ����
	player.velocity.x += player.accel.x;
	player.velocity.y += player.accel.y;

	//������ ����
	player.velocity.x *= friction;
	player.velocity.y *= friction;

	//�ӵ��� ��ġ�� ����
	player.coord.x += player.velocity.x;
	player.coord.y += player.velocity.y;

	//�ִ� �ӵ� ����
	if (player.velocity.x > max_speed) player.velocity.x = max_speed;
	if (player.velocity.x < -max_speed) player.velocity.x = -max_speed;
	if (player.velocity.y > max_speed) player.velocity.y = max_speed;
	if (player.velocity.y < -max_speed) player.velocity.y = -max_speed;
}
void CheckWallCollision()
{
	if (player.coord.x <= 0)
	{
		player.coord.x = 0.0f;
		player.velocity.x = -player.velocity.x * 0.5f;
		player.accel.x = 0;
	}
	else if (player.coord.x + player.size >= CP_System_GetWindowWidth())
	{
		player.coord.x = CP_System_GetWindowWidth() - player.size;
		player.velocity.x = -player.velocity.x * 0.5f;
		player.accel.x = 0;
	}

	if (player.coord.y <= 0)
	{
		player.coord.y = 0;
		player.velocity.y = -player.velocity.y * 0.5f;
		player.accel.y = 0;
	}
	else if (player.coord.y + player.size >= CP_System_GetWindowHeight())
	{
		player.coord.y = CP_System_GetWindowHeight() - player.size;
		player.velocity.y = -player.velocity.y * 0.5f;
		player.accel.y = 0;
	}
}

