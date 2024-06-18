#pragma once
#include "cprocessing.h"
#include "Player.h"
#include "Projectile.h"
#include "Weapon.h"

int CoolTime();
//int LongAttackCoolTime();

void SelectWeapon();

void PlayerCloseAttack();
void PlayerLongAttack();
void PlayerWandAttack();