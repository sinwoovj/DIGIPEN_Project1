#pragma once
#include <stdbool.h>

typedef struct Weapon
{
	int num; // 1 > Sword // 2 > Arrow // 3 > Wand
	float range;
	float damage;
	bool isAttack;
}Weapon;
Weapon sword, arrow, wand;

//Initialize WeaponData
void InitWeaponData();