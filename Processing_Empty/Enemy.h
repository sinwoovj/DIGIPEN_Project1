#pragma once
#include "Standard.h"
#include <stdbool.h>
#include "Player.h"
#include <math.h>
#include "EnemyAttack.h"
#include <stdlib.h>
#include <time.h>
#include "Calculate.h"
#include "Image.h"

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

bool isEnemyCloseAttack;
bool isEnemyProjectailAttack;
bool isEnemyPatternAttack;

int phaseTerm[3]; // 1 > 6s : 2 > 4s : 3 > 2s
int currentPhaseTerm;

int currentEnemyFrame;
int limitEnemyFrame;


void EnemyInit(float x, float y);

void EnemyAttack();

void EnemyDraw(float BossLocationX, float BossLocationY);

void EnemyPhaseSet();

void EnemyCheck();

void EnemyRandomAttack(bool isNear);
