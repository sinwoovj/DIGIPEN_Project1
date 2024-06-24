#include "Sound.h"

void SoundLoad()
{
	bgmSound = CP_Sound_Load("Assets/Sounds/bgm.wav");

	swordSound = CP_Sound_Load("Assets/Sounds/Player/SwordSound.wav");
	arrowSound = CP_Sound_Load("Assets/Sounds/Player/ArrowSound.mp3");
	wandSound = CP_Sound_Load("Assets/Sounds/Player/WandSound.wav");

	dashSound = CP_Sound_Load("Assets/Sounds/Player/DashSound.mp3");

	playerHurt = CP_Sound_Load("Assets/Sounds/Player/PlayerHurt.mp3");
	bossHurt = CP_Sound_Load("Assets/Sounds/Enemy/BossHurt.wav");
	bossPunch = CP_Sound_Load("Assets/Sounds/Enemy/punchSound.wav");

	changePhase = CP_Sound_Load("Assets/Sounds/Enemy/ChangePhase.mp3");


	gameOver = CP_Sound_Load("Assets/Sounds/GameOverSound.wav");

}

void SoundFree()
{
	CP_Sound_Free(&bgmSound);
	CP_Sound_Free(&swordSound);
	CP_Sound_Free(&arrowSound);
	CP_Sound_Free(&wandSound);
	CP_Sound_Free(&dashSound);
	CP_Sound_Free(&playerHurt);
	CP_Sound_Free(&bossHurt);
	CP_Sound_Free(&bossPunch);
	CP_Sound_Free(&changePhase);
	CP_Sound_Free(&gameOver);
}