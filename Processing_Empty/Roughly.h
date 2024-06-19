#pragma once

#include "cprocessing.h"
#include "Player.h"
#include "PlayerProjectile.h"
#include "PlayerAttack.h"
#include <stdlib.h>
#include "Weapon.h"
#include "UI.h"
#include <stdbool.h>

void Roughly_game_init(void);
void Roughly_game_update(void);
void Roughly_game_exit(void);

bool isGameOver;

void Init();
