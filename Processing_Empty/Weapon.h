#pragma once

#include <stdbool.h>

// Enum

typedef enum KindOfWeapon
{
	Sword = 1,
	Arrow = 2,
	Wand = 3
}KindOfWeapon;

// Struct

typedef struct Weapon
{
	KindOfWeapon kind;
	float range;
	float damage;
	bool isAttack;
}Weapon;