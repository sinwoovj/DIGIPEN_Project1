#include "Roughly.h"
const int WindowWidth = 1920;
const int WindowHeight = 1080;
CP_Image BossFace = NULL;
CP_Image BG = NULL;
//Initialize Setting
void Init()
{
	//Player size setting
	Rect.x = 100.f, Rect.y = 100.f, Rect.size = 50.f;
	
	aoc = 10; //Move distance

	//Active Projectile
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		projectile[i].active = 0;
	}

	CP_System_SetWindowSize(WindowWidth, WindowHeight);

	BossFace = CP_Image_Load("./Assets/Boss.png");
	BG = CP_Image_Load("./Assets/BG.png");
}


void Roughly_game_init(void)
{
	Init(); //Initialize
}

void Roughly_game_update(void)
{
	CP_Color myColor = CP_Color_Create(0, 0, 0, 255);
	CP_Graphics_ClearBackground(myColor);

	PlayerMove();
	PlayerAttack();



	float BossLocationX = WindowWidth / 2.0;
	float BossLocationY = WindowHeight / 2.0;

	CP_Image_Draw(BG, BossLocationX, BossLocationY, WindowWidth, WindowHeight, 255); //Draw BG
	CP_Image_Draw(BossFace, BossLocationX, BossLocationY, 400, 400, 255); //Draw Boss

	CP_Graphics_DrawRect(Rect.x, Rect.y, Rect.size, Rect.size); //Draw Player
	Draw_Projectile();


	//distance = velocity * CP_System_GetDt();
}

void Roughly_game_exit(void)
{
	CP_Image_Free(&BG);
	CP_Image_Free(&BossFace);
}