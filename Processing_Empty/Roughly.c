#include "Roughly.h"

const float WindowWidth = 1920;
const float WindowHeight = 1080;
float BossLocationX;
float BossLocationY;
CP_Image BossFace = NULL;
CP_Image BG = NULL;

//Initialize Setting
void Init()
{
	BossLocationX = WindowWidth / 2;
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
	BossFace = CP_Image_Load("./Assets/Boss.png");
	BG = CP_Image_Load("./Assets/BG.png");
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
	CP_Image_Draw(BossFace, BossLocationX, BossLocationY, 400, 400, 255); //Draw Boss

	CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));
	CP_Graphics_DrawRect(player.coord.x, player.coord.y, player.size, player.size); //Draw Player

	PlayerMove();
	PlayerUpdatePosition(); //Accel

	ShowUI();
	SelectWeapon();

	PlayerAttack(player.weapon.num);
	Draw_PlayerProjectile(); //투사체 출력


}

void Roughly_game_exit(void)
{
	CP_Image_Free(&BG);
	CP_Image_Free(&BossFace);
}