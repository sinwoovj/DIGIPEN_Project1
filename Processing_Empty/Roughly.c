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
#include "Standard.h"

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
	isPhase2Full = 1;
	isPhase3Full = 1;
	ImageLoad();
	SoundLoad();
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
	
	//****About the Draw****//
	//Background
	CP_Image_Draw(BG, WindowWidthHalf, WindowHeightHalf, WindowWidthSize, WindowHeightSize, 255);
	//Player, Enemy
	PlayerDraw();
	EnemyDraw(WindowWidthHalf, WindowHeightHalf);
	//=============================================


	//****About the Player****//
	PlayerMove();
	PlayerUpdatePosition();
	SelectWeapon();

	PlayerAttack(player.weapon.num);
	Draw_PlayerProjectile(); //플레이어 투사체 출력
	PlayerCheck();
	//=============================================
	

	//****About the Enemy****//
	if(enemy.isAlive)
	{
		EnemyAttack();
		DrawEnemyProjectile(); //보스 투사체 출력
		DrawEnemyProjectile_2();
	}
	EnemyCheck();
	UpdatePhase();
	UpdateEnemyHp();
	//==============================================


	//Show UI
	ShowUI();
}

void Roughly_game_exit(void)
{
	ImageFree();
	SoundFree();
}