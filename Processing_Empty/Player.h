#pragma once
#include "cprocessing.h"
#include "Projectile.h"

typedef struct Rect
{
	float x;
	float y;
	float size;
	CP_Color color;
}R;

R Rect;
int aoc;
float accel;
float playerVelocity;
float playerDistance;
void PlayerMove();
void PlayerAttack();