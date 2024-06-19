#pragma once
#include "cprocessing.h"
#include "Weapon.h"
#include "Roughly.h"
#include "Standard.h"

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
}Player;
Player player;

void PlayerInit();
void PlayerMove();
void PlayerUpdatePosition();
void CheckWallCollision();

int DashCoolTime();

void SelectWeapon();
