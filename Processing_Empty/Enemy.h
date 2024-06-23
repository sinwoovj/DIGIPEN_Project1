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
// 1 : 우하, 2 : 우상, 3 : 좌하, 4 : 좌상
// 5 : 우, 6 : 좌
// 7 : 하, 8 : 상, 9 : 체크1, 10 : 체크2
// 11 : 슬라이드 우>좌, 12 : 슬라이드 좌>우, 13 : 슬라이드 하>상, 14 : 슬라이드 상>하
// 15 : 슬라이드 체크 우하>좌상, 16 : 슬라이드 체크 우상>좌하, 17 : 슬라이드 좌하>우상, 18 : 슬라이드 좌상>우하
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

