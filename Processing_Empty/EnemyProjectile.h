#pragma once
#define MAX_ENEMYPROJECTIES 50
#include "cprocessing.h"
#include "Standard.h"

typedef struct EnemyProjectile
{
	CP_Vector position;
	CP_Vector target;
	float size;
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

CP_Vector CP_VectorSubtract(CP_Vector a, CP_Vector b);
CP_Vector CP_VectorNormalize(CP_Vector v);
CP_Vector CP_VectorScale(CP_Vector v, float scale);
float CP_VectorDistance(CP_Vector a, CP_Vector b);
