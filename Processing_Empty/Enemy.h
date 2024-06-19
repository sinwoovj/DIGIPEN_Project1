#pragma once
#include "Standard.h"
#include <stdbool.h>
#include "Player.h"
#include "math.h"
#include "EnemyAttack.h"
#include <stdlib.h>
#include <time.h>
#include "Calculate.h"

typedef struct Enemy
{
	CP_Vector coord;
	float size;
	float health;
	float closeDamage;
	float reachDamage;
	float projectileDamage;
	int phase;
	Shape shape;
	bool isAttack;
	bool isHit;
	bool isInvincibility;
	bool isAlive;
}Enemy;
Enemy enemy;

void EnemyInit(float x, float y);

void EnemyAttack();

void EnemyRandomAttack();
