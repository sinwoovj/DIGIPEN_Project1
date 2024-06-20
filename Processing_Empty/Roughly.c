#include "Roughly.h"

const float WindowWidth = 1920;
const float WindowHeight = 1080;
float BossLocationX;
float BossLocationY;

//Initialize Setting
void Init()
{
	BossLocationX = WindowWidth / 2 ;
	BossLocationY = WindowHeight / 2;
	//Active Projectile
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		projectile[i].active = 0;
	}

	CP_System_SetWindowSize((int)WindowWidth, (int)WindowHeight);


	InitWeaponData();
	EnemyInit(BossLocationX, BossLocationY);
	PlayerInit();
	UpdatePlayerHp();
	UpdateEnemyHp();
	isGameOver = 0;

	ImageLoad();
}

void Roughly_game_init(void)
{
	//Initialize
	Init();
}

void Roughly_game_update(void)
{
	if (isGameOver) {
		exit(0);
	}
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
	
	PlayerMove();
	PlayerUpdatePosition(); //Accel

	SelectWeapon();
	EnemyAttack();
	PlayerAttack(player.weapon.num);

	EnemyDraw(BossLocationX, BossLocationY); //Draw Boss
	PlayerDraw();
	
	Draw_PlayerProjectile(); //투사체 출력
	
	ShowUI();
	
	EnemyCheck();
	PlayerCheck();
	UpdatePhase();
	UpdatePlayerHp();
	UpdateEnemyHp();

	//CP_Graphics_DrawCircle(BossLocationX, BossLocationY, 400);

}

void Roughly_game_exit(void)
{
	ImageFree();
}