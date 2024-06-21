#pragma once

#include <stdbool.h>
#include "Standard.h"
#include "Weapon.h"
#include "cprocessing.h"

typedef struct Player
{
	CP_Vector coord;
	float size;
	CP_Vector velocity;
	CP_Vector accel;
	CP_Color color;
	Shape shape;
	float health;
	float dashAccel;
	float moveSpeed;
	float maxSpeed;
	bool isAlive;
	Weapon weapon;
	int direction; // 0 => down, 1 => right, 2 => up, 3 => left
}Player;
Player player;

void PlayerInit();
void PlayerMove();
void PlayerCheck();
void PlayerDraw();
void PlayerUpdatePosition();
void CheckWallCollision();

int DashCoolTime();

void SelectWeapon();
