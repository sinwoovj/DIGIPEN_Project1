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
	CP_Vector range;
	float health;
	float closeDamage;
	float reachDamage;
	float projectileDamage;
	int phase;
	int maxHP;
	Shape shape;
	bool isPhase1Full;
	bool isAttack;
	bool isHit;
	bool isInvincibility;
	bool isAlive;
	int closeAttackNum;
	float recognizeRange;
	float closeAttackCoolTime;
}Enemy;
Enemy enemy;

bool isEnemyCloseAttack;
bool isEnemyProjectailAttack;
bool isEnemyPatternAttack;

int currentPhaseTerm;

int currentEnemyFrame1;
int currentEnemyFrame2;
int limitEnemyFrame;


void EnemyInit(float x, float y);

void EnemyAttack();

void EnemyDraw(float BossLocationX, float BossLocationY);

void EnemyPhaseSet();

void EnemyCheck();

void EnemyRandomAttack(bool isNear);

bool InvincibleTime();

void EnemyRandomCloseAttack();