#pragma once
#include "cprocessing.h"
#include "Enemy.h"
#include "cprocessing.h"
void Text(char* text, float x, float y);
void ShowPlayerHP();
void ShowEnemyHP();
void ShowUI();

void UpdatePhase();
void UpdateEnemyHp();

int isPhase2Full, isPhase3Full;