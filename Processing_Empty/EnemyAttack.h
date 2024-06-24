#pragma once
#include <stdbool.h>

// Enum
typedef enum TypeOfAttack {
	Left,
	Right,
	Top,
	Bottom,
	Vertical,
	Horizontal,
	Omnidirectional,
}TypeOfAttack;

typedef enum EnemyPattern {
	Checked,
	Diagonal
}EnemyPattern;

// Function
void SignDanagerZone(float x, float y, float w, float h);
void SignDanagerPatternZone(float x, float y, float w, float h);
void SignCheckPatternZone(float x, float y, float w, float h);

void EnemyCloseAttack1();
void EnemyCloseAttack2();
void EnemyCloseAttack3();

bool isPlayerIncludeRange();
bool isPlayerIncludePatternRange();



void EnemyProjectileRandomAttack1();// 원형
void EnemyProjectileRandomAttack2();// 수평 수직
void EnemyProjectileRandomAttack3();// 유도


void EnemyPatternAttack1(); // 1/4
void EnemyPatternAttack2(); // 1/2
void EnemyPatternAttack3(); // check
void EnemyPatternAttack4(); // slide linear
void EnemyPatternAttack5(); // slide diagonal

void EnemyCheckPatternAnim();
void EnemyCheckPatternFrameCheck();

// Variable

int punchFrame;
int punchState;

int EnemyCheckPatternFrame;
int EnemyCheckPatternFrameLimit;