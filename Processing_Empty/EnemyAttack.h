#pragma once
#include "Roughly.h"

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


void EnemyProjectileRandomAttack1();
void EnemyProjectileRandomAttack2();
void EnemyProjectileRandomAttack3();




void EnemyPatternAttack1();
void EnemyPatternAttack2();
void EnemyPatternAttack3();

// Variable
