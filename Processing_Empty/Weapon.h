#pragma once
#include "cprocessing.h"
#include "Standard.h"
#include <stdbool.h>

// Struct
typedef struct Weapon
{
	int num; // 1 > Sword // 2 > Arrow // 3 > Wand
	float range;
	float damage;
	bool isAttack;
}Weapon;

// Const
Weapon sword, arrow, wand;

void InitWeaponData();