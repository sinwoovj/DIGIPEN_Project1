#pragma once
#include "cprocessing.h"
#include "Weapon.h"
#include "Roughly.h"

typedef struct Player
{
	CP_Vector coord;
	float size;
	CP_Vector velocity;
	CP_Vector accel;
	CP_Color color;
	float health;
	float moveSpeed;
	bool isAlive;
	int selectWeapon;
	Weapon weapon;
}Player;
Player player;


void PlayerMove();
void PlayerUpdatePosition();
void CheckWallCollision();

void SelectWeapon();
void PlayerAttack(int num);
