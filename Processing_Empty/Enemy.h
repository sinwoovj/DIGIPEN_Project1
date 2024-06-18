#pragma once

#include <stdbool.h>

typedef struct Enemy
{
	float health;
	int phase;
	bool isAttack;
	bool isHit;
	bool isInvincibility;
	bool isAlive;
};