#pragma once

#include <stdbool.h>
#include "Standard.h"
#include "cprocessing.h"


// Struct
typedef struct Weapon
{
	int num; // 1 > Sword // 2 > Arrow // 3 > Wand
	float range;
	Shape shape;
	float damage;
	bool isAttack;
}Weapon;

// Const
Weapon sword, arrow, wand;

void InitWeaponData();