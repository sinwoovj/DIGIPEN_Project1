#include "Roughly.h"
#include "Standard.h"
#include "UI.h"
#include "cprocessing.h"
#include "Player.h"
#include "PlayerProjectile.h"
#include "PlayerAttack.h"
#include <stdlib.h>
#include "Weapon.h"
#include "Image.h"
#include "EnemyAttack.h"
#include "Enemy.h"
#include "Sound.h"

float BossLocationX;
float BossLocationY;

//Initialize Setting
void Init()
{
	StandardInit();
	BossLocationX = WindowWidthSize / 2 ;
	BossLocationY = WindowHeightSize / 2;
	//Active Projectile
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		projectile[i].active = 0;
	}
	for (int i = 0; i < MAX_ENEMYPROJECTIES; i++)
	{
		enemyProjectile[i].active = 0;
		enemyProjectile_2[i].active = 0;
	}
	CP_System_SetWindowSize((int)WindowWidth, (int)WindowHeight);

	InitWeaponData();
	EnemyInit(BossLocationX, BossLocationY);
	PlayerInit();
	UpdatePlayerHp();
	UpdateEnemyHp();
	UpdatePlayerDash();
	isGameOver = 0;
	isPhase2Full = 1;
	isPhase3Full = 1;
	ImageLoad();
	SoundLoad();
}

void Roughly_game_init(void)
{
	//Initialize
	Init();
}

void Roughly_game_update(void)
{
	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		exit(0);
	}
	if (CP_Input_KeyDown(KEY_R))
	{
		// Initialize Data Code
		Init();
		CP_Engine_SetNextGameState(Roughly_game_init, Roughly_game_update, Roughly_game_exit);
	}
	CP_Image_Draw(BG, BossLocationX, BossLocationY, WindowWidth, WindowHeight, 255); //Draw BG

	EnemyDraw(BossLocationX, BossLocationY); //Draw Boss
	PlayerDraw();

	PlayerMove();
	PlayerUpdatePosition(); //Accel
	SelectWeapon();

	if(enemy.isAlive)
	{
		EnemyAttack();
		DrawEnemyProjectile(); //보스 투사체 출력
		DrawEnemyProjectile_2();
	}

	PlayerAttack(player.weapon.num);
	Draw_PlayerProjectile(); //플레이어 투사체 출력

	ShowUI();
	
	EnemyCheck();
	PlayerCheck();

	UpdatePhase();
	UpdatePlayerHp();
	UpdateEnemyHp();
	UpdatePlayerDash();
}

void Roughly_game_exit(void)
{
	ImageFree();
	SoundFree();
}