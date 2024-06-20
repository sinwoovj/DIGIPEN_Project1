#pragma once
#include "Roughly.h"
#include "EnemyProjectile.h"

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

void EnemyCloseAttack1();
void EnemyCloseAttack2();
void EnemyCloseAttack3();

bool isPlayerIncludeRange();




void EnemyProjectileRandomAttack1();// 원형
void EnemyProjectileRandomAttack2();// 수평 수직
void EnemyProjectileRandomAttack3();// 유도




void EnemyPatternAttack1();
void EnemyPatternAttack2();
void EnemyPatternAttack3();

// Variable
