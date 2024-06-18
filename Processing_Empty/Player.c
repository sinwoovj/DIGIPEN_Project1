#include "Player.h"

void PlayerMove()
{
	if (CP_Input_KeyDown(KEY_W))
	{
		//velocity += 0.5f;
		Rect.y -= aoc;
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