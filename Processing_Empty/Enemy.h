#pragma once

#include <stdbool.h>

typedef struct Enemy
{
	float health;
	int phase;
	bool isInvincibility;
	bool isAlive;
};