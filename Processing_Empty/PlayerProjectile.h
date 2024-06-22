#pragma once
#include "Standard.h"
#include <stdbool.h>
#define MAX_PROJECTILES 100

typedef struct Projectile
{
	float size;
	float position_x;
	float position_y;
	float velocity;
	Shape shape;
	int active;
	int direction; // 0: right, 1: left, 2: up, 3: down
}Proj;
Proj projectile[MAX_PROJECTILES];

void Create_PlayerProjectile(float x, float y, float velocity, int direction);
void Draw_PlayerProjectile();