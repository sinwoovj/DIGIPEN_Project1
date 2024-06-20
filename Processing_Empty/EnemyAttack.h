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
void SignDanagerZone(CP_Vector coord, float w, float h, CP_Color color);

void EnemyCloseAttack1();
void EnemyCloseAttack2();
void EnemyCloseAttack3();





void EnemyProjectileRandomAttack1();// ����
void EnemyProjectileRandomAttack2();// ���� ����
void EnemyProjectileRandomAttack3();// ����




void EnemyPatternAttack1();
void EnemyPatternAttack2();
void EnemyPatternAttack3();

// Variable
