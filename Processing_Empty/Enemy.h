#pragma once

#include <stdbool.h>
#include "Player.h"

typedef struct Enemy
{
	float health;
	int phase;
	bool isAttack;
	bool isHit;
	bool isInvincibility;
	bool isAlive;
}Enemy;
Enemy enemy;

void EnemyAttack(Enemy enemy_, Player player);

void EnemyRandomAttack(Enemy enemy_);
