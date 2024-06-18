#pragma once
#include "cprocessing.h"
#include "stdbool.h"
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

	int active;
}Proj;
Proj projectile[MAX_PROJECTILES];

void Create_Projectile(float x, float y, float velocity);
void Draw_Projectile();
void Draw_RightProjectile();
bool Right;