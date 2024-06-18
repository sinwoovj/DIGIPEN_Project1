#pragma once

#include <stdbool.h>


// Struct

typedef struct Weapon
{
	float range;
	float damage;
	bool isAttack;
}Weapon;


// Const
Weapon sword, arrow, wand;

void InitWeaponData();