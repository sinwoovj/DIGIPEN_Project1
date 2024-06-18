#include "Player.h"

void PlayerMove()
{
	if (CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_A))
	{
		Rect.y -= aoc;
		Rect.x -= aoc;
	}
	else if (CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_D))
	{
		Rect.y -= aoc;
		Rect.x += aoc;
	}
	else if (CP_Input_KeyDown(KEY_S) && CP_Input_KeyDown(KEY_D))
	{
		Rect.y += aoc;
		Rect.x += aoc;
	}
	else if (CP_Input_KeyDown(KEY_S) && CP_Input_KeyDown(KEY_A))
	{
		Rect.y += aoc;
		Rect.x -= aoc;
	}
	if (CP_Input_KeyDown(KEY_W))
	{
		Rect.accel_y = -0.5f;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		Rect.y += aoc;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		Rect.x += aoc;
	}
	else if (CP_Input_KeyDown(KEY_A))
	{
		Rect.x -= aoc;
	}
}

void PlayerAttack()
{
	float velocity = 10.0f;
	if (CP_Input_KeyTriggered(KEY_RIGHT))
	{
		Create_Projectile(Rect.x + 20, Rect.y + 20, velocity, 1);
	}
	else if (CP_Input_KeyTriggered(KEY_LEFT))
	{
		Create_Projectile(Rect.x + 20, Rect.y + 20, velocity, 2);
	}
	else if (CP_Input_KeyTriggered(KEY_UP))
	{
		Create_Projectile(Rect.x + 20, Rect.y + 20, velocity, 3);
	}
	else if (CP_Input_KeyTriggered(KEY_DOWN))
	{
		Create_Projectile(Rect.x + 20, Rect.y + 20, velocity, 4);
	}
}