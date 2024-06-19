#pragma once
#include "cprocessing.h"
#include "Player.h"
#include "PlayerProjectile.h"
#include "Weapon.h"

int AttackCoolTime();
int LongAttackCoolTime();

void SelectWeapon();

void PlayerCloseAttack();
void PlayerLongAttack();
void PlayerWandAttack();

