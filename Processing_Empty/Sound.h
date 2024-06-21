#pragma once
#include "cprocessing.h"

CP_Sound swordSound;
CP_Sound arrowSound;
CP_Sound wandSound;

CP_Sound dashSound;



CP_Sound playerHurt;
CP_Sound bossHurt;


CP_Sound changePhase;

CP_Sound gameOver;

//CP_Sound_PlayAdvanced(dashSound, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);

void SoundLoad();
void SoundFree();