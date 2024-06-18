#pragma once

#include <stdbool.h>
#include "Player.h"

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

void EnemyInit();

void EnemyAttack();

void EnemyRandomAttack();
