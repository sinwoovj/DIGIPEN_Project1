#pragma once
#include "cprocessing.h"
#include "Standard.h"

#define MAX_PROJECTILES 100


typedef struct Projectile
{
	//투사체 사이즈
	float size;

	//투사체 위치 (처음 위치는 플레이어 위치일 예정)
	float position_x;
	float position_y;

	//투사체 속도
	float velocity;
	Shape shape;

	int active;
	int direction; // 0: right, 1: left, 2: up, 3: down
}Proj;
Proj projectile[MAX_PROJECTILES];

void Create_PlayerProjectile(float x, float y, float velocity, int direction);
void Draw_PlayerProjectile();
