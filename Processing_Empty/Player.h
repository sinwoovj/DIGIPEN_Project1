#pragma once
#include "cprocessing.h"
#include "Projectile.h"

typedef struct Rect
{
	float x;
	float y;
	float size;
	float veloicity_x, veloicity_y;
	float accel_x, accel_y;
	CP_Color color;
}R;

R Rect;
int aoc;
float accel;
float friction;
float max_speed;
void PlayerMove();
void PlayerAttack();