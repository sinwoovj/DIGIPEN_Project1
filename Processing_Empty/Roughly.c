#include "Roughly.h"
const int WindowWidth = 1920;
const int WindowHeight = 1080;

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
}


void Roughly_game_init(void)
{
	Init(); //Initialize
}

void Roughly_game_update(void)
{
	CP_Color myColor = CP_Color_Create(0, 255, 255, 255);//Draw Background
	CP_Graphics_ClearBackground(myColor);
	CP_Graphics_DrawRect(Rect.x, Rect.y, Rect.size, Rect.size); //Draw Player

	PlayerMove();
	PlayerAttack();

	Draw_Projectile();



	//distance = velocity * CP_System_GetDt();
}

void Roughly_game_exit(void)
{

}