#pragma once

#include "cprocessing.h"
#include "stdbool.h"
#include "Projectile.h"
#include "Player.h"
#include<stdio.h>

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

typedef struct Player
{
	float health;
	float moveSpeed;
	bool isAlive;
	Weapon weapon;
}Player;

typedef struct Enemy
{
	float health;
	int phase;
	bool isInvincibility;
	bool isAlive;
};
void Roughly_game_init(void);
void Roughly_game_update(void);
void Roughly_game_exit(void);

void Init();
