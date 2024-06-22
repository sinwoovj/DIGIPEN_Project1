#pragma once
#include "cprocessing.h"
//Player HP, Enemy HP Text
void Text(char* text, float x, float y);
void ShowPlayerHP();
void ShowEnemyHP();
void ShowUI();

//Change Enemy Phase
void UpdatePhase();
//Change Enemy MaxHP as Phsae
int isPhase2Full, isPhase3Full;
void UpdateEnemyHp();

//Display HP Bar, DashCoolTime Bar
void UpdatePlayerHp();
void UpdatePlayerDash();