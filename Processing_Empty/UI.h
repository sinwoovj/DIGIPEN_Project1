#pragma once
#include "cprocessing.h"
#include "stdbool.h"
void Text(char* text, float x, float y);
void ShowPlayerHP();
void ShowEnemyHP();
void ShowUI();

void UpdatePhase();
void UpdateEnemyHp();

bool isPhase2Full;
bool isPhase3Full;

void UpdatePlayerDash();
void UpdatePlayerHp();