#pragma once
#include "cprocessing.h"
#include "Projectile.h"
#include "Weapon.h"

typedef struct Player
{
	CP_Vector coord;
	float size;
	CP_Color color;
	float health;
	float moveSpeed;
	bool isAlive;
	Weapon weapon;
}Player;
Player player;
int aoc;
float accel;
float playerVelocity;
float playerDistance;
void PlayerMove();
void PlayerAttack();