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
#include "EnemyProjectile.h"
#include "Enemy.h"
#include "Sound.h"
#include "Standard.h"
int isplaying = 0;
//Initialize Setting
void Init()
{
	StandardInit();

	//inactive Projectile
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		projectile[i].active = 0;
	}
	for (int i = 0; i < MAX_ENEMYPROJECTIES; i++)
	{
		enemyProjectile[i].active = 0;
		enemyProjectile_2[i].active = 0;
	}
	CP_System_SetWindowSize((int)WindowWidthSize, (int)WindowHeightSize);

	InitWeaponData();
	EnemyInit(WindowWidthHalf, WindowHeightHalf);
	PlayerInit();
	UpdatePlayerHp();
	UpdateEnemyHp();
	UpdatePlayerDash();
	isPhase2Full = true;
	isPhase3Full = true;
	ImageLoad();
	SoundLoad();
	isplaying = 0;
	CP_Sound_StopAll();
}

void Roughly_game_init(void)
{
	Init();
}

void Roughly_game_update(void)
{
	if (CP_Input_KeyDown(KEY_ESCAPE))
		exit(0);
	if (CP_Input_KeyDown(KEY_R))
	{
		Init();
		CP_Engine_SetNextGameState(Roughly_game_init, Roughly_game_update, Roughly_game_exit);
	}
	CP_Image_Draw(BG, WindowWidthHalf, WindowHeightHalf, WindowWidthSize, WindowHeightSize, 255); //Draw BG

	if (isplaying == 0)
	{
		CP_Sound_PlayMusic(bgmSound);
		isplaying = 1;
	}
	//****About the Player****//
	PlayerMove();
	PlayerUpdatePosition(); //Accel
	SelectWeapon();

	if (enemy.isAlive)
	{
		EnemyAttack();
		DrawEnemyProjectile(); //���� ����ü ���
		DrawEnemyProjectile_2();
	}


	EnemyDraw(WindowWidthHalf, WindowHeightHalf); //Draw Boss
	PlayerDraw();

	PlayerAttack(player.weapon.num);
	Draw_PlayerProjectile(); //�÷��̾� ����ü ���

	//ShowUI();

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