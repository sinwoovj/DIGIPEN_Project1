#pragma once
#include "cprocessing.h"
#include <stdbool.h>
void Text(char* text, float x, float y);
void ShowPlayerHP();
void ShowEnemyHP();
void ShowUI();

//Change Enemy Phase
void UpdatePhase();
//Change Enemy MaxHP as Phsae
void UpdateEnemyHp();

bool isPhase2Full;
bool isPhase3Full;

//Display HP Bar, DashCoolTime Bar
void UpdatePlayerDash();
void UpdatePlayerHp();