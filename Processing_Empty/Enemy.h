#pragma once

#include <stdbool.h>
#include "Player.h"
#include "EnemyAttack.h"
#include <stdlib.h>
#include <time.h>

typedef struct Enemy
{
	CP_Vector coord;
	float size;
	float health;
	float closeDamage;
	int phase;
	bool isAttack;
	bool isHit;
	bool isInvincibility;
	bool isAlive;
}Enemy;
Enemy enemy;

bool RangeTest(CP_Vector v1, float v1_size, CP_Vector v2, float v2_size); // v1¿Ã base, v2∞° target

void EnemyInit(float x, float y);

void EnemyAttack();

void EnemyRandomAttack();
