#pragma once

#include <stdbool.h>
#include "cprocessing.h"
#include "Standard.h"

#define MaxDangerZoneOpacity 60

typedef struct Enemy
{
	CP_Vector coord;
	float size;
	CP_Vector range;
	float health;
	float closeDamage;
	float reachDamage;
	float patternDamage;
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
	int patternAttackNum;
	int patternRandomNum;
	float recognizeRange;
	float closeAttackCoolTime;
}Enemy;
Enemy enemy;

bool isEnemyCloseAttack;
bool isEnemyProjectailAttack;
bool isEnemyPatternAttack;
bool isPlayerInsideRange;
bool isCloseAttackCool;
bool isPatternAttackCool;

int currentPhaseTerm;
int currentPatternPhaseTerm;

int currentEnemyFrame1;
int currentEnemyFrame2;
int currentEnemyFrame3;

int EnemyCloseAttackNum; 
// 1 : ����, 2 : ���, 3 : ����, 4 : �»�
// 5 : ��, 6 : ��
// 7 : ��, 8 : ��, 9 : üũ1, 10 : üũ2
// 11 : �����̵� ��>��, 12 : �����̵� ��>��, 13 : �����̵� ��>��, 14 : �����̵� ��>��
// 15 : �����̵� üũ ����>�»�, 16 : �����̵� üũ ���>����, 17 : �����̵� ����>���, 18 : �����̵� �»�>����
int EnemyPatternAttackNum;

int dangerZoneOpacity;
int dangerZonePatternOpacity;

void EnemyInit(float x, float y);

void EnemyAttack();

void EnemyDraw(float BossLocationX, float BossLocationY);

void EnemyPhaseSet();

void EnemyCheck();

void EnemyRandomAttack();

bool InvincibleTime();

void EnemyRandomPatternAttack();
void EnemyRandomCloseAttack();
bool EnemyFrameCheck1();
bool EnemyFrameCheck2();
bool EnemyFrameCheck3();

