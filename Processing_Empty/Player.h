#pragma once
#include "cprocessing.h"
#include "Projectile.h"
#include "Weapon.h"

typedef struct Player
{
	CP_Vector coord;
	float size;
	float veloicity_x, veloicity_y;
	float accel_x, accel_y;
	CP_Color color;
	float health;
	float moveSpeed;
	bool isAlive;
	Weapon weapon;
}Player;
Player player;
int aoc;
float accel;
float friction;
float max_speed;
void PlayerMove();
void PlayerAttack();