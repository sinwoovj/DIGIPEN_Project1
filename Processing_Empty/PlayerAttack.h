#pragma once
#include "cprocessing.h"
#include "Player.h"
#include "PlayerProjectile.h"
#include "Weapon.h"
#include "Enemy.h"
#include <math.h>
#include "Calculate.h"

void PlayerAttack(int num);

int AttackCoolTime();
int LongAttackCoolTime();

void SelectWeapon();

void PlayerCloseAttack();
void PlayerLongAttack();
void PlayerWandAttack();

bool isReach(float* position_x, float* position_y, int* active);
void SuccessAttack(int num);

