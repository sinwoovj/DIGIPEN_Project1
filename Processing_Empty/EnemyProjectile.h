#pragma once
#define MAX_ENEMYPROJECTIES 50
#include "cprocessing.h"
#include "Standard.h"

typedef struct EnemyProjectile
{
	//투사체 사이즈
	float size;

	//투사체 위치 (처음 위치는 플레이어 위치일 예정)
	CP_Vector position;
	//투사체 속도
	float velocity;
	Shape shape;

	int active;
	int direction; // 0: right, 1: left, 2: up, 3: down
}EnemyProject;
EnemyProject enemyProjectile[MAX_ENEMYPROJECTIES];
EnemyProject enemyProjectile_2[MAX_ENEMYPROJECTIES];


void CreateEnemyProjectile(float x, float y, float velocity, int direction); // 원형 수평 수직
void CreateEnemyProjectile_2(float x, float y, float velocity, int direction); // 유도
void DrawEnemyProjectile(); // 원형 수평 수직
void DrawEnemyProjectile_2(); // 유도